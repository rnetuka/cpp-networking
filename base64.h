/* 
 * File:   base64.h
 * Author: rnetuka
 *
 * Created on 6. září 2016, 20:14
 */

#ifndef BASE64_H
#define BASE64_H

#include <string>

namespace base64
{
    
    std::string encode(char a, char b = 0, char c = 0);
    std::string encode(const std::string& text);

    std::string decode(char a, char b, char c, char d);
    std::string decode(const std::string& text);
    
}

#endif /* BASE64_H */