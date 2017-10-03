/*
 */

/* 
 * File:   dns.h
 * Author: rnetuka
 *
 * Created on 31. října 2016, 11:24
 */

#ifndef DNS_H
#define DNS_H

#include <cstdint>
#include <string>
#include <vector>

#include <ipv4_address.h>
#include <types.h>


namespace dns
{
    
    ipv4::Address resolve(const std::string& hostname);
    
    std::vector<byte> encode(const std::string& hostname);
    
    
    
    enum QuestionType
    {
        ixfr = 251, axfr = 252, mailb = 253, maila = 254, wildcard = 255
    };
    
    
    class Question final
    {
    private:
        std::string name_;
        uint16_t type_;
        uint16_t class_;
        
    public:
        Question(const std::string& encoded_name, uint16_t type);
        
        std::vector<byte> bytes() const;
    };
    
    
    
    class Answer final
    {
        
    };
    
    
    
    class Authority final
    {
        
    };
    
    
    
    class AdditionalInformation final
    {
        
    };
    
    
    
    class Message
    {
    private:
        uint16_t identification;
        uint16_t flags;
        uint16_t question_count;
        uint16_t answer_record_count;
        uint16_t authority_record_count;
        uint16_t additional_record_count;
        
        std::vector<Question> questions;
        std::vector<Answer> answers;
        
    public:
        void add_question(const Question& question);
        
        bool query() const;
        bool reply() const;
        
        std::vector<byte> bytes() const;
    };
    
}

#endif /* DNS_H */

