## RSA-1024

`SPublic.pem`: is embedded in the ransomware application and used to encrypt
the **CPrivateRSA.pem** with keysize of **RSA-1024**

`SPrivateRSA.pem`: is loaded by the **bflyServerApp** on the attacker server and used for the secure remote decryption


Length of the CPrivateRSA.pem file is max of **910 Bytes** (`openssl genrsa -out CPrivateRSA.pem 1024` and verify byte size) <br>
Padding Size for PCKS: **11 Bytes** <br>
RSA factor: **8** <br>

`RSA Key size = (910 bytes + 11 bytes) * 8 = 7368 Bytes`

Create private master key
<pre><code>openssl genrsa -out SPrivateRSA.pem 7368</code></pre>

Create public master key
<pre><code>openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem</code></pre>