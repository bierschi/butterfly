
#ifndef BUTTERFLY_TCPSOCKET_H
#define BUTTERFLY_TCPSOCKET_H

#include "socket.h"

namespace butterfly
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
    bool send(const std::string& s) const;

    /**
     * Receives the buffer from the socket
     *
     * @param buf: Buffer to fill
     * @param len: Length of the buffer
     * @return True if the receiving was successful
     */
    bool recv(std::string& buf, int len) const;
};

} // namespace butterfly

#endif //BUTTERFLY_TCPSOCKET_H
