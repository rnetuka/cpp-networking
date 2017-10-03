/*
 */

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "ftp.h"
#include "socket.h"

using namespace std;

namespace ftp
{
    
    FtpConnection::~FtpConnection()
    {
        delete m_control_socket;
        delete m_control_connection;
    }
    
    bool FtpConnection::Opened() const
    {
        return m_control_connection != nullptr;
    }
    
    Reply FtpConnection::Open(const string& host)
    {
        if (Opened())
            throw ConnectionException("Connection is already opened");
        
        m_host = host;
        
        m_control_socket = new Socket();
        m_control_connection = m_control_socket->NewConnection(host, 21);
        return ReadReply();
    }
    
    Reply FtpConnection::Send(const string& request)
    {
        if (! Opened())
            throw ConnectionException("Connection is not opened");
        
        if (m_log_commands)
            cout << request.substr(0, (request.find_last_not_of("\r\n") + 1)) << endl;
        
        m_control_connection->Send(request);
        if (request != "LIST\r\n")
            return ReadReply();
        else
        {        
            Socket* socket = new Socket();
            Connection* connection = socket->NewConnection(m_host, data_port);
            cout << "[DATA]: " << connection->Receive() << endl;
            return Reply(0, "!!!");
        }
    }
    
    Reply FtpConnection::ReadReply() const
    {
        static const int buffer_length = 1024;
        
        string response = "";
        int response_code = 0;
        int bytesReceived = 0;
        bool multi_line = true;

        do 
        {
            char buffer[buffer_length];
            for (int i = 0; i < buffer_length; i++)
                buffer[i] = 0;

            bytesReceived = m_control_connection->Receive(&(buffer[0]), buffer_length);

            response += buffer;

            if (response_code == 0 && response.length() >= 4)
            {
                response_code = stoi(response.substr(0, 3));
                multi_line = (response[3] == '-');
            }

            if (response_code > 0)
                if (multi_line)
                {
                    int i = response.find(response.substr(0, 3) + " ");
                    int j = response.find_last_of("\n");
                    if (i != string::npos && j > i)
                        break;
                }
                else
                {
                    if (response.find("\n") != string::npos)
                        break;
                }
        } 
        while (bytesReceived > 0);
        
        return Reply(response_code, response);
    }
    
    void FtpConnection::Close()
    {
        if (! Opened())
            throw ConnectionException("Connection is not opened");
        
        m_control_socket->Close();
        delete m_control_connection;
    }
    
    void FtpConnection::Passivate()
    {
        Reply reply = Send(Pasv());
        
        if (reply.Code() != 227)
            throw ConnectionException("Couldn't enter passive mode");
        
        string text = reply.Text();
        int i = text.find_first_of('(');
        int j = text.find_last_of(')');
        
        string numbers = text.substr(i + 1, j - i - 1);
        cout << numbers << endl;
        
        stringstream stream(numbers);
        
        vector<string> tokens;
        string token;
        
        while (getline(stream, token, ',')) 
            tokens.push_back(token);
        
        int x = stoi(tokens[4]);
        int y = stoi(tokens[5]);
        
        stringstream hex_stream;
        hex_stream << std::hex;
        hex_stream << x;
        hex_stream << y;
        int port;
        hex_stream >> data_port;
 
        //cout << "x = " << x << ", y = " << y << " [hex " << hex_stream.str() << "] " << port << endl;
    }
    
    string User(const string& username) 
    { 
        return "USER " + username + "\r\n"; 
    }
    
    string Pass(const string& password) 
    { 
        return "PASS " + password + "\r\n"; 
    }
    
    string Pasv()
    {
        return "PASV\r\n";
    }
    
    string List()
    {
        return "LIST\r\n";
    }
    
    string List(const string& path) 
    { 
        return "LIST " + path + "\r\n"; 
    }
    
    string Help()
    {
        return "HELP\r\n";
    }
    
    string Quit()
    {
        return "QUIT\r\n";
    }
    
}