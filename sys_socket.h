#ifndef SYS_SOCKET
#define SYS_SOCKET

#include <cstdint>
#include <exception>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <vector>


namespace sys
{
    
    class ConnectionException : public std::exception
    {
    private:
        std::string m_message;

    public:
        ConnectionException(const std::string& message) : m_message(message) {}
        virtual ~ConnectionException() throw() {}
        //virtual const char* what() const { return m_message.c_str(); }
    };
 
    

    class Socket
    {
    private:
        int socket_fd;
        std::string interface_name_;
        
    public:
        Socket(const std::string& interface_name);
        
        int file_descriptor() const { return socket_fd; }
        
        void Send(const std::vector<uint8_t>& bytes);
        int Receive(uint8_t* buffer, int buffer_length) const;
    };
    
    
    
    std::string str(const std::vector<uint8_t>& bytes);

}

#endif