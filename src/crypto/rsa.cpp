
#include "crypto/rsa.h"

namespace butterfly {

CryptoRSA::CryptoRSA() {
    createRSAKey();
}

CryptoRSA::~CryptoRSA() {
    RSA_free(_rsa);
}

bool CryptoRSA::createRSAKey() {

    _rsa = RSA_new();

    if (_rsa != NULL) {
        BIGNUM *e = BN_new();
        return e != NULL && BN_set_word(e, RSA_F4) && RSA_generate_key_ex(_rsa, KEYSIZE, e, NULL);
    } else {
        return false;
    }
}

bool CryptoRSA::generateRSAKeyPair() {


    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pkey, _rsa);

    FILE* f_pri = fopen("pri.key", "wb");
    FILE* f_pub = fopen("pub.pem", "wb");

    PEM_write_RSAPublicKey(f_pub, _rsa);
    PEM_write_RSAPrivateKey(f_pri, _rsa, nullptr, nullptr, 0, nullptr, nullptr);

    fclose(f_pri);
    fclose(f_pub);

    return true;
}

} // namespace butterfly
