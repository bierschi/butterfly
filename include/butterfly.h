
#ifndef BUTTERFLY_BUTTERFLY_H
#define BUTTERFLY_BUTTERFLY_H

#include <memory>

#include "argumentParser.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"
#include "httpServer.h"
#include "logger.h"

namespace butterfly
{

/**
 * Class Butterfly for all blfy related tasks
 */
class Butterfly
{

private:
    std::unique_ptr<butterfly::ArgumentParser> _argparse;
    butterfly::ArgumentParser::Arguments _args;

    /**
     * Init logging Framework
     */
    void initLoggingFramework();

public:

    /**
     *
     *  Usage:
     *       std::unique_ptr<butterfly::Butterfly> blfy(new butterfly::Butterfly(argc, argv));
     *       blfy->run();
     *
     * @param argc: number of arguments
     * @param argv: char* of arguments
     */
    Butterfly(int argc, char *argv[]);

    /**
     * Destructor Butterfly
     */
    ~Butterfly() = default;

    /**
     * Run method for Butterfly
     */
    void run();

};

} // namespace butterfly

#endif //BUTTERFLY_BUTTERFLY_H
