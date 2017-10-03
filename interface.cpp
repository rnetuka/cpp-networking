/*
 */

#include <fstream>
#include <string>

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <mac.h>

#include "interface.h"

using namespace net;
using namespace std;


const string path = "/sys/class/net/";


Interface::Interface(const string& name) : name_(name), ipv4_address_(nullptr), ipv6_address_(nullptr)
{
    load_ipv4_address();
    load_ipv6_address();
}

Interface::~Interface()
{
    if (ipv4_address_)
        delete ipv4_address_;
    
    if (ipv6_address_)
        delete ipv6_address_;
}

void Interface::load_ipv4_address()
{
    struct ifaddrs* interface_head = nullptr;
    getifaddrs(&interface_head);

    char addressBuffer[INET_ADDRSTRLEN];

    for (struct ifaddrs* interface = interface_head; interface != nullptr; interface = interface->ifa_next) 
    {
        if (! interface->ifa_addr)
            continue;

        if (interface->ifa_addr->sa_family == AF_INET) 
        {                
            string interface_name = interface->ifa_name;

            if (interface_name == name_)
            {
                void* tmpAddrPtr = &((struct sockaddr_in *) interface->ifa_addr)->sin_addr;
                inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            }
        }
    }
    if (interface_head) 
        freeifaddrs(interface_head);

    string address_string = addressBuffer;

    ipv4_address_ = ipv4::Address::parse(address_string);
}

void Interface::load_ipv6_address()
{
    struct ifaddrs* ifAddrStruct = nullptr;
    struct ifaddrs* ifa = nullptr;
    void* tmpAddrPtr = nullptr;
    char addressBuffer[INET6_ADDRSTRLEN];

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != nullptr; ifa = ifa->ifa_next) 
    {
        if (! ifa->ifa_addr)
            continue;
        
        string interface_name = ifa->ifa_name;

        if (interface_name == name_)
        {
            if (ifa->ifa_addr->sa_family == AF_INET6) 
            {
                tmpAddrPtr = &((struct sockaddr_in6 *) ifa->ifa_addr)->sin6_addr;
                inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            }
        }
    }
    if (ifAddrStruct) 
        freeifaddrs(ifAddrStruct);

    string address_string = addressBuffer;

    ipv6_address_ = ipv6::Address::parse(address_string);
}

string Interface::name() const
{
    return name_;
}

bool Interface::up() const
{
    bool up;

    ifstream stream(path + name_ + "/carrier");
    stream >> up;
    stream.close();
    return up;
}

mac::Address Interface::mac_address() const
{
    ifstream stream(path + name_ + "/address");

    string line;
    getline(stream, line);

    stream.close();
    return mac::Address::parse(line);
}

ipv4::Address* Interface::ipv4_address() const
{
    return ipv4_address_;
}

ipv6::Address* Interface::ipv6_address() const
{
    return ipv6_address_;
}

Socket Interface::open_socket() const
{
    return Socket(name_);
}