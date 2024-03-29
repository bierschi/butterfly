
#include "torSocket.h"

namespace butterfly
{

TORSocket::TORSocket(const std::string &ip, int port) : Socket(AF_INET, SOCK_STREAM, 0), _ip(ip), _port(port)
{
    #ifdef LOGGING
    LOG_TRACE("Create class TORSocket");
    #endif

    if ( !Socket::connect(_ip, _port) )
    {
        throw SocketException("TORSocket error while connecting to " + _ip + " on port " + std::to_string(_port));
    }
    #ifdef LOGGING
    LOG_INFO("[*TOR*] TOR Client connected to "<< ip << " on port " << std::to_string(port));
    #endif

    if ( !authenticate(_sendAuthBuf, sizeof(_sendAuthBuf)) )
    {
        throw SocketException("TORSocket error at sending the Authentication Request to the Socket!");
    }

    char recvAuth[2];
    if ( recv(recvAuth, sizeof(recvAuth)) == -1 )
    {
        throw SocketException("TORSocket error at receiving the Authentication Response from the Socket!");
    }

    if (recvAuth[1] != 0x00)
    {
        throw SocketException("TORSocket error, authentication to the TOR network failed: " + serverStatusResponse(recvAuth[1]));
    }

    #ifdef LOGGING
    LOG_INFO("[*TOR*] TOR Client Authenticated");
    #endif
}

bool TORSocket::authenticate(const std::string &str, int size)
{
    if (::send(_fd, str.c_str(), static_cast<size_t>(size), MSG_NOSIGNAL) == -1)
    {
        return false;
    }

    return true;
}

std::string TORSocket::serverStatusResponse(char status)
{
    switch(status)
    {
        case 0x00:
            return "request granted";
        case 0x01:
            return "general failure";
        case 0x02:
            return "connection not allowed by ruleset";
        case 0x03:
            return "network unreachable";
        case 0x04:
            return "host unreachable";
        case 0x05:
            return "connection refused by destination host";
        case 0x06:
            return "TTL expired";
        case 0x07:
            return "command not supported / protocol error";
        case 0x08:
            return "address type not supported";
        default:
            return "server status was not found!";
    }
}

bool TORSocket::connect(const std::string &domain, int port)
{
    char domainLen   = static_cast<char>(domain.length());
    auto domainPort = static_cast<short>(htons(static_cast<uint16_t>(port)));

    int connReqSize = 4 + 1 + domainLen + 2;
    char* connReq = new char[connReqSize];

    std::memcpy(connReq, _connReqDomainBuf, 4);                                      // 5, 1, 0, 3
    std::memcpy(connReq + 4, &domainLen, 1);                                         // Domain Length
    std::memcpy(connReq + 5, domain.c_str(), static_cast<size_t>(domainLen));        // Domain
    std::memcpy(connReq + 5 + domainLen, &domainPort, 2);                            // Port

    if (::send(_fd, (char*)connReq, static_cast<size_t>(connReqSize), MSG_NOSIGNAL) == -1)
    {
        return false;
    }

    char recvConn[10];
    if ( ::recv(_fd, recvConn, 10, 0) == -1 )
    {
        return false;
    }

    std::string resp = serverStatusResponse(recvConn[1]);
    #ifdef LOGGING
    LOG_INFO("[*TOR*] TOR Connection Response: " << resp);
    #endif

    return true;
}

bool TORSocket::send(const std::string &s) const
{

    if (::send(_fd, s.c_str(), strlen(s.c_str()), MSG_NOSIGNAL) == -1)
    {
        return false;
    }

    return true;
}

int TORSocket::recv(char *buf, int len) const
{
    ssize_t recvLength = ::recv(_fd, buf, static_cast<size_t>(len), 0);

    if ( recvLength == -1)
    {
        return -1;
    } else
    {
        return static_cast<int>(recvLength);
    }
}

std::string TORSocket::recvAll(int chunkSize, bool blocking) const
{
    char buffer[chunkSize];
    std::string str;
    int flags;

    if (blocking)
    {
        flags = 0;
    } else
    {
        flags = MSG_WAITALL;
    }

    int recvLength;
    while ( (recvLength = static_cast<int>(::recv(_fd, buffer, sizeof(buffer), flags))) > 0 )
    {
        str.append(buffer, static_cast<unsigned long>(recvLength));
    }

    return str;
}

ISocket::Type TORSocket::getType() const
{
    return Type::TORSocket;
}

} // namespace butterfly
