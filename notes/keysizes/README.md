# Keysizes

- First RSA Encryption is for the **CPrivateRSA.pem**
- Second RSA Encryption is for the **AES Keypair**

## RSA-4096 (not recommended)
CPrivateRSA.pem size = 3247 Bytes + 11 Bytes (PCKS Padding) = 3258 Bytes

SPrivateRSA.pem (3258 Bytes * 8)
<pre><code>
openssl genrsa -out SPrivateRSA.pem 26064
</code></pre>

SPublic.pem
<pre><code>
openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem
</code></pre>

RSA.bin
<pre><code>
3258(EK1) + 16(IV) + 512(EK2) + 16(IV) = 3802 Bytes
</code></pre>

3258 => Depends on CPrivateRSA.pem size <br>
512  => Depends on the RSA keysize (4096/8)

## RSA-2048 (Default)
CPrivateRSA.pem size = 1679 Bytes + 11 Bytes (PCKS Padding) = 1690 Bytes

SPrivateRSA.pem (1690 Bytes * 8)
<pre><code>
openssl genrsa -out SPrivateRSA.pem 13520
</code></pre>

SPublic.pem
<pre><code>
openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem
</code></pre>

RSA.bin
<pre><code>
1690(EK1) + 16(IV) + 256(EK2) + 16(IV) = 1978 Bytes
</code></pre>

1690 => Depends on CPrivateRSA.pem size <br>
256  => Depends on the RSA keysize (2048/8)

## RSA-1024

CPrivateRSA.pem size = 910 Bytes + 11 Bytes (PCKS Padding) = 921 Bytes

SPrivateRSA.pem (921 Bytes * 8)
<pre><code>
openssl genrsa -out SPrivateRSA.pem 7368
</code></pre>

SPublic.pem
<pre><code>
openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem
</code></pre>

RSA.bin
<pre><code>
ca. 921(EK1) + 16(IV) + 128(EK2) + 16(IV) =  1081 Bytes
</code></pre>

921 => Depends on CPrivateRSA.pem size <br>
128 => Depends on the RSA keysize (1024/8)

## RSA-512

CPrivateRSA.pem size = 497 Bytes + 11 Bytes (PCKS Padding) = 508 Bytes

SPrivateRSA.pem (508 Bytes * 8)
<pre><code>
openssl genrsa -out SPrivateRSA.pem 4064
</code></pre>

SPublic.pem
<pre><code>
openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem
</code></pre>

RSA.bin
<pre><code>
ca. 508(EK1) + 16(IV) + 64(EK2) + 16(IV) =  604 Bytes
</code></pre>

508 => Depends on CPrivateRSA.pem size <br>
64 => Depends on the RSA keysize (512/8)

## AES