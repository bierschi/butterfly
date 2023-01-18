
#ifndef BUTTERFLY_HTTPMSGSCHEMA_H
#define BUTTERFLY_HTTPMSGSCHEMA_H

#include <iostream>
#include <vector>

#define	CRLF "\r\n"

namespace butterfly
{

typedef enum { GET, HEAD, POST, PUT, DELETE, CONNECT, NOT_IMPLEMENTED } Method;
typedef enum { HTTP1_0, HTTP1_1, HTTP_UNSUPPORTED } Protocol;

/**
 * Abstract Base Class HTTPMSGSchema to provide a Message Schema for HTTP Requests and Responses
 */
class HTTPMSGSchema
{

protected:
    std::string _httpData, _body, _messageType, _formParam;;
    Method _httpMethod;
    Protocol _protocol;
    std::vector< std::pair<std::string, std::string> > _httpHeaders;

public:

    /**
     * Constructor HTTPMSGSchema
     */
    explicit HTTPMSGSchema(const std::string &messageType);

    /**
     * Virtual Destructor HTTPMSGSchema
     */
    virtual ~HTTPMSGSchema() = default;

    /**
     * Prints the HTTP Request/Response
     */
    void print() const;

    /**
     * Adds HTTP Data to string container
     *
     * @param httpData: data as std::string
     */
    void addHTTPData(const std::string &httpData);

    /**
     * Getter for the HTTP Data string container
     *
     * @return data as std::string
     */
    inline std::string getHTTPData() const { return _httpData; }

    /**
     * Getter for the HTTPData size
     *
     * @return size of the HTTP data
     */
    inline size_t getHTTPDataSize() const { return _httpData.size(); }

    /**
     * Setter for the protocol
     *
     * @param protocol: HTTP Protocol
     */
    void setProtocol(Protocol protocol);

    /**
     * Getter for the protocol
     *
     * @return Protocol: HTTP Protocol
     */
    inline Protocol getProtocol() const { return _protocol; }

    /**
     * Adds the HTTP Body to the body container
     *
     * @param body: body as std::string
     */
    void addBody(const std::string &body);

    /**
     * Getter for the HTTP Body
     *
     * @return body as std::string
     */
    inline std::string getBody() const { return _body; }

    /**
     * Getter for the Body length
     *
     * @return length of the body
     */
    inline size_t getBodyLength() const { return _body.length(); }

    /**
     * Setter for the HTTP Headers
     *
     * @param headerName: Name of the header
     * @param headerContent: Content of the Header
     */
    void setHTTPHeader(const std::string &headerName, const std::string &headerContent);

    /**
     * Getter for the HTTP Headers
     *
     * @param headerName: Name of the header
     * @return Header content as std::string
     */
    std::string getHTTPHeader(const std::string &headerName) const;

    /**
     * Add HTTP Header Vector to the existing one
     *
     * @param headerVec: Vector of header arguments
     */
    void addHTTPHeaderVector(std::vector< std::pair<std::string, std::string> > &headerVec);

    /**
     * Getter for the HTTP Headers Size
     *
     * @return Number of received Headers
     */
    inline size_t getHTTPHeadersSize() const { return _httpHeaders.size(); }

    /**
     * Setter for the form parameter and the value
     *
     * @param param: form parameter
     * @param value: value for the parameter
     */
    void setFormParam(const std::string &param, const std::string &value);

    /**
     * Getter for the complete form parameter string
     *
     * @return form parameter string
     */
    inline std::string getFormParam() const { return _formParam; }

    /**
     * Add a vector consisting of params and values to the formParam string
     *
     * @param formParamVec: vector of params and values
     */
    void addFormParamVector(std::vector< std::pair<std::string, const std::string> > &formParamVec);

    /**
     * Abstract method parseIncoming for subclasses
     */
    virtual void parseIncoming() = 0;

    /**
     * Abstract method prepareOutgoing for subclasses
     */
    virtual void prepareOutgoing() = 0;
};

} // namespace butterfly

#endif //BUTTERFLY_HTTPMSGSCHEMA_H
