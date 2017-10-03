/* 
 * File:   tcp_packet_factory.h
 * Author: rnetuka
 *
 * Created on 14. října 2016, 0:37
 */

#ifndef TCP_PACKET_FACTORY_H
#define TCP_PACKET_FACTORY_H

#include <memory>
#include <vector>
#include "tcp_packet.h"

namespace tcp
{
    class SequenceHolder
    {
    public:
        virtual long sequence_number() const = 0;
        virtual long acknowledgement_number() const = 0;
    };
    
    
    
    
    class PacketFactory
    {
    private:
        long source_port;
        long destination_port;
        const SequenceHolder* sequence_holder;
        
    public:
        PacketFactory();
        
        void set_source_port(long port);
        void set_destination_port(long port);
        void set_sequence_holder(const SequenceHolder& sequence_holder);
        
        std::unique_ptr<Packet> create_packet() const;
        std::unique_ptr<Packet> create_packet(std::vector<byte> data) const;
        std::unique_ptr<Packet> create_syn_packet() const;
        std::unique_ptr<Packet> create_ack_packet() const;
        std::unique_ptr<Packet> create_fin_packet() const;
    };
    
}

#endif /* TCP_PACKET_FACTORY_H */

