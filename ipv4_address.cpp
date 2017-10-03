/*
 */

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

#include "ipv4_address.h"

using namespace ipv4;
using namespace std;

    
Address::Address()
{
    std::fill(bytes_, bytes_ + 4, 0);
}

Address::Address(uint32_t i)
{
    bytes_[0] = (i >> 24);
    bytes_[1] = (i >> 16) & 0b11111111;
    bytes_[2] = (i >> 8) & 0b11111111;
    bytes_[3] = i & 0b11111111;
}

Address::Address(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
    bytes_[0] = byte1;
    bytes_[1] = byte2;
    bytes_[2] = byte3;
    bytes_[3] = byte4;
}

uint32_t Address::i() const
{
    uint32_t result = bytes_[0];
    result <<= 8;
    result += bytes_[1];
    result <<= 8;
    result += bytes_[2];
    result <<= 8;
    result += bytes_[3];
    return result;
}

string Address::str() const
{
    stringstream stream;
    stream << (int) bytes_[0] << Address::delimeter;
    stream << (int) bytes_[1] << Address::delimeter;
    stream << (int) bytes_[2] << Address::delimeter;
    stream << (int) bytes_[3];
    return stream.str();
}

vector<uint8_t> Address::bytes() const
{
    vector<uint8_t> result;
    result.push_back(bytes_[0]);
    result.push_back(bytes_[1]);
    result.push_back(bytes_[2]);
    result.push_back(bytes_[3]);
    return result;
}

int Address::operator >>(int n) const
{
    return i() >> n;
}

int Address::operator <<(int n) const
{
    return i() << n;
}

int Address::operator &(uint32_t n) const
{
    return i() & n;
}

int Address::operator |(uint32_t n) const
{
    return i() | n;
}

int Address::operator [](int i) const
{
    if (i < 0 || i > 3)
        throw out_of_range("Index out of range. IPv4 address has only 4 bytes.");

    return bytes_[i];
}

bool Address::operator ==(const Address& other) const
{
    return bytes_[0] == other.bytes_[0]
            && bytes_[1] == other.bytes_[1]
            && bytes_[2] == other.bytes_[2]
            && bytes_[3] == other.bytes_[3];
}

bool Address::operator !=(const Address& other) const
{
    return !(*this == other);
}

Address* Address::parse(const string& str)
{
    stringstream stream(str);
    string str1, str2, str3, str4;

    getline(stream, str1, delimeter);
    getline(stream, str2, delimeter);
    getline(stream, str3, delimeter);
    stream >> str4;

    int byte1;
    int byte2;
    int byte3;
    int byte4;

    stringstream parser;
    parser << str1;
    parser >> byte1;
    parser.clear();
    parser << str2;
    parser >> byte2;
    parser.clear();
    parser << str3;
    parser >> byte3;
    parser.clear();
    parser << str4;
    parser >> byte4;

    if ((byte1 < 0 || byte1 > 255) || (byte2 < 0 || byte2 > 255) || (byte3 < 0 || byte3 > 255) || (byte4 < 0 || byte4 > 255))
        throw invalid_argument("Address part out of range");

    Address* address = new Address;
    address->bytes_[0] = byte1;
    address->bytes_[1] = byte2;
    address->bytes_[2] = byte3;
    address->bytes_[3] = byte4;

    return address;
}

Address Address::from_bytes(const vector<uint8_t>& bytes)
{
    if (bytes.size() != length)
        throw invalid_argument("IPv4 address must have exactly 4 bytes");

    return Address(bytes[0], bytes[1], bytes[2], bytes[3]);
}

ostream& operator <<(ostream& stream, const Address& address)
{
    return stream << address.str();
}
