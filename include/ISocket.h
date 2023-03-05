
#ifndef BUTTERFLY_ISOCKET_H
#define BUTTERFLY_ISOCKET_H

#include <iostream>

namespace butterfly
{

class ISocket
{

public:
    enum class Type {Socket, TCPSocket, TORSocket};

    /**
     * Constructor ISocket
     */
    ISocket() = default;

    /**
     * Virtual Destructor ISocket
     */
    virtual ~ISocket() = default;

    /**
     *
     * @param s
     * @return
     */
    virtual bool send(const std::string &s) const = 0;

    /**
     *
     * @param buf
     * @param len
     * @return
     */
    virtual int recv(char *buf, int len) const = 0;

    /**
     *
     * @param chunkSize
     * @param blocking
     * @return
     */
    virtual std::string recvAll(int chunkSize, bool blocking) const = 0;

    /**
    * Get the Type of the socket
    * @return ISocket::Type enum class
    */
    virtual ISocket::Type getType() const = 0;
};

}
#endif //BUTTERFLY_ISOCKET_H
