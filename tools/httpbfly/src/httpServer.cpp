
#include "httpServer.h"

namespace tools
{

HTTPServer::HTTPServer(unsigned int port) : _port(port),  _running(false), _tcpSocket(std::make_shared<TCPSocket>()), _newTCPSocket(std::make_shared<TCPSocket>())
{

    _tcpSocket->bind(_port);
    _tcpSocket->listen();
}

HTTPServer::~HTTPServer()
{
    _tcpSocket->disconnect();
}

void HTTPServer::run()
{

    _running = true;

    while(_running)
    {

        // blocking accept call
        _newTCPSocket = _tcpSocket->accept();

        std::thread t(&HTTPServer::handleRequest, this);
        t.join();

        // reset pointer before handle new request
        _newTCPSocket.reset();
    }

}

void HTTPServer::stop()
{
    _running = false;
}

bool HTTPServer::handleRequest()
{
    _httpRequest  = std::unique_ptr<HTTPRequest>(new HTTPRequest());
    _httpResponse = std::unique_ptr<HTTPResponse>(new HTTPResponse());

    // parse incoming data from TCP Socket
    std::string data = _newTCPSocket->recvAll(1024);

    if ( !data.empty() )
    {
        _httpRequest->addHTTPData(data);
        _httpRequest->parseIncoming();

        // process the HTTP request
        processRequest();

        // send the HTTP Response via the TCP Socket
        return sendResponse();
    }
    else
    {
        return false;
    }

}

void HTTPServer::processRequest()
{

    Method m = _httpRequest->getMethod();
    std::string url = _httpRequest->getURL();

    if ( m == Method::GET )
    {
        std::cout << "Handle GET Request" << std::endl;
        if ( url == "/" )
        {
            browserRoute();
        } else
        {
            errorResponse(404);
        }

    } else if ( m == Method::POST )
    {
        std::cout << "Handle POST Request" << std::endl;
        errorResponse(404);
    } else
    {
        errorResponse(500);
    }

    //_httpRequest->print();
}

bool HTTPServer::sendResponse()
{
    return _newTCPSocket->send(_httpResponse->getHTTPData());
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
    _httpResponse->setHTTPHeader("User-Agent", "butterfly");

    _httpResponse->prepareOutgoing();
}

} // namespace tools
