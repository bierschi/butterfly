//
// Created on 28.01.20.
//

#ifndef RANSOMWARE_ALGORITHM_H
#define RANSOMWARE_ALGORITHM_H
#include <boost/filesystem.hpp>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define KEYSIZE 2048

/**
 * Abstract Base Class Algorithm
 */
class Algorithm {

public:
    /**
     * Constructor
     */
    Algorithm() {};

    /**
     * Destructor
     */
    virtual ~Algorithm() {
        CRYPTO_cleanup_all_ex_data();
    };

    /**
     * abstract method encrypt for subclasses
     */
    virtual void encrypt(std::vector<boost::filesystem::path>&) = 0;

    /**
     * abstract method decrypt for subclasses
     */
    virtual void decrypt() = 0;

};


#endif //RANSOMWARE_ALGORITHM_H
