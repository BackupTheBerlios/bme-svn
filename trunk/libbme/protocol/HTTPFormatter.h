#ifndef HTTPFORMATTER_H
#define HTTPFORMATTER_H

#include <string>
#include <map>
#include <vector>
#include <stdint.h>

typedef std::map<std::string, std::string> HeaderMap;

class HTTPFormatter 
{
	public:
		HTTPFormatter(void);
		HTTPFormatter(const char *host, const char *document);
		HTTPFormatter(const char *response, int32_t length);
		~HTTPFormatter();

		void			SetHost(const char	*host);
		const char		*Host(void);
		
		void			SetDocument(const char *document);
		const char		*Document(void);
					
		void			SetVersion(const char *version);
		const char		*Version(void);
		
		void			SetRequestType(const char *request);
		const char		*RequestType(void);
		
		void			AddHeader(const char *name, const char *value);
		void			ClearHeaders(void);

		std::string		HeaderContents(const char *name);

		int32_t			Headers(void) { return fHeaders.size(); };
		const char		*HeaderNameAt(int32_t index);
		const char		*HeaderAt(int32_t index);

		void			SetContent(const char *content, size_t length);
		void			AppendContent(const char *content, size_t length);
		std::string		Content(void);
		void			ClearContent(void);
		
		void			Clear(void);

		int32_t			Length(void);
		const char		*Flatten(void);
	
		int16_t			Status(void) { return fStatus; };
	
	private:
		void			_init(void);
	
		std::string		fHost;
		std::string		fDocument;
		std::string		fVersion;
		std::string		fRequestType;
		
		HeaderMap		fHeaders;
					
		std::string		fContent;
		int16_t			fStatus;

		bool			fDirty;
		std::string		fFlattened;		
};

#endif
