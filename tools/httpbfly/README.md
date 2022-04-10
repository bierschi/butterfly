# HTTP Server/Client Tool

<pre><code>
mkdir build && cd build
cmake ../
make
./httpbfly --help
</code></pre>

Start the `httpblfy` app as server
<pre><code>
./httpbfly --server --port 8080
</code></pre>

Start the `httpbfly` app as client
<pre><code>
./httpbfly --client --get --url 127.0.0.1 --port 8080
./httpbfly --client --post --url http://127.0.0.1:5000/decryption/  --port 5000
./httpbfly --client --get --url www.google.de --port 80
</code></pre>
