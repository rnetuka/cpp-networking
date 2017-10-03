/*
 */

#include <bitset>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <ipv4.h>
#include "udp.h"

using namespace std;


namespace udp
{
    
    string Data::as_string() const
    {
        string result;
        for (byte b : bytes_)
            result += b;
        return result;
    }
    
    ostream& operator <<(ostream& stream, const Data& data)
    {
        for (int i = 0; i < data.bytes_.size(); i++)
        {
            stream << bitset<8>(data.bytes_.at(i));
            if ( i % 4 == 0)
                stream << endl;
            else
                stream << ' ';
        }
        return stream;
    }
    
    Packet::Packet() : length_(8)
    {
        
    }
    
    void Packet::set_source_port(long port) 
    { 
        source_port_ = port;
    }
    
    void Packet::set_destination_port(long port) 
    { 
        destination_port_ = port;
    }
    
    void Packet::set_length(long length) 
    { 
        length_ = length; 
    }
    
    void Packet::set_checksum(long checksum) 
    { 
        checksum_ = checksum; 
    }
    
    void Packet::set_data(const vector<byte>& data)
    {
        data_ = data;
        length_ += data.size();
    }
    
    void Packet::encapsulate_into(ip::Datagram& datagram)
    {
        datagram.set_data(*this);
        //TODO calculate checksum
    }
    
    Data Packet::data() const
    {
        return Data(data_);
    }
    
    vector<byte> Packet::bytes() const
    {
        vector<byte> bytes;
        bytes.push_back(source_port_ >> 8);
        bytes.push_back(source_port_ & 255);
        bytes.push_back(destination_port_ >> 8);
        bytes.push_back(destination_port_ & 255);
        bytes.push_back(length_ >> 8);
        bytes.push_back(length_ & 255);
        bytes.push_back(checksum_ >> 8);
        bytes.push_back(checksum_ & 255);
        for (byte b : data_)
            bytes.push_back(b);
        return bytes;
    }
    
    string Packet::info() const
    {
        stringstream stream;
        stream << "+--------------------------" << endl;
        stream << "| Source Port: " << source_port_ << endl;
        stream << "| Destination Port: " << destination_port_ << endl;
        stream << "| Length: " << length_ << endl;
        stream << "| Checksum: " << checksum_ << endl;
        stream << "*--------------------------" << endl;
        return stream.str();
    }
    
    Packet Packet::parse(byte bytes[], int length)
    {
        if (length < 8)
            throw invalid_argument("UDP packet size cannot be lower than 8 bytes");
        
        Packet packet;
        packet.source_port_ = (((bits_16) bytes[0]) << 8) + bytes[1];
        packet.destination_port_ = (((bits_16) bytes[2]) << 8) + bytes[3];
        packet.length_ = (((bits_16) bytes[4]) << 8) + bytes[5];
        packet.checksum_ = (((bits_16) bytes[6]) << 8) + bytes[7];
        
        for (int i = 8; i < length; i++)
            packet.data_.push_back(bytes[i]);
        
        return packet;
    }
    
    ostream& operator <<(ostream& stream, const Packet& packet)
    {
        stream << bitset<8>(packet.source_port() >> 8) << ' ';
        stream << bitset<8>(packet.source_port() & 255) << ' ';
        stream << bitset<8>(packet.destination_port() >> 8) << ' ';
        stream << bitset<8>(packet.destination_port() & 255) << endl;
        stream << bitset<8>(packet.length() >> 8) << ' ';
        stream << bitset<8>(packet.length() & 255) << ' ';
        stream << bitset<8>(packet.checksum() >> 8) << ' ';
        stream << bitset<8>(packet.checksum() & 255) << endl;
        stream << packet.data();
        return stream;
    }
    
    Packet Sender::send(Packet& packet)
    {
        sock::RawSocket socket;
        ip::Datagram* datagram = datagram_factory->create_datagram();
        packet.encapsulate_into(*datagram);
        socket.Send(datagram->bytes());
        
        byte buffer[1024];
        
        while (true)
        {
            int n = socket.Receive(buffer, 1024);

            cout << endl;
            cout << "Received " << n << " bytes" << endl;

            /*ipv4::Packet received_ip = ipv4::Packet::parse(buffer, n);
            if (received_ip.data_protocol() == PROTOCOL_NUMBER)
            {
                udp::Packet received_udp = udp::Packet::parse(&(buffer[received_ip.length()]), n - received_ip.length());

                cout << endl;
                cout << received_ip.info();
                cout << received_udp.info();

                return received_udp;
            }*/
        }
    }
    
    Packet Sender::send(long source_port, long destination_port, const string& data)
    {
        vector<byte> bytes;
        for (char character : data)
            bytes.push_back(character);
        
        Packet packet;
        packet.set_source_port(source_port);
        packet.set_destination_port(destination_port);
        packet.set_data(bytes);
        return send(packet);
    }
    
}