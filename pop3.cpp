/*
 */

#include <algorithm>
#include <string>

#include "pop3.h"

using namespace std;

namespace pop3
{
    
    const int PORT = 110;
        
    
    Connection::Connection() 
    {
        socket = new sock::Socket;
    }

    
    Connection::~Connection()
    {
        if (opened())
            close();
        
        delete socket;
    }
    
    string Connection::receive_simple()
    {
        string reply;
        char buffer[256];
        while (true)
        {
            tcp_connection->Receive(&(buffer[0]), 256);
            reply += buffer;
            
            if (reply.find("\r\n") != string::npos)
                break;
        }
        return reply;
    }
    
    string Connection::receive_full()
    {
        string reply;
        char buffer[1024];
        while (true)
        {
            tcp_connection->Receive(&(buffer[0]), 1024);
            reply += buffer;
            
            if (reply.find("\r\n.\r\n") != string::npos)
                break;
        }
        return reply;
    }
    
    string Connection::open(const string& host)
    {
        tcp_connection = socket->new_connection(host, PORT);
        return receive_simple();
    }
    
    void Connection::close()
    {
        if (! opened())
            throw "Connection not established";
        
        tcp_connection->Close();
        delete tcp_connection;
        
        //socket->Close();
    }
    
    string Connection::command(const string& command_string)
    {
        if (! opened())
            throw "Connection not established";
        
        tcp_connection->Send(command_string + "\r\n");
        
        //TODO: check lower case also
        //if (transform(command.begin(), command.end(), command.begin(), toupper)
        return (command_string == "LIST" || command_string.find("RETR") != string::npos) 
                ? receive_full()
                : receive_simple();
    }
    
    bool Connection::opened() const
    {
        return tcp_connection != 0;
    }
    
}