
#ifndef BUTTERFLY_HTTPSCHEMA_H
#define BUTTERFLY_HTTPSCHEMA_H

#include <iostream>
#include <vector>

#define	CRLF "\r\n"

namespace butterfly
{

typedef enum { GET, PUT, HEAD, POST, NOT_IMPLEMENTED } Method;
typedef enum { HTTP1_0, HTTP1_1, HTTP_UNSUPPORTED } Protocol;

/**
 * Abstract Base Class HTTPSchema to provide basic methods for HTTP Handling
 */
class HTTPSchema
{

protected:
    std::string _data, _body;
    Method _httpMethod;
    Protocol _protocol;
    std::vector< std::pair<std::string, std::string> > _httpHeaders;

public:

    /**
     * Constructor HTTPSchema
     */
    HTTPSchema();

    /**
     * Virtual Destructor HTTPSchema
     */
    virtual ~HTTPSchema() = default;

    /**
     * Prints the HTTP Request/Response
     */
    void print() const;

    /**
     * Adds HTTP Data to string container
     *
     * @param data: data as std::string
     */
    void addData(const std::string &data);

    /**
     * Getter for the string container
     *
     * @return data as std::string
     */
    inline std::string getData() const { return _data; }

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
     * Abstract method parse for subclasses
     *
     * @return
     */
    virtual int parse() = 0;

    /**
     * Abstract method prepare for subclasses
     */
    virtual void prepare() = 0;
};

} // namespace butterfly

#endif //BUTTERFLY_HTTPSCHEMA_H
