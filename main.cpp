//
// Created on 24.12.19.
//
#include <iostream>
#include "DirectoryIterator.h"
#include <thread>
#include <mutex>
std::mutex tmp_mut;

void test(std::vector<boost::filesystem::path> paths) {
    tmp_mut.lock();
    for(auto& path: paths )
        std::cout << path << std::endl;
    tmp_mut.unlock();
}

int main(int argc, char** argv) {

    std::cout << "Hello World" << std::endl;

    std::string path = "/home/christian/projects";
    std::string path2 = "/home/christian/";
    std::unique_ptr<DirectoryIterator> directoryIt(new DirectoryIterator());
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
    threads[0] = std::thread(&test, split_lo);
    threads[1] = std::thread(&test, split_hi);

    for (auto& t: threads) {
        t.join();
    }


    std::cout << "DIR Size: " << dirs.size() << std::endl;
    return 0;
}