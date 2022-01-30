# AES Encryption/Decryption Tool

## Build `aesbfly`

<pre><code>
mkdir build && cd build
cmake ../
make
./aesbfly --help
</code></pre>

## 1. aesbfly -> cli
#### Encrypt with `aesbfly`

<pre><code>
./aesbfly --encrypt 5357083.pdf
</code></pre>

#### Decrypt with openssl cli

<pre><code>
openssl enc -aes-256-cbc -d -iter 6 -salt -md sha256 -in 5357083.pdf.bfly -K $(cat AESKeyHex.txt) -iv $(cat AESIVHex.txt) -out 5357083.dec.pdf
</code></pre>

## 2. cli -> aesbfly
#### Encrypt with openssl cli

Generate the AESKey
<pre><code>
openssl rand -hex 32 > AESKeyHex.txt
</code></pre>

Generate the AESIV
<pre><code>
openssl rand -hex 16 > AESIVHex.txt
</code></pre>

Encrypt the file
<pre><code>
openssl enc -aes-256-cbc -e -iter 6 -salt -md sha256 -in ../5357083.pdf -K $(cat AESKeyHex.txt) -iv $(cat AESIVHex.txt) -out 5357083.pdf.bfly
</code></pre>

#### Decrypt with `aesbfly`

<pre><code>
./aesbfly --decrypt --key AESKeyHex.txt --iv AESIVHex.txt --hex 5357083.pdf.bfly
</code></pre>

## 3. aesbfly -> aesbfly
#### Encrypt with `aesbfly`

<pre><code>
./aesbfly --encrypt 5357083.pdf
</code></pre>

#### Decrypt with `aesbfly`

<pre><code>
./aesbfly --decrypt --key AESKey.txt --iv AESIV.txt 5357083.pdf.bfly
</code></pre>
or with hex values
<pre><code>
./aesbfly --decrypt --key AESKeyHex.txt --iv AESIVHex.txt --hex 5357083.pdf.bfly
</code></pre>

## 4. cli -> cli
#### Encrypt with openssl cli

Generate the AESKey
<pre><code>
openssl rand -hex 32 > AESKeyHex.txt
</code></pre>

Generate the AESIV
<pre><code>
openssl rand -hex 16 > AESIVHex.txt
</code></pre>

Encrypt the file
<pre><code>
openssl enc -aes-256-cbc -e -iter 6 -salt -md sha256 -in ../5357083.pdf -K $(cat AESKeyHex.txt) -iv $(cat AESIVHex.txt) -out 5357083.pdf.bfly
</code></pre>

#### Decrypt with openssl cli

<pre><code>
openssl enc -aes-256-cbc -d -iter 6 -salt -md sha256 -in 5357083.pdf.bfly -K $(cat AESKeyHex.txt) -iv $(cat AESIVHex.txt) -out 5357083.dec.pdf
</code></pre>
