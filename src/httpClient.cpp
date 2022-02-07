
#include "httpClient.h"

namespace butterfly
{

HTTPClient::HTTPClient(unsigned int port) : _port(port), _tcpSocket(std::make_shared<TCPSocket>())
{
    #ifdef LOGGING
    LOG_TRACE("Create class HTTPClient");
    #endif
}

HTTPClient::~HTTPClient()
{
    _tcpSocket->disconnect();
}

std::string HTTPClient::getIpFromUrl(std::string url)
{
    std::string http = "http://";
    size_t pos1 = url.find(http);
    if (pos1 != std::string::npos)
    {
        url.erase(pos1, http.length());
    }
    std::string https = "https://";
    size_t pos2 = url.find(https);

    if (pos2 != std::string::npos)
    {
        url.erase(pos2, https.length());
    }

    size_t pos3 = url.find('/');
    if (pos3 != std::string::npos)
    {
        url.erase(pos3, url.length());
    }

    size_t pos4 = url.find(':');
    if (pos4 != std::string::npos)
    {
        url.erase(pos4, url.length());
    }

    std::string ip;
    TCPSocket::hostnameToIP(url, ip);

    return ip;
}

void HTTPClient::prepareRequest(const std::string &url)
{
    // Create HTTP Request/Response instances
    _httpRequest  = std::unique_ptr<HTTPRequest>(new HTTPRequest());
    _httpResponse = std::unique_ptr<HTTPResponse>(new HTTPResponse());

    // Prepare HTTP Request
    _httpRequest->setURL(url);
    _httpRequest->setMethod(Method::POST);
    _httpRequest->setProtocol(Protocol::HTTP1_1);
    _httpRequest->setHTTPHeader("User-Agent", "butterfly");
    _httpRequest->setHTTPHeader("Content-Type", "application/x-www-form-urlencoded");

    if ( !_httpHeaders.empty() )
    {
        _httpRequest->addHTTPHeaderVector(_httpHeaders);
    }
    if ( !_formParams.empty() )
    {
        _httpRequest->addFormParamVector(_formParams);
    }

    std::string form = _httpRequest->getFormParam();
    _httpRequest->addBody(form);
    _httpRequest->setHTTPHeader("Content-Length", std::to_string(_httpRequest->getBody().length()));
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

    if (_httpResponse->getStatusCode() == 200)
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

void HTTPClient::setFormParam(const std::string &param, const std::string &value)
{
    _formParams.emplace_back(param, value);
}

std::string HTTPClient::post(const std::string &url)
{
    // Prepare the post request
    prepareRequest(url);

    std::string cert;
    std::string ip = getIpFromUrl(url);
    if ( _tcpSocket->connect(ip, static_cast<int>(_port)) )
    {
        #ifdef LOGGING
        LOG_TRACE("Send Post Request to URL " << url);
        #endif
        _tcpSocket->send(_httpRequest->getHTTPData());

        if ( processResponse() )
        {
            cert = _httpResponse->getBody();
            return cert;
        } else
        {
            size_t statuscode = _httpResponse->getStatusCode();
            std::string reasonphrase = _httpResponse->getReasonPhrase();

            #ifdef LOGGING
            LOG_ERROR("Failure on POST Request with StatusCode: " << statuscode << " and Reason: " << reasonphrase);
            #endif

            return cert;
        }

    } else
    {
        #ifdef LOGGING
        LOG_ERROR("Could not connect to " << ip << " on port " << _port);
        #endif
        return cert;
    }
}

} // namespace butterfly
