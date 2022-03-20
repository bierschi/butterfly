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
./rsabfly --encrypt message.txt
</code></pre>

Decrypt with openssl cli
<pre><code>
openssl rsautl -decrypt -inkey RSAPrivateKey.pem -in rsa_ek.bin -out rsa_ek.txt
</code></pre>

<pre><code>
openssl enc -aes-256-cbc -d -in encrypted.bin -K $(xxd -p -c 256 rsa_ek.txt) -iv $(xxd -p -c 256 rsa_iv.txt) -out encrypted.dec.txt
</code></pre>

## cli -> rsabfly (not complete)
Encrypt with openssl cli

<pre><code>
openssl rsautl -encrypt -inkey ../../../masterkeys/SPublic.pem -pubin -in message.txt -out encrypted.bin
</code></pre>

Decrypt with `rsabfly`
<pre><code>
./rsabfly --decrypt encrypted.bin --key ../../../masterkeys/SPrivateRSA.pem --ek rsa_ek.bin --iv rsa_iv.txt
</code></pre>

## rsabfly -> rsabfly

Encrypt with `rsabfly`
<pre><code>
./rsabfly --encrypt message.txt
</code></pre>

Decrypt with `rsabfly`
<pre><code>
./rsabfly --decrypt encrypted.bin --key RSAPrivateKey.pem --ek rsa_ek.bin --iv rsa_iv.txt
</code></pre>

## cli -> cli
Encrypt with openssl cli
<pre><code>
openssl rsautl -encrypt -inkey ../../../masterkeys/SPublic.pem -pubin -in CPrivateRSA.pem -out CPrivateRSA.bin
</code></pre>

Decrypt with openssl cli
<pre><code>
openssl rsautl -decrypt -inkey ../../../masterkeys/SPrivateRSA.pem -in CPrivateRSA.bin -out CPrivateRSA.dec.pem
</code></pre>

## butterfly -> rsabfly
#### Encrypt with butterfly application
<pre><code>
./butterfly --encrypt /home/testuser/projects/butterfly/5357083.pdf
</code></pre>

#### Decrypt with `rsabfly`
<pre><code>
./rsabfly --decrypt CPrivateRSA.bin --key ../../../masterkeys/SPrivateRSA.pem -p RSA.bin
</code></pre>
