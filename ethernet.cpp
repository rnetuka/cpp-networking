/*
 */

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "ethernet.h"
#include "mac.h"

using namespace eth;
using namespace mac;
using namespace std;

    
Frame::Frame() : ether_type_(0), checksum_(0)
{

}

void Frame::set_source_address(const Address& address)
{
    source_address_ = address;
}

void Frame::set_destination_address(const Address& address) 
{
    destination_address_ = address;
}

void Frame::set_ether_type(int type)
{
    ether_type_ = type;
}

void Frame::set_payload(const vector<uint8_t>& payload)
{
    payload_ = payload;
}

void Frame::set_checksum(int checksum)
{
    checksum_ = checksum;
}

Address Frame::source_address() const
{
    return source_address_;
}

Address Frame::destination_address() const
{
    return destination_address_;
}

uint16_t Frame::ether_type() const 
{
    return ether_type_;
}

vector<uint8_t> Frame::payload() const
{
    return payload_;
}

uint32_t Frame::checksum() const
{
    return checksum_;
}

vector<uint8_t> Frame::bytes() const
{
    vector<uint8_t> source_address_bytes = source_address_.bytes();
    vector<uint8_t> destination_address_bytes = destination_address_.bytes();

    vector<uint8_t> bytes;
    bytes.insert(bytes.end(), destination_address_bytes.begin(), destination_address_bytes.end());
    bytes.insert(bytes.end(), source_address_bytes.begin(), source_address_bytes.end());
    bytes.push_back(ether_type_ >> 8);
    bytes.push_back(ether_type_ & 0b11111111);
    bytes.insert(bytes.end(), payload_.begin(), payload_.end());
    /*
    bytes.push_back(checksum_ >> 24);
    bytes.push_back((checksum_ >> 16) & 255);
    bytes.push_back((checksum_ >> 8) & 255);
    bytes.push_back(checksum_ & 255);
    for (int i = bytes.size(); i < 64; i++
        bytes.push_back(0);
    */
    return bytes;
}

string Frame::str() const
{
    stringstream stream;
    stream << "Src MAC: " << source_address_ << endl;
    stream << "Dest MAC: " << destination_address_ << endl;
    return stream.str();
}

string Frame::info() const
{
    stringstream stream;
    stream << "+-----------------------" << endl;
    stream << "| Dest MAC: " << destination_address_ << endl;
    stream << "| Src MAC: " << source_address_ << endl;
    stream << "| Ether type: " << ether_type_ << endl;
    stream << "| Payload of " << payload_.size() << " bytes" << endl;
    stream << "| Checksum: " << checksum_ << endl;
    stream << "+-----------------------" << endl;
    return stream.str();
}

Frame Frame::parse(const vector<uint8_t>& bytes)
{
    Frame frame;
    frame.destination_address_ = Address(vector<uint8_t>(bytes.begin(), bytes.begin() + 6));
    frame.source_address_ = Address(vector<uint8_t>(bytes.begin() + 6, bytes.begin() + 12));
    frame.ether_type_ = (((uint16_t) bytes[12]) << 8) + bytes[13];

    vector<uint8_t> remaining_bytes(bytes.begin() + 14, bytes.end());        
    int payload_length;

    if (frame.ether_type_ <= 1500)
    {
        payload_length = frame.ether_type_;
    }
    else if (frame.ether_type_ == EtherType::IPv4)
    {
        payload_length = (((int) remaining_bytes[2]) << 8) + remaining_bytes[3];
    }
    else if (frame.ether_type_ == EtherType::IPv6)
    {
        // TODO: implement this
        payload_length = 0;
    }
    else if (frame.ether_type_ == EtherType::ARP)
    {
        //payload_length = remaining_bytes.size();
        payload_length = 28;
    }
    else
    {
        // TODO: implement this
    }

    frame.payload_.insert(frame.payload_.end(), remaining_bytes.begin(), remaining_bytes.begin() + payload_length);
    return frame;
}

FrameFactory::FrameFactory() : ether_type(0)
{

}

void FrameFactory::set_source_address(const Address& address)
{
    source_address = address;
}

void FrameFactory::set_destination_address(const Address& address)
{
    destination_address = address;
}

void FrameFactory::set_ether_type(uint16_t type)
{
    ether_type = type;
}
    
Frame FrameFactory::create_frame(const vector<uint8_t>& payload) const
{
    Frame frame;
    frame.set_source_address(source_address);
    frame.set_destination_address(destination_address);
    frame.set_ether_type(ether_type);
    frame.set_payload(payload);
    //frame.set_checksum(crc_checksum(frame.bytes()));
    return frame;
}

ostream& operator <<(ostream& stream, const Frame& frame)
{
    return stream << frame.str();
}