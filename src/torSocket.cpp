
#include "torSocket.h"

namespace butterfly
{

TORSocket::TORSocket(const std::string ip, const int port) : Socket(AF_INET, SOCK_STREAM, 0), _ip(ip), _port(port)
{

}

TORSocket::~TORSocket()
{

}



} // namespace butterfly
