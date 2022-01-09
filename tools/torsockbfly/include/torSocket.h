
#ifndef TORSOCKBFLY_TORSOCKET_H
#define TORSOCKBFLY_TORSOCKET_H

#include "socket.h"

namespace tools
{

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

    static std::string serverResponse(char status);
    int prepareDomainRequest(const std::string &domain, const int port);
    int prepareIPRequest(const std::string &domain, const int port);

public:
    TORSocket(std::string ip, int port);
    ~TORSocket() override = default;

    bool send(const std::string &s, int length) const;
    int recv(char *buf, int len) const;
    std::string recvAll(int chunkSize) const; // takes too long

    std::string request(const std::string &domain, const int port=80);
};

} // namespace tools

#endif //TORSOCKBFLY_TORSOCKET_H
