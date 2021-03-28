## AES Encryption and Decryption (Symmetric)


Encrypt 5357083.pdf with AES-256-CBC 
<pre><code>openssl enc -aes-256-cbc -md sha512 -pbkdf2 -iter 100000 -salt -kfile AESKey.txt -in ../../docs/5357083.pdf -out 5357083.bin</code></pre>

Decrypt 5357083.bin with AES-256-CBC
<pre><code>openssl enc -aes-256-cbc -md sha512 -pbkdf2 -iter 100000 -salt -d -kfile AESKey.txt -in 5357083.bin -out 5357083.pdf.dec</code></pre>

<br>
<br>

Check md5sum from 5357083.pdf and 5357083.pdf.dec
<pre><code>md5sum ../../docs/5357083.pdf 5357083.pdf.dec</code></pre>