
#ifndef BUTTERFLY_HTTPSERVER_H
#define BUTTERFLY_HTTPSERVER_H

#include <memory>

#include "logger.h"
#include "tcpSocket.h"
#include "httpRequest.h"

namespace butterfly
{

class HTTPServer
{

private:
    unsigned int _port;
    bool _running;
    std::shared_ptr<TCPSocket> _TCPSocket, _newTCPSocket;
    std::unique_ptr<HTTPRequest> _httpRequest;

    bool handleRequest();
    int recvRequest();
    void processRequest();
    void prepareResponse();
    void sendResponse();

public:

    /**
     * Constructor HTTPServer
     *
     * Usage:
     *      std::shared_ptr<butterfly::HTTPServer> server = std::make_shared<butterfly::HTTPServer>(8080);
     *      server.run();
     *
     * @param port: Port for the Server
     */
    explicit HTTPServer(unsigned int port=8080);

    /**
     * Destructor HTTPServer
     */
    ~HTTPServer();

    /**
     *
     */
    void run();

    /**
     *
     */
    void stop();

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPSERVER_H
