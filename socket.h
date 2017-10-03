/* 
 * File:   socket.h
 * Author: rnetuka
 *
 * Created on 7. listopadu 2016, 23:02
 */

#ifndef NET_SOCKET_H
#define NET_SOCKET_H

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <ethernet.h>
#include <ipv4/datagram.h>
#include <ipv6/datagram.h>
#include <system/socket.h>


namespace net
{
    
    class Socket
    {
    private:
        sys::Socket* system_socket;
        
        std::vector<std::function<bool(const eth::Frame& frame)>> ethernet_filters;
        std::vector<std::function<bool(const ipv4::Datagram& datagram)>> ipv4_filters;
        std::vector<std::function<bool(const ipv6::Datagram& datagram)>> ipv6_filters;
        
    public:
        Socket(const std::string& interface);
        
        void send(const eth::Frame& ethernet_frame);
        
        void add_ethernet_filter(bool (*filter)(const eth::Frame& frame));
        
        eth::Frame receive();
    };
    
}

#endif

