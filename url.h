#ifndef URL_H
#define URL_H

#include <string>

// scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]

class Url final
{
private:
    std::string scheme;
    std::string username;
    std::string password;
    std::string host;
    std::string ipv4_address;
    std::string ipv6_address;
    std::string port;
    std::string path;
    std::string query;
    std::string fragment;

    Url() {}
public:
    std::string Scheme() const { return scheme; }
    std::string UserName() const { return username; }
    std::string Password() const { return password; }
    std::string Host() const { return host; }
    std::string Port() const { return port; }
    std::string Path() const { return path; }
    std::string Query() const { return query; }
    std::string Fragment() const { return fragment; }

    bool ContainsPort() const { return !port.empty(); }
    bool ContainsQuery() const { return !query.empty(); }
    bool ContainsFragment() const { return !fragment.empty(); }

    static Url FromString(const std::string& string);
};

#endif