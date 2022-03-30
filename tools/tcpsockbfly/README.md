# TCPSocket Tool

<pre><code>
mkdir build && cd build
cmake ../
make
./tcpsockbfly --help
</code></pre>

Create a server socket instance
<pre><code>
./tcpsockbfly --server --port 8080
</code></pre>

Create a client socket instance
<pre><code>
./tcpsockbfly --client --ip 127.0.0.1 --port 8080
</code></pre>