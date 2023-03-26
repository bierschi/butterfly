#include <memory>
#include <gtest/gtest.h>

#include "httpResponse.h"

/**
 * Testclass HTTPResponseTest
 */
class HTTPResponseTest : public ::testing::Test
{

protected:
    std::string _userAgent = "butterfly", _contentType = "text/html; charset=utf8", _body = "<!DOCTYPE html><html><body><h1>Test Message</h1></body></html>";
    butterfly::Protocol _protocol = butterfly::Protocol::HTTP1_1;
    std::unique_ptr<butterfly::HTTPResponse> httpResponse;

    void SetUp() override
    {
        httpResponse = std::unique_ptr<butterfly::HTTPResponse>(new butterfly::HTTPResponse());
        // Set http response data
        httpResponse->setProtocol(_protocol);
        httpResponse->setStatusCode(200);
        httpResponse->setReasonPhrase(200);
        httpResponse->setHTTPHeader("User-Agent", _userAgent);
        httpResponse->setHTTPHeader("Content-Type", _contentType);
        httpResponse->addBody(_body);
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

    butterfly::Protocol protocol = httpResponse->getProtocol();

    EXPECT_TRUE(protocol == _protocol);
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
    std::string httpHeaderContentType = httpResponse->getHTTPHeader("Content-Type");

    EXPECT_TRUE(httpHeaderUserAgent == _userAgent);
    EXPECT_TRUE(httpHeaderContentType == _contentType);
}

/**
 * Testcase for testing the getBody
 */
TEST_F(HTTPResponseTest, getBody)
{
    std::string body = httpResponse->getBody();

    EXPECT_TRUE(body == _body);
}

/**
 * Testcase for testing the getHTTPData
 */
TEST_F(HTTPResponseTest, getHTTPData)
{
    std::string httpdata = httpResponse->getHTTPData();

    EXPECT_TRUE( !httpdata.empty() );
}

/**
 * Testcase for testing the getRequestSize
 */
TEST_F(HTTPResponseTest, getRequestSize)
{
    size_t httpDatasize = httpResponse->getHTTPDataSize();

    EXPECT_TRUE( httpDatasize > 0 );
}
