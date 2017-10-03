/*
 */

#include <bitset>
#include <ostream>

#include "ip_api.h"


using namespace std;


namespace ip
{
    
    ostream& operator <<(ostream& stream, const Datagram& datagram)
    {
        vector<unsigned char> bytes = datagram.bytes();
        
        for (int i = 0; i < bytes.size(); i++)
        {
            stream << bitset<8>(bytes[i]) << ' ';
            if ((i + 1) % 4 == 0)
                stream << endl;
        }
        return stream;
    }
    
    int Address::length() const
    {
        return bytes().size();
    }
    
}

ostream& operator <<(ostream& stream, const ip::Address& address)
{
    return stream << address.str();
}