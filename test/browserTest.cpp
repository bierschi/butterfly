#include <memory>
#include <gtest/gtest.h>

#include "browser.h"

/**
 * Testclass BrowserTest
 */
class BrowserTest : public ::testing::Test
{

protected:
    std::string url, terminalCMD;
    std::shared_ptr<butterfly::Browser> browser;
    std::shared_ptr<butterfly::Browser> browserException;

    void SetUp() override
    {
        url = "http://127.0.0.1:8080";
        terminalCMD = "x-www-browser";
        browser = std::make_shared<butterfly::Browser>(terminalCMD);
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the open method
 */
TEST_F(BrowserTest, open)
{

    EXPECT_NO_THROW(browser->open(url));

}

/**
 * Testcase for testing the close method
 */
TEST_F(BrowserTest, close)
{

    EXPECT_NO_THROW(browser->close());

}