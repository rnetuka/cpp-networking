/* 
 * File:   ipv6_address.h
 * Author: rnetuka
 *
 * Created on 4. října 2016, 14:32
 */

#ifndef IPV6_ADDRESS_H
#define IPV6_ADDRESS_H

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>


namespace ipv6
{   
    
    class Address final
    {
    private:
        constexpr static int length = 8;
        static const char delimeter = ':';
        
        uint16_t words[length];
        
    public:
        Address(uint16_t word1 = 0, uint16_t word2 = 0, uint16_t word3 = 0, 
                uint16_t word4 = 0, uint16_t word5 = 0, uint16_t word6 = 0,
                uint16_t word7 = 0, uint16_t word8 = 0);
        
        virtual std::string str() const;
        virtual std::vector<uint8_t> bytes() const;
        
        static Address* parse(const std::string& text);
        
        uint16_t operator [](int index) const;
        bool operator ==(const Address& other) const;
        bool operator !=(const Address& other) const;
        
    };
    
}

#endif /* IPV6_ADDRESS_H */