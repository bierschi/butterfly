#include <memory>
#include <gtest/gtest.h>

#include "connManager.h"

/**
 * Testclass ConnManager
 */
class ConnManagerTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::ConnManager> connManager;

    void SetUp() override
    {
        connManager = std::unique_ptr<butterfly::ConnManager>(new butterfly::ConnManager());
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the registerConnStateChangeCB method
 */
TEST_F(ConnManagerTest, registerConnStateChangeCB)
{

    std::function<void(bool)> cb;
    EXPECT_NO_THROW(connManager->registerConnStateChangeCB(cb));

}

/**
 * Testcase for testing the isInternetAvailable method
 */
TEST_F(ConnManagerTest, isInternetAvailable)
{

    EXPECT_TRUE(connManager->isInternetAvailable());

}

/**
 * Testcase for testing the start method
 */
TEST_F(ConnManagerTest, start)
{

    EXPECT_NO_THROW(connManager->start());

}

/**
 * Testcase for testing the stop method
 */
TEST_F(ConnManagerTest, stop)
{

    EXPECT_NO_THROW(connManager->stop());

}