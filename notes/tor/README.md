
# Tor

Official Tor Repo
<pre><code>
git clone https://github.com/torproject/tor.git
cd tor
sh autogen.sh
./configure --enable-static-tor --with-libevent-dir=/usr/lib/x86_64-linux-gnu --with-openssl-dir=/usr/lib/x86_64-linux-gnu --with-zlib-dir=/usr/lib/x86_64-linux-gnu --disable-asciidoc --disable-unittests
make
</code></pre>


## Create a `libtorcpp.a` library
<pre><code>
- Enable the usage of tor library with c++ compiler
- Embedding the tor api into butterfly application
</code></pre>