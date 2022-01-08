
#ifndef BUTTERFLY_TORSOCKET_H
#define BUTTERFLY_TORSOCKET_H

#include "socket.h"

namespace butterfly
{

/**
 * Class TORSocket to establish a proxy connection to the tor network via the tor binary
 */
class TORSocket : public Socket
{

private:
    std::string _ip;
    int _port;

public:
    TORSocket(const std::string ip, const int port);
    ~TORSocket();

};

} // namespace butterfly

#endif //BUTTERFLY_TORSOCKET_H
