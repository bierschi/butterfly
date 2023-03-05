
#ifndef BUTTERFLY_ISOCKET_H
#define BUTTERFLY_ISOCKET_H

#include <iostream>

namespace tools
{

class ISocket
{

private:

public:
    enum class Type {Socket, TCPSocket, TORSocket};

    ISocket() = default;
    virtual ~ISocket() = default;

    virtual bool send(const std::string &s) const = 0;
    virtual int recv(char *buf, int len) const = 0;
    virtual std::string recvAll(int chunkSize, bool blocking) const = 0;
    virtual ISocket::Type type() const = 0;
};

}
#endif //BUTTERFLY_ISOCKET_H
