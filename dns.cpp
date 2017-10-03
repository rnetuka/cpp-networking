/*
 */

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <ipv4_address.h>
#include <types.h>

#include "dns.h"

using namespace std;


namespace dns
{
    
    Question::Question(const string& name, uint16_t type) : name_(name), type_(type), class_(1)
    {
        
    }
    
    vector<byte> Question::bytes() const
    {
        vector<byte> bytes;
        //bytes.push_back();
        //bytes.push_back();
        return bytes;
    }
    
    void Message::add_question(const Question& question)
    {
        
    }
    
    bool Message::query() const
    {
        
    }
    
    bool Message::reply() const
    {
        
    }
    
    ipv4::Address resolve(const string& hostname)
    {
        ipv4::Address address("216.58.209.163");
        return address;
    }
    
    vector<byte> encode(const string& hostname)
    {
        stringstream stream(hostname);
        vector<string> tokens;
        string token;
        while (std::getline(stream, token, '.'))
            tokens.push_back(token);
     
        vector<byte> result;
        
        for (const string& part : tokens)
        {
            result.push_back(part.length());
            for (char character : part)
                result.push_back(character);
        }
        
        result.push_back(0);
        return result;
    }
    
}