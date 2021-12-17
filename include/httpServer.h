
#ifndef BUTTERFLY_HTTPSERVER_H
#define BUTTERFLY_HTTPSERVER_H

#include <memory>
#include <functional>

#include "logger.h"
#include "tcpSocket.h"
#include "httpRequest.h"
#include "httpResponse.h"

namespace butterfly
{

/**
 * Class HTTPServer to support incoming HTTP Requests and outgoing HTTP Responses
 */
class HTTPServer
{

private:
    unsigned int _port;
    bool _running;
    std::shared_ptr<TCPSocket> _TCPSocket, _newTCPSocket;
    std::unique_ptr<HTTPRequest> _httpRequest;
    std::unique_ptr<HTTPResponse> _httpResponse;
    std::function<void(std::string)> _masterPKeyCB;

    /**
     * Handles incoming requests to the http server
     *
     * @return True if the request could be handled, else False
     */
    bool handleRequest();

    /**
     * Receive the actual request from the TCP Socket
     *
     * @return True if data is available on the TCP Socket, else False
     */
    bool recvRequest();

    /**
     * Processes the incoming HTTP requests
     */
    void processRequest();

    /**
     * Sends the HTTP Response to the client
     *
     * @return True if sending was successful, else False
     */
    bool sendResponse();

    /**
     * Prepares the HTTP response for the browser route
     */
    void browserRoute();

    /**
     * Prepares the HTTP response for the master key route
     *
     * @return True if the masterkey was received, else False
     */
    bool masterKeyRoute();

    /**
     * Returns the success response to the client
     *
     * @param status code
     */
    void successResponse(size_t statusCode);

    /**
     * Returns the error response to the client
     *
     * @param status code
     */
    void errorResponse(size_t statusCode);

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
     * Registers the master pkey callback
     *
     * @param cb: callback to invoke as soon as the master key is received
     */
    void registerMasterPKeyCB(std::function<void(std::string)> cb);

    /**
     * Run method for the HTTP Server
     */
    void run();

    /**
     * Stop method for the HTTP Server
     */
    void stop();

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPSERVER_H
