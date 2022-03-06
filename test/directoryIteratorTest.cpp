#include <memory>
#include <gtest/gtest.h>

#include "directoryIterator.h"

/**
 * Testclass DirectoryIteratorTest
 */
class DirectoryIteratorTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::DirectoryIterator> directoryIterator;

    void SetUp() override
    {
        directoryIterator = std::unique_ptr<butterfly::DirectoryIterator>(new butterfly::DirectoryIterator());
    }

    void TearDown() override
    {

    }
};
