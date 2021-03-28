## RSA Encryption and Decryption (Asymmetric)

Generate private master key
<pre><code>openssl genrsa -out SPrivateRSA.pem 13768</code></pre>

Generate public master key
<pre><code>openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem</code></pre>

Generate RSA Private Key
<pre><code>openssl genrsa -out CPrivateRSA.pem 2048</code></pre>

Generate Public Key from RSA Private Key
<pre><code>openssl rsa -in CPrivateRSA.pem -pubout -out CPublic.pem</code></pre>

Encrypt the CPrivateRSA.pem with the embedded SPublic.pem
<pre><code>openssl rsautl -encrypt -oaep -inkey SPublic.pem -pubin -in CPrivateRSA.pem -out CPrivateRSA.bin</code></pre>

Encrypt AESKey.txt with CPublic.pem 
<pre><code>openssl rsautl -encrypt -oaep -inkey CPublic.pem -pubin -in AESKey.txt -out AESKey.bin</code></pre>

<br>
<br>

Decrypt the CPrivateRSA.bin with the SPrivateRSA.pem file
<pre><code>openssl rsautl -decrypt -oaep -inkey SPrivateRSA.pem -in CPrivateRSA.bin -out CPrivateRSA.pem.dec</code></pre>


Decrypt AESKey.bin with CPrivateRSA.pem.dec
<pre><code>openssl rsautl -decrypt -oaep -inkey CPrivateRSA.pem.dec -in AESKey.bin -out AESKey.txt.dec</code></pre>

<br>
<br>

Check the md5sum from original files and decrypted files

<pre><code>md5sum CPrivateRSA.pem CPrivateRSA.pem.dec</code></pre>
<pre><code>md5sum AESKey.txt AESKey.txt.dec</code></pre>