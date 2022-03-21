# RSA Encryption/Decryption Tool

## Build `rsabfly`

<pre><code>
mkdir build && cd build
cmake ../
make
./rsabfly --help
</code></pre>

## 1. rsabfly -> cli

Encrypt with `rsabfly`

<pre><code>
./rsabfly --encrypt ../CPrivateRSA.pem
</code></pre>

Decrypt with openssl cli
<pre><code>
openssl rsautl -decrypt -inkey RSAPrivateKey.pem -in rsa_ek.bin -out rsa_ek.txt
</code></pre>

<pre><code>
openssl enc -aes-256-cbc -d -in encrypted.bin -K $(xxd -p -c 256 rsa_ek.txt) -iv $(xxd -p -c 256 rsa_iv.txt) -out CPrivateRSA.pem.dec
</code></pre>

## 2. cli -> rsabfly (not complete)
Encrypt with openssl cli

<pre><code>
openssl rand 1679 > rsa_ek.txt
openssl rand 16 > rsa_iv.txt
openssl enc -aes-256-cbc -e -in ../CPrivateRSA.pem -K $(xxd -p -c 15000 rsa_ek.txt) -iv $(xxd -p -c 256 rsa_iv.txt) -out CPrivateRSA.bin
openssl rsautl -encrypt -inkey ../../../masterkeys/SPublic.pem -pubin -in rsa_ek.txt -out rsa_ek.bin
</code></pre>

Decrypt with `rsabfly`
<pre><code>
./rsabfly --decrypt CPrivateRSA.bin --key ../../../masterkeys/SPrivateRSA.pem --ek rsa_ek.bin --iv rsa_iv.txt
</code></pre>

## 3. rsabfly -> rsabfly

Encrypt with `rsabfly`
<pre><code>
./rsabfly --encrypt ../CPrivateRSA.pem
</code></pre>

Decrypt with `rsabfly`
<pre><code>
./rsabfly --decrypt encrypted.bin --key RSAPrivateKey.pem --ek rsa_ek.bin --iv rsa_iv.txt
</code></pre>

## 4. cli -> cli
Encrypt with openssl cli
<pre><code>
openssl rsautl -encrypt -inkey ../../../masterkeys/SPublic.pem -pubin -in ../CPrivateRSA.pem -out CPrivateRSA.bin
</code></pre>

Decrypt with openssl cli
<pre><code>
openssl rsautl -decrypt -inkey ../../../masterkeys/SPrivateRSA.pem -in CPrivateRSA.bin -out CPrivateRSA.dec.pem
</code></pre>

## 5. butterfly -> rsabfly
#### Encrypt with butterfly application
<pre><code>
./butterfly --encrypt /home/testuser/projects/butterfly/5357083.pdf
</code></pre>

#### Decrypt with `rsabfly`
<pre><code>
./rsabfly --decrypt CPrivateRSA.bin --key ../../../masterkeys/SPrivateRSA.pem -p RSA.bin
</code></pre>
