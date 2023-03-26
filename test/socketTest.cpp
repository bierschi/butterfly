#include <memory>
#include <gtest/gtest.h>

#include "socket.h"

/**
 * Testclass Socket
 */
class SocketTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::Socket> clientSocket;
    std::unique_ptr<butterfly::Socket> serverSocket;

    void SetUp() override
    {
        clientSocket = std::unique_ptr<butterfly::Socket>(new butterfly::Socket(AF_INET, SOCK_STREAM, 0));
        serverSocket = std::unique_ptr<butterfly::Socket>(new butterfly::Socket(AF_INET, SOCK_STREAM, 0));
        serverSocket->bind(2346);
        serverSocket->listen();
    }

    void TearDown() override
    {
        clientSocket->disconnect();
        serverSocket->disconnect();
    }
};

/**
 * Testcase for testing the getFileDescriptor method
 */
TEST_F(SocketTest, getFileDescriptor)
{
    int fd = clientSocket->getFileDescriptor();
    EXPECT_TRUE( fd != -1 );
}

/**
 * Testcase for testing the shutdown method
 */
TEST_F(SocketTest, shutdown)
{
    std::unique_ptr<butterfly::Socket> testSocket = std::unique_ptr<butterfly::Socket>(new butterfly::Socket(AF_INET, SOCK_STREAM, 0));
    if (testSocket->connect("localhost", 2346))
    {
        bool rc = testSocket->shutdown();
        EXPECT_TRUE( rc == true );
    } else
    {
        std::cerr << "Could not connect to localhost in shutdown test!" << std::endl;
    }

}

/**
 * Testcase for testing the bind method
 */
TEST_F(SocketTest, bind)
{
    bool rc = clientSocket->bind(2345);
    EXPECT_TRUE( rc == true );
}

/**
 * Testcase for testing the listen method
 */
TEST_F(SocketTest, listen)
{
    bool rc = clientSocket->listen();
    EXPECT_TRUE( rc == true );
}

/**
 * Testcase for testing the accept method
 */
TEST_F(SocketTest, accept)
{
    std::unique_ptr<butterfly::Socket> testSocket = std::unique_ptr<butterfly::Socket>(new butterfly::Socket(AF_INET, SOCK_STREAM, 0));
    testSocket->connect("localhost", 2346);

    std::shared_ptr<butterfly::Socket> newSocket = serverSocket->accept();
    int fd = newSocket->getFileDescriptor();
    EXPECT_TRUE(fd != -1);

    testSocket->disconnect();
}

/**
 * Testcase for testing the connect method
 */
TEST_F(SocketTest, connect)
{
    bool rc = clientSocket->connect("localhost", 2346);
    EXPECT_TRUE( rc == true );
}

/**
 * Testcase for testing the disconnect method
 */
TEST_F(SocketTest, disconnect)
{
    bool rc = clientSocket->disconnect();
    EXPECT_TRUE( rc == true );
}

/**
 * Testcase for testing the hostnameToIP method
 */
TEST_F(SocketTest, hostnameToIP)
{
    std::string ip;
    int rc = clientSocket->hostnameToIP("localhost", ip);
    EXPECT_TRUE( !ip.empty() );
    EXPECT_TRUE( rc != -1 );
}

/**
 * Testcase for testing the send method
 */
TEST_F(SocketTest, send)
{

    bool response = clientSocket->send("");
    EXPECT_TRUE( response );

}

/**
 * Testcase for testing the recv method
 */
TEST_F(SocketTest, recv)
{

    char *buf = nullptr;
    int len = 0;
    int rc = clientSocket->recv(buf, len);
    EXPECT_TRUE( rc == 0 );

}

/**
 * Testcase for testing the recvAll method
 */
TEST_F(SocketTest, recvAll)
{

    int chunkSize = 0;
    bool blocking = false;
    std::string response = clientSocket->recvAll(chunkSize, blocking);
    EXPECT_TRUE( response.empty() );

}

/**
 * Testcase for testing the getType method
 */
TEST_F(SocketTest, getType)
{

    butterfly::ISocket::Type type = clientSocket->getType();
    EXPECT_TRUE( type == butterfly::ISocket::Type::Socket );

}
