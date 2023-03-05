
#ifndef TORSOCKBFLY_TORSOCKET_H
#define TORSOCKBFLY_TORSOCKET_H

#include "socket.h"
#include "bflyUtils.h"

namespace tools
{

/**
 *  Class TORSocket to create socks connection to the tor network
 */
class TORSocket : public Socket
{

private:
    std::string _ip;
    int _port;

    char _sendAuthBuf[3] =
    {
            0x05, // SOCKS 5
            0x01, // One Authentication Method
            0x00  // No Authentication
    };
    char _connReqDomainBuf[4] =
    {
            0x05, // SOCKS5
            0x01, // CONNECT
            0x00, // RESERVED
            0x03, // DOMAIN
    };

    /**
     * Get the server status response
     *
     * @param status: character
     * @return server status converted to a string
     */
    static std::string serverStatusResponse(char status);



public:

    /**
     * TORSocket Constructor
     *
     * Usage:
     *      std::shared_ptr<tools::TORSocket> torSocket = std::make_shared<tools::TORSocket>("127.0.0.1", 9050);
     *      std::string response = torSocket->get("y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion", 80)
     *
     */
    TORSocket(const std::string &ip, int port);

    /**
     * Destructor TORSocket
     */
    ~TORSocket() override = default;

    /**
     * Sends the string
     *
     * @param s: std::string
     * @param length: length of the string
     * @return True if the sending was successful
     */
    bool send(const std::string &s, int length) const;

    /**
     * Receives the len size from the socket
     *
     * @param buf: buffer
     * @param len:  length of the buffer
     * @return true if receiving was successful
     */
    int recv(char *buf, int len) const;

    /**
     * Receives the complete buffer as chunks from the socket
     *
     * @param chunkSize: Size of the chunks
     * @return data as std::string
     */
    std::string recvAll(int chunkSize) const; // takes too long

    /**
     * HTTP Get request to the url
     *
     * @param url: url to request
     * @param port: port for the url
     * @return http response as std::string
     */
    std::string get(const std::string &url, int port=80);

    /**
     * HTTP Post request to the url
     *
     * @param url: url to request
     * @param data: data for the post request
     * @param port: port for the url
     * @return http response as std::string
     */
    std::string post(const std::string &url, const std::string &data, int port=80);

    /**
    * Prepares the request to the tor network
    *
    * @param domain: domain name
    * @param port: port of the domain
    * @return rc of the action
    */
    int prepareRequest(const std::string &domain, int port);
};

} // namespace tools

#endif //TORSOCKBFLY_TORSOCKET_H
