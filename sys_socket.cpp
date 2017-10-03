#include <cstdint>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <netinet/ether.h>
#include <linux/if_packet.h>

#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>

#include "socket.h"

using namespace std;
using namespace sys;


Socket::Socket(const string& interface_name) : interface_name_(interface_name)
{
    socket_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (socket_fd < 0)
    {
        cerr << "Failed creating socked" << endl;
        cerr << strerror(errno) << endl;
        throw "Socket exception: ";
    }
}

void Socket::Send(const vector<uint8_t>& bytes)
{
    int length = bytes.size();

    char* buffer = new char[length];
    for (int i = 0; i < length; i++)
        buffer[i] = bytes.at(i);

    struct sockaddr_in dst;
    struct in_addr inaddr = { .s_addr = 3627733411 };
    dst.sin_addr = inaddr;
    dst.sin_family = AF_INET;

    struct ifreq if_idx;
    memset(&if_idx, 0, sizeof(struct ifreq));
    strncpy(if_idx.ifr_name, interface_name_.c_str(), IFNAMSIZ-1);
    if (ioctl(socket_fd, SIOCGIFINDEX, &if_idx) < 0)
        cerr << "SIOCGIFINDEX" << endl;

    struct ifreq ifopts;
    ioctl(socket_fd, SIOCGIFFLAGS, &ifopts);
    ifopts.ifr_flags |= IFF_PROMISC;
    ioctl(socket_fd, SIOCSIFFLAGS, &ifopts);

    struct sockaddr_ll socket_address;
    socket_address.sll_ifindex = if_idx.ifr_ifindex;
    socket_address.sll_halen = ETH_ALEN;

    if (sendto(socket_fd, buffer, length, 0, (struct sockaddr*) &socket_address, sizeof(struct sockaddr_ll)) < 0)
    {
        cerr << "Failed sending data" << endl;
        cerr << strerror(errno) << endl;
        close(socket_fd);
        throw "Socket exception: ";
    }
    delete buffer;
}

int Socket::Receive(uint8_t* buffer, int buffer_length) const
{
    struct sockaddr_ll socket_address;
    socket_address.sll_halen = ETH_ALEN;
    socklen_t addr_len = sizeof socket_address;

    int bytes_read = recvfrom(socket_fd, buffer, buffer_length, 0, 0, 0);

    if (bytes_read == 0)
        throw ConnectionException(string("Connection closed by the server"));

    if (bytes_read < 0)
        throw ConnectionException(string(strerror(errno)));

    return bytes_read;
}

string str(const vector<uint8_t>& bytes)
{
    stringstream stream;
    for (int i = 0; i < bytes.size(); i++)
    {
        stream << bitset<8>(bytes.at(i)) << ' ';

        if ((i + 1) % 4 == 0)
            stream << endl;
    }
    return stream.str();
}
