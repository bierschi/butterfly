
#ifndef BUTTERFLY_HTTPSERVER_H
#define BUTTERFLY_HTTPSERVER_H

#include "tcpSocket.h"

namespace butterfly
{

class HTTPServer : public TCPSocket
{

private:

public:

    HTTPServer();
    ~HTTPServer() override = default;

};

} // namespace butterfly

#endif //BUTTERFLY_HTTPSERVER_H
