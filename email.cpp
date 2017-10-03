/*
 */

#include <base64.h>
#include <string>

#include "email.h"
#include "smtp.h"

using namespace std;
using namespace smtp;

string Email::NamedAddress(const string& name, const string& address) const
{
    string result;
    if (! name.empty())
    {
        result += '\"';
        result += name;
        result += '\"';
        result += ' ';
    }
    result += '<';
    result += address;
    result += '>';
    return result;
}

void Email::AddRecipient(const std::string& address)
{
    recipients.push_back(address);
}

void Email::AddCarbonCopy(const std::string& address)
{
    carbon_copies.push_back(address);
}

void Email::AddBlindCarbonCopy(const std::string& address)
{
    blind_carbon_copies.push_back(address);
}

string Email::Sender() const
{
    return NamedAddress(sender_name, sender_address);
}

string Email::ReplyTo() const
{
    return NamedAddress(reply_to_name, reply_to_address);
}

bool Email::HasReplyTo() const
{
    return !reply_to_address.empty();
}

EmailSender& EmailSender::SmtpHost(const string& host)
{
    smtp_host = host;
    return *this;
}

EmailSender& EmailSender::SmtpPort(int port)
{
    smtp_port = port;
    return *this;
}

EmailSender& EmailSender::UserName(const string& username)
{
    this->username = username;
    return *this;
}

EmailSender& EmailSender::Password(const string& password)
{
    this->password = password;
    return *this;
}

void EmailSender::Authenticate(const SmtpConnection& connection)
{
    connection.Send("AUTH LOGIN");
    connection.Send(base64::encode(username));
    connection.Send(base64::encode(password));
}

void EmailSender::Send(const Email& email)
{
    SmtpConnection connection;
    connection.Open(smtp_host, smtp_port);
    connection.Send(EHLO + " email.cz");
    Authenticate(connection);
    connection.Send(MAIL_FROM + '<' + username + '>');
    
    for (const string& recipient : email.Recipients())
        connection.Send(RCPT_TO + '<' + recipient + '>');
    
    for (const string& recipient : email.CarbonCopies())
        connection.Send(RCPT_TO + '<' + recipient + '>');
    
    for (const string& recipient : email.BlindCarbonCopies())
        connection.Send(RCPT_TO + '<' + recipient + '>');
    
    connection.Send(DATA);
    connection.Data("Subject: " + email.Subject());
    connection.Data("From: " + email.Sender());
    
    for (const string& recipient : email.Recipients())
        connection.Data("To: " + recipient);
    
    for (const string& cc : email.CarbonCopies())
        connection.Data("cc: " + cc);
    
    for (const string& bcc : email.BlindCarbonCopies())
        connection.Data("bcc: " + bcc);
    
    if (email.HasReplyTo())
        connection.Data("Reply-To: " + email.ReplyTo());
    
    connection.Data("");
    connection.Data(email.Message());
    connection.Data(".");
    connection.Send(QUIT);
    connection.Close();
}