#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsaDecryptor.h"

/**
 * Testclass CryptoRSATest
 */
class RSADecryptorTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor;

    void SetUp() override
    {
        rsaDecryptor.reset(new butterfly::rsa::RSADecryptor("../masterkeys/SPrivateRSA.pem"));
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for CPrivateRSA.bin file
 */
TEST_F(RSADecryptorTest, CPrivateRSA_String)
{
    std::string encCPrivateRSA = rsaDecryptor->getBinKeyFileContents("CPrivateRSA.bin");
    ASSERT_TRUE( !encCPrivateRSA.empty());
}

/**
 * Testcase for Decryption
 */
TEST_F(RSADecryptorTest, Decryption)
{

    std::string encCPrivateRSA = rsaDecryptor->getBinKeyFileContents("CPrivateRSA.bin");
    ASSERT_TRUE( !encCPrivateRSA.empty());

    rsaDecryptor->decryptEVP(rsaDecryptor->getEvpPkey(), encCPrivateRSA);

    std::string decryptedMessage = rsaDecryptor->getDecryptedMessage();
    ASSERT_TRUE( !decryptedMessage.empty());

    butterfly::writeBinFile("CPrivateRSA.pem.dec", decryptedMessage.c_str(), static_cast<long>(decryptedMessage.length()));
}

