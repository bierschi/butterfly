# OpenSSL CLI with BFLY files (Hybrid Mechanism)
Files were encrypted with the `butterfly` application
<br><br>
`5357083.pdf.bfly` -> Encrypted pdf file <br>
`AES.bin` -> Encrypted AES KeyPair<br>
`CPrivateRSA.bin` -> Encrypted CPrivateRSA.pem certificate<br>
`RSA.bin` -> Includes the EK and IV for the RSA Encryption/Decryption<br>

### Decrypt with CLI

Size of `RSA.bin` = 2009 Bytes (1721 (EK1) + 16 (IV1) + 256 (EK2) + 16 (IV2))

Get `EK1` and `IV1` from `RSA.bin`
<pre><code>
dd skip=0 count=1721 if=RSA.bin of=rsa_ek1.bin bs=1
dd skip=1721 count=16 if=RSA.bin of=rsa_iv1.txt bs=1
</code></pre>

Get `EK2` and `IV2` from `RSA.bin`
<pre><code>
dd skip=1737 count=256 if=RSA.bin of=rsa_ek2.bin bs=1
dd skip=1993 count=16 if=RSA.bin of=rsa_iv2.txt bs=1
</code></pre>

Decrypt the `rsa_ek1.bin` with the `openssl rsautl` cli
<pre><code>
openssl rsautl -decrypt -inkey ../../masterkeys/SPrivateRSA.pem -in rsa_ek1.bin -out rsa_ek1.txt
</code></pre>

Decrypt the `CPrivateRSA.bin` file with the `AES-256-CBC` Cipher
<pre><code>
openssl enc -aes-256-cbc -d -in CPrivateRSA.bin -K $(xxd -p -c 256 rsa_ek1.txt) -iv $(xxd -p -c 256 rsa_iv1.txt) -out CPrivateRSA.pem
</code></pre>

Decrypt the `rsa_ek2.bin` with the `openssl rsautl` cli and the previous decrypted `CPrivateRSA.pem`
<pre><code>
openssl rsautl -decrypt -inkey CPrivateRSA.pem -in rsa_ek2.bin -out rsa_ek2.txt
</code></pre>

Decrypt the `AES.bin` file with the `AES-256-CBC` Cipher
<pre><code>
openssl enc -aes-256-cbc -d -in AES.bin -K $(xxd -p -c 256 rsa_ek2.txt) -iv $(xxd -p -c 256 rsa_iv2.txt) -out AES.dec.txt
</code></pre>

Decrypt the `5357083.pdf.bfly` file with the AES Key and IV from `AES.dec.txt`
<pre><code>
openssl enc -aes-256-cbc -d -iter 6 -salt -md sha256 -in 5357083.pdf.bfly -K $(xxd -l 32 -p -c 256 AES.dec.txt) -iv $(xxd -l 16 -s 32 -p -c 256 AES.dec.txt) -out 5357083.dec.pdf
</code></pre>

Compare the md5sum of both files
<pre><code>
md5sum ../papers/5357083.pdf 5357083.dec.pdf
</code></pre>

Validation
<pre><code>
b411f593df510506131549a8f79158a2  ../papers/5357083.pdf
b411f593df510506131549a8f79158a2  5357083.dec.pdf
</code></pre>

### Encrypt with CLI

<pre><code>
openssl rand 32 > AESKey.txt
openssl rand 16 > AESIV.txt
openssl enc -aes-256-cbc -e -iter 6 -salt -md sha256 -in 5357083.pdf -K $(xxd -p -c 256 AESKey.txt)  -iv $(xxd -p -c 256 AESIV.txt) -out 5357083.pdf.bfly
</code></pre>

<pre><code>
openssl rand 256 > rsa_ek2.txt
openssl rand 16 > rsa_iv2.txt
openssl enc -aes-256-cbc -e -in AES.txt -K $(xxd -p -c 256 rsa_ek2.txt) -iv $(xxd -p -c 256 rsa_iv2.txt) -out AES.bin
</code></pre>

Encrypt the `rsa_ek2.txt` with the `openssl rsautl` cli and the `CPrivateRSA.pem`
<pre><code>
openssl rsautl -encrypt -inkey CPrivateRSA.pem -in rsa_ek2.txt -out rsa_ek2.bin
</code></pre>

Encrypt the `CPrivateRSA.pem` file with the `AES-256-CBC` Cipher
<pre><code>
openssl rand 1721 > rsa_ek1.txt
openssl rand 16 > rsa_iv1.txt
openssl enc -aes-256-cbc -e -in CPrivateRSA.pem -K $(xxd -p -c 256 rsa_ek1.txt) -iv $(xxd -p -c 256 rsa_iv1.txt) -out CPrivateRSA.bin
</code></pre>

Encrypt the `rsa_ek1.txt` with the `openssl rsautl` cli
<pre><code>
openssl rsautl -encrypt -inkey ../../masterkeys/SPublic.pem -in rsa_ek1.txt -out rsa_ek1.bin
</code></pre>

Concatenate rsa_ek1.bin + rsa_iv1.txt + rsa_ek2.bin + rsa_iv2.txt => RSA.bin