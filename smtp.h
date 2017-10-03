/*
 */

/* 
 * File:   smtp.h
 * Author: rnetuka
 *
 * Created on 6. září 2016, 15:18
 */

#ifndef SMTP_H
#define SMTP_H

#include <string>

#include "socket.h"

namespace smtp
{
    const int PORT = 25;
    
    class SmtpConnection
    {
    private:
        Socket* socket;
        Connection* socket_connection;
        
    public:
        SmtpConnection();
        ~SmtpConnection();
        
        std::string Send(const std::string& request) const;
        void Data(const std::string& data) const;
        
        std::string Open(const std::string& host, int port = PORT);
        void Close();
    };
    
    const std::string HELO = "HELO";
    const std::string EHLO = "EHLO";
    const std::string MAIL_FROM = "MAIL FROM:";
    const std::string RCPT_TO = "RCPT TO:";
    const std::string DATA = "DATA";
    const std::string QUIT = "QUIT";
    
}

#endif /* SMTP_H */