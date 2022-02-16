
#include "httpRequest.h"

namespace butterfly
{

HTTPRequest::HTTPRequest() : HTTPMSGSchema("Request")
{

}

void HTTPRequest::setMethod(Method method)
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

void HTTPRequest::parseIncoming()
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

    // HTTP Method
    parseCursorNew = _httpData.find_first_of(" ", parseCursorOld);
    httpMethod = _httpData.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    parseCursorOld = parseCursorNew + 1;

    if( httpMethod == "GET" )
    {
        _httpMethod = Method::GET;

    } else if ( httpMethod == "HEAD" )
    {
        _httpMethod = Method::HEAD;

    } else if ( httpMethod == "POST" )
    {
        _httpMethod = Method::POST;

    } else if ( httpMethod == "PUT" )
    {
        _httpMethod = Method::PUT;

    } else if ( httpMethod == "DELETE" )
    {
        _httpMethod = Method::DELETE;

    } else if ( httpMethod == "CONNECT" )
    {
        _httpMethod = Method::CONNECT;

    } else
    {
        _httpMethod = Method::NOT_IMPLEMENTED;
    }

    // URL
    parseCursorNew = _httpData.find_first_of(" ", parseCursorOld);
    _url = _httpData.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    parseCursorOld = parseCursorNew + 1;

    //HTTP Protocol
    parseCursorNew = _httpData.find_first_of(CRLF, parseCursorOld);
    httpProtocol = _httpData.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    parseCursorOld = parseCursorNew + 1;

    if ( httpProtocol == "HTTP/1.0" )
    {
        _protocol = Protocol::HTTP1_0;

    } else if ( httpProtocol == "HTTP/1.1" )
    {
        _protocol = Protocol::HTTP1_1;

    } else
    {
        _protocol = Protocol::HTTP_UNSUPPORTED;
    }

    // Skip the CRLF
    parseCursorOld++;

    // Request Headers start here
    while(1){
        parseCursorNew = _httpData.find_first_of(CRLF, parseCursorOld);
        requestHeader = _httpData.substr(parseCursorOld, parseCursorNew - parseCursorOld);
        parseCursorOld = parseCursorNew + 1;

        headerParseCursorOld = headerParseCursorNew = 0;
        // Further parse the request header
        // Header Name
        headerParseCursorNew = requestHeader.find_first_of(":", headerParseCursorOld);
        requestHeaderName = requestHeader.substr(headerParseCursorOld, headerParseCursorNew - headerParseCursorOld);
        headerParseCursorOld = headerParseCursorNew + 2;

        // Header Content
        headerParseCursorNew = requestHeader.find_first_of(CRLF, headerParseCursorOld);
        requestHeaderContent = requestHeader.substr(headerParseCursorOld, headerParseCursorNew - headerParseCursorOld);
        headerParseCursorOld = headerParseCursorNew;

        setHTTPHeader(requestHeaderName, requestHeaderContent);

        // Skip the CRLF
        parseCursorOld++;

        // Is there another CRLF?
        if (_httpData.substr(parseCursorOld, 2) == CRLF)
            break;
    }

    parseCursorOld += 2;
    _body = _httpData.substr(parseCursorOld);
}

void HTTPRequest::prepareOutgoing()
{
    std::string httpMethod, protocol;

    switch(_httpMethod)
    {
        case Method::GET:
            httpMethod = "GET";
            break;
        case Method::HEAD:
            httpMethod = "GET";
            break;
        case Method::POST:
            httpMethod = "POST";
            break;
        case Method::PUT:
            httpMethod = "PUT";
            break;
        case Method::DELETE:
            httpMethod = "DELETE";
            break;
        case Method::CONNECT:
            httpMethod = "CONNECT";
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

    _httpData += httpMethod + " " + _url + " " + protocol + CRLF;

    for(auto it = _httpHeaders.begin(); it != _httpHeaders.end(); it++)
    {
        _httpData += it->first + ": " + it->second + CRLF;
    }

    _httpData += CRLF;

    _httpData += _body;

}

} // namespace butterfly
