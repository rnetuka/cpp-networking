/*
 */

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "mac.h"
#include "types.h"

using namespace std;


namespace mac
{
    
    Address::Address(uint64_t i)
    {
        std::fill(bytes_, bytes_ + length, 0);

        if (i < 0 || i > 281474976710655L)
            throw invalid_argument("MAC address be only 6 bytes long");

        bytes_[0] = (i >> 40);
        bytes_[1] = (i >> 32) & 255;
        bytes_[2] = (i >> 24) & 255;
        bytes_[3] = (i >> 16) & 255;
        bytes_[4] = (i >> 8) & 255;
        bytes_[5] = i & 255;
    }

    Address::Address(const vector<uint8_t>& bytes)
    {
        if (bytes.size() != length)
            throw invalid_argument("MAC address must have exactly 6 bytes");

        bytes_[0] = bytes[0];
        bytes_[1] = bytes[1];
        bytes_[2] = bytes[2];
        bytes_[3] = bytes[3];
        bytes_[4] = bytes[4];
        bytes_[5] = bytes[5];
    }

    string Address::str() const
    {
        stringstream stream;
        stream << hex;
        stream << (int) bytes_[0] << delimeter;
        stream << (int) bytes_[1] << delimeter;
        stream << (int) bytes_[2] << delimeter;
        stream << (int) bytes_[3] << delimeter;
        stream << (int) bytes_[4] << delimeter;
        stream << (int) bytes_[5];
        return stream.str();
    }

    vector<uint8_t> Address::bytes() const
    {
        vector<uint8_t> result { bytes_[0], bytes_[1], bytes_[2], bytes_[3], bytes_[4], bytes_[5] };
        return result;
    }

    Address Address::parse(const std::string& text)
    {
        Address address;

        stringstream stream(text);

        string str1, str2, str3, str4, str5, str6;
        int i1, i2, i3, i4, i5, i6;

        getline(stream, str1, delimeter);
        getline(stream, str2, delimeter);
        getline(stream, str3, delimeter);
        getline(stream, str4, delimeter);
        getline(stream, str5, delimeter);
        stream >> str6;

        stringstream format;
        format << hex;
        format << str1;
        format >> i1;
        format.clear();
        format << str2;
        format >> i2;
        format.clear();
        format << str3;
        format >> i3;
        format.clear();
        format << str4;
        format >> i4;
        format.clear();
        format << str5;
        format >> i5;
        format.clear();
        format << str6;
        format >> i6;

        address.bytes_[0] = i1;
        address.bytes_[1] = i2;
        address.bytes_[2] = i3;
        address.bytes_[3] = i4;
        address.bytes_[4] = i5;
        address.bytes_[5] = i6;

        return address;
    }

    uint8_t Address::operator [](int i) const
    {
        if (i < 0 || i >= length)
            throw out_of_range("Index out of range. MAC address only has 6 bytes.");

        return bytes_[i];
    }

    bool Address::operator ==(const Address& other) const
    {
        return bytes_[0] == other.bytes_[0]
                && bytes_[1] == other.bytes_[1]
                && bytes_[2] == other.bytes_[2]
                && bytes_[3] == other.bytes_[3]
                && bytes_[4] == other.bytes_[4]
                && bytes_[5] == other.bytes_[5];
    }

    bool Address::operator !=(const Address& other) const
    {
        return !(*this == other);
    }

}

ostream& operator <<(ostream& stream, const mac::Address& address)
{
    return stream << address.str();
}