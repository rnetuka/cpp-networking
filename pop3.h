/* 
 * File:   pop3.h
 * Author: rnetuka
 *
 * Created on 6. září 2016, 15:18
 */

#ifndef POP3_H
#define POP3_H

#include <string>

#include <socket.h>

namespace pop3
{
    static const std::string& USER = "USER";
    static const std::string& PASS = "PASS";
    static const std::string& LIST = "LIST";
    static const std::string& RETR = "RETR";
    static const std::string& DELE = "DELE";
    static const std::string& QUIT = "QUIT";
    
    
    class Connection
    {
    private:
        sock::Socket* socket;
        sock::Connection* tcp_connection;
        
        std::string receive_simple();
        std::string receive_full();
        
    public:
        Connection();
        ~Connection();
        
        std::string open(const std::string& host);
        void close();
        
        std::string command(const std::string& command);
        
        bool opened() const;
    };
    
}

#endif /* POP3_H */