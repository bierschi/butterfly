#include <iostream>
#include <memory>

#include "argumentParser.h"

#include "httpRequest.h"
#include "httpResponse.h"
#include "httpClient.h"
#include "httpServer.h"
#include "bflyUtils.h"

std::string v1 = "3c242fa7d8d8c7c3c63063a9f87f2f63ad9400f9bca773c5a905d16aceccc5f060d4f4594fc5287f485f90bbab9caac52309f6b658283ce80efb80a0d9b9efabcc5a9faf8a4c8f0fb6ce1f3e13fbf79a1ef874340df9932aee4b88764083ca5c2e15043aa1bb4be4cb5d1d060a4a80a05bc75938679b35881f6cbf42368d2e7f35866a54682777cb85879b3bd6818128eefbc8ef568374d06136f2bff02486e81ae2b2c5bcdfed8b4a2d868365a583317647b13eee35e0b4e082c672bd5b362be032dc9924f0199d751f42550e5291b18170b3060e66aea7745187acf75d6da5638b9ae0277d3c7116927aab060c8815ab04108556769548ebfbc090e4ae4534fe08f7937e941bdb3dc082f2e71e283c6255ace8d2d7fc1c050c1db557c9b1eb98873f7dc67c7a3f901ccb5f124f4e55065b9d64fa9f76cebc5641fa0f6ba6ade0ce17c47fc9f0c95ebbcd45272f29ef5956e30a0eb78b495cdf6841a378df9f16678ad44cb0c6fd77b6052b5dec5c26de95f5c1eda73e20664f82d5702bb9f389f55a5b2062d474ba62da09dd956a4c7d15b282e7cfb625f09357cf4c82e8db1594aa4e17de47563db3a17083be734c0d1eec87480b34354b4516df1ec91882d0ab38c013b9621d8ea82d332c3eeee76721a29cac14574e552a5f80e3e8065fab82ab53672bee9330e397e0fdfced0f785bf201e391b83e45135487d524d5112ca1f8b4a495a67c237d12eb3291b599a63284620a807cc817b176517084dde637a845e4affd6a4e5f067b1c82877ff72973ef482a09a2b98b789c38e11900142eb8bddc64eba80b1b577ab6f1b9b42106f329677ee24bcbf5f94dc5b72bf055f55956fb866e7dda16f4feace9b62b784d3906f4619eaf8a137e05a4c7783d3994804cbd0cac97947b7a8b6d8036c93ddc4028209705a1e708d881eb81f80e81ccc128e14b612e9c462936a3937861836651ee1119c1c7aa678473f7e302a8574163743908a388a0fe7cf1920a35a8cdcdd02fd7ac76a0c0ceb12e837954630f726959efee5373a09097507d7618e47388321eb85f2e2458ecc5c312e59c5e5893b02f7ac27d94c4b2b8a14aabd79d3a19c3524b046be7f25afe06b96d7575aaffe83ba313b767dd4fba837e57463db7c703c3d667a3569155e511a0807ebf9d9dd63ad53ade887bfd0f29a9de99fb93bb713a8cf8e4e62f896544bd4724a580548a5eea9cd130951e63c6a51b8788283cefcbcf5d1e0cfd0014a3047437783e6217bdae78aab6ee569b0012295e22923f4092d8a9e4d1ff84c78746a76df1f8d96683f7b6e6d8ca83cdd9f10ed747d1d804bb95fc4176aaa0b7acd7a2cbc468d85d0662f50d8ac13646988db80200a696e71daaf526b6ddf64e4c8d55bc2012988a4f49a014d9b81899ddcd42af2d4650e8bb204a9873a10c5cc8ad76494d3afdb15794bfa2e219ba4bb792db41c17ba52d6563eea28842aff5b08bb312c6d8a4e053e10cda716d296a19bf05e1d42afe44e489fc11e43e9c10dc2a8f6434c09e3cbdb326e86459049b2933963618bfb60f61f6bca1bbdb18811b18b73021855eded260da230aa2cffb1b589710606e007b1f2334804ab67df7ad09ac67b1f4a9d976fc70f3ff116243485b22abd8b20055acba5e0eb37d4457f505b2dea0dcfe69ae806f5bb02718e07ed296d2a20c93a5cce4b49de2ba95a4128b9aa6a9e6ebea6fb4dde73e6eea17a6af98f71af1ac0a61ea859c741f476fac200781e955c389b155f7453a6b3e834f4c0ed6db9b96822500c1521907f4b24c47446d9ba8a1c6cd664355bfad382286340b578e4b5161b5567a208bf9c39729b73d76dc156694f1235f0bfcdebd45ccc3f31d5e3d0e539183cfda262005300acfd14079e85e8a6052b1ec0ec6c3f0938ca3150612ea60a5e00c411805dff6041c5d770cbd6297d029866c03214711bb0949db94cc5f4313b5729bc3bd2371f6bdd7232d3c16d19c473d7a68890c8ca353a2300b9bb316dfcda6ea69a96adafaf5397536d845597eb54e4dc292c40a9d966066d6bb19f7a93a4bc03d017cbfed6eb972af9972140ba68d38d4165d69d74653fa09b78fa3e351069fbc3c3a67de67e33b8f1ff0de39fb3b00ae7c54a621bf20dfb70bf6263b0ed58f617c3ba2027a19041ca0ac8236909199dc35d41c2bf03e34f85a4e4447afa1013766a0d7d5c44f1245cd10f3520054c6748d8e77cec9393f3a62191e0e1d67c8cf67305ce9ee540f5178e3d04d3ed2cfea2f9c670c752f7701d4309d87d014f8ab0a343661a125f2b28546656c9a2163dad53d5a2b0acd1bb37d185793bc46d3a370f5f44c800c456be35560ced61f5be4be2a1fc3be003bbb88";
std::string v2 = "33f693c506c4fce7985699e0e4f63bd2a8fde159652286758cba2f529772d8a8ec915cda9a04feebe24d0c8f33208fc2c37c1573851d61920bd0113d8b503c2eff05c4d87c031d649e77547540dbe55024153400de20cc03dee6bb8ebac4dbaae7d9856b050310937b44d2e59454f7f0f0f141e5cc902770034f375c103fae6d51fa34aed947f818f4c7a50e3368cedeb15947d89788581f8379ea80a19b5d0f16cd53eec66b2e61011872f1a57d205260cf8842231e55a1ad3ee11b35dcf59310ff0512a2eaccaa1485226019d42f6d20d91849b79b41c223038253fae921622e92048f687c0ca4dfb85b29e03c498980f5eabd9c1143d4e63d6ffd6f78031b63f92ed0467fb2e9d41202117458a2b81a352f57827156434c56cdddda5b4050c7962a438ce79fa0448d619bb6e169b3b000407e80b889cba4fe1a0e61a6434464d74a0bdf6c9ea14e2d6d4be7e0ecb4521b3188ace9d263d7a678b9e4428766fabe79c3a741b5b9814252bbf88e7d52506381cbc047fafb82260cfda22c5d45e6f3df46347e682f55a7f57fe8693198671b5626d785b671d32ffc2c0f3cfbcdd6ceae95a25268639cf00dc5b36be5e64c905bd452faa0471597654b85eb4bbd679036511c5e87c3afb8ce38e99515e91bbb30b9572bbb3fdcab6d98f2660615dfb192415d138644defb1f7c52b7bca9a7086ad4744d60027c237e4a05dff2cf115748f9e1b04ae7d346a7606f1dfaf5ad0c5d7f88024516b1cb2e8f02cacf84ed5fbfa8c341f862a0f9ef75dcbc8025c5562acfdce3e5d53d0ad281929c144133e17a76c6948ace484892e4403256d1c776cb1df75d2436c3efcee57fa78bdc1935c74f81f40831e09ba92dd4c0dcc01bb11d75d8ba4e2a7a00f30f823b5c05dd4b33cde4f2dbbaa2d6ef32266e75534b476770263e8326e2f82e79ac74e66e1df088d3468d68c02f440674cfb0959e089226418227a0cc4577feef0e49af78fba3319153b122adf78795feaf14de314c6d11f7dbf6e7aac05ebc58f41282e02a4cf1c403fbfe02adde3cb0ccfb35e485e41fc48987c263bbffaac4f1d6f68046b51bf88d77bbd965631aa0c46b304479f725631628fa4cc8b4d87123f9a7686015c814ac6eca85f61a58e61c84bd0736b4d9e74cf0903ffa2bbca72cd07fa53ac6628a3a36e2cb08a88f6cd6204e3fe6da80d528c3b29e15ce10811666e53d08e5e5cbdb6e471a870db031912a70f6e662ca6c696590051e5836234fc8c3aa9d5707743ef4e0beaa2279140aeef28bffe4db69da25a5baa2bc5c2c7918a58105cd723f4fbf4c6747fedad523cf004ecd3c8fb315c0681aa470b2e32fd7e20cf3ad79ce5fa0e00d4adc3b63704f3cd169f6d0a2fa6d00214fa98a503d999c03961830ec9359e4a9c3bc40de17077d70c7b2d1e805e29a1365ba6cd35c3f5c8d6f0ffa42aca33f78125608fda8ffa3c0e76d83faadbb40a112c4929402f0ef119afadfb8d6a1edd8b45dadfbe6947679938dbfb3530a26e8be82c0f3045365488f5146aa955c2d6ef53dff26dd39b14a1457a27180646eba1d5e8fe14645cf0852c21079beba62c4ebe7ed53a9c4af897cc2a38c025941a235656764c180297a24a83eba7981e36aac375ef97848697f67d1fe0150c2cbc59d9e285bb4272129dd3027a80193e96b41e3adf1cb1c65a44cd92a4aba0711e41ef683727cc1b92dde68487c4ff5c4c3426c723cb8fc392b710678dfffba1b2eefd1ebdac20ed3454bdb1894bf7057689bb7bc8066c7e49ca2428f8070fa0ee110b07212f78a7b900eb7a8104d1b441acb68221821c30a38db603a2a0bb7d6dce3322fd0806b5baa6ac6470123e80ea8e907672e6afde5e3157969efed19572f9f6f5750208e0da9bc39ff4862b7dce88f16ca9fd50b4c2ad4bab2f4ae627c0945b954e194cf0ce0d9c61ec6aed7995ae50c2df7d170ab4ed35af0e8a80b064e037486fd5e467e0918ad4095ec00e9c03d18cd5ba284c7e018978a95f21a0eba7837a9fb648e20a16ced66c3518cd9549be175204176415d0655c0c1548bacd8dfab138e505d26b051c4720b233b8b16fc0f6cbbb6f265822f762fe12783026ca6b7e23949f1463662838d6349c49fb7a3ca430a6387de16f81937c8f24241404c8a2cb1825baffdd6417551988c800b9132d3d2c39b8c44bc586df00f7ab7644df7d502fe22ea3e2ca86bb6c6e05406e89a0d97141445453a26904e1cd565de16124ed15a895a7c2134fa6f16c24d46823a939cde5f3d8d843f090910e57ececc637ab8fe03a4091751a0b7942d390f4dcf30b6ecd204b3ee7ca8aca6f1871c7db1b24e8cfec15adff71b5fe7b3e825c9f1a617d9735f4641598a68e39554a9852440141d8b899a0c152e0d119503c5ab5a17844efe0d386e50390124a2cc0f2fdf95d5e4d723251704b32845e1caea85b29525fd092d7eeaf28853d5bb016707306cc6583ef48e8c73b920af6f1b8c295040dcb0ffff414e73edd0d31e11e5385e782b6408207164790e35463bfcaf0fcd9e77aabd242920139669fa28635bdec2a9b8b708b7a2a0a1cfe90a5c8b2d6587d875b0f52460c211901b4ac50130cabe1552a5ccdcd6dfad2d54912815e3ac6cc2bec10717690ece284b328dcb9b15bd72ef0a1d27ddf66634c80a0c5cb9674d9f044269b17fb48fb8b6efee99608a5ae55626eb40fda574679166ff7f439466bbd47f3104436040c13afd8a1a31e913ab7930153ea563ec90fc0f9994b021c274787c74fa6ab9619a3fcfdda3bcc5d5";

