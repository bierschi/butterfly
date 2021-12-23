# BFLY Files

### AES.bin
RSA encrypted AESKeyPair (AESKey+AESIV) 

### AES.bin.unencrypted

Size of `AES.bin.unencrypted` = 48 Bytes <br>
AESKey = 1 - 32 Bytes <br>
<pre><code>
xxd -l 32 -p AES.bin.unencrypted
</code></pre>
AESIV  = 32-48 Bytes <br>
<pre><code>
xxd -l 16 -s 32 -p AES.bin.unencrypted
</code></pre>

### CPrivateRSA.bin
RSA encrypted CPrivateRSA.pem string with the embedded `SPublic.pem` File

### RSA.bin
EK and IV for each RSA Encryption are saved in file `RSA.bin`

Size of `RSA.bin` = 2009 Bytes <br>
1. CPrivateRSA.bin encryption with RSA
<pre><code>
CPrivateRSA.pem size = 1721 Bytes <br>
IV                   = 16 Bytes
= 1737 Bytes
</code></pre>

2. AES.bin encryption with RSA
<pre><code>
AESKey = 256 Bytes <br>
IV     = 16 Bytes
= 272 Bytes
</code></pre>

Summery: 1737 Bytes + 272 Bytes => 2009 Bytes
