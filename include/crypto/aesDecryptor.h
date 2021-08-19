
#ifndef BUTTERFLY_AESDECRYPTOR_H
#define BUTTERFLY_AESDECRYPTOR_H

#include "aes.h"
#include "utils.h"

namespace butterfly
{

class AESDecryptor : public CryptoAES
{
private:

public:
    AESDecryptor();
    ~AESDecryptor() = default;

    void setAESKey(const std::string &aesKey);
    void setAESIv(const std::string &aesIv);

    void decryptFile2(const std::string &filename);

    void decryptFile(char *filename, char *encryptedFilename);
};

} // namespace butterfly

#endif //BUTTERFLY_AESDECRYPTOR_H
