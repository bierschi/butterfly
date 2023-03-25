#include <memory>
#include <gtest/gtest.h>

#include "tcpSocket.h"
#include "httpClient.h"
#include "httpServer.h"

/**
 * Testclass HTTPClientTest
 */
class HTTPClientTest : public ::testing::Test
{

protected:
    std::string googleURL, localHostURL;
    int port = 8900;
    std::shared_ptr<butterfly::TCPSocket> tcpSocket;
    std::shared_ptr<butterfly::HTTPClient> httpClient;
    std::shared_ptr<butterfly::HTTPServer> httpServer;

    void SetUp() override
    {
        googleURL = "www.google.de";
        localHostURL = "http://127.0.0.1/";
        tcpSocket = std::make_shared<butterfly::TCPSocket>();
        httpClient = std::make_shared<butterfly::HTTPClient>(tcpSocket);
        httpServer = std::make_shared<butterfly::HTTPServer>(port);
        httpServer->run(false);
    }

    void TearDown() override
    {
        httpServer->stop();
    }
};

/**
 * Testcase for the get method
 */
TEST_F(HTTPClientTest, get)
{

    std::string response = httpClient->get(googleURL, 80);

    EXPECT_TRUE( !response.empty() );
    EXPECT_TRUE(httpClient->statusCode == 200);
}

/**
 * Testcase for the post method
 */
TEST_F(HTTPClientTest, post)
{
    std::string response = httpClient->post(localHostURL, "data", port);

    EXPECT_TRUE(httpClient->statusCode == 404);
}

/**
 * Testcase for the ConnectionException
 */
TEST_F(HTTPClientTest, ConnectionException)
{

    EXPECT_THROW({

        httpClient->get("http://127.0.0.5", 80);
        }, butterfly::ConnectionException);

}
