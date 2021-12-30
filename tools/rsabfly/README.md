# RSA Encryption/Decryption Tool

## Build `rsabfly`

<pre><code>
mkdir build && cd build
cmake ../
make
./rsabfly --help
</code></pre>

## rsabfly -> cli

Encrypt with `rsabfly`

<pre><code>
./rsabfly --encrypt 
</code></pre>

<pre><code>
./rsabfly --decrypt
</code></pre>

## cli -> rsabfly

## rsabfly -> rsabfly

## cli -> cli
Encrypt with openssl cli
<pre><code>
openssl rsautl -encrypt -oaep -inkey ../../masterkeys/SPublic.pem -pubin -in CPrivateRSA.pem -out CPrivateRSA.bin
</code></pre>

Decrypt with openssl cli
<pre><code>
openssl rsautl -decrypt -oaep -inkey ../../masterkeys/SPrivateRSA.pem -in CPrivateRSA.bin -out CPrivateRSA.dec.pem
</code></pre>
