/* 
 * File:   ethernet.h
 * Author: rnetuka
 *
 * Created on 3. října 2016, 21:33
 */

#ifndef ETHERNET_H
#define ETHERNET_H

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

#include "mac.h"


namespace eth
{
    
    enum EtherType
    {
        IPv4 = 0x0800, 
        IPv6 = 0x86dd, 
        ARP = 0x0806
    };
    
    
    
    class Frame final
    {
    private:
        mac::Address destination_address_;
        mac::Address source_address_;
        uint16_t ether_type_;
        uint32_t checksum_;
        std::vector<uint8_t> payload_;
        
    public:
        Frame();
        
        void set_source_address(const mac::Address& address);
        void set_destination_address(const mac::Address& address);
        void set_ether_type(int type);
        void set_checksum(int checksum);
        void set_payload(const std::vector<uint8_t>& payload);
        
        mac::Address source_address() const;
        mac::Address destination_address() const;
        uint16_t ether_type() const;
        uint32_t checksum() const;
        std::vector<uint8_t> payload() const;
        std::vector<uint8_t> bytes() const;
        std::string str() const;
        std::string info() const;
        
        static Frame parse(const std::vector<uint8_t>& bytes);
    };
    
    
    
    class FrameFactory final
    {
    private:
        mac::Address source_address;
        mac::Address destination_address;
        uint16_t ether_type;
        
    public:
        FrameFactory();
        
        void set_source_address(const mac::Address& address);
        void set_destination_address(const mac::Address& address);
        void set_ether_type(uint16_t ether_type);
        
        Frame create_frame(const std::vector<uint8_t>& payload) const;
    };
    
}

std::ostream& operator <<(std::ostream& stream, const eth::Frame& frame);

#endif /* ETHERNET_H */

