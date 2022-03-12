#include <memory>
#include <gtest/gtest.h>

#include "httpResponse.h"

/**
 * Testclass HTTPResponseTest
 */
class HTTPResponseTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::HTTPResponse> httpResponse;

    void SetUp() override
    {
        httpResponse = std::unique_ptr<butterfly::HTTPResponse>(new butterfly::HTTPResponse());
        // Set http response data
        httpResponse->setProtocol(butterfly::Protocol::HTTP1_1);
        httpResponse->setStatusCode(200);
        httpResponse->setReasonPhrase(200);
        httpResponse->setHTTPHeader("User-Agent", "butterfly");
        httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");
        httpResponse->addBody("<!DOCTYPE html><html><body><h1>Test Message</h1></body></html>");
        httpResponse->setHTTPHeader("Content-Length", std::to_string(httpResponse->getBody().length()));

        httpResponse->prepareOutgoing();
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the getProtocol
 */
TEST_F(HTTPResponseTest, getProtocol)
{

    butterfly::Protocol prot = httpResponse->getProtocol();

    EXPECT_TRUE(prot == butterfly::Protocol::HTTP1_1);
}

/**
 * Testcase for testing the getStatusCode
 */
TEST_F(HTTPResponseTest, getStatusCode)
{
    size_t statuscode = httpResponse->getStatusCode();

    EXPECT_TRUE(statuscode == 200);
}

/**
 * Testcase for testing the getReasonPhrase
 */
TEST_F(HTTPResponseTest, getReasonPhrase)
{
    std::string reason = httpResponse->getReasonPhrase();

    EXPECT_TRUE(reason == "OK");
}

/**
 * Testcase for testing the getHTTPHeader
 */
TEST_F(HTTPResponseTest, getHTTPHeader)
{
    std::string httpHeaderUserAgent = httpResponse->getHTTPHeader("User-Agent");
    std::string httpHeaderContent = httpResponse->getHTTPHeader("Content-Type");

    EXPECT_TRUE(httpHeaderUserAgent == "butterfly");
    EXPECT_TRUE(httpHeaderContent == "text/html; charset=utf8");
}

/**
 * Testcase for testing the getBody
 */
TEST_F(HTTPResponseTest, getBody)
{
    std::string body = httpResponse->getBody();

    EXPECT_TRUE(body == "<!DOCTYPE html><html><body><h1>Test Message</h1></body></html>");
}

/**
 * Testcase for testing the getHTTPData
 */
TEST_F(HTTPResponseTest, getHTTPData)
{
    std::string httpdata = httpResponse->getHTTPData();

    EXPECT_TRUE(!httpdata.empty());
}

/**
 * Testcase for testing the getRequestSize
 */
TEST_F(HTTPResponseTest, getRequestSize)
{
    size_t httpDatasize = httpResponse->getResponseSize();

    EXPECT_TRUE( httpDatasize > 0);
}
