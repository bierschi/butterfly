
#include "torSocket.h"

namespace tools
{

TORSocket::TORSocket(const std::string &ip, int port) : Socket(AF_INET, SOCK_STREAM, 0), _ip(ip), _port(port)
{

    if ( !connect(_ip, _port) )
    {
        throw SocketException("Error at connecting to " + _ip + " on port " + std::to_string(_port));
    }
    std::cout << "[*] Connected to " + ip + " on port " + std::to_string(port) << std::endl;

    if ( !send(_sendAuthBuf, sizeof(_sendAuthBuf)) )
    {
        throw SocketException("Error at sending the Authentication Request to the Socket!");
    }

    char recvAuth[2];
    if ( ::recv(_fd, recvAuth, 2, 0) == -1)
    {
      throw SocketException("Error at receiving the Authentication Response from the Socket!");
    }

    if (recvAuth[1] != 0x00)
    {
        throw SocketException("Authentication to the TOR network failed: " + serverStatusResponse(recvAuth[1]));
    }
    std::cout << "[*] Client Authenticated " << std::endl;
}

std::string TORSocket::getDomainFromUrl(std::string url)
{
    std::string http = "http://";
    size_t pos1 = url.find(http);
    if (pos1 != std::string::npos)
    {
        url.erase(pos1, http.length());
    }
    std::string https = "https://";
    size_t pos2 = url.find(https);

    if (pos2 != std::string::npos)
    {
        url.erase(pos2, https.length());
    }

    size_t pos3 = url.find('/');
    if (pos3 != std::string::npos)
    {
        url.erase(pos3, url.length());
    }

    size_t pos4 = url.find(':');
    if (pos4 != std::string::npos)
    {
        url.erase(pos4, url.length());
    }

    return url;
}

std::string TORSocket::getRouteFromUrl(std::string url)
{
    std::string http = "http://";
    size_t pos1 = url.find(http);
    if (pos1 != std::string::npos)
    {
        url.erase(pos1, http.length());
    }
    std::string https = "https://";
    size_t pos2 = url.find(https);

    if (pos2 != std::string::npos)
    {
        url.erase(pos2, https.length());
    }

    size_t pos3 = url.find('/');
    if (pos3 != std::string::npos)
    {
        url.erase(0, pos3);
    } else
    {
        // not route was included
        url = "";
    }

    return url;
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

int TORSocket::prepareRequest(const std::string &url, const int port)
{
    char domainLen   = static_cast<char>(url.length());
    short domainPort = htons(port);

    int connReqSize = 4 + 1 + domainLen + 2;
    char* connReq = new char[connReqSize];

    std::memcpy(connReq, _connReqDomainBuf, 4);                 // 5, 1, 0, 3
    std::memcpy(connReq + 4, &domainLen, 1);               // Domain Length
    std::memcpy(connReq + 5, url.c_str(), domainLen);      // Domain
    std::memcpy(connReq + 5 + domainLen, &domainPort, 2);  // Port

    if ( ::send(_fd, (char*)connReq, connReqSize, MSG_NOSIGNAL) == -1)
    {
        return -1;
    }

    char recvConn[10];
    if ( ::recv(_fd, recvConn, 10, 0) == -1 )
    {
        return -1;
    }

    std::string resp = serverStatusResponse(recvConn[1]);
    std::cout << "[*] Connection Response: " << resp << std::endl;

    return 0;
}

bool TORSocket::send(const std::string &s, int length) const
{

    if ( ::send(_fd, s.c_str(), length, MSG_NOSIGNAL) == -1)
    {
        return false;
    }

    return true;
}

int TORSocket::recv(char *buf, int len) const
{
    size_t recvLength = ::recv(_fd, buf, len, 0);

    if ( recvLength == -1)
    {
        return -1;
    } else
    {
        return static_cast<int>(recvLength);
    }
}

std::string TORSocket::recvAll(int chunkSize) const
{
    char buffer[chunkSize];
    std::string str;

    int recvLength;
    while ( (recvLength = static_cast<int>(::recv(_fd, buffer, sizeof(buffer), MSG_WAITALL))) > 0 )
    {
        str.append(buffer, static_cast<unsigned long>(recvLength));
    }

    return str;
}

std::string TORSocket::get(const std::string &url, const int port)
{
    std::string domain = getDomainFromUrl(url);

    if (prepareRequest(domain, port) != 0)
    {
        throw SocketException("Error at get connection request!");
    }
    std::cout << "[*] Connected successfully\n" << std::endl;

    std::string route = getRouteFromUrl(url);
    if (route.empty())
    {
        route = "/";
    }
    std::string request = "GET " + route + " HTTP/1.1\r\nHost: " + url + "\r\nCache-Control: no-cache\r\n\r\n\r\n";

    if ( !send(request, request.length()) )
    {
        throw SocketException("Error at sending the request to the Socket!");
    }

    char buf[4096];
    int recvSize = recv(buf, 4096);
    if ( recvSize == -1)
    {
        throw SocketException("Error at receiving the response from the Socket!");
    }

    std::string s(buf, recvSize);

    return s;
}

std::string TORSocket::post(const std::string &url, const std::string &data, int port)
{
    std::string domain = getDomainFromUrl(url);

    if (prepareRequest(domain, port) != 0)
    {
        throw SocketException("Error at post connection request!");
    }
    std::cout << "[*] Connected successfully\n" << std::endl;

    std::string route = getRouteFromUrl(url);
    if (route.empty())
    {
        route = "/";
    }
    std::string request = "POST " + route + " HTTP/1.1\r\nHost: " + url + "\r\nCache-Control: no-cache\r\n\r\n\r\n";

    if ( !send(request, request.length()) )
    {
        throw SocketException("Error at sending the request to the Socket!");
    }

    char buf[4096];
    int recvSize = recv(buf, 4096);
    if ( recvSize == -1)
    {
        throw SocketException("Error at receiving the response from the Socket!");
    }

    std::string s(buf, recvSize);

    return s;
}

} // namespace tools
