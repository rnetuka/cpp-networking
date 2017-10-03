/*
 */

#include <cstdint>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

#include "ip_api.h"
#include "ipv4.h"
#include "ipv4_address.h"

using namespace std;


namespace ipv4
{
    
    Datagram::Datagram() : version_(4), ihl_(5), dscp_(0), ecn_(0), total_length_(20),
            identification_(0), dont_fragment_(0), more_fragments_(0), 
            fragment_offset_(0), time_to_live_(0), protocol_(0), header_checksum_(0), 
            data_(0)
    {
        
    }
    
    Datagram::~Datagram()
    {
        
    }
    
    int Datagram::version() const 
    {
        return version_;
    }
    
    int Datagram::ihl() const 
    {
        return ihl_; 
    }
    
    int Datagram::dscp() const 
    { 
        return dscp_; 
    }
    
    int Datagram::ecn() const 
    { 
        return ecn_;
    }
    
    long Datagram::total_length() const 
    { 
        return total_length_; 
    }
    
    long Datagram::identification() const 
    { 
        return identification_; 
    }
    
    int Datagram::flags() const
    {
        if (dont_fragment_)
            return more_fragments_ ? 1 : 0;
        else
            return more_fragments_ ? 3 : 2;
    }
    
    bool Datagram::dont_fragment() const 
    { 
        return dont_fragment_;
    }
    
    bool Datagram::more_fragments() const 
    { 
        return more_fragments_; 
    }
    
    int Datagram::fragment_offset() const 
    {
        return fragment_offset_;
    }
    
    int Datagram::time_to_live() const
    { 
        return time_to_live_; 
    }
    
    long Datagram::header_checksum() const 
    { 
        return header_checksum_; 
    }
    
    Address Datagram::source_address() const 
    { 
        return source_address_; 
    }
    
    Address Datagram::destination_address() const 
    {
        return destination_address_; 
    }
    
    vector<uint8_t> Datagram::data() const
    {
        return data_;
    }
    
    int Datagram::length() const
    {
        return ihl() * 4;
    }
    
    void Datagram::set_dscp(int code_point)
    {
        if (code_point < 0 || code_point > 63) // 0b111111
            throw invalid_argument("DSCP value not in range");
        
        dscp_ = code_point;
    }
    
    void Datagram::set_ecn(int notification)
    {
        if (notification < 0 || notification > 3) // 0b11
            throw invalid_argument("ECN value not in range");
        
        ecn_ = notification;
    }
    
    void Datagram::set_total_length(long length)
    {
        if (length < 0 || length > 65535) // 0b1111111111111111
            throw invalid_argument("Total length not in range");
        
        if (length < 20)
            throw invalid_argument("Total length cannot be lower than 20 bytes");
        
        total_length_ = length;
    }
    
    void Datagram::set_identification(long identification)
    {
        identification_ = identification;
    }

    void Datagram::set_flags(int flags) 
    {
        if (flags < 0 || flags > 3)
            throw invalid_argument("Invalid flags");
        
        dont_fragment_ = flags >> 1;
        more_fragments_ = flags & 1; // b01
    }

    void Datagram::set_dont_fragment(bool option) 
    {
        dont_fragment_ = option;
    }

    void Datagram::set_more_fragments(bool option)
    {
        more_fragments_ = option;
    }
    
    void Datagram::set_fragment_offset(int offset)
    {
        fragment_offset_ = offset;
    }
    
    void Datagram::set_time_to_live(int time_to_live)
    {
        time_to_live_ = time_to_live;
    }
    
    void Datagram::set_data_protocol(int protocol)
    {
        protocol_ = protocol;
    }
    
    void Datagram::set_source_address(const Address& address)
    {
        source_address_ = address;
    }
    
    void Datagram::set_destination_address(const Address& address)
    {
        destination_address_ = address;
    }
    
    void Datagram::set_data(const vector<uint8_t>& bytes)
    {   
        set_total_length(total_length() + bytes.size());
        data_ = bytes;
        calculate_checksum();
    }
    
    void Datagram::calculate_checksum()
    {
        header_checksum_ = checksum(*this);
    }
    
    string Datagram::str() const
    {
        stringstream stream;
        stream << "[IPv4] " << endl;
        return stream.str();
    }
    
    string Datagram::info() const
    {
        stringstream stream;
        stream << "+------------------------------------------+" << endl;
        stream << "| Version: " << version() << endl;
        stream << "| IHL: " << ihl() << endl;
        stream << "| DSCP: " << dscp() << endl;
        stream << "| ECN: " << ecn() << endl;
        stream << "| Total length: " << total_length() << endl;
        stream << "| Identification: " << identification() << endl;
        stream << "| Don't Fragment: " << dont_fragment_ << endl;
        stream << "| More Fragments: " << more_fragments_ << endl;
        stream << "| Fragment offset: " << fragment_offset() << endl;
        stream << "| TTL: " << time_to_live() << endl;
        stream << "| Protocol: " << data_protocol() << endl;
        stream << "| Checksum: " << header_checksum() << endl;
        stream << "| Source IP: " << source_address() << endl;
        stream << "| Destination IP: " << destination_address() << endl;
        stream << "| Data: " << data_.size() << " bytes" << endl;
        stream << "+------------------------------------------+" << endl;
        return stream.str();
    }
    
