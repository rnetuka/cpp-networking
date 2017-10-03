/* 
 * File:   ipv6.h
 * Author: rnetuka
 *
 * Created on 12. září 2016, 18:30
 */

#ifndef IPV6_H
#define IPV6_H

#include <cstdint>
#include <vector>

#include <ip/api.h>
#include <ipv6/address.h>

namespace ipv6
{
    
    class Datagram : public ip::Datagram
    {
    private:
        uint8_t version_;
        uint8_t traffic_class_;
        uint32_t flow_label_;
        uint16_t payload_length_;
        uint8_t next_header_;
        uint8_t hop_limit_;
        Address source_address_;
        Address destination_address_;
        std::vector<uint8_t> data_;
        
    public:
        virtual ~Datagram() {}
        
        virtual std::vector<uint16_t> pseudo_header() const = 0;
        virtual std::vector<uint8_t> bytes() const = 0;
        virtual void set_data(const std::vector<uint8_t>& bytes) = 0;
        virtual std::string str() const = 0;
        virtual std::string info() const = 0;
        virtual int length() const = 0;
        virtual int data_protocol() const = 0;
    };
    
}

#endif /* IPV6_H */

