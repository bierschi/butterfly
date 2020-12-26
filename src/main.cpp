
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"

int main(int argc, char* argv[]) {

    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application "<< PROJECT_NAME << " with version " << arg._version);

    std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());
    std::vector<boost::filesystem::path> files = dirIterator->getFilesFromDir("/home/christian/PycharmProjects/comunio_brute");
    for (auto &file: files) {
        LOG_TRACE(file);
    }
    return 0;
}