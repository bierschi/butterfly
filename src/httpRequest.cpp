
#include "httpRequest.h"

namespace butterfly
{

HTTPRequest::HTTPRequest() : HTTPSchema()
{

}

void HTTPRequest::setMethod(Method &method)
{
    _httpMethod = method;
}

void HTTPRequest::setURL(const std::string &url)
{
    _url = url;
}

void HTTPRequest::setUserAgent(const std::string &userAgent)
{
    _userAgent = userAgent;
}

int HTTPRequest::parseIncoming()
{
    /*
       Request = Request-Line CRLF
       (Request-Header CRLF)*
       CRLF
       Message-Body
       Request-Line = Method-Name <space> Request-URI <space> HTTP/1.0 CRLF
       Request-Header = Header-Name ":" <space> Header-Content CRLF
     */

    size_t parseCursorOld = 0, parseCursorNew = 0;
    size_t headerParseCursorOld, headerParseCursorNew;
    std::string httpMethod, httpProtocol, requestHeader;
    std::string requestHeaderName, requestHeaderContent;

    /* Parse Request-Line */
    /* HTTP Method */
    parseCursorNew = _data.find_first_of(" ", parseCursorOld);
    httpMethod = _data.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    parseCursorOld = parseCursorNew+1;

    if(httpMethod == "GET")
    {
        _httpMethod = GET;
    }else if(httpMethod == "PUT")
    {
        _httpMethod = PUT;
    }else
    {
        _httpMethod = NOT_IMPLEMENTED;
        return 0;
    }

    /* URL */
    parseCursorNew = _data.find_first_of(" ", parseCursorOld);
    _url = _data.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    parseCursorOld = parseCursorNew+1;

    /* HTTP Protocol */
    parseCursorNew = _data.find_first_of(CRLF, parseCursorOld);
    httpProtocol = _data.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    parseCursorOld = parseCursorNew+1;

    if(httpProtocol == "HTTP/1.0")
    {
        _protocol = HTTP1_0;
    }else if(httpProtocol == "HTTP/1.1")
    {
        _protocol = HTTP1_1;
    }else
    {
        _protocol = HTTP_UNSUPPORTED;
        return 0;
    }

    /* Skip the CRLF */
    parseCursorOld++;

    /* Request Headers start here */
    while(1){
        parseCursorNew = _data.find_first_of(CRLF, parseCursorOld);
        requestHeader = _data.substr(parseCursorOld, parseCursorNew - parseCursorOld);
        parseCursorOld = parseCursorNew+1;

        headerParseCursorOld = headerParseCursorNew = 0;
        /* Further parse the request header */
        /* Header Name */
        headerParseCursorNew = requestHeader.find_first_of(":", headerParseCursorOld);
        requestHeaderName = requestHeader.substr(headerParseCursorOld, headerParseCursorNew - headerParseCursorOld);
        headerParseCursorOld = headerParseCursorNew+2;

        /* Header Content */
        headerParseCursorNew = requestHeader.find_first_of(CRLF, headerParseCursorOld);
        requestHeaderContent = requestHeader.substr(headerParseCursorOld, headerParseCursorNew - headerParseCursorOld);
        headerParseCursorOld = headerParseCursorNew;

        setHTTPHeader(requestHeaderName, requestHeaderContent);

        /* Skip the CRLF */
        parseCursorOld++;

        /* Is there another CRLF? */
        if(_data.substr(parseCursorOld, 2) == CRLF)
            break;
    }

    parseCursorOld+=2;
    _body = _data.substr(parseCursorOld);

    return 0;
}

void HTTPRequest::prepareOutgoing()
{
    std::string httpMethod, protocol;

    switch(_httpMethod)
    {
        case GET:
            httpMethod = "GET";
            break;
        case PUT:
            httpMethod = "PUT";
            break;
        default:
            httpMethod = "GET";
            break;
    }

    switch(_protocol)
    {
        case HTTP1_0:
            protocol = "HTTP/1.0";
            break;
        case HTTP1_1:
            protocol = "HTTP/1.1";
            break;
        default:
            protocol = "HTTP/1.1";
            break;
    }

    _data += httpMethod + " " + _url + " " + protocol + CRLF;

    for(auto it = _httpHeaders.begin(); it!=_httpHeaders.end(); it++)
    {
        _data += it->first + ": " + it->second + CRLF;
    }

    _data += CRLF;

    _data += _body;

}

} // namespace butterfly
