
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

void HTTPServer::run()
{
    LOG_INFO("Run HTTPServer on port " << _port);
    _running = true;

    while(_running){

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
    _httpRequest = std::unique_ptr<HTTPRequest>(new HTTPRequest());
    _httpResponse = std::unique_ptr<HTTPResponse>(new HTTPResponse());

    // parse incoming data from TCP Socket
    if ( recvRequest() )
    {
        // process the http request
        processRequest();

        // prepare the actual HTTP Response message
        prepareResponse();

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

    if ( !data.empty())
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

    //_httpRequest->print();
}

void HTTPServer::prepareResponse()
{

    _httpResponse->setProtocol(HTTP1_1);
    _httpResponse->setStatusCode(302);
    _httpResponse->setReasonPhrase(_httpResponse->getStatusCode());
    _httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");
    _httpResponse->addBody("<!DOCTYPE html><html><body><h1>YOU HAVE BEEN HACKED!!!</h1></body></html>");
    _httpResponse->setHTTPHeader("Content-Length", std::to_string(_httpResponse->getBody().length()));

    _httpResponse->prepareOutgoing();

}

bool HTTPServer::sendResponse()
{

    return _newTCPSocket->send(_httpResponse->getHTTPData());
}

} // namespace butterfly
