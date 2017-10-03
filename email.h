/*
 */

/* 
 * File:   email.h
 * Author: rnetuka
 *
 * Created on 6. září 2016, 17:36
 */

#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include <vector>

#include "smtp.h"

class Email
{
private:
    std::string sender_name;
    std::string sender_address;
    std::string reply_to_name;
    std::string reply_to_address;
    
    std::vector<std::string> recipients;
    std::vector<std::string> carbon_copies;
    std::vector<std::string> blind_carbon_copies;
    
    std::string subject;
    std::string message;
    
    std::string NamedAddress(const std::string& name, const std::string& address) const;
    
public:
    void SetFrom(const std::string& address, const std::string& name = "") { sender_name = name; sender_address = address; }
    void SetSubject(const std::string& subject) { this->subject = subject; }
    void SetMessage(const std::string& message) { this->message = message; }
    void SetReplyTo(const std::string address, const std::string& name = "") { reply_to_name = name, reply_to_address = address; }
    void AddRecipient(const std::string& address);
    void AddCarbonCopy(const std::string& address);
    void AddBlindCarbonCopy(const std::string& address);
    
    std::string SenderName() const { return sender_name; }
    std::string SenderAddress() const { return sender_address; }
    std::string Sender() const;
    std::string ReplyToName() const { return reply_to_name; }
    std::string ReplyToAddress() const { return reply_to_address; }
    std::string ReplyTo() const;
    std::string Subject() const { return subject; }
    std::string Message() const { return message; }
    
    std::vector<std::string> Recipients() const { return recipients; }
    std::vector<std::string> CarbonCopies() const { return carbon_copies; }
    std::vector<std::string> BlindCarbonCopies() const { return blind_carbon_copies; }
    
    bool HasReplyTo() const;
};

class EmailSender
{
private:
    std::string smtp_host;
    int smtp_port;
    std::string username;
    std::string password;
    
    void Authenticate(const smtp::SmtpConnection& connection);
    
public:
    EmailSender() {}
    EmailSender& SmtpHost(const std::string& host);
    EmailSender& SmtpPort(int port);
    EmailSender& UserName(const std::string& username);
    EmailSender& Password(const std::string& password);
    
    void Send(const Email& email);
};

#endif /* EMAIL_H */