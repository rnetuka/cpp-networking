/* 
 * File:   ip.h
 * Author: rnetuka
 *
 * Created on 21. října 2016, 9:15
 */

#ifndef IP_H
#define IP_H

#include <cstdint>
#include <memory>

#include <ip/api.h>


namespace ip
{
    
    std::unique_ptr<Datagram> parse(uint8_t bytes[], int length);
    
}

#endif /* IP_H */

