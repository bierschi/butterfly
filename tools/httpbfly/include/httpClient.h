
#ifndef HTTPBFLY_HTTPCLIENT_H
#define HTTPBFLY_HTTPCLIENT_H

#include <memory>

#include "tcpSocket.h"
#include "httpRequest.h"
#include "httpResponse.h"
#include "bflyUtils.h"

namespace tools
{

/**
 * Class HTTPClient to send HTTP Requests and process HTTP Responses
 */
class HTTPClient
{

private:
    unsigned int _port;
    std::shared_ptr<TCPSocket> _tcpSocket;
    std::unique_ptr<HTTPRequest> _httpRequest;
    std::unique_ptr<HTTPResponse> _httpResponse;
    std::vector< std::pair<std::string, std::string> > _httpHeaders;

    /**
     * Prepares the Request
     *
     * @param url: URL string
     */
    void prepareRequest(const std::string &url, Method method, const std::string &data="");

    /**
     * Processes the HTTP Response
     *
     * @return True if the statuscode is 200, else False
     */
    bool processResponse();

public:
    size_t statusCode;
    std::string reasonPhrase;

    /**
     * Constructor HTTPClient
     *
     * Usage:
     *      std::shared_ptr<butterfly::HTTPClient> httpClient = std::make_shared<butterfly::HTTPClient>(5000);
     *      std::string cert = httpClient->post("http://127.0.0.1:5000/decryption/");
     *
     * @param port: Port for the Server
     */
    explicit HTTPClient(unsigned int port=5000);

    /**
     * Destructor HTTPClient
     */
    ~HTTPClient();

    /**
     * Setter for the HTTP Headers
     *
     * @param headerName: Name of the header
     * @param headerContent: Content of the Header
     */
    void setHTTPHeader(const std::string &headerName, const std::string &headerContent);

    /**
     * Get request to the URL
     *
     * @param url: URL string
     */
    std::string get(const std::string &url);

    /**
     * Post request to the URL
     *
     * @param url: URL string
     */
    std::string post(const std::string &url, const std::string &data);

};

} // namespace tools

#endif //HTTPBFLY_HTTPCLIENT_H
