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
