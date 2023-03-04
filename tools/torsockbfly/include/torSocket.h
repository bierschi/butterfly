
#ifndef TORSOCKBFLY_TORSOCKET_H
#define TORSOCKBFLY_TORSOCKET_H

#include "socket.h"

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
    * Get Domain name from provided URL
    *
    * @param url: URL address
    * @return domain as std::string
    */
    std::string getDomainFromUrl(std::string url);

    /**
    * Get Route name from provided URL
    *
    * @param url: URL address
    * @return domain as std::string
    */
    std::string getRouteFromUrl(std::string url);

    /**
     *
     * @param status
     * @return
     */
    static std::string serverStatusResponse(char status);

    /**
     *
     * @param url
     * @param port
     * @return
     */
    int prepareRequest(const std::string &url, int port);

public:

    /**
     *
     * @param ip
     * @param port
     */
    TORSocket(const std::string &ip, int port);

    /**
     *
     */
    ~TORSocket() override = default;

    /**
     *
     * @param s
     * @param length
     * @return
     */
    bool send(const std::string &s, int length) const;

    /**
     *
     * @param buf
     * @param len
     * @return
     */
    int recv(char *buf, int len) const;

    /**
     *
     * @param chunkSize
     * @return
     */
    std::string recvAll(int chunkSize) const; // takes too long

    /**
     *
     * @param url
     * @param port
     * @return
     */
    std::string get(const std::string &url, int port=80);

    /**
     *
     * @param url
     * @param data
     * @param port
     * @return
     */
    std::string post(const std::string &url, const std::string &data, int port=80);
};

} // namespace tools

#endif //TORSOCKBFLY_TORSOCKET_H
