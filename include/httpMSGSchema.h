
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
    std::string _httpData, _body, _messageType;
    Method _httpMethod;
    Protocol _protocol;
    std::vector< std::pair<std::string, std::string> > _httpHeaders;

public:

    /**
     * Constructor HTTPSchema
     */
    explicit HTTPMSGSchema(const std::string &messageType);

    /**
     * Virtual Destructor HTTPSchema
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
     * Setter for the protocol
     *
     * @param protocol
     */
    void setProtocol(Protocol protocol);

    /**
     * Getter for the protocol
     *
     * @return Protocol
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
     * Getter for the HTTP Header Size
     *
     * @return Number of received Headers
     */
    inline size_t getHTTPHeaderSize() const { return _httpHeaders.size(); }

    /**
     * Abstract method parse for subclasses
     *
     */
    virtual void parseIncoming() = 0;

    /**
     * Abstract method prepare for subclasses
     */
    virtual void prepareOutgoing() = 0;
};

} // namespace butterfly

#endif //BUTTERFLY_HTTPMSGSCHEMA_H