void request()
{
    std::unique_ptr<tools::HTTPRequest> httpRequest = std::unique_ptr<tools::HTTPRequest>(new tools::HTTPRequest());

    std::string url = "localhost:8080";
    httpRequest->setURL(url);
    httpRequest->setMethod(tools::Method::POST);
    httpRequest->setProtocol(tools::Protocol::HTTP1_1);
    httpRequest->setUserAgent("testuser");
    httpRequest->setHTTPHeader("Content-Type", "application/x-www-form-urlencoded");
    httpRequest->setFormParam("form1", "value1");
    httpRequest->setFormParam("form2", "value2");
    httpRequest->addBody(httpRequest->getFormParam());
    httpRequest->setHTTPHeader("Content-Length", std::to_string(httpRequest->getBodyLength()));
    httpRequest->prepareOutgoing();

    httpRequest->print();

}

void response()
{

    std::unique_ptr<tools::HTTPResponse> httpResponse = std::unique_ptr<tools::HTTPResponse>(new tools::HTTPResponse());

    httpResponse->setProtocol(tools::Protocol::HTTP1_1);
    httpResponse->setStatusCode(200);
    httpResponse->setReasonPhrase(httpResponse->getStatusCode());
    httpResponse->setHTTPHeader("Connection", "Keep-Alive");
    httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");
    httpResponse->addBody("<!DOCTYPE html><html><body><h1>Test Message</h1></body></html>");
    httpResponse->setHTTPHeader("Content-Length", std::to_string(httpResponse->getBodyLength()));
    httpResponse->prepareOutgoing();
    std::string http = httpResponse->getHTTPData();

    httpResponse->print();
    std::cout << "H: " << http << std::endl;
}

