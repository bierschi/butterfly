#include <memory>
#include <gtest/gtest.h>

#include "httpResponse.h"

/**
 * Testclass HTTPResponse
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
        httpResponse->setReasonPhrase(200);
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
 * Testcase for testing the setgetStatusCode
 */
TEST_F(HTTPResponseTest, setgetStatusCode)
{
    httpResponse->setStatusCode(500);
    size_t statuscode = httpResponse->getStatusCode();

    EXPECT_TRUE(statuscode == 500);
}

/**
 * Testcase for testing the setgetReasonPhrase
 */
TEST_F(HTTPResponseTest, setgetReasonPhrase)
{
    httpResponse->setReasonPhrase(500);
    std::string reason = httpResponse->getReasonPhrase();

    EXPECT_TRUE(reason == "Internal Server Error");
}