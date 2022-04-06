
#include "httpClient.h"

namespace tools
{

HTTPClient::HTTPClient() : _tcpSocket(std::make_shared<TCPSocket>()), statusCode(0), reasonPhrase("Not Implemented")
{

}

HTTPClient::~HTTPClient()
{
    _tcpSocket->disconnect();
}

void HTTPClient::prepareRequest(const std::string &url, Method method, const std::string &data)
{
    // Create HTTP Request/Response instances
    _httpRequest  = std::unique_ptr<HTTPRequest>(new HTTPRequest());
    _httpResponse = std::unique_ptr<HTTPResponse>(new HTTPResponse());

    // Prepare HTTP Request
    _httpRequest->setURL(url);
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

    std::string httpData = _tcpSocket->recvAll(1024, true);

    if ( httpData.empty() )
    {
        return false;
    }

    _httpResponse->addHTTPData(httpData);
    _httpResponse->parseIncoming();

    statusCode = _httpResponse->getStatusCode();
    reasonPhrase = _httpResponse->getReasonPhrase();

    if (statusCode == 200)
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
    prepareRequest(url,Method::GET);

    std::string response, ip;
    std::string domain = getDomainFromUrl(url);

    _tcpSocket->hostnameToIP(domain, ip);
    if ( _tcpSocket->connect(ip, port) )
    {

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

} // namespace tools
