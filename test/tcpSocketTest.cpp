#include <memory>
#include <gtest/gtest.h>

#include "tcpSocket.h"

/**
 * Testclass TCPSocket
 */
class TCPSocket : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::TCPSocket> _tcpSocket;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};
