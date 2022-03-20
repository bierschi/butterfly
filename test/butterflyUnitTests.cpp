#include <gtest/gtest.h>

#define FILTER false

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    if ( FILTER )
    {
        int rc;

        ::testing::GTEST_FLAG(filter) = "CryptoAESTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "AESEncryptorTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "AESDecryptorTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "CryptoRSATest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "RSAEncryptorTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "RSADecryptorTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "SocketTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "TCPSocketTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "DirectoryIteratorTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "HTTPRequestTest.*";
        rc = RUN_ALL_TESTS();

        ::testing::GTEST_FLAG(filter) = "HTTPResponseTest.*";
        rc = RUN_ALL_TESTS();

        return rc;
    } else
    {
        return RUN_ALL_TESTS();
    }
}