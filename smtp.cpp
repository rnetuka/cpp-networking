/*
 */

#include <string>

#include "smtp.h"
#include "socket.h"

using namespace std;

namespace smtp
{
    
    SmtpConnection::SmtpConnection()
    {
        socket = new Socket();
    }
    
    SmtpConnection::~SmtpConnection()
    {
        delete socket_connection;
        delete socket;
    }
    
    string SmtpConnection::Open(const string& host, int port)
    {
        socket_connection = socket->NewConnection(host, port);
        char buffer[1024];
        socket_connection->Receive(&(buffer[0]), 1024);
        string response(buffer);
        return response;
    }
    
    string SmtpConnection::Send(const string& request) const
    {
        socket_connection->Send(request + "\r\n");
        char buffer[1024];
        socket_connection->Receive(&(buffer[0]), 1024);
        string response(buffer);
        return response;
    }
    
    void SmtpConnection::Data(const string& data) const
    {
        socket_connection->Send(data + "\r\n");
    }
    
    void SmtpConnection::Close()
    {
        socket_connection->Close();
        socket->Close();
    }
    
    string helo(const std::string& domain)
    {
        return "HELO " + domain;
    }
    
    string ehlo(const std::string& domain)
    {
        return "EHLO " + domain;
    }
    
    string mail_from(const std::string& from)
    {
        return "MAIL FROM:" + from;
    }
    
    string rcpt_to(const std::string& to)
    {
        return "RCPT TO:" + to;
    }
    
    string data()
    {
        return "DATA";
    }
    
    string quit()
    {
        return "QUIT";
    }
    
}