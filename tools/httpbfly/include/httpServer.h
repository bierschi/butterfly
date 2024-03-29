
#ifndef HTTPBFLY_HTTPSERVER_H
#define HTTPBFLY_HTTPSERVER_H

#include <memory>
#include <functional>
#include <thread>

#include "tcpSocket.h"
#include "httpRequest.h"
#include "httpResponse.h"

namespace tools
{

/**
 * Class HTTPServer to process incoming HTTP Requests and send outgoing HTTP Responses
 */
class HTTPServer
{

private:
    unsigned int _port;
    bool _running;
    std::shared_ptr<TCPSocket> _tcpSocket, _newTCPSocket;
    std::unique_ptr<HTTPRequest> _httpRequest;
    std::unique_ptr<HTTPResponse> _httpResponse;

    /**
     * Handles incoming requests to the http server
     *
     * @return True if the request could be handled, else False
     */
    bool handleRequest();

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
     *      std::shared_ptr<tools::HTTPServer> server = std::make_shared<tools::HTTPServer>(8080);
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
     * Run method for the HTTP Server
     */
    void run();

    /**
     * Stop method for the HTTP Server
     */
    void stop();

};

} // namespace tools

#endif
