
#include "httpServer.h"

namespace butterfly
{

HTTPServer::HTTPServer(unsigned int port) : _port(port), _tcpSocket(std::make_shared<TCPSocket>()), _newSocket(std::make_shared<TCPSocket>())
{
    _tcpSocket->bind(_port);
    _tcpSocket->listen();
}

HTTPServer::~HTTPServer()
{
    _tcpSocket->disconnect();
}

int HTTPServer::run()
{
    std::string funcName = "run: ";

    while(1){

        // blocking accept call
        _newSocket = _tcpSocket->accept();

        if(fork() == 0){
            if(handleRequest()){
                std::cerr<<funcName<<"Failed handling request"<<std::endl;
                exit(-1);
            }

            exit(0);

        }

        _newSocket->disconnect();
        _newSocket.reset();
    }

    return 0;
}

bool HTTPServer::handleRequest()
{
    std::cout << "Handle REQUEST!" << std::endl;
    if(recvRequest()){
        std::cerr<<"Receiving request failed"<<std::endl;
        return -1;
    }

    return 0;
}

int HTTPServer::recvRequest()
{

    std::string data = _newSocket->recvAll(1024);

    if ( !data.empty())
        std::cout << "DATA: " << data << std::endl;

    return 0;
}

} // namespace butterfly
