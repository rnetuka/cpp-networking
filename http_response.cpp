#include <string>
#include <sstream>

#include "http_response.h"

using namespace std;

namespace http
{
    string HeaderNameFromString(const string& text)
    {
        return text.substr(0, text.find(':'));
    }
    
    string HeaderValueFromString(const string& text)
    {
        string header_value = text.substr(text.find(':') + 1);
            
        int first = header_value.find_first_not_of(" \r\n");
        int last = header_value.find_last_not_of(" \r\n");
        return header_value.substr(first, (last - first + 1));
    }

    Response Response::FromString(const string& text)
    {
        Response response;
        response.text = text;
        
        stringstream stream(text);

        stream >> response.http_version;
        stream >> response.status_code;

        string line;
        getline(stream, line);
        
        response.reason_phrase = line.substr(0, line.find_last_not_of('\r') + 1);
        
        while(true)
        {     
            getline(stream, line);
            if (line.find_first_not_of(" \r\n") == string::npos)
                break;
            
            response.headers.emplace(HeaderNameFromString(line), HeaderValueFromString(line));
        }
        
        response.body = "";
        while(true)
        {     
            getline(stream, line);
            if (line.find_first_not_of("\r\n") == string::npos)
                break;
            
            response.body += line.substr(0, line.find_last_not_of('\r') + 1);
            response.body += '\n';
        }
        return response;
    }

}