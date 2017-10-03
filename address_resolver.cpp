/*
 */

#include <arp.h>
#include <ethernet.h>

#include "address-resolver.h"
#include "network.h"
#include "socket.h"

using namespace arp;
using namespace eth;
using namespace net;
using namespace std;


void AddressResolver::set_source_hardware_address(const mac::Address& address)
{
    source_hardware_address = address;
}

void AddressResolver::set_source_protocol_address(const ip::Address& address)
{
    source_protocol_address = ip::new_address(address.bytes());
}

mac::Address AddressResolver::resolve(const ip::Address& address) const
{
    Packet packet;
    if (address.length() == 4)
        packet.set_protocol_type(ProtocolType::IPv4);
    else if (address.length() == 6)
        packet.set_protocol_type(ProtocolType::IPv6);
    packet.set_protocol_address_length(address.length());
    packet.set_operation(Operation::Request);
    packet.set_sender_hardware_address(source_hardware_address);
    packet.set_sender_protocol_address(*source_protocol_address);
    packet.set_target_protocol_address(address);

    Frame frame;
    frame.set_source_address(source_hardware_address);
    frame.set_destination_address(mac::Address::parse("ff:ff:ff:ff:ff:ff"));
    frame.set_ether_type(EtherType::ARP);
    frame.set_payload(packet.bytes());

    Socket socket = default_interface().open_socket();
    socket.add_ethernet_filter([] (const Frame& frame) { return frame.ether_type() == EtherType::ARP; });
    socket.send(frame);
    
    Frame received_frame = socket.receive();
    Packet received_packet = Packet::parse(received_frame.payload());
    return received_packet.target_hardware_address();
}