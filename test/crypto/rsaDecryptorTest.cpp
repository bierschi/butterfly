#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsaDecryptor.h"

/**
 * Testclass RSADecryptorTest
 */
class RSADecryptorTest : public ::testing::Test
{

protected:
    std::string cprivatersaDec;
    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor;

    void SetUp() override
    {
        cprivatersaDec = "CPrivateRSA.pem.dec";
        rsaDecryptor = std::unique_ptr<butterfly::rsa::RSADecryptor>(new butterfly::rsa::RSADecryptor("../masterkeys/SPrivateRSA.pem"));
    }

    void TearDown() override
    {
        if ( butterfly::existsFile(butterfly::params::ENC_CPRIVATERSA_FILENAME) )
        {
            butterfly::removeFile(butterfly::params::ENC_CPRIVATERSA_FILENAME);
        }

        if ( butterfly::existsFile(cprivatersaDec) )
        {
            butterfly::removeFile(cprivatersaDec);
        }

        if ( butterfly::existsFile(butterfly::params::RSA_EKIV_FILENAME) )
        {
            butterfly::removeFile(butterfly::params::RSA_EKIV_FILENAME);
        }

        if ( butterfly::existsFile(butterfly::params::ENC_AESKEY_FILENAME) )
        {
            butterfly::removeFile(butterfly::params::ENC_AESKEY_FILENAME);
        }
    }
};

/**
 * Testcase for RSA Decryption
 */
TEST_F(RSADecryptorTest, rsaDecryption)
{

    std::string encCPrivateRSA = rsaDecryptor->readEncMSGFromFile(butterfly::params::ENC_CPRIVATERSA_FILENAME);
    ASSERT_TRUE(!encCPrivateRSA.empty());

    std::string decryptedMessage;
    int decLen = rsaDecryptor->decryptEVP(rsaDecryptor->getEvpPkey(), encCPrivateRSA, decryptedMessage, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
    ASSERT_TRUE(decLen != -1);

    ASSERT_TRUE(!decryptedMessage.empty());

    butterfly::writeBinFile(cprivatersaDec, decryptedMessage.c_str(), decLen);
}
