
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
     * Sends the string to the socket
     *
     * @param s: std::string
     * @return True if the sending was successful
     */
    virtual bool send(const std::string &s) const = 0;

    /**
     * Receives the len size from the socket
     *
     * @param buf: buffer
     * @param len: length of the buffer
     * @return return code as int
     */
    virtual int recv(char *buf, int len) const = 0;

    /**
     * Receives the complete buffer as chunks from the socket
     *
     * @param chunkSize: size of the chunks
     * @param blocking: recv is blocking
     * @return  data as std::string
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
