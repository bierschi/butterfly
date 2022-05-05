#include <memory>
#include <gtest/gtest.h>

#include "httpRequest.h"
#include "bflyParams.h"

/**
 * Testclass HTTPRequestTest
 */
class HTTPRequestTest : public ::testing::Test
{

protected:
    std::string url = "www.google.de", formParamStr;
    std::vector< std::pair<std::string, std::string> > formParams;
    std::unique_ptr<butterfly::HTTPRequest> httpRequest;

    void SetUp() override
    {
        httpRequest = std::unique_ptr<butterfly::HTTPRequest>(new butterfly::HTTPRequest());
        // Set http request data
        httpRequest->setURL(url);
        httpRequest->setMethod(butterfly::Method::POST);
        httpRequest->setProtocol(butterfly::Protocol::HTTP1_1);
        httpRequest->setHTTPHeader("User-Agent", "butterfly");
        httpRequest->setHTTPHeader("Content-Type", "application/x-www-form-urlencoded");

        formParams.emplace_back(butterfly::params::ENC_CPRIVATERSA_FILENAME, "abcdef123");
        formParams.emplace_back(butterfly::params::RSA_EKIV_FILENAME, "abcdef123");
        formParams.emplace_back("RSAKeySize", std::to_string(butterfly::params::RSA_KEYSIZE));

        httpRequest->addFormParamVector(formParams);
        formParamStr = httpRequest->getFormParam();
        httpRequest->addBody(formParamStr);
        httpRequest->setHTTPHeader("Content-Length", std::to_string(httpRequest->getBody().length()));

        httpRequest->prepareOutgoing();
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the getMethod
 */
TEST_F(HTTPRequestTest, getMethod)
{
    butterfly::Method method = httpRequest->getMethod();

    EXPECT_TRUE(method == butterfly::Method::POST);
}

/**
 * Testcase for testing the getURL
 */
TEST_F(HTTPRequestTest, getURL)
{
    std::string url = httpRequest->getURL();

    EXPECT_TRUE(url == url);
}

/**
 * Testcase for testing the getUserAgent
 */
TEST_F(HTTPRequestTest, getUserAgent)
{
    httpRequest->setUserAgent("butterfly");
    std::string useragent = httpRequest->getUserAgent();

    EXPECT_TRUE(useragent == "butterfly");
}

/**
 * Testcase for testing the getRequestSize
 */
TEST_F(HTTPRequestTest, getRequestSize)
{
    size_t httpDatasize = httpRequest->getHTTPDataSize();

    EXPECT_TRUE( httpDatasize > 0);
}

/**
 * Testcase for testing the getHTTPData
 */
TEST_F(HTTPRequestTest, getHTTPData)
{
    std::string httpdata = httpRequest->getHTTPData();

    EXPECT_TRUE(!httpdata.empty());
}

/**
 * Testcase for testing the getProtocol
 */
TEST_F(HTTPRequestTest, getProtocol)
{

    butterfly::Protocol prot = httpRequest->getProtocol();

    EXPECT_TRUE(prot == butterfly::Protocol::HTTP1_1);
}

/**
 * Testcase for testing the getBody
 */
TEST_F(HTTPRequestTest, getBody)
{
    std::string body = httpRequest->getBody();

    EXPECT_TRUE(body == formParamStr);
}

/**
 * Testcase for testing the getHTTPHeader
 */
TEST_F(HTTPRequestTest, getHTTPHeader)
{
    std::string httpHeaderUserAgent = httpRequest->getHTTPHeader("User-Agent");
    std::string httpHeaderContent = httpRequest->getHTTPHeader("Content-Type");

    EXPECT_TRUE(httpHeaderUserAgent == "butterfly");
    EXPECT_TRUE(httpHeaderContent == "application/x-www-form-urlencoded");
}
