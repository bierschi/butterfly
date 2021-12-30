# BFLY RSA Decryption

size of `RSA.bin` = 2009 Bytes (1721 (EK1) + 16 (IV1) + 256 (EK2) + 16 (IV2))

Get `EK1` and `IV1` from `RSA.bin`
<pre><code>
dd skip=0 count=1721 if=RSA.bin of=rsa_ek1.bin bs=1
dd skip=1721 count=16 if=RSA.bin of=rsa_iv1.bin bs=1
</code></pre>

Get `EK2` and `IV2` from `RSA.bin`
<pre><code>
dd skip=1737 count=256 if=RSA.bin of=rsa_ek2.bin bs=1
dd skip=1993 count=16 if=RSA.bin of=rsa_iv2.bin bs=1
</code></pre>

Decrypt the `rsa_ek1.bin` with the openssl rsautl cli
<pre><code>
openssl rsautl -decrypt -inkey ../../../../masterkeys/SPrivateRSA.pem -in rsa_ek1.bin -out rsa_ek1.txt
</code></pre>

Convert the `rsa_ek1.txt` and `rsa_iv1.bin` to hex numbers
<pre><code>
xxd -p rsa_ek1.txt > rsa_ek1.hex.txt
xxd -p rsa_iv1.bin > rsa_iv1.hex.bin
</code></pre>

Decrypt the `CPrivateRSA.bin` file with the `AES-256-CBC` Cipher
<pre><code>
openssl enc -aes-256-cbc -d -in CPrivateRSA.bin -K 'b6a22a414b75b5b0a5223bda3cd55531de85c27a9280b922019bb03a2a0b6bb6' -iv 'b80e388686265fcf49b4e2e5276b4674' -out CPrivateRSA.pem
</code></pre>

Decrypt the `rsa_ek2.bin` with the openssl rsautl cli and the previous decyrpted `CPrivateRSA.pem`
<pre><code>
openssl rsautl -decrypt -inkey CPrivateRSA.pem -in rsa_ek2.bin -out rsa_ek2.txt
</code></pre>

Convert the `rsa_ek2.txt` and `rsa_iv2.bin` to hex numbers
<pre><code>
xxd -p rsa_ek2.txt > rsa_ek2.hex.txt
xxd -p rsa_iv2.bin > rsa_iv2.hex.bin
</code></pre>

Decrypt the `AES.bin` file with the `AES-256-CBC` Cipher
<pre><code>
openssl enc -aes-256-cbc -d -in AES.bin -K '3760389e42eed42c2e8e44f988ca891094cc6f7ff27996ba4d8d0003598bbb27' -iv '38a80c3fc773c0080b931d8633905391' -out AES.txt
</code></pre>
