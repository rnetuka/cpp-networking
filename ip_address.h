/* 
 * File:   ip_address.h
 * Author: rnetuka
 *
 * Created on 7. listopadu 2016, 10:11
 */

#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H

#include <cstdint>
#include <memory>
#include <vector>

#include <ip/api.h>

namespace ip
{
    
    std::unique_ptr<Address> new_address(const std::vector<uint8_t>& bytes);
    
}

#endif /* IP_ADDRESS_H */