void http_client(const std::string &url, const int &port)
{
    std::vector<std::pair<std::string, std::string>> formParamVec;

    formParamVec.insert(formParamVec.end(), {std::make_pair("CPrivateRSA.bin", v1),
                                             std::make_pair("RSA.bin", v2),
                                             std::make_pair("RSAKeySize", "2048")});
    std::string formParamStr = tools::createFormParamStr(formParamVec);

    std::unique_ptr<tools::HTTPClient> httpClient(new tools::HTTPClient());

    std::string cert = httpClient->post("http://127.0.0.1:5000/decryption/", formParamStr, 5000);
    std::cout << "Cert: " << cert << std::endl;

    //std::string data = httpClient->get("www.google.de");
    //std::cout << "Data: " << data << std::endl;
}

void http_server(const int &port)
{

    std::unique_ptr<tools::HTTPServer> httpServer(new tools::HTTPServer(8080));
    httpServer->run();

}

int main(int argc, char* argv[])
{

    std::unique_ptr<tools::ArgumentParser> argparse = std::unique_ptr<tools::ArgumentParser>(new tools::ArgumentParser(argc, argv));
    tools::ArgumentParser::Arguments args = argparse->parseArgs();

    std::unique_ptr<tools::HTTPServer> httpServer(new tools::HTTPServer(8080));
    httpServer->run();

    if (args.server)
    {
        http_server(args.port);
    } else if (args.client)
    {

    } else
    {

    }

    return 0;
}

