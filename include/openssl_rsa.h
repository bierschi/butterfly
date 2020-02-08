//
// Created on 08.02.20.
//

#ifndef RSATEST_OPENSSL_RSA_H
#define RSATEST_OPENSSL_RSA_H


#define KEY_LENGTH       2048
#define PUBLIC_EXPONENT  59     //Public exponent should be a prime number.
#define PUBLIC_KEY_PEM   1
#define PRIVATE_KEY_PEM  0

#define LOG(x)               \
        cout << x << endl;   \

/*
 * @brief   create_RSA function creates public key and private key file
 *
 */
RSA * create_RSA(RSA *keypair, int pem_type, char *file_name);

/*
 * @brief   public_ecrypt function encrypts data.
 * @return  If It is fail, return -1
 */
int public_encrypt(int flen, unsigned char* from, unsigned char *to, RSA* key);

/*
 * @brief   private_decrypt function decrypt data.
 * @return  If It is fail, return -1
 */
int private_decrypt(int flen, unsigned char* from, unsigned char *to, RSA* key);

/*
 * @brief   create_ecrypted_file function creates .bin file. It contains encrypted data.
 */
void create_encrypted_file(char* encrypted, RSA * key_pair);




#endif //RSATEST_OPENSSL_RSA_H
