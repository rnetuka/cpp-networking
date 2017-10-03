/*
 */

#include <memory>

#include "ip.h"
#include "ipv4.h"
#include "ipv6.h"

using namespace std;


namespace ip
{
    
    unique_ptr<Datagram> parse(uint8_t bytes[], int length)
    {
        int version = bytes[0] >> 4;
        if (version == 4)
            return ipv4::Datagram::parse(bytes, length);
        else
            return unique_ptr<Datagram>(nullptr);
    }
    
}