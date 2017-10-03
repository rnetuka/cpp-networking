/*
 */

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <map>
#include <memory>
#include <sstream>

#include <ethernet2.h>
#include <ipv4.h>
#include <ipv6.h>
#include <mac.h>
#include <socket.h>
#include <system.h>

#include "tcp.h"
#include "tcp_packet_factory.h"

using namespace eth;
using namespace std;


namespace tcp
{
    
    Connection::Connection() : sequence(rand()), acknowledgement(0)
    {
        packet_factory.set_sequence_holder(*this);
    }
    
    Connection::~Connection()
    {
        if (datagram_factory)
            delete datagram_factory;
    }

    void Connection::open(const ipv4::Address& ip_address, int source_port, int destination_port)
    {
        //arp::AddressResolver address_resolver;
        //address_resolver.resolve(ipv4::Address("192.168.0.1")
        
        my_ip_address = ipv4::my_address();
        my_port = source_port;
        
        their_ip_address = ip_address;
        their_port = destination_port;
        
        frame_factory.set_source_address(sys::mac_address());
        frame_factory.set_destination_address(MacAddress::parse("cc:35:40:2b:ed:e5"));
        frame_factory.set_ether_type(EtherType::IPv4);
        
        datagram_factory = new ipv4::DatagramFactory;
        datagram_factory->set_source_address(my_ip_address);
        datagram_factory->set_destination_address(ip_address);
        datagram_factory->set_data_protocol(PROTOCOL_NUMBER);
        
        packet_factory.set_source_port(source_port);
        packet_factory.set_destination_port(destination_port);
        
        establish();
    }
    
    void Connection::open(const ipv4::Address& ip_address, int destination_port)
    {
        open(ip_address, sys::free_port(), destination_port);
    }
    
    void Connection::open(const ipv6::Address& ip_address, int source_port, int destination_port)
    {

    }
    
    void Connection::establish()
    {
        unique_ptr<Packet> syn_packet = packet_factory.create_syn_packet();
        send(*syn_packet);
        
        Packet received_packet = wait_for_packet([](const Packet& packet) { return packet.syn() && packet.ack(); });
        
        acknowledgement = received_packet.sequence_number() + 1;
        max_data_size = received_packet.option(Options::MAXIMUM_SEGMENT_SIZE);
        
        unique_ptr<Packet> ack_packet = packet_factory.create_ack_packet();
        ack_packet->set_window_size(40000);
        send(*ack_packet);
    }
    
    void Connection::send(Packet& packet)
    {
        ip::Datagram* datagram = datagram_factory->create_datagram();
        packet.encapsulate_into(*datagram);
        
        eth::Frame frame = frame_factory.create_frame(datagram->bytes());
        
        cout << "Sending:" << endl;
        //cout << frame.info() << endl;
        //cout << datagram->info() << endl;
        //cout << packet.info() << endl;
        cout << packet.str() << endl;
        
        socket.Send(frame.bytes());
        delete datagram;
        
        if (packet.syn() || packet.fin())
            sequence++;
        else
            sequence += packet.data_size();
    }
    
    void Connection::send_ack()
    {
        unique_ptr<Packet> ack_packet = packet_factory.create_ack_packet();
        ack_packet->set_window_size(40000);
        send(*ack_packet);
    }
    
    void Connection::send(const string& data)
    {
        int part_size = max_data_size;
        int steps = ceil((double) data.length() / part_size);
        
        for (int i = 0; i < steps; i++)
        {
            vector<byte> bytes;
            
            string part = data.substr(i * part_size, part_size);
            int part_length = part.length();
        
            for (int j = 0; j < min(part_length, part_size); j++)
                bytes.push_back(part[j]);
            
            unique_ptr<Packet> packet = packet_factory.create_packet(bytes);
            packet->set_window_size(40000);
            
            if (i == steps - 1)
                ;//packet->set_psh(true);
            
            send(*packet);
            cout << part << endl;
            wait_for_packet([](const Packet& packet) { return packet.ack(); });
        }
        
        unique_ptr<Packet> packet = packet_factory.create_packet();
        packet->set_psh(true);
        packet->set_acknowledgment_number(0);
        packet->set_window_size(40000);
        send(*packet);
    }
    
    bool Connection::is_for_me(const ipv4::Datagram& datagram) const
    {
        return datagram.destination_address() == my_ip_address 
                && datagram.source_address() == their_ip_address
                && datagram.data_protocol() == tcp::PROTOCOL_NUMBER;
    }
    
    bool Connection::is_for_me(const Packet& packet) const
    {
        return packet.destination_port() == my_port 
                && packet.source_port() == their_port;
    }
    
    Packet Connection::wait_for_packet(bool (*selector)(const Packet& packet))
    {
        while (true)
        {
            byte buffer[2000];
            int n = socket.Receive(buffer, 2000);
            
            vector<byte> bytes;
            for (int i = 0; i < n; i++)
                bytes.push_back(buffer[i]);
            
                    
            //cout << "Received " << n << " bytes:" << endl;
            //cout << sock::str(bytes) << endl;
            
            Frame ethernet_frame = Frame::parse(bytes);
            
            //cout << "Parsing Ethernet packet..." << endl;
            //cout << ethernet_frame.info() << endl;
            
            if (ethernet_frame.ether_type() == EtherType::IPv4)
            {   
                unique_ptr<ipv4::Packet> received_ip = ipv4::Packet::parse(ethernet_frame.payload());
                
                //cout << "Parsing IPv4 packet..." << endl;
                //cout << received_ip->info() << endl;
                
                if (is_for_me(*received_ip))
                {  
                    Packet received_tcp = Packet::parse(received_ip->data());

                    if (is_for_me(received_tcp))
                    {
                        cout << "Received: "<< endl;
                        cout << received_tcp.str() << endl;

                        if (selector(received_tcp))  
                            return received_tcp;

                    }
                }
            }
        }
    }
    
    Packet Connection::receive_packet()
    {
        Packet received_packet = wait_for_packet([](const Packet& packet) { return true; });
        acknowledgement += received_packet.data_size();
        send_ack();
        return received_packet;
    }
    
    vector<Packet> Connection::receive()
    {
        vector<Packet> packets;
        
        Packet received_packed = receive_packet();
        packets.push_back(received_packed);
        
        send_ack();
        
        while (! received_packed.psh())
        {
            received_packed = receive_packet();
            packets.push_back(received_packed);
        }
        
        return packets;
    }
    
    vector<byte> Connection::receive_bytes()
    {
        vector<byte> bytes;
        vector<Packet> packets = receive();
        for (Packet& packet : packets)
        {
            vector<byte> packet_bytes = packet.data();
            bytes.insert(bytes.end(), packet_bytes.begin(), packet_bytes.end());
        }
        return bytes;
    }
    
    void Connection::close()
    {
        unique_ptr<Packet> fin_packet = packet_factory.create_fin_packet();
        send(*fin_packet);
        
        Packet received_ack = wait_for_packet([](const Packet& packet) { return packet.ack(); });
        if (! received_ack.fin())
            wait_for_packet([](const Packet& packet) { return packet.fin(); });
        
        acknowledgement++;
        
        unique_ptr<Packet> ack_packet = packet_factory.create_ack_packet();
        ack_packet->set_window_size(1000);
        send(*ack_packet);
        
        delete datagram_factory;
        datagram_factory = nullptr;
    }

}

