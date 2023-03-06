
#ifndef BUTTERFLY_SOCKET_H
#define BUTTERFLY_SOCKET_H

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <memory>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>

#include "ISocket.h"
#include "bflyExceptions.h"

#define MAX_CONNECTIONS 50

namespace butterfly
{

/**
 * Class Socket to read and write from a socket
 */
class Socket
{

private:
    int _socketDomain, _socketType, _socketProtocol;

protected:
    int _fd;
    sockaddr_in _addr;

public:

    /**
     * Socket Constructor
     *
     * Usage:
     *      std::shared_ptr<butterfly::Socket> _socket = std::make_shared<butterfly::Socket>(AF_INET, SOCK_STREAM, 0);
     *      _socket->bind(1234);
     *      _socket->listen();
     *      std::shared_ptr<butterfly::Socket> newSocket = _socket->accept();
     *
     * @param domain: Address families like AF_INET
     * @param type: Types of sockets like SOCK_STREAM or SOCK_DGRAM
     * @param protocol: Protocol for socket
     */
    Socket(int domain, int type, int protocol);

    /**
     * Socket Constructor
     *
     * Usage:
     *      std::shared_ptr<butterfly::Socket> _socket = std::make_shared<butterfly::Socket>(fd, AF_INET, SOCK_STREAM, 0);
     *      _socket->bind(1234);
     *      _socket->listen();
     *      std::shared_ptr<butterfly::Socket> newSocket = _socket->accept();
     *
     * @param fileDescriptor: File Descriptor for the Socket
     * @param domain: Address families like AF_INET
     * @param type: Types of sockets like SOCK_STREAM or SOCK_DGRAM
     * @param protocol: Protocol for socket
     */
    Socket(int fileDescriptor, int domain, int type, int protocol);

    /**
     * Destructor Socket
     */
    virtual ~Socket();

    /**
     * Get the File Descriptor for the socket
     *
     * @return File Descriptor as int
     */
    int getFileDescriptor() const;

    /**
     * Cleanly shutdown of a Socket
     *
     * @return True if the shutdown was successful
     */
    bool shutdown() const;

    /**
     * Set options for the Socket
     *
     * @return True if the set operation was successful
     */
    bool setOptions() const;

    /**
     * Sets the Socket to Blocking
     */
    void setBlocking() const;

    /**
     * Sets the Socket to Non Blocking
     */
    void setNonBlocking() const;

    /**
     * Binds the socket to given port
     *
     * @param port: unsigned int port
     * @return True if the binding was successful
     */
    bool bind(unsigned int port);

    /**
     * Listen to a Socket
     *
     * @return True if the listening was successful
     */
    bool listen() const;

    /**
     * Accept incoming connections from the socket
     *
     * @return std::shared_ptr<Socket>
     */
    std::shared_ptr<Socket> accept();

    /**
     * Connect to a Socket with host and port argument
     *
     * @param host: Host to connect to
     * @param port: Port to connect to
     * @return True if the connection was successful, else False
     */
    virtual bool connect(const std::string &host, int port);

    /**
     * Disconnect cleanly from a socket
     *
     * @return True if the disconnection was successful
     */
    bool disconnect() const;

    /**
     * Converts given hostname to IP address
     *
     * @param hostname: hostname as std::string
     * @param ip: std::string reference for the IP
     * @return Returns 0 on success and -1 on error
     */
    static int hostnameToIP(const std::string &hostname, std::string &ip);

    /**
     * Sends the string to the socket
     *
     * @param s: std::string
     * @return True if the sending was successful
     */
    virtual bool send(const std::string &s) const;

    /**
     * Receives the len size from the socket
     *
     * @param buf: buffer
     * @param len: length of the buffer
     * @return return code as int
     */
    virtual int recv(char *buf, int len) const;

    /**
     * Receives the complete buffer as chunks from the socket
     *
     * @param chunkSize: size of the chunks
     * @param blocking: recv is blocking
     * @return  data as std::string
     */
    virtual std::string recvAll(int chunkSize, bool blocking) const;

    /**
     * Get the Type of the socket
     * @return ISocket::Type enum class
     */
    virtual ISocket::Type getType() const;
};

} // namespace butterfly

#endif //BUTTERFLY_SOCKET_H
