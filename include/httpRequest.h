
#ifndef BUTTERFLY_HTTPREQUEST_H
#define BUTTERFLY_HTTPREQUEST_H

#include "httpMSGSchema.h"

namespace butterfly
{

/**
 * Class HTTPRequest for incoming HTTP Requests (Client -> Server)
 */
class HTTPRequest: public HTTPMSGSchema
{

private:
    std::string _url, _userAgent;

public:

    /**
     * Constructor HTTPRequest
     *
     * Usage:
     *      std::unique_ptr<butterfly::HTTPRequest> _httpRequest(new HTTPRequest());
     *      _httpRequest->addHTTPData(data);
     *      _httpRequest->parseIncoming();
     *
     */
    HTTPRequest();

    /**
     * Destructor HTTPRequest
     */
    ~HTTPRequest() override = default;

    /**
     * Setter for the method
     *
     * @param method: HTTP Method
     */
    void setMethod(Method &method);

    /**
     * Getter for the Method
     *
     * @return HTTP Method
     */
    inline Method getMethod() const { return _httpMethod; }

    /**
     * Setter for the URL
     *
     * @param url: URL as std::string
     */
    void setURL(const std::string &url);

    /**
     * Getter for the URL
     *
     * @return URL as std::string
     */
    inline std::string getURL() const { return _url; }

    /**
     * Setter for the UserAgent
     *
     * @param userAgent: user agent as std::string
     */
    void setUserAgent(const std::string &userAgent);

    /**
     * Getter for the UserAgent
     *
     * @return user agent as std::string
     */
    inline std::string getUserAgent() const { return _userAgent; }

    /**
     * Getter for the HTTP Request size
     *
     * @return size of the request
     */
    inline size_t getRequestSize() const { return _httpData.size(); }

    /**
     * Method to parse the incoming HTTP Requests
     *
     */
    void parseIncoming() override;

    /**
     * Method to prepare the HTTP Requests for further usage
     */
    void prepareOutgoing() override;

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPREQUEST_H
