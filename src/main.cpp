
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"

int main(int argc, char* argv[]) {

    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application "<< PROJECT_NAME << " with version " << arg._version);

    std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());
    std::vector<boost::filesystem::path> dirs = dirIterator->getAllDirectories("/home/christian/PycharmProjects/comunio_brute");
    std::vector<boost::filesystem::path> files;
    for (auto &dir: dirs) {
        //LOG_TRACE(dirIterator->getFileSize(file));
        LOG_TRACE(dir);
        files = dirIterator->getFilesFromDir(dir);
        for (auto &file: files) {
            LOG_TRACE(file)
        }
    }
    return 0;
}