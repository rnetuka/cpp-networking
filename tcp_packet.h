/* 
 * File:   tcp_packet.h
 * Author: rnetuka
 *
 * Created on 14. října 2016, 0:37
 */

#ifndef TCP_PACKET_H
#define TCP_PACKET_H

#include <cstdint>
#include <bitset>
#include <map>
#include <string>
#include <vector>
#include <ip.h>

#include <types.h>


namespace tcp
{
    
    const int PROTOCOL_NUMBER = 6;
    
    
    
    /*struct Option
    {
        Option(int kind, int length, bool syn_packet_only_ = false) : kind_(kind), length_(length), syn_packet_only_(syn_packet_only_) {}
        int kind_;
        int length_;
        bool syn_packet_only_;
    } 
    maximum_segment_size(2, 4, true), 
    window_scale(3, 3, true),
    selective_acknowledgement_permitted(4, 2);*/
    
    
    enum Flags
    {
        NS, CWR, ECE, URG, ACK, PST, RST, SYN, FIN
    };
    
    
    
    enum Options
    {
        MAXIMUM_SEGMENT_SIZE = 2,
        WINDOW_SCALE = 3,
    };
    
    
    
    class Packet
    {
    private:
        bits_16 source_port_;
        bits_16 destination_port_;
        bits_32 sequence_number_;
        bits_32 acknowledgment_number_;
        bits_4 data_offset_;
        bits_1 ns_;
        bits_1 cwr_;
        bits_1 ece_;
        bits_1 urg_;
        bits_1 ack_;
        bits_1 psh_;
        bits_1 rst_;
        bits_1 syn_;
        bits_1 fin_;
        bits_16 window_size_;
        bits_16 checksum_;
        bits_16 urgent_pointer_;
        std::map<int, unsigned int> options_;
        std::vector<byte> data_;
        
    public:
        Packet();
        
        uint16_t source_port() const;
        uint16_t destination_port() const;
        uint32_t sequence_number() const;
        uint32_t acknowledgment_number() const;
        int data_offset() const;
        std::bitset<9> flags() const;
        bool ns() const;
        bool cwr() const;
        bool ece() const;
        bool urg() const;
        bool ack() const;
        bool psh() const;
        bool rst() const;
        bool syn() const;
        bool fin() const;
        long window_size() const;
        long checksum() const;
        long urgent_pointer() const;
        bool contains_option(int option) const;
        unsigned int option(int option) const;
        std::vector<byte> data() const;
        int header_size() const;
        int data_size() const;
        int size() const;
        
        void set_source_port(long port);
        void set_destination_port(long port);
        void set_sequence_number(long long number);
        void set_acknowledgment_number(long long number);
        void set_data_offset(int offset);
        void set_flags(int flags);
        void set_ns(bool ns);
        void set_cwr(bool cwr);
        void set_ece(bool ece);
        void set_urg(bool urg);
        void set_ack(bool ack);
        void set_psh(bool psh);
        void set_rst(bool rst);
        void set_syn(bool syn);
        void set_fin(bool finish);
        void set_finish(bool finish) { set_fin(finish); }
        void set_window_size(long size);
        void set_checksum(long checksum);
        void set_urgent_pointer(long pointer);
        void set_option(int option, unsigned int value);
        void set_data(const std::vector<byte>& data);
        
        void encapsulate_into(ip::Datagram& datagram);
        
        std::string str() const;
        std::string info() const;
        std::vector<byte> bytes() const;
        
        static Packet parse(const std::vector<byte>& bytes);
        
        friend int calculate_checksum(const Packet& packet, const ip::Datagram& ip_datagram);
    };
}

#endif /* TCP_PACKET_H */

