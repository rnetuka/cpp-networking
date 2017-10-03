/*
 */

#include <cstdint>
#include <ostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

#include <ethernet.h>
#include <ip/api.h>
#include <ip/address.h>
#include <ipv4/address.h>
#include <mac.h>
#include <sys/socket.h>

#include "arp.h"

using namespace arp;
using namespace eth;
using namespace std;


Packet::Packet() : hardware_type_(HardwareType::Ethernet), protocol_type_(0),
        hardware_address_length_(6), protocol_address_length_(0), operation_(0)
{

}

void Packet::set_hardware_type(int type)
{
    hardware_type_ = type;
}

void Packet::set_protocol_type(int type)
{
    protocol_type_ = type;
}

void Packet::set_hardware_address_length(int length)
{
    hardware_address_length_ = length;
}

void Packet::set_protocol_address_length(int length)
{
    protocol_address_length_ = length;
}

void Packet::set_operation(Operation operation)
{
    operation_ = operation;
}

void Packet::set_sender_hardware_address(const mac::Address& address)
{
    sender_hardware_address_ = address;
}

void Packet::set_target_hardware_address(const mac::Address& address)
{
    target_hardware_address_ = address;
}

void Packet::set_sender_protocol_address(const ip::Address& address)
{
    sender_protocol_address_ = ip::new_address(address.bytes());
}

void Packet::set_target_protocol_address(const ip::Address& address)
{
    target_protocol_address_ = ip::new_address(address.bytes());
}

bool Packet::request() const
{
    return operation_ == Operation::Request;
}

bool Packet::reply() const
{
    return operation_ == Operation::Reply;
}

mac::Address Packet::sender_hardware_address() const
{
    return sender_hardware_address_;
}

mac::Address Packet::target_hardware_address() const
{
    return target_hardware_address_;
}

const ip::Address& Packet::sender_protocol_address() const
{
    return *sender_protocol_address_;
}

const ip::Address& Packet::target_protocol_address() const
{
    return *target_protocol_address_;
}

string Packet::str() const
{
    stringstream stream;
    if (request())
    {
        stream << "Who has " << target_protocol_address() << "? ";
        stream << "Tell " << sender_protocol_address();
    }
    else
    {
        stream << target_protocol_address() << " is at " << target_hardware_address();
    }
    return stream.str();
}

string Packet::info() const
{
    stringstream stream;
    stream << "Hardware Type: " << hardware_type_ << endl;
    stream << "Protocol Type: " << protocol_type_ << endl;
    stream << "Hardware Address Length: " << hardware_address_length_ << endl;
    stream << "Protocol Address Length: " << protocol_address_length_ << endl;
    stream << "Operation: " << operation_ << endl;
    stream << "Sender Hardware Address: " << sender_hardware_address_ << endl;
    stream << "Sender Protocol Address: " << sender_protocol_address_->str()<< endl;
    stream << "Target Hardware Address: " << target_hardware_address_ << endl;
    stream << "Target Protocol Address: " << target_protocol_address_->str() << endl;
    return stream.str();
}

vector<uint8_t> Packet::bytes() const
{
    vector<uint8_t> sender_hardware_address_bytes = sender_hardware_address_.bytes();
    vector<uint8_t> target_hardware_address_bytes = target_hardware_address_.bytes();
    vector<uint8_t> sender_protocol_address_bytes = sender_protocol_address_->bytes();
    vector<uint8_t> target_protocol_address_bytes = target_protocol_address_->bytes();
    
    vector<uint8_t> bytes;
    bytes.push_back(hardware_type_ >> 8);
    bytes.push_back(hardware_type_ & 0b11111111);
    bytes.push_back(protocol_type_ >> 8);
    bytes.push_back(protocol_type_ & 0b11111111);
    bytes.push_back(hardware_address_length_);
    bytes.push_back(protocol_address_length_);
    bytes.push_back(operation_ >> 8);
    bytes.push_back(operation_ & 0b11111111);
    bytes.insert(bytes.end(), sender_hardware_address_bytes.begin(), sender_hardware_address_bytes.end());
    bytes.insert(bytes.end(), sender_protocol_address_bytes.begin(), sender_protocol_address_bytes.end());
    bytes.insert(bytes.end(), target_hardware_address_bytes.begin(), target_hardware_address_bytes.end());
    bytes.insert(bytes.end(), target_protocol_address_bytes.begin(), target_protocol_address_bytes.end());
    return bytes;
}

Packet Packet::parse(const vector<uint8_t>& bytes)
{
    //if (bytes.size() < )

    Packet packet;
    packet.hardware_type_ = (((int) bytes[0]) << 8) + bytes[1];
    packet.protocol_type_ = (((int) bytes[2]) << 8) + bytes[3];
    packet.hardware_address_length_ = bytes[4];
    packet.protocol_address_length_ = bytes[5];
    packet.operation_ = (((int) bytes[6]) << 8) + bytes[7];
    packet.sender_hardware_address_ = mac::Address(vector<uint8_t>(bytes[8], bytes[8] + packet.hardware_address_length_));
    packet.sender_protocol_address_ = ip::new_address(vector<uint8_t>(bytes[8 + packet.hardware_address_length_], bytes[8 + packet.hardware_address_length_ + packet.protocol_address_length_]));
    packet.target_hardware_address_ = mac::Address(vector<uint8_t>(bytes[8 + packet.hardware_address_length_ + packet.protocol_address_length_], bytes[8 + 2*packet.hardware_address_length_ + packet.protocol_address_length_]));
    packet.target_protocol_address_ = ip::new_address(vector<uint8_t>(bytes[8 + 2*packet.hardware_address_length_ + packet.protocol_address_length_], bytes[8 + 2*packet.hardware_address_length_ + 2*packet.protocol_address_length_]));
    return packet;
}
    
ostream& operator <<(ostream& stream, const arp::Packet& packet)
{
    return stream << packet.str();
}