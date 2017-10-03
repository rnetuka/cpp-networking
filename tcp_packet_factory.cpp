/*
 */

#include <memory>
#include <vector>
#include "tcp_packet_factory.h"

using namespace std;


namespace tcp
{
    
    PacketFactory::PacketFactory() : source_port(0), destination_port(0), sequence_holder(nullptr)
    {
        
    }
    
    void PacketFactory::set_source_port(long port)
    {
        source_port = port;
    }
    
    void PacketFactory::set_destination_port(long port)
    {
        destination_port = port;
    }
    
    void PacketFactory::set_sequence_holder(const SequenceHolder& sequence_holder)
    {
        this->sequence_holder = &sequence_holder;
    }
    
    unique_ptr<Packet> PacketFactory::create_packet() const
    {
        Packet* packet = new Packet;
        packet->set_source_port(source_port);
        packet->set_destination_port(destination_port);
        if (sequence_holder)
        {
            packet->set_sequence_number(sequence_holder->sequence_number());
            packet->set_acknowledgment_number(sequence_holder->acknowledgement_number());
        }
        return auto_ptr<Packet>(packet);
    }
    
    unique_ptr<Packet> PacketFactory::create_packet(vector<byte> data) const
    {
        unique_ptr<Packet> packet = create_packet();
        packet->set_data(data);
        packet->set_ack(true);
        return packet;
    }
    
    unique_ptr<Packet> PacketFactory::create_syn_packet() const
    {
        unique_ptr<Packet> packet = create_packet();
        packet->set_syn(true);
        return packet;
    }
    
    unique_ptr<Packet> PacketFactory::create_ack_packet() const
    {
        unique_ptr<Packet> packet = create_packet();
        packet->set_ack(true);
        return packet;
    }
    
    unique_ptr<Packet> PacketFactory::create_fin_packet() const
    {
        unique_ptr<Packet> packet = create_packet();
        packet->set_fin(true);
        packet->set_ack(true);
        return packet;
    }
    
}