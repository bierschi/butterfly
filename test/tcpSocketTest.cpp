#include <memory>
#include <gtest/gtest.h>
#include <thread>

#include "tcpSocket.h"

/**
 * Testclass TCPSocket
 */
class TCPSocketTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::TCPSocket> serverSocket;
    std::unique_ptr<butterfly::TCPSocket> clientSocket;

    void SetUp() override
    {
        serverSocket = std::unique_ptr<butterfly::TCPSocket>(new butterfly::TCPSocket());
        clientSocket = std::unique_ptr<butterfly::TCPSocket>(new butterfly::TCPSocket());
        serverSocket->bind(2347);
        serverSocket->listen();
    }

    void TearDown() override
    {
        clientSocket->disconnect();
        serverSocket->disconnect();
    }

public:
    void sendToSocket()
    {
        if ( clientSocket->connect("localhost", 2347) )
        {
            clientSocket->send("testMessage");
        }

    }
};

/**
 * Testcase for testing the accept
 */
TEST_F(TCPSocketTest, accept)
{
    std::unique_ptr<butterfly::TCPSocket> testSocket = std::unique_ptr<butterfly::TCPSocket>(new butterfly::TCPSocket());
    testSocket->connect("localhost", 2347);

    std::shared_ptr<butterfly::TCPSocket> newSocket = serverSocket->accept();
    int fd = newSocket->getFileDescriptor();
    EXPECT_TRUE(fd != -1);

    testSocket->disconnect();
}

/**
 * Testcase for testing the send
 */
TEST_F(TCPSocketTest, send)
{
    if ( clientSocket->connect("localhost", 2347) )
    {
        bool rc = clientSocket->send("test");
        EXPECT_TRUE( rc == true );
    } else
    {
        std::cerr << "Could not connect to localhost in send test method!" << std::endl;
    }

}

/**
 * Testcase for testing the recv
 */
TEST_F(TCPSocketTest, recv)
{
    std::thread t(&TCPSocketTest::sendToSocket, this);
    t.join();

    std::shared_ptr<butterfly::TCPSocket> newSocket  = serverSocket->accept();
    char s[1024];
    int size = newSocket->recv(s, 1024);

    EXPECT_TRUE( size != 0 );
    EXPECT_TRUE(size == 11);
}

/**
 * Testcase for testing the recvAll
 */
TEST_F(TCPSocketTest, recvAll)
{
    std::thread t(&TCPSocketTest::sendToSocket, this);
    t.join();

    std::shared_ptr<butterfly::TCPSocket> newSocket  = serverSocket->accept();
    std::string s = newSocket->recvAll(1024);

    EXPECT_TRUE( !s.empty() );
    EXPECT_TRUE(s.length() == 11);
    EXPECT_FALSE(s.length() == 10);
}