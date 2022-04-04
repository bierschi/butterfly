
#ifndef HTTPBFLY_HTTPRESPONSE_H
#define HTTPBFLY_HTTPRESPONSE_H

#include "httpMSGSchema.h"

namespace tools
{

/**
 * Class HTTPResponse for incoming/outgoing HTTP Responses
 */
class HTTPResponse: public HTTPMSGSchema
{

private:
    std::string _reasonPhrase;
    size_t _statusCode;

public:

    /**
     * Constructor HTTPResponse
     *
     * Usage:
     *      std::unique_ptr<tools::HTTPResponse> _httpResponse(new tools::HTTPResponse());
     *      _httpResponse->setProtocol(Protocol::HTTP1_1);
     *      _httpResponse->setStatusCode(200);
     *      _httpResponse->setReasonPhrase(_httpResponse->getStatusCode());
     *      _httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");
     *      _httpResponse->addBody("<!DOCTYPE html><html><body><h1>Test Message</h1></body></html>");
     *      _httpResponse->setHTTPHeader("Content-Length", std::to_string(_httpResponse->getBodyLength()));
     *      _httpResponse->prepareOutgoing();
     *
     *      std::unique_ptr<tools::HTTPResponse> _httpResponse(new tools::HTTPResponse());
     *      _httpResponse->parseIncoming();
     *      _httpResponse->getStatusCode();
     *      _httpResponse->getReasonPhrase();
     *
     */
    HTTPResponse();

    /**
     * Destructor HTTPResponse
     */
    ~HTTPResponse() override = default;

    /**
     * Setter for the status code
     *
     * @param statusCode: http status code
     */
    void setStatusCode(size_t statusCode);

    /**
     * Getter for the status code
     *
     * @return http status code
     */
    inline size_t getStatusCode() const { return _statusCode; }

    /**
     * Setter for the reason phrase
     *
     * @param statusCode: status code
     */
    void setReasonPhrase(size_t statusCode);

    /**
     * Getter for the reason phrase
     *
     * @return reason phrase as std::string
     */
    inline std::string getReasonPhrase() const { return _reasonPhrase; }

    /**
     * Method to parse the incoming HTTP Responses
     */
    void parseIncoming() override;

    /**
     * Method to prepare the HTTP Responses for further usage
     */
    void prepareOutgoing() override;

};

} // namespace tools

#endif
