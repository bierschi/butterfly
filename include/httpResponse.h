
#ifndef BUTTERFLY_HTTPRESPONSE_H
#define BUTTERFLY_HTTPRESPONSE_H

#include "httpSchema.h"

namespace butterfly
{

/**
 * Class HTTPResponse for outgoing HTTP Responses (Server -> Client)
 */
class HTTPResponse: public HTTPSchema
{

private:
    std::string _reasonPhrase;
    size_t _statusCode;

public:

    /**
     * Constructor HTTPResponse
     *
     * Usage:
     *      std::unique_ptr<butterfly::HTTPResponse> _httpResponse(new HTTPResponse());
     *
     *      _httpResponse->setProtocol(HTTP1_1);
     *      _httpResponse->setReasonPhrase(302);
     *      _httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");
     *      _httpResponse->addBody("<!DOCTYPE html><html><body><h1>Test Message</h1></body></html>");
     *      _httpResponse->setHTTPHeader("Content-Length", std::to_string(_httpResponse->getBody().length()));
     *
     *      _httpResponse->prepareOutgoing();
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
     * @param statusCode: status code
     */
    void setStatusCode(size_t statusCode);

    /**
     * Getter for the status code
     *
     * @return status code
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
     * Getter for the response size
     *
     * @return size of the response
     */
    inline size_t getResponseSize() const { return _httpData.length(); }

    /**
     * Method to parse the incoming HTTP Responses
     *
     * @return
     */
    void parseIncoming() override;

    /**
     * Method to prepare the HTTP Responses for further usage
     */
    void prepareOutgoing() override;

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPRESPONSE_H
