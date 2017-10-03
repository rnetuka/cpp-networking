/*
 */

/* 
 * File:   interface.h
 * Author: rnetuka
 *
 * Created on 7. listopadu 2016, 22:58
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

#include <mac.h>
#include <ipv4/address.h>
#include <ipv6/address.h>

#include <net/socket.h>


namespace net
{
    
    class Interface
    {
    private:
        std::string name_;
        bool up_;
        mac::Address mac_address_;
        ipv4::Address* ipv4_address_;
        ipv6::Address* ipv6_address_;
        
        void load_ipv4_address();
        void load_ipv6_address();
        
    public:
        Interface(const std::string& name);
        ~Interface();
        
        std::string name() const;
        bool up() const;
        mac::Address mac_address() const;
        ipv4::Address* ipv4_address() const;
        ipv6::Address* ipv6_address() const;
        
        Socket open_socket() const;
    };
    
}

#endif /* INTERFACE_H */

