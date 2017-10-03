/* 
 * File:   ipv4_address.h
 * Author: rnetuka
 *
 * Created on 3. října 2016, 23:17
 */

#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include <ip/api.h>


namespace ipv4
{
    
    class Address final : public ip::Address
    {
    private:
        static constexpr int length = 4;
        static const char delimeter = '.';
        
        uint8_t bytes_[length];
        
    public:
        Address();
        Address(uint32_t i);
        Address(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
        
        uint32_t i() const;
        
        virtual std::string str() const override;
        virtual std::vector<uint8_t> bytes() const override;
        
        int operator >>(int n) const;
        int operator <<(int n) const;
        int operator &(uint32_t n) const;
        int operator |(uint32_t n) const;
        int operator [](int i) const;
        bool operator ==(const Address& other) const;
        bool operator !=(const Address& other) const;
        
        static Address* parse(const std::string& string);
        static Address from_bytes(const std::vector<uint8_t>& bytes);
    };

}

#endif