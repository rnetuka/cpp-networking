/*
 */

#include <cstdint>
#include <bitset>
#include <map>
#include <sstream>
#include <string>
#include <ip.h>

#include "tcp_packet.h"

using namespace std;


namespace tcp
{
    
    Packet::Packet() : source_port_(0), destination_port_(0), sequence_number_(0), 
            acknowledgment_number_(0), data_offset_(5), ns_(0),
            cwr_(0), ece_(0), urg_(0), ack_(0), psh_(0), rst_(0), syn_(0), fin_(0),
            window_size_(0), checksum_(0), urgent_pointer_(0)
    {
        
    }
    
    uint16_t Packet::source_port() const 
    { 
        return source_port_; 
    }
    
    uint16_t Packet::destination_port() const 
    { 
        return destination_port_; 
    }
    
    uint32_t Packet::sequence_number() const 
    { 
        return sequence_number_; 
    }
    
    uint32_t Packet::acknowledgment_number() const 
    { 
        return acknowledgment_number_; 
    }
    
    int Packet::data_offset() const 
    { 
        return data_offset_; 
    }
    
    bitset<9> Packet::flags() const
    {
        int flags = ns_;
        flags <<= 1;
        flags += cwr_;
        flags <<= 1;
        flags += ece_;
        flags <<= 1;
        flags += urg_;
        flags <<= 1;
        flags += ack_;
        flags <<= 1;
        flags += psh_;
        flags <<= 1;
        flags += rst_;
        flags <<= 1;
        flags += syn_;
        flags <<= 1;
        flags += fin_;
        return bitset<9>(flags);
    }
    
    bool Packet::ns() const 
    { 
        return ns_; 
    }
    
    bool Packet::cwr() const 
    { 
        return cwr_; 
    }
    
    bool Packet::ece() const 
    { 
        return ece_; 
    }
    
    bool Packet::urg() const 
    { 
        return urg_; 
    }
    
    bool Packet::ack() const 
    { 
        return ack_; 
    }
    
    bool Packet::psh() const 
    { 
        return psh_; 
    }
    
    bool Packet::rst() const 
    { 
        return rst_; 
    }
    
    bool Packet::syn() const 
    { 
        return syn_; 
    }
    
    bool Packet::fin() const 
    { 
        return fin_; 
    }
    
    long Packet::window_size() const 
    { 
        return window_size_; 
    }
    
    long Packet::checksum() const 
    { 
        return checksum_; 
    }
    
    long Packet::urgent_pointer() const 
    { 
        return urgent_pointer_; 
    }
    
    void Packet::set_source_port(long port)
    {
        source_port_ = port;
    }
    
    void Packet::set_destination_port(long port)
    {
        destination_port_ = port;
    }
    
    void Packet::set_sequence_number(long long number)
    {
        sequence_number_ = number;
    }
    
    void Packet::set_acknowledgment_number(long long number)
    {
        acknowledgment_number_ = number;
    }
    
    void Packet::set_data_offset(int offset)
    {
        data_offset_ = offset;
    }
    
    void Packet::set_flags(int flags)
    {
        ns_ = flags & 256; // b1_0000_0000
        cwr_ = flags & 128; // b1000_0000
        ece_ = flags & 64; // b100_0000
        urg_ = flags & 32; // b10_0000
        ack_ = flags & 16; // b1_0000
        psh_ = flags & 8; // b1000
        rst_ = flags & 4; // b100
        syn_ = flags & 2; // b10
        fin_ = flags & 1; // b1
    }
    
    void Packet::set_ns(bool ns)
    {
        ns_ = ns;
    }
    
    void Packet::set_cwr(bool cwr)
    {
        cwr_ = cwr;
    }
    
    void Packet::set_ece(bool ece)
    {
        ece_ = ece;
    }
    
    void Packet::set_urg(bool urg)
    {
        urg_ = urg;
    }
    
    void Packet::set_ack(bool ack)
    {
        ack_ = ack;
    }
    
    void Packet::set_psh(bool psh)
    {
        psh_ = psh;
    }
    
    void Packet::set_rst(bool rst)
    {
        rst_ = rst;
    }
    
