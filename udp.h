/* 
 * File:   udp.h
 * Author: rnetuka
 *
 * Created on 6. září 2016, 15:18
 */

#ifndef UDP_H
#define UDP_H

#include <bitset>
#include <ostream>
#include <string>
#include <vector>

#include <ip.h>
#include <ipv4.h>
#include <ipv6.h>
#include <socket.h>

namespace udp
{
    
    const int PROTOCOL_NUMBER = 17;
    
    
    
    class Data
    {
    private:
        std::vector<byte> bytes_;
        
    public:
        Data(const std::vector<byte>& bytes) : bytes_(bytes) {}
        
        std::vector<byte> bytes() const { return bytes_; }
        std::string as_string() const;
        
        friend std::ostream& operator <<(std::ostream& stream, const Data& data);
    };
    
    
    
    class Packet final : public ip::DataSegment
    {
    private:
        bits_16 source_port_;
        bits_16 destination_port_;
        bits_16 length_;
        bits_16 checksum_;
        std::vector<bits_8> data_;
        
    public:
        Packet();
        
        void set_source_port(long port);
        void set_destination_port(long port);
        void set_length(long length);
        void set_checksum(long checksum);
        void set_data(const std::vector<byte>& data);
        void encapsulate_into(ip::Datagram& datagram);
        
        long source_port() const { return source_port_; }
        long destination_port() const { return destination_port_; }
        long length() const { return length_; }
        long checksum() const { return checksum_; }
        Data data() const;
        
        virtual int protocol_number() const override { return PROTOCOL_NUMBER; }
        virtual std::vector<byte> bytes() const override;
        virtual std::string info() const override;
        
        static Packet parse(byte bytes[], int length);
        
        friend std::ostream& operator <<(std::ostream& stream, const Packet& packet);
    };
    
    
    
    class Sender
    {
    private:
        ip::DatagramFactory* datagram_factory;
        
    public:
        Sender(ip::DatagramFactory* factory) : datagram_factory(factory) {}
        
        Packet send(Packet& packet);
        Packet send(long source_port, long destination_port, const std::string& data);
    };
    
}

#endif /* UDP_H */