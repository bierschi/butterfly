
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
     *      std::shared_ptr<butterfly::HTTPClient> httpClient = std::make_shared<butterfly::HTTPClient>();
     *      std::string cert = httpClient->post("http://127.0.0.1:5000/decryption/", data, 5000);
     *
     */
     HTTPClient();

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
     * @param port: port to connect to
     */
    std::string get(const std::string &url, int port=80);

    /**
     * Post request to the URL
     *
     * @param url: URL string
     * @param data: data for the post request
     * @param port: port to connect to
     */
    std::string post(const std::string &url, const std::string &data, int port=80);

};

} // namespace tools

#endif //HTTPBFLY_HTTPCLIENT_H
