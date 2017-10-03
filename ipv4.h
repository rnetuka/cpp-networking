/* 
 * File:   ipv4.h
 * Author: rnetuka
 *
 * Created on 12. září 2016, 16:18
 */

#ifndef IPV4_H
#define IPV4_H

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include <ip/api.h>
#include <ipv4/address.h>


namespace ipv4
{
    
    class Datagram final : public ip::Datagram
    {
    private:
        uint8_t version_;
        uint8_t ihl_;
        uint8_t dscp_;
        uint8_t ecn_;
        uint16_t total_length_;
        uint16_t identification_;
        uint8_t dont_fragment_;
        uint8_t more_fragments_;
        uint16_t fragment_offset_;
        uint8_t time_to_live_;
        uint8_t protocol_;
        uint16_t header_checksum_;
        Address source_address_;
        Address destination_address_;
        //std::vector<int> options;  
        std::vector<uint8_t> data_;

    public:
        Datagram();
        virtual ~Datagram();
        
        int version() const;
        int ihl() const;
        int dscp() const;
        int ecn() const;
        long total_length() const;
        long identification() const;
        int flags() const;
        bool dont_fragment() const;
        bool more_fragments() const;
        int fragment_offset() const;
        int time_to_live() const;
        long header_checksum() const;
        Address source_address() const;
        Address destination_address() const;
        std::vector<uint8_t> data() const;
        
        void set_dscp(int code_point);
        void set_ecn(int notification);
        void set_total_length(long total_length);
        void set_identification(long identification);
        void set_flags(int flags);
        void set_dont_fragment(bool);
        void set_more_fragments(bool);
        void set_fragment_offset(int offset);
        void set_time_to_live(int time_to_live);
        void set_data_protocol(int protocol);
        void set_source_address(const Address& address);
        void set_destination_address(const Address& address);
        void calculate_checksum();
      
        virtual std::vector<uint8_t> bytes() const override;
        virtual std::vector<uint16_t> pseudo_header() const override;
        virtual void set_data(const std::vector<uint8_t>& bytes) override;
        virtual std::string str() const override;
        virtual std::string info() const override;
        virtual int length() const override;
        virtual int data_protocol() const override { return protocol_; }
        
        static std::unique_ptr<Datagram> parse(uint8_t bytes[], int length);
        static std::unique_ptr<Datagram> parse(const std::vector<uint8_t>& bytes);
        
        friend int checksum(const Datagram& header);
    };
    
    
    
    class DatagramFactory : public ip::DatagramFactory
    {
    private:
        Address source_address;
        Address destination_address;
        int data_protocol;
        int time_to_live;
        mutable int identification;
        bool allow_fragmentation_;
        
    public:
        DatagramFactory();
        
        void set_source_address(const Address& address) { source_address = address; }
        void set_destination_address(const Address& address) { destination_address = address; }
        void set_data_protocol(int protocol) { data_protocol = protocol; }
        void set_time_to_live(int time) { time_to_live = time; }
        void set_allow_fragmentation(bool allow) { allow_fragmentation_ = allow; }
        
        virtual ip::Datagram* create_datagram() const override;
    };
    
}

#endif /* IPV4_H */