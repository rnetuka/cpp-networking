#ifndef HTTP_ALL
#define HTTP_ALL

#include <string>
#include <url.h>

#include "http_request.h"
#include "http_response.h"

namespace http
{
    const int port = 80;
    
    Response send(const Request& request);

    Request Get();
    Request Get(const std::string& url);
    Request Get(const Url& url);

    Request Post();
    Request Post(const std::string& url);
    Request Post(const Url& url);

    Request Put();
    Request Put(const std::string& url);
    Request Put(const Url& url);

    Request Delete();
    Request Delete(const std::string& url);
    Request Delete(const Url& url);

    Request Head();
    Request Head(const std::string& url);
    Request Head(const Url& url);

    Request Options();
    Request Options(const std::string& url);
    Request Options(const Url& url);
}

#endif