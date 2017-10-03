/*
 */

/* 
 * File:   tcp.h
 * Author: rnetuka
 *
 * Created on 28. srpna 2016, 21:34
 */

#ifndef TCP_H
#define TCP_H

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <ethernet2.h>
#include <ip.h>
#include <ipv4.h>
#include <ipv6.h>
#include <socket.h>

#include "tcp_packet.h"
#include "tcp_packet_factory.h"


namespace tcp
{

    class ConnectionException : public std::runtime_error
    {
    public:
        ConnectionException(const std::string& message) : std::runtime_error(message) {}
    };
    
    
    
    class Connection : public SequenceHolder
    {
    private:
        sock::RawSocket socket;
        ipv4::Address my_ip_address;
        ipv4::Address their_ip_address;
        int my_port;
        int their_port;

        eth::FrameFactory frame_factory;
        ipv4::DatagramFactory* datagram_factory;
        PacketFactory packet_factory;
        
        long max_data_size;
        long sequence;
        long acknowledgement;
        
        void establish();
        void send(Packet& packet);
        
        bool is_for_me(const ipv4::Datagram& datagram) const;
        bool is_for_me(const Packet& packet) const;
        
        void send_ack();
        
        Packet wait_for_packet(bool (*selector)(const Packet& packet));
        
    public:
        Connection();
        ~Connection();
        
        void open(const ipv4::Address& ip_address, int source_port, int destination_port);
        void open(const ipv4::Address& ip_address, int destination_port);
        void open(const ipv6::Address& ip_address, int source_port, int destination_port);
        void send(const std::string& data);
        Packet receive_packet();
        std::vector<Packet> receive();
        std::vector<byte> receive_bytes();
        void close();
        
        virtual long sequence_number() const override { return sequence; }
        virtual long acknowledgement_number() const override { return acknowledgement; }
    };

}

#endif /* TCP_H */