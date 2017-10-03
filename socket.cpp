/*
 */

#include <cstdint>
#include <string>
#include <vector>

#include <ethernet.h>
#include <sys/socket.h>

#include "socket.h"

using namespace eth;
using namespace net;
using namespace std;


Socket::Socket(const string& interface)
{
    system_socket = new sys::Socket(interface);
}

void Socket::send(const Frame& ethernet_frame)
{
    system_socket->Send(ethernet_frame.bytes());
}
        
Frame Socket::receive()
{
    constexpr int buffer_size = 2000;
    
    uint8_t buffer[buffer_size];
    int n = system_socket->Receive(buffer, 2000);
            
    vector<uint8_t> bytes;
    for (int i = 0; i < n; i++)
        bytes.push_back(buffer[i]);
            
    Frame ethernet_frame = Frame::parse(bytes);
    
    
    return ethernet_frame;
}

void Socket::add_ethernet_filter(bool (*filter)(const Frame& frame))
{
    
}