//
// Created on 24.12.19.
//
#include <iostream>
#include "DirectoryIterator.h"

int main(int argc, char** argv) {

    std::cout << "Hello World" << std::endl;

    std::string path = "/home/christian/Bilder";
    std::unique_ptr<DirectoryIterator> dir(new DirectoryIterator(path));

    return 0;
}