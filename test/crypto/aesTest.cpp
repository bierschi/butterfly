#include <memory>
#include <gtest/gtest.h>

#include "crypto/aes.h"

/**
 * Testclass CryptoAESTest
 */
class CryptoAESTest : public ::testing::Test
{

protected:
    std::string aeskeyTest = "0123456789abcefghijklmnopqrstuvw", aesivTest = "0123456789abcefg";
    std::unique_ptr<butterfly::aes::CryptoAES> cryptoAES;

    void SetUp() override
    {
        cryptoAES = std::unique_ptr<butterfly::aes::CryptoAES>(new butterfly::aes::CryptoAES());
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the AESKey
 */
TEST_F(CryptoAESTest, getAESKey)
{
    std::string aeskey = cryptoAES->getAESKey();
    EXPECT_TRUE( aeskey.length() == 32);
    EXPECT_FALSE(aeskey.length() == 33);
}

/**
 * Testcase for testing the AESIV
 */
TEST_F(CryptoAESTest, getAESIv)
{
    std::string aesiv = cryptoAES->getAESIv();
    EXPECT_TRUE( aesiv.length() == 16);
    EXPECT_FALSE(aesiv.length() == 17);
}

/**
 * Testcase for testing the AESKeyPair
 */
TEST_F(CryptoAESTest, getAESKeyPair)
{
    std::string aeskeypair = cryptoAES->getAESKeyPair();
    EXPECT_TRUE( aeskeypair.length() == 48);
    EXPECT_FALSE(aeskeypair.length() == 49);
}

/**
 * Testcase for testing the AESKeyLength
 */
TEST_F(CryptoAESTest, getAESKeyLength)
{
    int aeskeyLength = cryptoAES->getAESKeyLength();
    EXPECT_TRUE( aeskeyLength == 32);
    EXPECT_FALSE(aeskeyLength == 33);
}

/**
 * Testcase for testing the AESIVLength
 */
TEST_F(CryptoAESTest, getAESIVLength)
{
    int aesivLength = cryptoAES->getAESIVLength();
    EXPECT_TRUE( aesivLength == 16);
    EXPECT_FALSE(aesivLength == 17);
}

/**
 * Testcase for testing the setAESKey
 */
TEST_F(CryptoAESTest, setAESKey)
{
    cryptoAES->setAESKey(aeskeyTest);
    std::string aeskey = cryptoAES->getAESKey();
    EXPECT_TRUE( aeskey.length() == 32);
    EXPECT_TRUE( aeskey == aeskeyTest);
}

/**
 * Testcase for testing the setAESIv
 */
TEST_F(CryptoAESTest, setAESIv)
{
    cryptoAES->setAESIv(aesivTest);
    std::string aesiv = cryptoAES->getAESIv();
    EXPECT_TRUE(aesiv.length() == 16);
    EXPECT_TRUE(aesiv == aesivTest);
}
