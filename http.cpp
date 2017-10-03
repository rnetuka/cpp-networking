/*
 */

#include <string>
#include <vector>

#include <dns.h>
#include <tcp.h>
#include <url.h>

#include "http.h"

using namespace dns;
using namespace std;
using namespace tcp;


namespace http
{

    Response send(const Request& request)
    {
        string hostname = request.Header("Host");
        
        tcp::Connection connection;
        connection.open(resolve(hostname), port);
        connection.send(request.String());
        vector<byte> bytes = connection.receive_bytes();
        connection.close();
        
        string received_string;
        Response response = Response::FromString(received_string);
        return response;
    }

    Request AddUrl(Request& request, const Url& url)
    {
        string host = url.Host();
        string path = url.Path();

        if (url.ContainsPort())
            host += ":" + url.Port();
        if (url.ContainsQuery())
            path += "?" + url.Query();
        if (url.ContainsFragment())
            path += "#" + url.Fragment();

        return request.Host(host).Path(path);
    }

    Request Get()
    {
        Request request;
        return request.Method("GET");
    }

    Request Get(const string& url)
    {
        return Get(Url::FromString(url));
    }

    Request Get(const Url& url)
    {
        Request request = Get();
        return AddUrl(request, url);
    }

    Request Post()
    {
        Request request;
        return request.Method("POST");
    }

    Request Post(const string& url)
    {
        return Post(Url::FromString(url));
    }

    Request Post(const Url& url)
    {
        Request request = Post();
        return AddUrl(request, url);
    }

    Request Put()
    {
        Request request;
        return request.Method("PUT");
    }

    Request Put(const string& url)
    {
        return Put(Url::FromString(url));
    }

    Request Put(const Url& url)
    {
        Request request = Put();
        return AddUrl(request, url);
    }

    Request Delete()
    {
        Request request;
        return request.Method("DELETE");
    }

    Request Delete(const string& url)
    {
        return Delete(Url::FromString(url));
    }

    Request Delete(const Url& url)
    {
        Request request = Delete();
        return AddUrl(request, url);
    }

    Request Head()
    {
        Request request;
        return request.Method("HEAD");
    }

    Request Head(const string& url)
    {
        return Head(Url::FromString(url));
    }

    Request Head(const Url& url)
    {
        Request request = Head();
        return AddUrl(request, url);
    }

    Request Options()
    {
        Request request;
        return request.Method("OPTIONS");
    }

    Request Options(const string& url)
    {
        return Options(Url::FromString(url));
    }

    Request Options(const Url& url)
    {
        Request request = Options();
        return AddUrl(request, url);
    }

}