    void Packet::set_syn(bool syn)
    {
        syn_ = syn;
    }
    
    void Packet::set_fin(bool fin)
    {
        fin_ = fin;
    }
    
    void Packet::set_window_size(long size)
    {
        window_size_ = size;
    }
    
    void Packet::set_checksum(long checksum)
    {
        checksum_ = checksum;
    }
    
    void Packet::set_urgent_pointer(long pointer)
    {
        urgent_pointer_ = pointer;
    }
    
    void Packet::set_option(int option, unsigned int value)
    {
        options_[option] = value;
        // TODO data_offset_ += 4;
    }
    
    void Packet::set_data(const std::vector<byte>& data)
    {
        data_ = data;
    }
    
    bool Packet::contains_option(int option) const
    {
        return options_.find(option) != options_.end();
    }
    
    unsigned int Packet::option(int option) const
    {
        map<int, unsigned int>::const_iterator it(options_.find(option));
        return (it == options_.end()) ? 0 : it->second;
    }
    
    vector<byte> Packet::data() const
    {
        return data_;
    }
    
    int Packet::header_size() const
    {
        return 20; // TODO + options size
    }
    
    int Packet::data_size() const
    {
        return data_.size();
    }
    
    int Packet::size() const
    {
        return header_size() + data_size();
    }
    
    vector<byte> Packet::bytes() const
    {        
        vector<byte> bytes;
        bytes.push_back(source_port_ >> 8);
        bytes.push_back(source_port_ & 255);
        bytes.push_back(destination_port_ >> 8);
        bytes.push_back(destination_port_ & 255);
        bytes.push_back((sequence_number_ >> 24) & 255);
        bytes.push_back((sequence_number_ >> 16) & 255);
        bytes.push_back((sequence_number_ >> 8) & 255);
        bytes.push_back(sequence_number_);
        bytes.push_back(acknowledgment_number_ >> 24);
        bytes.push_back(acknowledgment_number_ >> 16);
        bytes.push_back(acknowledgment_number_ >> 8);
        bytes.push_back(acknowledgment_number_);
        bytes.push_back((((bits_8) data_offset_) << 4) + ns_);
        bytes.push_back(flags().to_ulong() & 255);
        bytes.push_back(window_size_ >> 8);
        bytes.push_back(window_size_ & 255);
        bytes.push_back(checksum_ >> 8);
        bytes.push_back(checksum_ & 255);
        bytes.push_back(urgent_pointer_ >> 8);
        bytes.push_back(urgent_pointer_ & 255);
        bytes.insert(bytes.end(), data_.begin(), data_.end());
        return bytes;
    }
    
    void Packet::encapsulate_into(ip::Datagram& datagram)
    {
        set_checksum(calculate_checksum(*this, datagram));
        datagram.set_data(bytes());
    }
    
    Packet Packet::parse(const vector<byte>& bytes)
    {
        if (bytes.size() < 20)
            throw invalid_argument("TCP packet size cannot be lower than 20 bytes");
        
        if ((bytes.size() - 20) % 4 != 0)
            throw invalid_argument("Invalid TCP packet length. Not divisable by 32 bits.");
        
        Packet packet;
        packet.source_port_ = (((bits_16) bytes[0]) << 8) + bytes[1];
        packet.destination_port_ = (((bits_16) bytes[2]) << 8) + bytes[3];
        packet.sequence_number_ = (((bits_32) bytes[4]) << 24) + (((bits_32) bytes[5]) << 16) + (((bits_16) bytes[6]) << 8) + bytes[7];
        packet.acknowledgment_number_ = (((bits_32) bytes[8]) << 24) + (((bits_32) bytes[9]) << 16) + (((bits_16) bytes[10]) << 8) + bytes[11];
        packet.data_offset_ = bytes[12] >> 4;
        packet.set_flags(((((bits_16) bytes[12]) & 1) << 8) + bytes[13]);
        packet.window_size_ = (((bits_16) bytes[14]) << 8) + bytes[15];
        packet.checksum_ = (((bits_16) bytes[16]) << 8) + bytes[17];
        packet.urgent_pointer_ = (((bits_16) bytes[18]) << 8) + bytes[19];
        
        int i;
        for (i = 20; i < 4*packet.data_offset_; i += 4)
        {
            int option_kind = bytes[i];
            int option_length = bytes[i + 1];
            
            unsigned int size = (((unsigned int) bytes[i + 2]) << 8) + bytes[i + 3];
            packet.set_option(option_kind, size);
        }
        
        packet.set_data(vector<byte>(bytes.begin() + i, bytes.end()));
        return packet;
    }
    
