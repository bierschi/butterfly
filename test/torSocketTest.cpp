#include <memory>
#include <gtest/gtest.h>

#include "torSocket.h"

/**
 * Testclass TORSocket
 */
class TORSocketTest : public ::testing::Test
{

protected:
    std::string _ip = "127.0.0.1";
    int _port = 9050;
    std::unique_ptr<butterfly::TORSocket> torSocket;

    void SetUp() override
    {
        torSocket = std::unique_ptr<butterfly::TORSocket>(new butterfly::TORSocket(_ip, _port));
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the connect method
 */
TEST_F(TORSocketTest, connect)
{

    bool response = torSocket->connect("", 80);
    EXPECT_TRUE( response );

}

/**
 * Testcase for testing the send method
 */
TEST_F(TORSocketTest, send)
{

    bool response = torSocket->send("");
    EXPECT_TRUE( response );

}

/**
 * Testcase for testing the recv method
 */
TEST_F(TORSocketTest, recv)
{

    char *buf = nullptr;
    int len = 0;
    int rc = torSocket->recv(buf, len);
    EXPECT_TRUE( rc == 0 );

}

/**
 * Testcase for testing the recvAll method
 */
TEST_F(TORSocketTest, recvAll)
{

    int chunkSize = 0;
    bool blocking = false;
    std::string response = torSocket->recvAll(chunkSize, blocking);
    EXPECT_TRUE( response.empty() );

}

/**
 * Testcase for testing the getType method
 */
TEST_F(TORSocketTest, getType)
{

    butterfly::ISocket::Type type = torSocket->getType();
    EXPECT_TRUE( type == butterfly::ISocket::Type::TORSocket );

}
