#include <iostream>
#include <memory>
#include <cstring>

#include "rsa.h"
#include "utils.h"


void encrypt_decrypt_with_evp(std::string msg_to_encrypt)
{
    std::unique_ptr<tools::CryptoRSA> cryptoRSA = std::unique_ptr<tools::CryptoRSA>(new tools::CryptoRSA(2048));

    unsigned char *encryptedMessage = nullptr;
    char *decryptedMessage = nullptr;
    unsigned char *encryptedKey;
    unsigned char *iv;
    size_t encryptedKeyLength;

    std::string priv = cryptoRSA->getRSAPrivateKeyStr();
    std::string pub = cryptoRSA->getPublicKeyStr();

    // Save RSA KeyPair
    writeBinFile("RSAPrivateKey.pem", priv.c_str(), priv.length());
    writeBinFile("PublicKey.pem", pub.c_str(), pub.length());

    // Start RSA Encryption
    int encryptedMessageLength = cryptoRSA->encryptEVP(cryptoRSA->getEvpPkey(), (const unsigned char*)msg_to_encrypt.c_str(), msg_to_encrypt.size()+1,
                                                       &encryptedMessage, &encryptedKey, &encryptedKeyLength, &iv);

    if(encryptedMessageLength == -1)
    {
        std::cerr << "Encryption failed" << std::endl;
        exit(1);
    }

    std::cout << "Encrypted message: " << encryptedMessage << std::endl;
    writeBinFile("enc_msg.bin", reinterpret_cast<const char *>(encryptedMessage), encryptedMessageLength);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Start RSA Decryption
    int decryptedMessageLength = cryptoRSA->decryptEVP(cryptoRSA->getEvpPkey(), encryptedMessage, (size_t)encryptedMessageLength,
                                                       encryptedKey, encryptedKeyLength, iv, (unsigned char**)&decryptedMessage);

    if(decryptedMessageLength == -1)
    {
        std::cerr << "Decryption failed" << std::endl;
        exit(1);
    }

    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

}

void encrypt_with_evp(std::unique_ptr<tools::CryptoRSA> &cryptoRSA)
{


}

void decrypt_with_evp()
{

}

int main(int argc, char* argv[])
{

    encrypt_decrypt_with_evp("abcdef");


    return 0;
}