    string Packet::str() const
    {
        stringstream stream;
        int flag_cout = flags().count();
        stream << "[";
        if (syn_)
        {
            stream << "SYN";
            flag_cout--;
            if (flag_cout > 0)
                stream << ",";
        }
        if (psh_)
        {
            stream << "PSH";
            flag_cout--;
            if (flag_cout > 0)
                stream << ",";
        }
        if (ack_)
        {
            stream << "ACK";
            flag_cout--;
            if (flag_cout > 0)
                stream << ",";
        }
        if (fin_)
        {
            stream << "FIN";
            flag_cout--;
            if (flag_cout > 0)
                stream << ",";
        }
        stream << "]";
        stream << " seq = " << sequence_number();
        stream << ", ack = " << acknowledgment_number();
        if (data_size() > 0)
            stream << ", data = " << data_size() << "b";
        stream << endl;
        return stream.str();
    }
    
    string Packet::info() const
    {
        stringstream stream;
        stream << "+------------------------------------------+" << endl;
        stream << "| Source port: " << source_port() << endl;
        stream << "| Destination port: " << destination_port() << endl;
        stream << "| Sequence number: " << sequence_number() << endl;
        stream << "| ACK number: " << acknowledgment_number() << endl;
        stream << "| Data offset: " << data_offset() << endl;
        stream << "| NS: " << ns_ << endl;
        stream << "| CWR: " << cwr_ << endl;
        stream << "| ECE: " << ece_ << endl;
        stream << "| URG: " << urg_ << endl;
        stream << "| ACK: " << ack_ << endl;
        stream << "| PSH: " << psh_ << endl;
        stream << "| RST: " << rst_ << endl;
        stream << "| SYN: " << syn_ << endl;
        stream << "| FIN: " << fin_ << endl;
        stream << "| Window size: " << window_size() << endl;
        stream << "| Checksum: " << checksum() << endl;
        stream << "| URG pointer: " << urgent_pointer() << endl;
        
        if (! options_.empty())
            stream << "| Options: " << endl;
            
        for (map<int, unsigned int>::const_iterator it = options_.begin(); it != options_.end(); it++)
            stream << "|   * " << it->first << ": " << it->second << endl;
        
        stream << "| Data: " << data_.size() << " bytes" << endl;
        stream << "+------------------------------------------+" << endl;
        return stream.str();
    }
    
    int calculate_checksum(const Packet& packet, const ip::Datagram& ip_datagram)
    {
        uint32_t sum = 0;
        
        vector<bits_16> pseudo_header = ip_datagram.pseudo_header();
        
        for (bits_16 bits : pseudo_header)
            sum += bits;
        sum += ((PROTOCOL_NUMBER << 16) + packet.size());
        
        sum += packet.source_port();
        sum += packet.destination_port();
        sum += (packet.sequence_number() >> 16);
        sum += (packet.sequence_number() & 65535);
        sum += (packet.acknowledgment_number() >> 16);
        sum += (packet.acknowledgment_number() & 65535);
        sum += ((packet.data_offset() << 12) + packet.flags().to_ulong()) ;
        sum += packet.window_size();
        sum += packet.urgent_pointer();
        // TODO options
        
        for (int i = 0; i < packet.data_.size(); i += 2)
        {
            uint32_t word = ((uint32_t) packet.data_[i]) << 8;
            
            if (i + 1 < packet.data_.size())
                word += packet.data_[i + 1];
            
            sum += word;
        }
        
        sum = (sum >> 16) + (sum & 65535);
        return ~sum & 65535;
    }
    
}