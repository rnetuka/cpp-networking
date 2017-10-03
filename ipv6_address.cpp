/*
 */

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "ipv6_address.h"

using namespace ipv6;
using namespace std;



Address::Address(uint16_t word1, uint16_t word2, uint16_t word3, 
                 uint16_t word4, uint16_t word5, uint16_t word6,
                 uint16_t word7, uint16_t word8)
{
    words[0] = word1;
    words[1] = word2;
    words[2] = word3;
    words[3] = word4;
    words[4] = word5;
    words[5] = word6;
    words[6] = word7;
    words[7] = word8;
}

string Address::str() const
{
    stringstream stream;
    stream << hex;

    for (int i = 0; i < length; i++)
    {
        stream << setw(4) << setfill('0');
        stream << words[i];

        if (i < length - 1)
            stream << Address::delimeter;
    }
    return stream.str();
}

Address* Address::parse(const string& str)
{
    string str_copy = str;

    int i;
    if ((i = str.find("::")) != string::npos)
    {
        int full_length = 39;
        int current_length = str.length();

        int zeros = (full_length - current_length) / 4;

        string padding;
        for (int j = 0; j < zeros; j++)
        {
            padding += "0000";
            if (j < zeros - 1)
                padding += delimeter;
        }
        str_copy.insert(i + 1, padding);
    }

    stringstream stream(str_copy);
    string str1, str2, str3, str4, str5, str6, str7, str8;

    getline(stream, str1, delimeter);
    getline(stream, str2, delimeter);
    getline(stream, str3, delimeter);
    getline(stream, str4, delimeter);
    getline(stream, str5, delimeter);
    getline(stream, str6, delimeter);
    getline(stream, str7, delimeter);
    stream >> str8;

    // TODO support omitting dbytes (::, even in the middle ot the string)
    // Note: only one :: is supported
    // !! Don't expect the dwords to be exatly 4 chars wide (b4 = 00b4)

    // TODO throw invalid argument if word is not hex or not in limit

    Address* address = new Address;
    stringstream format;
    format << hex;
    format << str1;
    format >> address->words[0];
    format.clear();
    format << str2;
    format >> address->words[1];
    format.clear();
    format << str3;
    format >> address->words[2];
    format.clear();
    format << str4;
    format >> address->words[3];
    format.clear();
    format << str5;
    format >> address->words[4];
    format.clear();
    format << str6;
    format >> address->words[5];
    format.clear();
    format << str7;
    format >> address->words[6];
    format.clear();
    format << str8;
    format >> address->words[7];

    return address;
}

uint16_t Address::operator [](int index) const
{
    if (index < 0 || index >= length)
        throw out_of_range("Illegal index. IPv6 address only has 8 bytes.");

    return words[index];
}

bool Address::operator ==(const Address& other) const
{
    return words[0] == other.words[0]
            && words[1] == other.words[1]
            && words[2] == other.words[2]
            && words[3] == other.words[3]
            && words[4] == other.words[4]
            && words[5] == other.words[5]
            && words[6] == other.words[6]
            && words[7] == other.words[7];
}

bool Address::operator !=(const Address& other) const
{
    return !(*this == other);
}
