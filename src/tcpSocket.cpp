
#include "tcpSocket.h"

namespace butterfly
{

TCPSocket::TCPSocket() : Socket(AF_INET, SOCK_STREAM)
{

    if ( !Socket::setOptions() )
    {
        throw SocketException("Error on setting options for the socket!");
    }

}

std::shared_ptr<TCPSocket> TCPSocket::accept()
{
    struct sockaddr_storage new_addr;
    socklen_t addr_size;
    addr_size = sizeof(new_addr);

    int newSockFD = ::accept(_fd, (struct sockaddr *)&new_addr, &addr_size);
    if (newSockFD == -1)
    {
        throw SocketException("Error on creating a valid socket file descriptor!");
    }

    std::shared_ptr<TCPSocket> newSocket(new TCPSocket());
    newSocket->_fd = newSockFD;

    return newSocket;
}

bool TCPSocket::send(const std::string &s) const
{

    if (::send(_fd, s.c_str(), strlen(s.c_str()), MSG_NOSIGNAL) == -1)
    {
        return false;
    }

    return true;
}

bool TCPSocket::recv(std::string &buf, int len) const
{
    char buffer[len];
    bzero(buffer, static_cast<size_t>(len));

    if (::recv(_fd, buffer, static_cast<size_t>(len - 1), 0) == -1)
    {
        return false;
    }

    buf = std::string(buffer);

    return true;
}

} // namespace butterfly
