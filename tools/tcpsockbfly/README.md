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

ServerSocket listens for incoming connections on port 8081...
Connected with client!
Awaiting client response...
Client: hello server
>hello client
Awaiting client response...
</code></pre>

Create a client socket instance
<pre><code>
./tcpsockbfly --client --ip 127.0.0.1 --port 8080

ClientSocket connected to 127.0.0.1 on port 8081
> hello server
Awaiting server response...
Server: hello client
>
</code></pre>