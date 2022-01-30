#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsaDecryptor.h"

/**
 * Testclass RSADecryptorTest
 */
class RSADecryptorTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor;

    void SetUp() override
    {
        rsaDecryptor = std::unique_ptr<butterfly::rsa::RSADecryptor>(new butterfly::rsa::RSADecryptor("../masterkeys/SPrivateRSA.pem"));
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for RSA Decryption
 */
TEST_F(RSADecryptorTest, rsaDecryption)
{

    std::string encCPrivateRSA = rsaDecryptor->readEncMSGFromFile(butterfly::ENC_CPRIVATERSA_FILENAME);
    ASSERT_TRUE( !encCPrivateRSA.empty());

    std::string decryptedMessage;
    int decLen = rsaDecryptor->decryptEVP(rsaDecryptor->getEvpPkey(), encCPrivateRSA, decryptedMessage, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
    ASSERT_TRUE(decLen != -1);

    ASSERT_TRUE( !decryptedMessage.empty());

    butterfly::writeBinFile("CPrivateRSA.pem.dec", decryptedMessage.c_str(), decLen);
}
