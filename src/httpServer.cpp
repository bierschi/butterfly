
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

    recvRequest();

    _httpRequest->print();


    processRequest();

    prepareResponse();

    sendResponse();

    return true;
}

int HTTPServer::recvRequest()
{

    std::string data = _newTCPSocket->recvAll(1024);

    if ( !data.empty())
    {
        std::cout <<  data << std::endl;
        _httpRequest->addData(data);
    }
    else
        LOG_ERROR("No Data received!");
    return 0;
}

void HTTPServer::processRequest()
{
    _httpRequest->parse();
    std::cout << "HEader: " << _httpRequest->getHTTPHeader("Connection") << std::endl;

    Method method = _httpRequest->getMethod();
    std::cout << method << std::endl;
}

void HTTPServer::prepareResponse()
{

}

void HTTPServer::sendResponse()
{
    std::string body = "<!DOCTYPE html><html><body><h1>YOU HAVE BEEN HACKED!!!</h1></body></html>";
    std::string test = "HTTP/1.1 302 Found \r\nContent-Type: text/html; charset=utf8 \r\nContent-Length:" + std::to_string(body.length()) + "\r\n\r\n" + body;

    _newTCPSocket->send(test);
}

} // namespace butterfly
