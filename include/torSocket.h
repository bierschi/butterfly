
#ifndef BUTTERFLY_TORSOCKET_H
#define BUTTERFLY_TORSOCKET_H

#include "socket.h"
#include "ISocket.h"
#include "bflyUtils.h"
#include "logger.h"

namespace butterfly
{

/**
 * Class TORSocket to establish a proxy connection to the tor network via the tor binary
 */
class TORSocket : public Socket, ISocket
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
     * Authenticate for the tor network access
     *
     * @param str: string
     * @param size: size of the string
     * @return True if authentication was successful
     */
    bool authenticate(const std::string &str, int size);

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
    * Connect to the tor network
    *
    * @param domain: domain name
    * @param port: port of the domain
    * @return rc of the action
    */
    bool connect(const std::string &domain, int port) override;

    /**
     * Sends the string
     *
     * @param s: std::string
     * @return True if the sending was successful
     */
    bool send(const std::string &s) const override;

    /**
     * Receives the len size from the socket
     *
     * @param buf: buffer
     * @param len:  length of the buffer
     * @return true if receiving was successful
     */
    int recv(char *buf, int len) const override;

    /**
     * Receives the complete buffer as chunks from the socket
     *
     * @param chunkSize: Size of the chunks
     * @return data as std::string
     */
    std::string recvAll(int chunkSize, bool blocking) const override;

    /**
     * Get the Type of the socket
     * @return ISocket::Type enum class
     */
    ISocket::Type getType() const override;
};

} // namespace butterfly

#endif //BUTTERFLY_TORSOCKET_H
