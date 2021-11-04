#include <memory>
#include <gtest/gtest.h>

#include "connManager.h"

/**
 * Testclass ConnManager
 */
class ConnManager : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::ConnManager> _connManager;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};
