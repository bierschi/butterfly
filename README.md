# Butterfly
Butterfly is a cryptographic ransomware that includes the following features

- Hybrid Encryption (RSA Asymmetric/AES Symmetric Encryption)
- Supports multiple operating systems (Linux, Windows, MacOS)
- Offline Encryption
- Supports over .. file extensions
- Connection to the TOR network
- Bitcoin payments

## Dependencies

Install boost libraries
<pre><code>
sudo apt-get install -y libboost-filesystem-dev libboost-regex-dev libboost-log-dev
</code></pre>

## Build Butterfly

Build butterfly
<pre><code>
git clone https://github.com/bierschi/ransomware.git
cd ransomware
mkdir build && cd build
cmake ..
make
</code></pre>

CMake Arguments 
<pre><code>
-DUNITTESTS=ON   # Enables the Unit Tests
</code></pre>

## Usage and Examples

Print the available arguments for Butterfly
<pre><code>
butterfly --help
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

## Logs

logs can be found in `/var/log/ransomware`

## Changelog
All changes and versioning information can be found in the [CHANGELOG](https://github.com/bierschi/ransomware/CHANGELOG.rst)

## License
Copyright (c) 2021 Bierschneider Christian. See [LICENSE](https://github.com/bierschi/ransomware/blob/master/LICENSE)
for details