    vector<uint8_t> Datagram::bytes() const
    {
        vector<uint8_t> bytes;        
        bytes.push_back(((uint8_t) version_ << 4) + ihl_);
        bytes.push_back(((uint8_t) dscp_ << 2) + ecn_);
        bytes.push_back(total_length_ >> 8);
        bytes.push_back(total_length_);
        bytes.push_back(identification_ >> 8);
        bytes.push_back(identification_);
        bytes.push_back((flags() << 5) + (fragment_offset_ >> 8));
        bytes.push_back(fragment_offset_);
        bytes.push_back(time_to_live_);
        bytes.push_back(protocol_);
        bytes.push_back(header_checksum_ >> 8);
        bytes.push_back(header_checksum_);
        bytes.push_back(source_address_[0]);
        bytes.push_back(source_address_[1]);
        bytes.push_back(source_address_[2]);
        bytes.push_back(source_address_[3]);
        bytes.push_back(destination_address_[0]);
        bytes.push_back(destination_address_[1]);
        bytes.push_back(destination_address_[2]);
        bytes.push_back(destination_address_[3]);
        bytes.insert(bytes.end(), data_.begin(), data_.end());
        return bytes;
    }
    
    vector<uint16_t> Datagram::pseudo_header() const
    {
        vector<uint16_t> pseudo_header;
        pseudo_header.push_back(source_address_ >> 16);
        pseudo_header.push_back(source_address_ & 65535);
        pseudo_header.push_back(destination_address_ >> 16);
        pseudo_header.push_back(destination_address_ & 65535);
        return pseudo_header;
    }
    
    int checksum(const Datagram& packet)
    {
        unsigned int sum = ((packet.version() << 12) + (packet.ihl() << 8) + (packet.dscp() << 2) + packet.ecn()) +
                packet.total_length() +
                packet.identification() +
                ((packet.flags() << 13) + packet.fragment_offset()) +
                ((packet.time_to_live() << 8) + packet.data_protocol()) +
                (packet.source_address() >> 16) +
                (packet.source_address() & 65535) + 
                (packet.destination_address() >> 16) +
                (packet.destination_address() & 65535);
        sum = (sum >> 16) + (sum & 65535);
        return ~sum & 65535;
    }
    
    unique_ptr<Datagram> Datagram::parse(uint8_t bytes[], int length)
    {
        if (length < 20)
            throw invalid_argument("IPv4 packet must have at least 20 bytes length");
            
        Datagram* packet = new Datagram;
        packet->version_ = bytes[0] >> 4;
        packet->ihl_ = bytes[0] & 15; // b1111
        packet->dscp_ = bytes[1] >> 2;
        packet->ecn_ = bytes[1] & 3; // b11
        packet->total_length_ = (((unsigned long) bytes[2]) << 8) + bytes[3];
        packet->identification_ = (((unsigned long) bytes[4]) << 8) + bytes[5];
        packet->dont_fragment_ = 0;
        packet->more_fragments_ = 0;
        packet->fragment_offset_ = 0;
        packet->time_to_live_ = bytes[8];
        packet->protocol_ = bytes[9];
        packet->header_checksum_ = (((unsigned long) bytes[10]) << 8) + bytes[11];
        packet->source_address_ = Address(bytes[12], bytes[13], bytes[14], bytes[15]);
        packet->destination_address_ = Address(bytes[16], bytes[17], bytes[18], bytes[19]);
        //packet->data_ = nullptr;
        return unique_ptr<Datagram>(packet);
    }
    
    unique_ptr<Datagram> Datagram::parse(const vector<uint8_t>& bytes)
    {
        if (bytes.size() < 20)
            throw invalid_argument("IPv4 packet must have at least 20 bytes length");
        
        Datagram* packet = new Datagram;
        packet->version_ = bytes[0] >> 4;
        packet->ihl_ = bytes[0] & 15; // b1111
        packet->dscp_ = bytes[1] >> 2;
        packet->ecn_ = bytes[1] & 3; // b11
        packet->total_length_ = (((unsigned long) bytes[2]) << 8) + bytes[3];
        packet->identification_ = (((unsigned long) bytes[4]) << 8) + bytes[5];
        packet->dont_fragment_ = 0;
        packet->more_fragments_ = 0;
        packet->fragment_offset_ = 0;
        packet->time_to_live_ = bytes[8];
        packet->protocol_ = bytes[9];
        packet->header_checksum_ = (((unsigned long) bytes[10]) << 8) + bytes[11];
        packet->source_address_ = Address(bytes[12], bytes[13], bytes[14], bytes[15]);
        packet->destination_address_ = Address(bytes[16], bytes[17], bytes[18], bytes[19]);
        packet->data_ = vector<uint8_t>(bytes.begin() + 20, bytes.end());
        return unique_ptr<Datagram>(packet);
    }
    
    DatagramFactory::DatagramFactory() : data_protocol(0), time_to_live(128), identification(1000), allow_fragmentation_(true) 
    {
        
    }
    
    ip::Datagram* DatagramFactory::create_datagram() const
    {
        ipv4::Datagram* datagram = new ipv4::Datagram;
        datagram->set_source_address(source_address);
        datagram->set_destination_address(destination_address);
        
        if (data_protocol != 0)
            datagram->set_data_protocol(data_protocol);
        
        datagram->set_time_to_live(time_to_live);
        datagram->set_identification(++identification);
        datagram->set_dont_fragment(! allow_fragmentation_);
        return datagram;
    }
        
}
