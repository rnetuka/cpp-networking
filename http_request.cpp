#include <string>

#include "http_request.h"

using namespace std;

namespace http
{
	Request& Request::Method(const string& method)
	{ 
		m_method = method;
		return *this;
	};

	Request& Request::Path(const string& path)
	{ 
		m_path = path;
		return *this;
	}

	Request& Request::Version(const string& version)
	{
		m_version = version;
		return *this;
	}

	Request& Request::Header(const string& header, const string& value)
	{ 
		m_headers[header] = value;
		return *this;
	}
	Request& Request::Body(const string& body)
	{ 
		m_body = body;
		return *this;
	}

	string Request::String() const
	{
		/*if (m_method.empty())
			throw IncompleteRequestException("Request has no HTTP method");

		if (m_path.empty())
			throw IncompleteRequestException("Request has no path");

		if (m_version.empty())
			throw IncompleteRequestException("Request has no version");

		if (m_headers.at("Host").empty())
			throw IncompleteRequestException("Request has no host");*/

		string result = m_method + " " + m_path + " " + m_version + NEWLINE;
		for (auto it = m_headers.begin(); it != m_headers.end(); it++)
		{
			pair<string, string> header = *it;
			result += (header.first + ": " + header.second + NEWLINE);
		}
		//result += NEWLINE;
		//result += (m_body + NEWLINE);
		result += NEWLINE;
		return result;
	}

}