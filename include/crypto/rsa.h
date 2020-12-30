
#ifndef BUTTERFLY_RSA_H
#define BUTTERFLY_RSA_H

#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#define KEYSIZE 2048

namespace butterfly {

class CryptoRSA {
private:
    RSA *_rsa;

    bool createRSAKey();

public:
    CryptoRSA();
    ~CryptoRSA();

    bool generateRSAKeyPair();

};

} // namespace butterfly
#endif //BUTTERFLY_RSA_H
