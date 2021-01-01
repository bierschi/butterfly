
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/rsa.h"

int main(int argc, char* argv[]) {

    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application "<< PROJECT_NAME << " with version " << arg._version);
    //std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());

    std::unique_ptr<butterfly::CryptoRSA> rsa(new butterfly::CryptoRSA());

    //rsa->createRSAPrivateKeyFile("rsaprivate.key");
    //rsa->createRSAPublicKeyFile("rsapublic.pem");
    //rsa->createPublicKeyFile("public.pem");

    // encrypt

    char plain[] = "However, the test is done numerically,";
    FILE *f = fopen("file.bin", "wb");
    //SA* priv = rsa->getPrivateKeyFromFile("rsaprivate.key");
    RSA* pub = rsa->getPublicKeyFromFile("rsapublic.pem");
    LOG_INFO("PUB: " << pub)
    char* ct = rsa->encrypt(pub, plain);
    fprintf(f, "%s", ct);
    fclose(f);

    // decrypt
    //FILE *r = fopen("file.bin", "rb");
    //fwrite()
    //RSA* priv = rsa->getPrivateKeyFromFile("rsaprivate.key");
    //char* pt = rsa->decrypt(priv, )
    return 0;
}