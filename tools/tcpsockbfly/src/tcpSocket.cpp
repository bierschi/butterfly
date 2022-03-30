
#include "tcpSocket.h"

namespace tools
{

TCPSocket::TCPSocket() : Socket(AF_INET, SOCK_STREAM, 0)
{

    if ( !Socket::setOptions() )
    {
        throw SocketException("Error on setting options for the socket!");
    }

}

TCPSocket::TCPSocket(int fileDescriptor) : Socket(fileDescriptor, AF_INET, SOCK_STREAM, 0)
{
    if ( !Socket::setOptions() )
    {
        throw SocketException("Error on setting options for the socket!");
    }
}

std::shared_ptr<TCPSocket> TCPSocket::accept()
{
    //struct sockaddr_storage new_addr;
    struct sockaddr_in new_addr;
    socklen_t addr_size;
    addr_size = sizeof(new_addr);

    int newSockFD = ::accept(_fd, (struct sockaddr *)&new_addr, &addr_size);
    if (newSockFD == -1)
    {
        throw SocketException("Error on creating a valid socket file descriptor!");
    }

    std::shared_ptr<TCPSocket> newSocket = std::make_shared<TCPSocket>(newSockFD);

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

int TCPSocket::recv(char *buf, int len) const
{
    std::string s;
    ssize_t size_recv , total_size= 0;

    memset(buf , 0 , static_cast<size_t>(len));	//clear the variable

    while(1)
    {

        if((size_recv =  ::recv(_fd , buf , static_cast<size_t>(len), MSG_DONTWAIT) ) < 0 )
        {
            break;
        }
        else
        {
            total_size += size_recv;
        }
    }

    return static_cast<int>(total_size);

}

std::string TCPSocket::recvAll(int chunkSize, bool blocking) const
{
    char buffer[chunkSize];
    std::string str;
    int flags;

    if (blocking)
    {
        flags = 0;
    } else
    {
        flags = MSG_DONTWAIT;
    }

    int recvLength;
    while ( (recvLength = static_cast<int>(::recv(_fd, buffer, sizeof(buffer), flags))) > 0 )
    {
        str.append(buffer, static_cast<unsigned long>(recvLength));
    }

    return str;
}

} // namespace tools
