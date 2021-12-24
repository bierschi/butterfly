# BFLY RSA Decryption

<pre><code>
openssl rsautl -encrypt -pkcs -inkey f3.pem -pubin -in in.txt -out out.bin
</code></pre>

<pre><code>
openssl rsautl -decrypt -pkcs -inkey f1.pem  -in out.bin -out out.dec.txt
</code></pre>