
#ifndef TCPSOCKBFLY_TCPSOCKET_H
#define TCPSOCKBFLY_TCPSOCKET_H

#include "socket.h"

namespace tools
{

/**
 * Class TCPSocket to create a TCP socket
 */
class TCPSocket : public Socket
{

private:

public:

    /**
     * TCPSocket Constructor
     *
     * Usage:
     *      std::shared_ptr<butterfly::TCPSocket> _serverSocket = std::make_shared<butterfly::TCPSocket>();
     *      _serverSocket->bind(1234);
     *      _serverSocket->listen();
     *      std::shared_ptr<butterfly::TCPSocket> newSocket = _serverSocket->accept();
     *      std::string s;
     *      newSocket->recv(s, 1024);
     *
     *      std::shared_ptr<butterfly::TCPSocket> _clientSocket = std::make_shared<butterfly::TCPSocket>();
     *      if (_clientSocket->connect("127.0.0.1", 8080))
     *      {
     *          _clientSocket->send("Message to server");
     *      }
     *
     */
    TCPSocket();

    /**
     * TCPSocket Constructor
     *
     * @param fileDescriptor: Create TCPSocket with a File Descriptor
     */
    explicit TCPSocket(int fileDescriptor);

    /**
     * Destructor TCPSocket
     */
    ~TCPSocket() override = default;

    /**
    * Accept incoming connections from the socket
    *
    * @return std::shared_ptr<Socket>
    */
    std::shared_ptr<TCPSocket> accept();

    /**
     * Sends the string
     *
     * @param s: std::string
     * @return True if the sending was successful
     */
    bool send(const std::string &s) const;

    /**
     * Receives the len size from the socket
     *
     * @param buf: buffer
     * @param len: length of the buffer
     * @return size of the read data
     */
    int recv(char *buf, int len) const;

    /**
     * Receives the complete buffer as chunks from the socket
     *
     * @param chunkSize: Size of the chunks
     * @param blocking: recv is blocking
     * @return data as std::string
     */
    std::string recvAll(int chunkSize, bool blocking=false) const;

};

} // namespace tools

#endif //TCPSOCKBFLY_TCPSOCKET_H
