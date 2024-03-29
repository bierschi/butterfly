
#ifndef BUTTERFLY_HTTPREQUEST_H
#define BUTTERFLY_HTTPREQUEST_H

#include <numeric>

#include "httpMSGSchema.h"

namespace butterfly
{

/**
 * Class HTTPRequest for incoming/outgoing HTTP Requests
 */
class HTTPRequest: public HTTPMSGSchema
{

private:
    std::string _url, _userAgent, _route;

public:

    /**
     * Constructor HTTPRequest
     *
     * Usage:
     *      std::unique_ptr<butterfly::HTTPRequest> _httpRequest(new butterfly::HTTPRequest());
     *      _httpRequest->setURL(url);
     *      _httpRequest->setMethod(Method::POST);
     *      _httpRequest->setProtocol(Protocol::HTTP1_1);
     *      _httpRequest->setUserAgent("butterfly");
     *      _httpRequest->setHTTPHeader("Content-Type", "application/x-www-form-urlencoded");
     *      _httpRequest->setFormParam("form1", "value1");
     *      _httpRequest->setFormParam("form2", "value2");
     *      _httpRequest->addBody(_httpRequest->getFormParam());
     *      _httpRequest->setHTTPHeader("Content-Length", std::to_string(_httpRequest->getBodyLength()));
     *      _httpRequest->prepareOutgoing();
     *
     *      std::unique_ptr<butterfly::HTTPRequest> _httpRequest(new butterfly::HTTPRequest());
     *      _httpRequest->addHTTPData(httpData);
     *      _httpRequest->parseIncoming();
     *      _httpRequest->getMethod();
     *      _httpRequest->getURL();
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
    void setMethod(Method method);

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
     * Setter for the route
     * @param route: route as std::string
     */
    void setRoute(const std::string &route);

    /**
     * Getter for the route
     * @return route as std::string
     */
    inline std::string getRoute() const { return _route; };

    /**
     * Method to parse the incoming HTTP Requests
     */
    void parseIncoming() override;

    /**
     * Method to prepare the HTTP Requests for further usage
     */
    void prepareOutgoing() override;

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPREQUEST_H
