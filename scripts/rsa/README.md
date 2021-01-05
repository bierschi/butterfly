## RSA Encryption and Decryption

Generate RSA Private Key
<pre><code>openssl genrsa -out CPrivateRSA.pem 2048</code></pre>

Generate Public Key from RSA Private Key
<pre><code>openssl rsa -in CPrivateRSA.pem -pubout -out CPublic.pem</code></pre>

Encrypt random key (aes-key) with CPublic.pem 
<pre><code>openssl rsautl -encrypt -oaep -inkey CPublic.pem -pubin -in secret.txt -out secret.bin</code></pre>

Decrypt random key (aes-key) with CPrivateRSA.pem
<pre><code>openssl rsautl -decrypt -oaep -inkey CPrivateRSA.pem -in secret.bin -out secret.txt.dec</code></pre>

Check md5sum from secret.txt and secret.txt.dec

<pre><code>md5sum secret.txt secret.txt.dec</code></pre>