
#include "socket.h"

namespace butterfly
{

Socket::Socket(int domain, int type, int protocol) : _socketDomain(domain), _socketType(type), _socketProtocol(protocol), _fd(-1)
{
    memset(&_addr, 0, sizeof(_addr));

    _fd = socket(_socketDomain, _socketType, _socketProtocol);
    if (_fd == -1)
    {
        throw SocketException("Error on creating a valid socket file descriptor!");
    }

    _addr.sin_family      = static_cast<sa_family_t>(_socketDomain);     // For IPv4
    _addr.sin_addr.s_addr = INADDR_ANY;                                  // Accept any incoming message
}

Socket::Socket(int fileDescriptor, int domain, int type, int protocol) : _socketDomain(domain), _socketType(type), _socketProtocol(protocol), _fd(fileDescriptor)
{
    memset(&_addr, 0, sizeof(_addr));

    _addr.sin_family      = static_cast<sa_family_t>(_socketDomain);     // For IPv4
    _addr.sin_addr.s_addr = INADDR_ANY;                                  // Accept any incoming message
}

Socket::~Socket()
{
    ::close(_fd);
}

int Socket::getFileDescriptor() const
{
    return _fd;
}

bool Socket::shutdown() const
{
    // no receptions and transmission anymore
    if ( ::shutdown(_fd, SHUT_RDWR) == -1 )
    {
        return false;
    }

    return true;
}

bool Socket::setOptions() const
{
    int optval = 1;
    if ( setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) == -1 )
    {
        return false;
    }

    return true;
}

void Socket::setBlocking() const
{
    long status = fcntl(_fd, F_GETFL, NULL);

    status &= (~O_NONBLOCK);

    fcntl(_fd, F_SETFL, status);
}

void Socket::setNonBlocking() const
{
    long status = fcntl(_fd, F_GETFL, NULL);

    status |= O_NONBLOCK;

    fcntl(_fd, F_SETFL, status);
}

bool Socket::bind(unsigned int port)
{

    _addr.sin_port = htons(static_cast<uint16_t>(port));

    if ( ::bind(_fd, (struct sockaddr*)&_addr, sizeof(_addr)) == -1 )
    {
        return false;
    }

    return true;
}

bool Socket::listen() const
{
    if ( ::listen(_fd, MAX_CONNECTIONS) == -1 )
    {
        return false;
    }

    return true;
}

std::shared_ptr<Socket> Socket::accept()
{
    struct sockaddr_storage new_addr;
    socklen_t addr_size;
    addr_size = sizeof(new_addr);

    int newSockFD = ::accept(_fd, (struct sockaddr *)&new_addr, &addr_size);
    if (newSockFD == -1)
    {
        throw SocketException("Error on creating a valid socket file descriptor!");
    }

    std::shared_ptr<Socket> newSocket = std::make_shared<Socket>(newSockFD, _socketDomain, _socketType, _socketProtocol);

    return newSocket;
}

bool Socket::connect(const std::string& host, int port)
{
    _addr.sin_port   = htons(static_cast<uint16_t>(port));

    inet_pton(_addr.sin_family, host.c_str(), &_addr.sin_addr);

    if ( ::connect(_fd, (sockaddr*)&_addr, sizeof(_addr)) == -1 )
    {
        return false;
    }

    return true;
}

bool Socket::disconnect() const
{
    if ( ::close(_fd) == -1 )
    {
        return false;
    }

    return true;
}

} // namespace butterfly
