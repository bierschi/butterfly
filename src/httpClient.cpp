
#include "httpClient.h"

namespace butterfly
{

HTTPClient::HTTPClient() : _torport(9050), _torSocketFlag(false), statusCode(0), reasonPhrase("Not Implemented")
{
    #ifdef LOGGING
    LOG_TRACE("Create class HTTPClient");
    #endif

    _tcpSocket = std::make_shared<TCPSocket>();

}

HTTPClient::HTTPClient(const std::string &torip, int torport) : _torip(torip), _torport(torport), _torSocketFlag(true), statusCode(0), reasonPhrase("Not Implemented")
{
    #ifdef LOGGING
    LOG_TRACE("Create class HTTPClient");
    #endif

    _torSocket = std::make_shared<TORSocket>(_torip, _torport);
}

HTTPClient::~HTTPClient()
{
    if (_torSocketFlag)
    {
        _torSocket->disconnect();
    } else
    {
        _tcpSocket->disconnect();
    }
}

void HTTPClient::prepareRequest(const std::string &url, Method method, const std::string &data)
{
    // Create HTTP Request/Response instances
    _httpRequest  = std::unique_ptr<HTTPRequest>(new HTTPRequest());
    _httpResponse = std::unique_ptr<HTTPResponse>(new HTTPResponse());

    std::string route = butterfly::getRouteFromUrl(url);

    // Prepare HTTP Request
    _httpRequest->setURL(url);
    _httpRequest->setRoute(route);
    _httpRequest->setMethod(method);
    _httpRequest->setProtocol(Protocol::HTTP1_1);
    _httpRequest->setHTTPHeader("User-Agent", "butterfly");
    _httpRequest->setHTTPHeader("Content-Type", "application/x-www-form-urlencoded");
    _httpRequest->setHTTPHeader("Host", url);
    _httpRequest->setHTTPHeader("Connection", "close");

    if ( !_httpHeaders.empty() )
    {
        _httpRequest->addHTTPHeaderVector(_httpHeaders);
    }

    _httpRequest->addBody(data);
    _httpRequest->setHTTPHeader("Content-Length", std::to_string(_httpRequest->getBodyLength()));
    _httpRequest->prepareOutgoing();
}

bool HTTPClient::processResponse()
{
    std::string httpData;
    if (_torSocketFlag)
    {
        httpData = _torSocket->recvAll(1024);
    } else
    {
        httpData = _tcpSocket->recvAll(1024, true);
    }

    if ( httpData.empty() )
    {
        return false;
    }

    _httpResponse->addHTTPData(httpData);
    _httpResponse->parseIncoming();

    statusCode = _httpResponse->getStatusCode();
    reasonPhrase = _httpResponse->getReasonPhrase();

    if (statusCode == 200 || statusCode == 302)
    {
        return true;
    } else
    {
        return false;
    }

}

void HTTPClient::setHTTPHeader(const std::string &headerName, const std::string &headerContent)
{
    _httpHeaders.emplace_back(headerName, headerContent);
}

std::string HTTPClient::post(const std::string &url, const std::string &data, int port)
{
    // Prepare the post request
    prepareRequest(url, Method::POST, data);

    std::string response, ip;
    std::string domain = getDomainFromUrl(url);

    _tcpSocket->hostnameToIP(domain, ip);
    if ( _tcpSocket->connect(ip, port) )
    {
        #ifdef LOGGING
        LOG_INFO("Sending post request to url " << url);
        #endif
        _tcpSocket->send(_httpRequest->getHTTPData());

        if ( processResponse() )
        {
            response = _httpResponse->getBody();
            return response;
        } else
        {
            return response;
        }

    } else
    {
        throw ConnectionException("Could not connect to " + url + " on port " + std::to_string(port));
    }
}

std::string HTTPClient::get(const std::string &url, int port)
{
    // Prepare the get request
    prepareRequest(url, Method::GET);

    std::string response, ip;
    std::string domain = butterfly::getDomainFromUrl(url);

    _tcpSocket->hostnameToIP(domain, ip);
    if ( _tcpSocket->connect(ip, port) )
    {
        #ifdef LOGGING
        LOG_INFO("Sending get request to url " << url);
        #endif
        _tcpSocket->send(_httpRequest->getHTTPData());

        if ( processResponse() )
        {
            response = _httpResponse->getBody();
            return response;
        } else
        {
            return response;
        }

    } else
    {
        throw ConnectionException("Could not connect to " + url + " on port " + std::to_string(port));
    }
}

std::string HTTPClient::getTor(const std::string &url, int port)
{
    std::string domain = butterfly::getDomainFromUrl(url);
    // Prepare the get request
    _torSocket->prepareRequest(domain, port);

    prepareRequest(url, Method::GET);

    if ( !_torSocket->send(_httpRequest->getHTTPData(), static_cast<int>(_httpRequest->getHTTPData().length())) )
    {
        throw SocketException("Error at sending the request to the Socket!");
    }

    std::string response;
    if ( processResponse() )
    {
        response = _httpResponse->getBody();
        return response;
    } else
    {
        return response;
    }

}

std::string HTTPClient::postTor(const std::string &url, const std::string &data, int port)
{
    std::string domain = getDomainFromUrl(url);
    // Prepare the post request
    _torSocket->prepareRequest(domain, port);

    prepareRequest(url, Method::POST, data);

    if ( !_torSocket->send(_httpRequest->getHTTPData(), static_cast<int>(_httpRequest->getHTTPData().length())) )
    {
        throw SocketException("Error at sending the request to the Socket!");
    }

    std::string response;
    if ( processResponse() )
    {
        response = _httpResponse->getBody();
        return response;
    } else
    {
        return response;
    }

}

} // namespace butterfly
