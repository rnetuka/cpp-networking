/* 
 * File:   mac.h
 * Author: rnetuka
 *
 * Created on 3. října 2016, 21:43
 */

#ifndef MAC_H
#define MAC_H

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace mac
{
    
    class Address final
    {
    private:
        static constexpr int length = 6;
        static constexpr char delimeter = ':';

        uint8_t bytes_[length];

    public:
        Address(uint64_t i = 0);
        Address(const std::vector<uint8_t>& bytes);

        std::string str() const;
        std::vector<uint8_t> bytes() const;

        uint8_t operator [](int i) const;
        bool operator ==(const Address& other) const;
        bool operator !=(const Address& other) const;

        static Address parse(const std::string& text);
    };

}

std::ostream& operator <<(std::ostream& stream, const mac::Address& address);

#endif /* MAC_H */