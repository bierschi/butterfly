
#ifndef BUTTERFLY_HTTPSERVER_H
#define BUTTERFLY_HTTPSERVER_H

#include <memory>

#include "tcpSocket.h"

namespace butterfly
{

class HTTPServer
{

private:
    unsigned int _port;
    std::shared_ptr<TCPSocket> _tcpSocket, _newSocket;

public:

    /**
     *
     * @param port
     */
    explicit HTTPServer(unsigned int port);

    /**
     *
     */
    ~HTTPServer();
    
    int run();
    bool handleRequest();
    int recvRequest();
};

} // namespace butterfly

#endif //BUTTERFLY_HTTPSERVER_H
