
#include "httpClient.h"

namespace tools
{

HTTPClient::HTTPClient(std::shared_ptr<Socket> socket) : statusCode(0), reasonPhrase("Not Implemented")
{
    #ifdef LOGGING
    LOG_TRACE("Create class HTTPClient");
    #endif

    if(socket->type() == Socket::Type::TCPSocket)
    {
        std::cout << "Create tcpsocket" << std::endl;
        _socket = std::dynamic_pointer_cast<TCPSocket>(socket);
    } else
    {
        std::cout << "Create torsocket" << std::endl;
        _socket = std::dynamic_pointer_cast<TORSocket>(socket);
    }

}

HTTPClient::~HTTPClient()
{
    _socket->disconnect();
}

void HTTPClient::prepareRequest(const std::string &url, Method method, const std::string &data)
{
    // Create HTTP Request/Response instances
    _httpRequest  = std::unique_ptr<HTTPRequest>(new HTTPRequest());
    _httpResponse = std::unique_ptr<HTTPResponse>(new HTTPResponse());

    std::string route = tools::getRouteFromUrl(url);

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

    httpData = _socket->recvAll(1024, true);

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
        std::cerr << "Error on request: " << reasonPhrase << ": " << _httpResponse->getBody() << std::endl;
        return false;
    }

}

void HTTPClient::setHTTPHeader(const std::string &headerName, const std::string &headerContent)
{
    _httpHeaders.emplace_back(headerName, headerContent);
}

std::string HTTPClient::post(const std::string &url, const std::string &data, int port)
{
    std::string domain = getDomainFromUrl(url);

    if ( _socket->connect(domain, port) )
    {
        // Prepare the post request
        prepareRequest(url, Method::POST, data);

        _socket->send(_httpRequest->getHTTPData());

        std::string response;
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
    std::string domain = tools::getDomainFromUrl(url);

    if ( _socket->connect(domain, port) )
    {
        // Prepare the get request
        prepareRequest(url, Method::GET);

        int rc = _socket->send(_httpRequest->getHTTPData());
        std::cout << "2 rc: " << rc << " : " << _httpRequest->getHTTPData() << std::endl;

        std::string response;
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

} // namespace butterfly
