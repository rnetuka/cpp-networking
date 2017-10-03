/*
 */

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <vector>

#include <arp.h>
#include <base64.h>
#include <socket.h>
#include <tcp.h>
#include <ip.h>
#include <ipv4.h>
#include <ipv6.h>
#include <system.h>

//using namespace ftp;
/*using namespace std;
using namespace tcp;
using namespace http;*/
//using namespace pop3;
using namespace std;
using namespace sys;


int main()
{
    
    //cout << "Packet:" << endl;
    //cout << packet.SYN << endl;
    //cout << packet.ACK << endl;
    
    /*Request request = Get("www.seznam.cz").Accept("text/html");
    Response response = Send(request);
    cout << response.StatusCode() << ' ' << response.ReasonPhrase() << endl;
    cout << response.Header("Content-Type") << endl;
    cout << response.Body() << endl;*/
    //cout << endl << "---" << endl;
    //cout << response.String() << endl;
    
    
    /*ftp::FtpConnection connection;
    connection.LogCommands(true);
    cout << connection.Open("ftp.linux.cz") << endl;
    cout << connection.Send(ftp::User("anonymous")) << endl;
    cout << connection.Send(ftp::Pass("rnetuka@redhat.com")) << endl;
    connection.Passivate();
    cout << connection.Send(ftp::Help()) << endl;
    cout << connection.Send(ftp::Pasv()) << endl;
    cout << connection.Send(ftp::List()) << endl;
    cout << connection.Send("QUIT\r\n") << endl;*/
    
    /*smtp::SmtpConnection smtpConnection;
    cout << smtpConnection.Open("smtp.seznam.cz") << endl;
    cout << smtpConnection.Send("EHLO email.cz") << endl;
    cout << smtpConnection.Send("AUTH LOGIN") << endl;
    cout << smtpConnection.Send(base64::encode("radovan.netuka@email.cz"));
    cout << smtpConnection.Send(base64::encode("karigane"));
    cout << smtpConnection.Send("MAIL FROM: <radovan.netuka@email.cz>") << endl;
    cout << smtpConnection.Send("RCPT TO: <rnetuka@redhat.com>") << endl;
    cout << smtpConnection.Send("DATA") << endl;
    smtpConnection.Data("Subject: Test of SMTP");
    smtpConnection.Data("From: \"Radovan Netuka\" <radovan.netuka@email.cz>");
    smtpConnection.Data("To: rnetuka@redhat.com");
    smtpConnection.Data("");
    smtpConnection.Data("Hi, this email was sent");
    smtpConnection.Data("from my C++ program");
    smtpConnection.Data(".");
    cout << smtpConnection.Send("QUIT") << endl;
    smtpConnection.Close();*/
    
    /*Email email;
    email.SetFrom("radovan.netuka@email.cz", "Radovan Netuka");
    email.SetReplyTo("radovan.netuka2@email.cz");
    email.AddRecipient("rnetuka@redhat.com");
    email.AddCarbonCopy("radovan.netuka@email.cz");
    email.AddBlindCarbonCopy("desmond.ol@email.cz");
    email.SetSubject("Test2");
    email.SetMessage("Hi, this email was sent\nfrom my C++ program");
    
    EmailSender sender;
    sender.SmtpHost("smtp.seznam.cz");
    sender.SmtpPort(25);
    sender.UserName("radovan.netuka@email.cz");
    sender.Password("karigane");
    sender.Send(email);*/
    
    /*pop3::Connection connection;
    cout << connection.Open("pop3.seznam.cz") << endl;
    cout << connection.Command("USER desmond.ol@email.cz") << endl;
    cout << connection.Command("PASS aikamiura") << endl;
    cout << connection.Command("LIST") << endl;
    cout << connection.Command("RETR 4");
    cout << connection.Command("QUIT");*/
    
    /*udp::packet udp_packet;
    cout << udp_packet.source_port << endl;
    
    udp::UdpConnection connection;
    connection.open(ipv4::Address("10.0.0.138"));
    connection.close();*/
    
    
    cout << endl;
    cout << "***" << endl;
    cout << "Ethernet cable: " << ethernet_device_up() << endl;
    cout << "Wi-Fi: " << wifi_device_up() << endl;
    cout << "My IPv4 address: " << ipv4::my_address() << endl;
    cout << "My IPv6 address: " << ipv6::my_address() << endl;
    cout << "My MAC address: " << mac_address() << endl;
    cout << endl;
    
    arp::AddressResolver address_resolver;
    address_resolver.
    cout << "Router's MAC address: " << address_resolver.resolve(ipv4::Address("192.168.0.1"));
    
    /*tcp::Connection connection;
    connection.open(ipv4::Address("216.58.209.163"), 18002, 80);
    connection.send("GET / HTTP/1.1\r\nHost: www.google.cz\r\nAccept: text/html\r\n\r\n");
    
    vector<byte> received_bytes = connection.receive_bytes();
    cout << "Received " << received_bytes.size() << " bytes of HTTP response" << endl;
    connection.close();
    
    char* buffer = new char[received_bytes.size() + 1];
    for (int i = 0; i < received_bytes.size(); i++)
        buffer[i] = received_bytes[i];
    buffer[received_bytes.size()] = '\0';
    
    cout << buffer << endl;*/
    return 0;
}