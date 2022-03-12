#include <memory>
#include <gtest/gtest.h>

#include "directoryIterator.h"

/**
 * Testclass DirectoryIteratorTest
 */
class DirectoryIteratorTest : public ::testing::Test
{

protected:
    std::string testDirectory = "../test/";
    std::string testFile = "../test/butterflyUnitTests.cpp";
    std::unique_ptr<butterfly::DirectoryIterator> directoryIterator;

    void SetUp() override
    {
        directoryIterator = std::unique_ptr<butterfly::DirectoryIterator>(new butterfly::DirectoryIterator());
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the isDirectory
 */
TEST_F(DirectoryIteratorTest, isDirectory)
{

    bool isDir = directoryIterator->isDirectory(testDirectory);

    EXPECT_TRUE(isDir == true);
}

/**
 * Testcase for testing the isFile
 */
TEST_F(DirectoryIteratorTest, isFile)
{

    bool isFile = directoryIterator->isFile(testFile);

    EXPECT_TRUE(isFile == true);
}

/**
 * Testcase for testing the getAllFiles
 */
TEST_F(DirectoryIteratorTest, getAllFiles)
{

    auto files = directoryIterator->getAllFiles(testDirectory);

    EXPECT_TRUE(files.size() > 0);

    for(auto &file: files)
    {
        auto isFile = directoryIterator->isFile(file);
        EXPECT_TRUE(isFile == true);
    }
}

/**
 * Testcase for testing the getAllDirectories
 */
TEST_F(DirectoryIteratorTest, getAllDirectories)
{

    auto files = directoryIterator->getAllDirectories(testDirectory);

    EXPECT_TRUE(files.size() > 0);

    for(auto &file: files)
    {
        auto isDir = directoryIterator->isDirectory(file);
        EXPECT_TRUE(isDir == true);
    }
}

/**
 * Testcase for testing the getFilesFromDir
 */
TEST_F(DirectoryIteratorTest, getFilesFromDir)
{

    auto files = directoryIterator->getFilesFromDir(testDirectory);

    EXPECT_TRUE(files.size() > 0);

    for(auto &file: files)
    {
        auto isFile = directoryIterator->isFile(file);
        EXPECT_TRUE(isFile == true);
    }
}

/**
 * Testcase for testing the getFileSize
 */
TEST_F(DirectoryIteratorTest, getFileSize)
{

    uintmax_t fileSize = directoryIterator->getFileSize(testFile);

    EXPECT_TRUE(fileSize > 0);
}

/**
 * Testcase for testing the getFileExtension
 */
TEST_F(DirectoryIteratorTest, getFileExtension)
{

    std::string fileExt = directoryIterator->getFileExtension(testFile);

    EXPECT_TRUE(fileExt == ".cpp");

}