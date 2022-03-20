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

Decrypt with openssl cli
<pre><code>
openssl rsautl -decrypt -inkey RSAPrivateKey.pem -in rsa_ek.bin -out rsa_ek.txt
</code></pre>

<pre><code>
openssl enc -aes-256-cbc -d -in encrypted.bin -K $(xxd -p -c 256 rsa_ek.txt) -iv $(xxd -p -c 256 rsa_iv.txt) -out encrypted.dec.txt
</code></pre>

## cli -> rsabfly
Encrypt with openssl cli

<pre><code>
openssl rsautl
</code></pre>

Decrypt with `rsabfly`
<pre><code>
./rsabfly --decrypt
</code></pre>

## rsabfly -> rsabfly

Encrypt with `rsabfly`
<pre><code>
./rsabfly --encrypt
</code></pre>

Decrypt with `rsabfly`
<pre><code>
./rsabfly --decrypt
</code></pre>

## cli -> cli
Encrypt with openssl cli
<pre><code>
openssl rsautl -encrypt -oaep -inkey ../../masterkeys/SPublic.pem -pubin -in CPrivateRSA.pem -out CPrivateRSA.bin
</code></pre>

Decrypt with openssl cli
<pre><code>
openssl rsautl -decrypt -oaep -inkey ../../masterkeys/SPrivateRSA.pem -in CPrivateRSA.bin -out CPrivateRSA.dec.pem
</code></pre>

## butterfly -> rsabfly

<pre><code>
./rsabfly --decrypt CPrivateRSA.bin --key ../../../masterkeys/SPrivateRSA.pem -p RSA.bin
</code></pre>