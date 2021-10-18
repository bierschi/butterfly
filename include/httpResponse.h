
#ifndef BUTTERFLY_HTTPRESPONSE_H
#define BUTTERFLY_HTTPRESPONSE_H

#include "httpSchema.h"

namespace butterfly
{

/**
 * Class HTTPResponse for outgoing HTTP Responses
 */
class HTTPResponse: public HTTPSchema
{

private:
    std::string _responseBody, _reasonPhrase;
    size_t _statusCode;

public:

    /**
     * Constructor HTTPResponse
     *
     * Usage:
     *      std::unique_ptr<butterfly::HTTPResponse> _httpResponse(new HTTPResponse());
     *      _httpResponse->addData(data);
     *      _httpResponse->parse();
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
    inline size_t getResponseSize() const { return _data.length(); }

    /**
     * Getter for the response data
     *
     * @return size of the response data
     */
    std::string getResponseData() const { return _data; }

    /**
     * Method to parse the incoming HTTP Responses
     *
     * @return
     */
    int parse() override;

    /**
     * Method to prepare the HTTP Responses for further usage
     */
    void prepare() override;

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPRESPONSE_H
