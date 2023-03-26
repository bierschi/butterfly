#include <memory>
#include <gtest/gtest.h>

#include "httpServer.h"
#include "httpClient.h"

/**
 * Testclass HTTPServerTest
 */
class HTTPServerTest : public ::testing::Test
{

protected:
    std::string localHostURL;
    int port = 8901;
    std::shared_ptr<butterfly::TCPSocket> tcpSocket;
    std::shared_ptr<butterfly::HTTPServer> httpServer;
    std::shared_ptr<butterfly::HTTPClient> httpClient;

    void SetUp() override
    {
        localHostURL = "http://127.0.0.1/";
        tcpSocket = std::make_shared<butterfly::TCPSocket>();
        httpServer = std::make_shared<butterfly::HTTPServer>(port);
        httpClient = std::make_shared<butterfly::HTTPClient>(tcpSocket);
        httpServer->run(false);
    }

    void TearDown() override
    {
        httpServer->stop();
    }
};

/**
 * Testcase for the browserRoute method
 */
TEST_F(HTTPServerTest, browserRoute)
{
    std::string response = httpClient->get(localHostURL, port);

    EXPECT_TRUE( !response.empty() );
    EXPECT_TRUE(httpClient->statusCode == 302);
}

/**
 * Error Testcase for the post method
 */
TEST_F(HTTPServerTest, errorResponsePost)
{
    std::string response = httpClient->post(localHostURL, "data", port);

    EXPECT_TRUE( response.empty() );
    EXPECT_TRUE(httpClient->statusCode == 404);
}

/**
 * Testcase for the ConnectionException
 */
TEST_F(HTTPServerTest, ConnectionException)
{

    EXPECT_THROW({

        httpClient->get("http://127.0.0.5", 2565);

        }, butterfly::ConnectionException);

}
