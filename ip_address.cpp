/*
 */

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <ip/address.h>
#include <ip/api.h>
#include <ipv4/address.h>
#include <ipv6/address.h>

using namespace std;


namespace ip
{
    
    unique_ptr<Address> new_address(const vector<uint8_t>& bytes)
    {
        if (bytes.size() == 4)
        {
            ipv4::Address* address = new ipv4::Address(ipv4::Address::from_bytes(bytes));
            return unique_ptr<Address>(address);
        }
        //else if (bytes.size() == 6)
        else
            throw invalid_argument(string("Cannot create IP address from bytes. Unknown length") + to_string(bytes.size()));
    }
    
}