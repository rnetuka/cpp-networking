/* 
 * File:   arp.h
 * Author: rnetuka
 *
 * Created on 4. listopadu 2016, 17:43
 */

#ifndef ARP_H
#define ARP_H

#include <cstdint>
#include <ostream>
#include <memory>
#include <string>
#include <vector>

#include <ip/api.h>
#include <mac.h>


namespace arp
{
    
    enum HardwareType
    {
        Ethernet = 1
    };
    
    
    
    enum ProtocolType
    {
        IPv4 = 0x0800,
        IPv6 = 0x86dd
    };
    
    
    
    enum Operation
    {
        Request = 1, 
        Reply = 2
    };
    
    
    
    class Packet final
    {
    private:
        int hardware_type_;
        int protocol_type_;
        int hardware_address_length_;
        int protocol_address_length_;
        int operation_;
        mac::Address sender_hardware_address_;
        std::unique_ptr<ip::Address> sender_protocol_address_;
        mac::Address target_hardware_address_;
        std::unique_ptr<ip::Address> target_protocol_address_;
        
    public:
        Packet();
        
        void set_hardware_type(int type);
        void set_protocol_type(int type);
        void set_hardware_address_length(int length);
        void set_protocol_address_length(int length);
        void set_operation(Operation operation);
        void set_sender_hardware_address(const mac::Address& address);
        void set_target_hardware_address(const mac::Address& address);
        void set_sender_protocol_address(const ip::Address& address);
        void set_target_protocol_address(const ip::Address& address);
        
        bool request() const;
        bool reply() const;
        mac::Address sender_hardware_address() const;
        mac::Address target_hardware_address() const;
        const ip::Address& sender_protocol_address() const;
        const ip::Address& target_protocol_address() const;
        std::string str() const;
        std::string info() const;
        std::vector<uint8_t> bytes() const;
        
        static Packet parse(const std::vector<uint8_t>& bytes);
    };
    
}

std::ostream& operator <<(std::ostream& stream, const arp::Packet& packet);

#endif /* ARP_H */

