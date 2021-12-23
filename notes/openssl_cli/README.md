# OpenSSL CLI


### RSAUTL

Generate the `CPrivateRSA.pem`
<pre><code>
openssl genrsa -out CPrivateRSA.pem 2048
</code></pre>

Encrypt the `CPrivateRSA.pem` with the embedded `SPublic.pem`
<pre><code>
openssl rsautl -encrypt -oaep -inkey ../../masterkeys/SPublic.pem -pubin -in CPrivateRSA.pem -out CPrivateRSA.bin
</code></pre>

Decrypt the `CPrivateRSA.bin` with the `SPrivateRSA.pem` from the attacker
<pre><code>
openssl rsautl -decrypt -oaep -inkey ../../masterkeys/SPrivateRSA.pem -in CPrivateRSA.bin -out CPrivateRSA.dec.pem
</code></pre>

Compare the md5sum of both files to validate
<pre><code>
md5sum CPrivateRSA.pem CPrivateRSA.dec.pem
9ede908085d7aef033ba37fe8a997ff9  CPrivateRSA.pem
9ede908085d7aef033ba37fe8a997ff9  CPrivateRSA.dec.pem
</code></pre>

### AES-256-CBC

Generate random encryption key in hex
<pre><code>
hexdump -n 32 -e '4/4 "%08X" 1 "\n"' /dev/urandom
</code></pre>
Generate random iv in hex
<pre><code>
hexdump -n 16 -e '4/4 "%08X" 1 "\n"' /dev/urandom
</code></pre>

<pre><code>
openssl enc -aes-256-cbc -e -iter 6 -salt -md sha256 -in ../papers/5357083.pdf -K '7c07f68ea8494b2f8b9fea297119350d78708afa69c1c76' -iv 'FEDCBA987654321' -out 5357083.bin
</code></pre>

<pre><code>
openssl enc -aes-256-cbc -d -iter 6 -salt -md sha256 -in 5357083.bin -K '7c07f68ea8494b2f8b9fea297119350d78708afa69c1c76' -iv 'FEDCBA987654321' -out 5357083.dec.pdf
</code></pre>



### Hybrid RSA/AES



### CMDS

<pre><code>
openssl enc -aes-256-cbc -nosalt -e -a -A -in input.txt -K '7c07f68ea8494b2f8b9fea297119350d78708afa69c1c76' -iv 'FEDCBA987654321' -out input-test.enc
</code></pre>

<pre><code>
openssl enc -aes-256-cbc -nosalt -d -a -A -in input-test.enc -K '7c07f68ea8494b2f8b9fea297119350d78708afa69c1c76' -iv 'FEDCBA987654321'
</code></pre>


RSA.bin = 1737 Bytes (1721 Bytes (EK) + 16 Bytes (IV))