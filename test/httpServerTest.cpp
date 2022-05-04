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
    std::string localhostURL;
    int port = 8901;
    std::shared_ptr<butterfly::HTTPServer> httpServer;
    std::shared_ptr<butterfly::HTTPClient> httpClient;

    void SetUp() override
    {
        localhostURL = "http://127.0.0.1/";
        httpServer = std::make_shared<butterfly::HTTPServer>(port);
        httpClient = std::make_shared<butterfly::HTTPClient>();
        httpServer->run(false);
    }

    void TearDown() override
    {
        httpServer->stop();
    }
};
