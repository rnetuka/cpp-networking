#ifndef HTTP_RESPONSE
#define HTTP_RESPONSE

#include <map>
#include <string>

namespace http
{
    using namespace std;

    class Response final
    {
    private:
        string http_version;
        int status_code;
        string reason_phrase;
        
        map<string, string> headers;
        string body;
        string text;
        
        Response() {}

    public:
        int StatusCode() const { return status_code; }
        string HttpVersion() const { return http_version; }
        string ReasonPhrase() const { return reason_phrase; }
        string Header(const string& name) const { return headers.at(name); }
        string Body() const { return body; }
        string String() const { return text; }

        static Response FromString(const string& text);
    };

}

#endif