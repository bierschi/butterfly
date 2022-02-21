## RSA-4096 (Not Recommended)

`SPublic.pem`: is embedded in the ransomware application and used to encrypt
the **CPrivateRSA.pem** with keysize of **RSA-4096**

`SPrivateRSA.pem`: is loaded by the **bflyServerApp** on the attacker server and used for the secure remote decryption


Length of the CPrivateRSA.pem file is max of 3247 **Bytes** (`openssl genrsa -out CPrivateRSA.pem 4096` and verify byte size) <br>
Padding Size for PCKS: **11 Bytes** <br>
RSA factor: **8** <br>

`RSA Key size = (3247 bytes + 11 bytes) * 8 = 26064 Bytes`

Create private master key
<pre><code>openssl genrsa -out SPrivateRSA.pem 26064</code></pre>

Create public master key
<pre><code>openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem</code></pre>