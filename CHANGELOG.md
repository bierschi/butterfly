# Changelog
All notable changes to project [butterfly](https://github.com/bierschi/butterfly) will be documented in this file


## [1.4] - 2024-01-03

### Added

- Solved bug with large files during AES Encryption/Decryption
- Prevention of Out-of-Memory errors with huge files
- Restructured project to support multiple platforms
- Enhancement of the browser payment page after encryption

## [1.3] - 2023-03-13

### Added

- Added and integrated official butterfly image
- Improved CI/CD Pipeline
- Integration of docker containers
- Added cppcheck to repository and resolved all errors/warnings
- Added reports to the repository
- Added toolchain for multiple platforms
- Updated the API routes of the bflyServerApp
- Integration of TorSocket class (Tor Proxy)
- Added Tor Hidden Service Support

## [1.2] - 2022-06-02

### Added

- Support of different RSA key sizes
- Support of different AES key sizes
- Integration of an HTTP Server/Client
- Open browser with a basic html page after encryption

## [1.1] - 2022-02-11

### Added

- Support of over 300 File Extensions
- Remote decryption capability
- Webserver bflyServerApp for a secure remote decryption
- Notes section for encryption/decryption with the openssl cli
- Tools section for common actions
- Improvements of the argument parser

## [1.0] - 2021-09-17

### Added

- First runnable version with basic encryption/decryption capability

##  Development Start

### Added

- GTest as Unittest Framework
- RSA Encryption/Decryption
- AES Encryption/Decryption
- Hybrid Encryption/Decryption mechanism


[1.4]: https://github.com/bierschi/butterfly/compare/v1.3...v1.4
[1.3]: https://github.com/bierschi/butterfly/compare/v1.2...v1.3
[1.2]: https://github.com/bierschi/butterfly/compare/v1.1...v1.2
[1.1]: https://github.com/bierschi/butterfly/compare/v1.0...v1.1
[1.0]: https://github.com/bierschi/butterfly/releases/tag/v1.0