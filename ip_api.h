/* 
 * File:   ip_api.h
 * Author: rnetuka
 *
 * Created on 3. října 2016, 17:34
 */

#ifndef IP_API_H
#define IP_API_H

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <vector>


namespace ip
{    
    
    class Address
    {
    public:
        int length() const;
        
        virtual std::string str() const = 0;
        virtual std::vector<uint8_t> bytes() const = 0;
    };
    
    
    
    class Datagram
    {
    public:
        virtual ~Datagram() {}
        
        virtual std::vector<uint16_t> pseudo_header() const = 0;
        virtual std::vector<uint8_t> bytes() const = 0;
        
        virtual void set_data(const std::vector<uint8_t>& data) = 0;
        
        virtual std::string str() const = 0;
        virtual std::string info() const = 0;
        
        virtual int length() const = 0;
        virtual int data_protocol() const = 0;
        
        friend std::ostream& operator <<(std::ostream& stream, const Datagram& datagram);
    };
    
    
    
    class DatagramFactory
    {
    public:
        virtual Datagram* create_datagram() const = 0;
    };
    
}

std::ostream& operator <<(std::ostream& stream, const ip::Address& address);

#endif /* IP_API_H */