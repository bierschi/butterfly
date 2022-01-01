#include <iostream>
#include <memory>
#include <unistd.h>

#include "rsa.h"
#include "utils.h"

#define RSA_PRIVATE_KEY "RSAPrivateKey.pem"
#define PUBLIC_KEY      "PublicKey.pem"
#define ENCRYPTED_FILE  "encrypted.bin"
#define RSA_EK_FILE     "rsa_ek.bin"
#define RSA_IV_FILE     "rsa_iv.txt"

void encrypt_decrypt_with_evp(std::string msg_to_encrypt)
{
    std::unique_ptr<tools::CryptoRSA> cryptoRSA = std::unique_ptr<tools::CryptoRSA>(new tools::CryptoRSA(4096));

    std::string priv = cryptoRSA->getRSAPrivateKeyStr();
    std::string pub = cryptoRSA->getPublicKeyStr();

    // Save RSA KeyPair
    writeBinFile(RSA_PRIVATE_KEY, priv.c_str(), priv.length());
    writeBinFile(PUBLIC_KEY, pub.c_str(), pub.length());

    // Start RSA Encryption
    unsigned char *encryptedMessage = nullptr;
    int encryptedMessageLength = cryptoRSA->encryptEVP(cryptoRSA->getEvpPkey(), (const unsigned char*)msg_to_encrypt.c_str(), msg_to_encrypt.size()+1, &encryptedMessage);

    if(encryptedMessageLength == -1)
    {
        std::cerr << "Encryption failed" << std::endl;
        exit(1);
    }

    std::string rsaek = reinterpret_cast<const char *>(cryptoRSA->getRSAEncryptedKey());
    std::string rsaiv = reinterpret_cast<const char *>(cryptoRSA->getRSAIV());

    writeBinFile(ENCRYPTED_FILE, reinterpret_cast<const char *>(encryptedMessage), encryptedMessageLength);
    writeBinFile(RSA_EK_FILE, rsaek.c_str(), rsaek.length());
    writeBinFile(RSA_IV_FILE, rsaiv.c_str(), rsaiv.length());

    std::cout << "Encrypted message: " << encryptedMessage << std::endl;


    sleep(1);


    std::string rsaek_dec = readBinFile(RSA_EK_FILE);
    std::string rsaiv_dec = readBinFile(RSA_IV_FILE);

    // Decrypt the encrypted Message
    char *decryptedMessage = nullptr;
    int decryptedMessageLength = cryptoRSA->decryptEVP(cryptoRSA->getEvpPkey(), encryptedMessage, encryptedMessageLength, (unsigned char *) rsaek_dec.c_str(), (unsigned char *) rsaiv_dec.c_str(), (unsigned char**)&decryptedMessage);

    if(decryptedMessageLength == -1)
    {
        std::cerr << "Decryption failed" << std::endl;
        exit(1);
    }

    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

}

void encrypt_with_evp(std::string msg_to_encrypt)
{
    std::unique_ptr<tools::CryptoRSA> cryptoRSA = std::unique_ptr<tools::CryptoRSA>(new tools::CryptoRSA(2048));

    std::string privateKeyStr = cryptoRSA->getRSAPrivateKeyStr();
    std::string pubKeyStr = cryptoRSA->getPublicKeyStr();

    // Save RSA KeyPair
    writeBinFile(RSA_PRIVATE_KEY, privateKeyStr.c_str(), privateKeyStr.length());
    writeBinFile(PUBLIC_KEY, pubKeyStr.c_str(), pubKeyStr.length());

    // Start RSA Encryption
    unsigned char *encryptedMessage = nullptr;
    int encryptedMessageLength = cryptoRSA->encryptEVP(cryptoRSA->getEvpPkey(), (const unsigned char*)msg_to_encrypt.c_str(), msg_to_encrypt.size(), &encryptedMessage);

    if(encryptedMessageLength == -1)
    {
        std::cerr << "RSA Encryption failed! Exiting..." << std::endl;
        exit(1);
    }

    // Save EK and IV (AES) for the RSA Decryption
    unsigned char* rsaek = cryptoRSA->getRSAEncryptedKey();
    unsigned char* rsaiv = cryptoRSA->getRSAIV();

    // Finally save all files
    writeBinFile(ENCRYPTED_FILE, reinterpret_cast<const char *>(encryptedMessage), encryptedMessageLength);
    writeBinFile(RSA_EK_FILE, reinterpret_cast<const char *>(rsaek), cryptoRSA->getEvpPkeySize(cryptoRSA->getEvpPkey()));
    writeBinFile(RSA_IV_FILE, reinterpret_cast<const char *>(rsaiv), EVP_MAX_IV_LENGTH);
}

void decrypt_with_evp()
{

    std::string privateKeyStr = readBinFile(RSA_PRIVATE_KEY);
    std::unique_ptr<tools::CryptoRSA> cryptoRSA = std::unique_ptr<tools::CryptoRSA>(new tools::CryptoRSA(privateKeyStr));

    // Read EK and IV
    std::string encryptedMessage = readBinFile(ENCRYPTED_FILE);
    std::string rsaek = readBinFile(RSA_EK_FILE);
    std::string rsaiv = readBinFile(RSA_IV_FILE);

    // Decrypt the encrypted Message
    char *decryptedMessage = nullptr;
    int decryptedMessageLength = cryptoRSA->decryptEVP(cryptoRSA->getEvpPkey(), (unsigned char *) encryptedMessage.c_str(), encryptedMessage.length(), (unsigned char *) rsaek.c_str(), (unsigned char *) rsaiv.c_str(), (unsigned char**)&decryptedMessage);

    if(decryptedMessageLength == -1)
    {
        std::cerr << "RSA Decryption failed! Exiting..." << std::endl;
        exit(1);
    }

    std::string str(reinterpret_cast<const char *>(decryptedMessage), static_cast<unsigned long>(decryptedMessageLength));
    std::cout << "Decrypted message: " << str << " with length of: " << decryptedMessageLength<< std::endl;
}

int main(int argc, char* argv[])
{

    //encrypt_with_evp("abcdef");
    decrypt_with_evp();
    return 0;
}

