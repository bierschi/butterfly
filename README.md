# Butterfly
Butterfly is a cryptographic ransomware that includes the following features

- Hybrid Encryption (RSA Asymmetric/AES Symmetric Encryption) :heavy_check_mark:
- Supports multiple operating systems (Linux, Windows, MacOS)
- Offline Encryption
- Supports over .. file extensions
- Connection to the TOR network
- Bitcoin payments

## Dependencies

Install sqlite3 and boost libraries
<pre><code>
sudo apt-get install -y sqlite3 libsqlite3-dev libboost-filesystem-dev libboost-regex-dev libboost-log-dev
</code></pre>

## Build Butterfly

Build butterfly
<pre><code>
git clone https://github.com/bierschi/butterfly.git
cd butterfly
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
./butterfly --help
</code></pre>

<pre><code>
Usage: 
	butterfly --dir /home/butterfly/test/
	butterfly --dir /home/butterfly/test/ --protected
	butterfly --encrypt /home/butterfly/test/ 
	butterfly --decrypt /home/butterfly/test/ --key /home/butterfly/SPrivateRSA.pem

Options:
-d, --dir		Directory Path to start the Encryption+Decryption
--encrypt		Encrypts all files in provided directory
--decrypt		Decrypts all files in provided diretory
-k, --key		Private Key from the Server for the Decryption (Corresponds to the embedded Server Public Key)
-p, --protected		Save all key files to System
-c, --config		Config Path
-h, --help		Print help Message
-v, --version		Print current Version

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

logs can be found in `/var/log/butterfly`

## Changelog
All changes and versioning information can be found in the [CHANGELOG](https://github.com/bierschi/butterfly/blob/master/CHANGELOG.rst)

## License
Copyright (c) 2021 Bierschneider Christian. See [LICENSE](https://github.com/bierschi/butterfly/blob/master/LICENSE)
for details