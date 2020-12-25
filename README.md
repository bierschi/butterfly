# Ransomware that makes you cry


## Installation
<pre><code>
git clone https://github.com/bierschi/ransomware.git
cd ransomware
mkdir build
cmake ..
make
</code></pre>

### GTEST
<pre><code>
sudo apt-get install libgtest-dev
sudo apt-get install cmake # install cmake
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make

#copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib
</code></pre>

### Boost
<pre><code>
sudo apt-get install -y libboost-filesystem-dev libboost-regex-dev libboost-log-dev
</code></pre>

## Usage and Examples

Print the available arguments for Ransomware
<pre><code>
ransomware --help
</code></pre>


## Logs

logs can be found in `/var/log/ransomware`

## Troubleshooting


## Changelog
All changes and versioning information can be found in the [CHANGELOG](https://github.com/bierschi/ransomware/CHANGELOG.rst)