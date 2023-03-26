#include "torSocket.h"

namespace butterfly
{

TORSocket::TORSocket(const std::string &ip, int port) : Socket(AF_INET, SOCK_STREAM, 0), _ip(ip), _port(port)
{

}

bool TORSocket::connect(const std::string&, int)
{
    return true;
}

bool TORSocket::send(const std::string&) const
{
    return true;
}

int TORSocket::recv(char*, int) const
{
    return 0;
}

std::string TORSocket::recvAll(int, bool) const
{
    return "";
}

ISocket::Type TORSocket::getType() const
{
    return Type::TORSocket;
}

} // namespace butterfly
