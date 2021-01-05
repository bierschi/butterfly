## AES Encryption and Decryption (Symmetric)


Encrypt secret.txt with AES-256-CBC 
<pre><code>openssl enc -aes-256-cbc -md sha512 -pbkdf2 -iter 100000 -salt -k 12345 -in ../secret.txt -out secret.bin</code></pre>

Decrypt secret.txt with AES-256-CBC
<pre><code>openssl enc -aes-256-cbc -md sha512 -pbkdf2 -iter 100000 -salt -d -k 12345 -in secret.bin -out secret.txt.dec</code></pre>

Check md5sum from secret.txt and secret.txt.dec
<pre><code>md5sum ../secret.txt secret.txt.dec</code></pre>