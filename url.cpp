#include <string>

#include "url.h"

using namespace std;


Url Url::FromString(const string& str) 
{
    string remaining = str;

    string scheme;
    string username;
    string password;
    string host;
    string ipv4_address;
    string ipv6_address;
    string port;
    string path;
    string query;
    string fragment;

    int i, j;

    // scheme
    if (remaining.find("//") == 0)
        remaining = remaining.substr(2);

    else if ((i = remaining.find(":")) != string::npos) 
    {
        scheme = remaining.substr(0, i);
        remaining = remaining.substr(scheme.length() + 1);

        if (remaining.find("//") == 0)
            remaining = remaining.substr(2);
    }

    // user:password@
    if ((i = remaining.find(":")) != string::npos
            && (j = remaining.find("@")) != string::npos
            && (i < j)) 
    {
        username = remaining.substr(0, i);
        remaining = remaining.substr(i + 1);

        j = remaining.find("@");

        password = remaining.substr(0, j);
        remaining = remaining.substr(j + 1);
    }
    
    // IP address
    //if (remaining.find("[")) != string::npos

    // :port
    if ((i = remaining.find(":")) != string::npos) 
    {
        host = remaining.substr(0, i);
        remaining = remaining.substr(i + 1);

        if ((i = remaining.find("/")) != std::string::npos) 
        {
            port = remaining.substr(0, i);
            remaining = remaining.substr(i);
        } else if ((i = remaining.find("?")) != std::string::npos) 
        {
            port = remaining.substr(0, i);
            remaining = remaining.substr(i);
        } else if ((i = remaining.find("#")) != std::string::npos) 
        {
            port = remaining.substr(0, i);
            remaining = remaining.substr(i);
        } else 
        {
            port = remaining;
            remaining = "";
        }
    } else 
    {
        if ((i = remaining.find("/")) != std::string::npos) 
        {
            host = remaining.substr(0, i);
            remaining = remaining.substr(i);
        } 
        else if ((i = remaining.find("?")) != std::string::npos) 
        {
            host = remaining.substr(0, i);
            remaining = remaining.substr(i);
        } 
        else if ((i = remaining.find("#")) != std::string::npos) 
        {
            host = remaining.substr(0, i);
            remaining = remaining.substr(i);
        } 
        else 
        {
            host = remaining;
            remaining = "";
        }
    }

    // /path
    if (remaining.find("/") == 0) 
    {
        if ((i = remaining.find("?")) != std::string::npos) 
        {
            path = remaining.substr(0, i);
            remaining = remaining.substr(i);
        } 
        else if ((i = remaining.find("#")) != std::string::npos) 
        {
            path = remaining.substr(0, i);
            remaining = remaining.substr(i);
        } 
        else 
        {
            path = remaining;
            remaining = "";
        }
    } 
    else
        path = "/";

    // ?query
    if (remaining.find("?") == 0) 
    {
        if ((i = remaining.find("#")) != std::string::npos) 
        {
            query = remaining.substr(1, i - 1);
            remaining = remaining.substr(i);
        } 
        else 
        {
            query = remaining;
            remaining = "";
        }
    }

    // #fragment
    if (remaining.find("#") == 0)
        fragment = remaining;

    Url url;
    url.scheme = scheme;
    url.username = username;
    url.password = password;
    url.host = host;
    url.port = port;
    url.path = path;
    url.query = query;
    url.fragment = fragment;
    return url;
}