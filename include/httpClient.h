
#ifndef BUTTERFLY_HTTPCLIENT_H
#define BUTTERFLY_HTTPCLIENT_H

#include <memory>

#include "logger.h"
#include "tcpSocket.h"
#include "httpRequest.h"
#include "httpResponse.h"

namespace butterfly
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
    std::vector< std::pair<std::string, std::string> > _formParams;

    /**
     * Get IP from URL
     *
     * @param url: URL string
     * @return IP from URL string
     */
    std::string getIpFromUrl(std::string url);

    /**
     * Process the HTTP Response
     *
     * @return True if the statuscode is 200, else False
     */
    bool processResponse();

public:

    /**
     * Constructor HTTPClient
     *
     * Usage:
     *      std::shared_ptr<butterfly::HTTPClient> httpClient = std::make_shared<butterfly::HTTPClient>(5000);
     *      httpClient->post("http://127.0.0.1:5000/decryption/");
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
     * Setter for the form parameter and the value
     *
     * @param param: form parameter
     * @param value: value for the parameter
     */
    void setFormParam(const std::string &param, const std::string &value);

    void get(const std::string &url);

    /**
     *
     * @param url
     */
    void post(const std::string &url);

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPCLIENT_H
