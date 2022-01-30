#include <memory>
#include <gtest/gtest.h>

#include "httpRequest.h"

// TODO Replace data with actual http data
/**
 * Testclass HTTPRequest
 */
class HTTPRequestTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::HTTPRequest> httpRequest;

    void SetUp() override
    {
        httpRequest = std::unique_ptr<butterfly::HTTPRequest>(new butterfly::HTTPRequest());
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the setMethod
 */
TEST_F(HTTPRequestTest, setMethod)
{
    butterfly::Method m = butterfly::Method::GET;
    httpRequest->setMethod(m);
    butterfly::Method newM = httpRequest->getMethod();

    EXPECT_TRUE(newM == butterfly::Method::GET);
    EXPECT_FALSE(newM == butterfly::Method::POST);
}

/**
 * Testcase for testing the getMethod
 */
TEST_F(HTTPRequestTest, getMethod)
{
    butterfly::Method m = butterfly::Method::GET;
    httpRequest->setMethod(m);
    butterfly::Method newM = httpRequest->getMethod();

    EXPECT_TRUE(newM == butterfly::Method::GET);
}

/**
 * Testcase for testing the setgetURL
 */
TEST_F(HTTPRequestTest, setgetURL)
{
    httpRequest->setURL("www.google.de");
    std::string url = httpRequest->getURL();

    EXPECT_TRUE(url == "www.google.de");
}

/**
 * Testcase for testing the setgetUserAgent
 */
TEST_F(HTTPRequestTest, setgetUserAgent)
{
    std::string useragent = "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0";
    httpRequest->setUserAgent(useragent);
    std::string newuseragent = httpRequest->getUserAgent();

    EXPECT_TRUE(useragent == newuseragent);
}

/**
 * Testcase for testing the getRequestSize
 */
TEST_F(HTTPRequestTest, getRequestSize)
{

}

/**
 * Testcase for testing the addgetHTTPData
 */
TEST_F(HTTPRequestTest, addgetHTTPData)
{
    httpRequest->addHTTPData("httpData");
    std::string httpdata = httpRequest->getHTTPData();

    EXPECT_TRUE(httpdata == "httpData");
}

/**
 * Testcase for testing the setgetProtocol
 */
TEST_F(HTTPRequestTest, setgetProtocol)
{
    butterfly::Protocol prot = butterfly::Protocol::HTTP1_1;
    httpRequest->setProtocol(prot);
    butterfly::Protocol newProt = httpRequest->getProtocol();

    EXPECT_TRUE(prot == newProt);
}

/**
 * Testcase for testing the addgetBody
 */
TEST_F(HTTPRequestTest, addgetBody)
{
    httpRequest->addBody("body");
    std::string body = httpRequest->getBody();

    EXPECT_TRUE(body == "body");
}

/**
 * Testcase for testing the setgetHTTPHeader
 */
TEST_F(HTTPRequestTest, setgetHTTPHeader)
{
    httpRequest->setHTTPHeader("UserAgent", "userdata");
    std::string httpheader = httpRequest->getHTTPHeader("UserAgent");

    EXPECT_TRUE(httpheader == "userdata");
}
