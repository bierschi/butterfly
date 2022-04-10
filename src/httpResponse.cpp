
#include "httpResponse.h"

namespace butterfly
{

HTTPResponse::HTTPResponse() : HTTPMSGSchema("Response"), _statusCode(501)
{

}

void HTTPResponse::setStatusCode(size_t statusCode)
{
    _statusCode = statusCode;
}

void HTTPResponse::setReasonPhrase(size_t statusCode)
{
    switch(statusCode){
        case 200:
            _reasonPhrase = "OK";
            break;
        case 201:
            _reasonPhrase = "Created";
            break;
        case 302:
            _reasonPhrase = "Found";
            break;
        case 400:
            _reasonPhrase = "Bad Request";
            break;
        case 403:
            _reasonPhrase = "Forbidden";
            break;
        case 404:
            _reasonPhrase = "Not Found";
            break;
        case 411:
            _reasonPhrase = "Length Required";
            break;
        case 500:
            _reasonPhrase = "Internal Server Error";
            break;
        case 501:
            _reasonPhrase = "Not Implemented";
            break;
        case 502:
            _reasonPhrase = "Bad Gateway";
            break;
        case 505:
            _reasonPhrase = "HTTP Version Not Supported";
            break;
        default:
            _reasonPhrase = "Not Implemented";
            break;
    }

}

void HTTPResponse::parseIncoming()
{
    /*
       Response = Status-Line CRLF
       (Response-Header CRLF)*
       CRLF
       [message-body]
       Status-Line = HTTP/1.0 <space> Status-Code <space> Reason-Phrase CRLF
     */

    size_t parseCursorOld = 0, parseCursorNew = 0;
    size_t headerParseCursorOld, headerParseCursorNew;
    std::string httpProtocol, statusCode, reasonPhrase, responseHeader;
    std::string responseHeaderName, responseHeaderContent;

    // HTTP Protocol
    parseCursorNew = _httpData.find_first_of(" ", parseCursorOld);
    httpProtocol = _httpData.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    parseCursorOld = parseCursorNew+1;

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

    // Status Code
    parseCursorNew = _httpData.find_first_of(" ", parseCursorOld);
    statusCode = _httpData.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    _statusCode = static_cast<size_t>(std::stoi(statusCode));
    parseCursorOld = parseCursorNew+1;

    // Reason Phrase
    parseCursorNew = _httpData.find_first_of(CRLF, parseCursorOld);
    _reasonPhrase = _httpData.substr(parseCursorOld, parseCursorNew - parseCursorOld);
    parseCursorOld = parseCursorNew+1;

    // Skip the CRLF
    parseCursorOld++;

    // Response Headers start here
    while(1)
    {
        parseCursorNew = _httpData.find_first_of(CRLF, parseCursorOld);
        responseHeader = _httpData.substr(parseCursorOld, parseCursorNew - parseCursorOld);
        parseCursorOld = parseCursorNew+1;

        headerParseCursorOld = headerParseCursorNew = 0;
        // Header Name
        headerParseCursorNew = responseHeader.find_first_of(":", headerParseCursorOld);
        responseHeaderName = responseHeader.substr(headerParseCursorOld, headerParseCursorNew - headerParseCursorOld);
        headerParseCursorOld = headerParseCursorNew + 2;

        // Header Content
        headerParseCursorNew = responseHeader.find_first_of(CRLF, headerParseCursorOld);
        responseHeaderContent = responseHeader.substr(headerParseCursorOld, headerParseCursorNew - headerParseCursorOld);
        headerParseCursorOld = headerParseCursorNew;

        setHTTPHeader(responseHeaderName, responseHeaderContent);

        // Skip the CRLF
        parseCursorOld++;

        // Is there another CRLF?
        if ( _httpData.substr(parseCursorOld, 2) == CRLF )
            break;
    }

    parseCursorOld += 2;
    _body = _httpData.substr(parseCursorOld);

}

void HTTPResponse::prepareOutgoing()
{

    std::string protocol;

    switch(_protocol)
    {
        case Protocol::HTTP1_0:
            protocol = "HTTP/1.0";
            break;
        case Protocol::HTTP1_1:
            protocol = "HTTP/1.1";
            break;
        default:
            protocol = "HTTP/1.1";
            break;
    }

    _httpData += protocol + " " + std::to_string(_statusCode) + " " + _reasonPhrase + CRLF;

    for(auto &httpHeader: _httpHeaders)
    {
        _httpData += httpHeader.first + ": " + httpHeader.second + CRLF;
    }

    _httpData += CRLF;

    _httpData += _body;

}

} // namespace butterfly
