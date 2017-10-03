#ifndef HTTP_REQUEST
#define HTTP_REQUEST

#include <exception>
#include <map>
#include <string>

namespace http
{   
    using namespace std;

    const string VERSION_1_0 = "HTTP/1.0";
    const string VERSION_1_1 = "HTTP/1.1";

    const string NEWLINE = "\r\n";


    class BadRequestException : public logic_error
    {
    public:
        BadRequestException(const string& message) : logic_error(message) {}
    };

    class Request final
    {
    private:
        string m_method;
        string m_path;
        string m_version;
        map<string, string> m_headers;
        string m_body;

    public:
        Request() : m_path("/"), m_version(VERSION_1_1) {};

        string Method() const { return m_method; }
        string Path() const { return m_path; }
        string Version() const { return m_version; }
        string Header(const string& header) const { return m_headers.at(header); }
        string Body() const { return m_body; }

        Request& Method(const string& method);
        Request& Path(const string& path);
        Request& Version(const string& version);
        Request& Header(const string& header, const string& value);
        Request& Body(const string& body);

        Request& Host(const string& host) { return Header("Host", host); }
        Request& Accept(const string& accept) { return Header("Accept", accept); }
        Request& ContentType(const string& contentType) { return Header("Content-Type", contentType); }

        string String() const;
    };

}

#endif