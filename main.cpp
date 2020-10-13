//
// Created on 24.12.19.
//
#include <iostream>
#include <boost/filesystem.hpp>

#include "logger.h"
#include "app.h"

int main(int argc, char** argv) {

    std::string filepath;
    if (argc > 1) {
        filepath = argv[1];
    } else {
        //filepath = "/home/christian/projects/ransomware/config/log_config.ini";
        filepath = "/home/christian/projects/ransomware/config/console_config.ini";
    }
    // init logger instance
    Logger::initFromConfig(filepath);

    LOG_INFO("Start application "<< PROJECT_NAME << " with version " << PROJECT_VER);

    return 0;
}