# HTTP Server

<pre><code>
IP: 127.0.0.1
Port: 8080
</code></pre>

### Browser

<pre><code>
x-www-browser 127.0.0.1:8000
xdg-open  http://127.0.0.1:8000

# check config
update-alternatives --config x-www-browser
</code></pre>

### Routes
- /masterkey
- 

### Curl

<pre><code>
curl -v -X POST http://127.0.0.1:8081/masterkey -H 'Expect:' --data-binary "@/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem"
</code></pre>