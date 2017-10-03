/*
 */

/* 
 * File:   ftp.h
 * Author: rnetuka
 *
 * Created on 5. září 2016, 15:42
 */

#ifndef FTP_H
#define FTP_H

#include <ostream>
#include <string>

#include "socket.h"

namespace ftp
{
    using namespace std;
    
    class Reply
    {
    private:
        int code_;
        string text_;
        
    public:
        Reply(int code, const string& text) : code_(code), text_(text) {}
        
        int Code() const { return code_; }
        string Text() const { return text_; }
        
        friend std::ostream& operator<<(ostream& stream, const Reply& reply) { return stream << reply.text_; }
    };
    
    class FtpConnection
    {
    private:
        Socket* m_control_socket;
        Connection* m_control_connection;
        Socket* m_data_socket;
        Connection* m_data_connection;
        bool m_log_commands;
        
        string m_host;
        int data_port;
        
        bool Opened() const;
        Reply ReadReply() const;
        
    public:
        FtpConnection() : m_control_socket(nullptr), m_control_connection(nullptr), m_log_commands(false) {}
        ~FtpConnection();
        
        Reply Open(const string& host);
        Reply Send(const string& request);
        void Close();
        void LogCommands(bool log_commands) { m_log_commands = log_commands; }
        
        void Passivate();
    };
    
    string User(const string& username);
    string Pass(const string& password);
    string List();
    string List(const string& path);
    string Pasv();
    string Help();
    string Quit();
}

#endif /* FTP_H */