#include "HTTPFormatter.h"

#include <stdio.h>

HTTPFormatter::HTTPFormatter(void) 
{
	_init();
};

HTTPFormatter::HTTPFormatter(const char *host, const char *document) 
{
	_init();
	fHost = host;
	fDocument = document;
};

void HTTPFormatter::_init(void) 
{
	fHost = "";
	fDocument = "";
	fVersion = "1.1";
	fHeaders.clear();
	fContent = "";
	fDirty = true;
	fFlattened = "";
	fStatus = 0;
	fRequestType = "GET";
};

HTTPFormatter::HTTPFormatter(const char *response, int32_t length) 
{
	_init();
	
	std::string buffer = response;
	std::string line = "";
	
	size_t position = 0;
	size_t seperator = 0;
	std::vector <std::string> tempVect;
	const char *kSeperator = "\r\n";
	const int32_t kSeperatorLen = strlen("\r\n");
	
	
	while ((seperator = buffer.find(kSeperator, position)) != std::string::npos) 
	{
		if (seperator == position) 
		{
			// end of headers, copy rest to content
			fContent = buffer.substr(position + 2, buffer.size() - position - 2);
			break;
		}
		line = buffer.substr(position, seperator - position);
		position = seperator + kSeperatorLen;		
		tempVect.push_back(line);
	}
	
	std::vector<std::string>::iterator i = tempVect.begin();
	line = *i;
	if (line.compare(0, strlen("HTTP/1."),"HTTP/1.") == 0)
	{ // Actual HTTP response. Not present in MSN messages
		seperator = line.find_first_of("/");
		position = line.find_first_of(" ");//, seperator);

		fVersion = line.substr(seperator + 1, position - seperator - 1);
		seperator = line.find_first_of(" ", position + 1);//, seperator + 1);
		if (seperator < 0)
			seperator = line.size();
		
		buffer = line.substr(position + 1, seperator - position - 1);
		
		fStatus = atol(buffer.c_str());
		
		i++;
	} 
	else 
	{
		// Let's suppose this is ok and set the status to 200
		fStatus = 200;
	}
	
	for (; i != tempVect.end(); i++) 
	{
		std::string line = *i;
		if ((seperator = line.find_first_of(": ")) >= 0) 
		{
			std::string name = line.substr(0, seperator);
			std::string value = line.substr(seperator + 2, line.size() - (seperator + 2));			
			fHeaders[name] = value;
		};
	};
}

HTTPFormatter::~HTTPFormatter(void) 
{
	fHeaders.clear();
}

void HTTPFormatter::SetHost(const char *host) 
{
	fDirty = true;
	fHost = host;
}

const char *HTTPFormatter::Host(void) 
{
	return fHost.c_str();
}

void HTTPFormatter::SetDocument(const char *document) 
{
	fDirty = true;
	fDocument = document;
}		

const char *HTTPFormatter::Document(void) 
{
	return fDocument.c_str();
}
					
void HTTPFormatter::SetVersion(const char *version) 
{
	fDirty = true;
	fVersion = version;
}

const char *HTTPFormatter::Version(void) 
{
	return fVersion.c_str();
}

void HTTPFormatter::SetRequestType(const char *request) 
{
	fDirty = true;
	fRequestType = request;
}

const char *HTTPFormatter::RequestType(void) 
{
	return fRequestType.c_str();
}

void HTTPFormatter::AddHeader(const char *name, const char *value) 
{
	fDirty = true;
	fHeaders[name] = value;
}

void HTTPFormatter::ClearHeaders(void) 
{
	fDirty = true;
	fHeaders.clear();
}

std::string HTTPFormatter::HeaderContents(const char *name) 
{
	HeaderMap::iterator i = fHeaders.find(name);
	
	if (i != fHeaders.end()) 
	{
		return i->second;
	} 
	else 
	{
		return "";
	}
}

const char *HTTPFormatter::HeaderNameAt(int32_t index) 
{
	HeaderMap::iterator i = fHeaders.begin();
	for (; index > 0; index--) 
		i++;
//	i += index;
	
	if (i != fHeaders.end()) 
	{
		return i->first.c_str();
	} 
	else 
	{
		return NULL;
	}
}

const char *HTTPFormatter::HeaderAt(int32_t index) 
{
	HeaderMap::iterator i = fHeaders.begin();
	for (; index > 0; index--) 
		i++;
//	i += index;
	
	if (i != fHeaders.end()) 
	{
		return i->second.c_str();
	} 
	else 
	{
		return NULL;
	}
}

void HTTPFormatter::SetContent(const char *content, size_t length) 
{
	fDirty = true;
	fContent = content;
}

void HTTPFormatter::AppendContent(const char *content, size_t length) 
{
	fDirty = true;
	fContent = content;
}

std::string HTTPFormatter::Content(void) 
{
	return fContent;
}

void HTTPFormatter::ClearContent(void) 
{
	fContent = "";
}
		
void HTTPFormatter::Clear(void) 
{
	_init();
}

int32_t HTTPFormatter::Length(void) 
{
	if (fDirty) 
	{
		Flatten();
	}
	
	return fFlattened.size();
}

const char *HTTPFormatter::Flatten(void) 
{
	if (fDirty) 
	{
		fFlattened = fRequestType;
		fFlattened += " " + fDocument + " HTTP/" + fVersion + "\r\n";
		fFlattened += "Host: " + fHost + "\r\n";
		
		HeaderMap::iterator i;
		
		for (i = fHeaders.begin(); i != fHeaders.end(); i++) 
		{
			fFlattened += i->first + ": " + i->second + "\r\n";
		}
		
		fFlattened += "\r\n\r\n";

		fDirty = false;
	}
	
	return fFlattened.c_str();
}

