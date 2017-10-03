/* 
 * File:   address-resolver.h
 * Author: rnetuka
 *
 * Created on 8. listopadu 2016, 17:26
 */

#ifndef ADDRESS_RESOLVER_H
#define ADDRESS_RESOLVER_H

#include <ip/address.h>
#include <mac.h>

namespace net
{
    
    class AddressResolver final
    {
    private:
        mac::Address source_hardware_address;
        std::unique_ptr<ip::Address> source_protocol_address;
        
    public:
        void set_source_hardware_address(const mac::Address& address);
        void set_source_protocol_address(const ip::Address& address);
        
        mac::Address resolve(const ip::Address& address) const;
    };
    
}

#endif

