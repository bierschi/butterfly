#include <memory>
#include <gtest/gtest.h>

#include "tcpSocket.h"

/**
 * Testclass TCPSocket
 */
class TCPSocket : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::TCPSocket> serverSocket;
    std::unique_ptr<butterfly::TCPSocket> clientSocket;

    void SetUp() override
    {
        serverSocket = std::unique_ptr<butterfly::TCPSocket>(new butterfly::TCPSocket());
        clientSocket = std::unique_ptr<butterfly::TCPSocket>(new butterfly::TCPSocket());
    }

    void TearDown() override
    {

    }
};
