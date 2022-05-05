
#ifndef BUTTERFLY_HTTPSERVER_H
#define BUTTERFLY_HTTPSERVER_H

#include <memory>
#include <functional>
#include <thread>
#include <atomic>

#include "logger.h"
#include "tcpSocket.h"
#include "httpRequest.h"
#include "httpResponse.h"

namespace butterfly
{

/**
 * Class HTTPServer to process incoming HTTP Requests and send outgoing HTTP Responses
 */
class HTTPServer
{

private:
    unsigned int _port;
    std::atomic<bool> _running;
    std::shared_ptr<TCPSocket> _tcpSocket, _newTCPSocket;
    std::unique_ptr<HTTPRequest> _httpRequest;
    std::unique_ptr<HTTPResponse> _httpResponse;
    std::thread _serverThread;
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

    /**
     * Private run method for the HTTP Server
     */
    void _run();

public:

    /**
     * Constructor HTTPServer
     *
     * Usage:
     *      std::shared_ptr<butterfly::HTTPServer> server = std::make_shared<butterfly::HTTPServer>(8080);
     *      server->run();
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
     *
     * @param blocking: sets the blocking mode of the run method
     */
    void run(bool blocking=false);

    /**
     * Stop method for the HTTP Server
     */
    void stop();

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPSERVER_H
