//
// Created on 28.01.20.
//

#ifndef RANSOMWARE_CRYPTO_H
#define RANSOMWARE_CRYPTO_H
#include <boost/filesystem.hpp>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define KEYSIZE 2048

/**
 * Abstract Base Class Crypto
 */
class Crypto {

public:
    /**
     * Constructor
     */
    Crypto() {};

    /**
     * Destructor
     */
    virtual ~Crypto() {
        CRYPTO_cleanup_all_ex_data();
    };

};


#endif //RANSOMWARE_CRYPTO_H
