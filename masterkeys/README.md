## Masterkeys (from attacker) for the Encryption & Decryption process

`SPublic.pem`: is embedded in the ransomware application and used to encrypt 
the CPrivateRSA.pem (RSA-2048)

`SPrivateRSA.pem`: will be provided from the attacker server when the ransom 
was paid successfully


Create private master key
<pre><code>openssl genrsa -out SPrivateRSA.pem 13768</code></pre>

Create public master key
<pre><code>openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem</code></pre>

<br>
Length of the CPrivateRSA.pem (for 2048 RSA key size): 1679 bytes <br>
Padding Size for OAEP: 42 Bytes <br>
RSA factor: 8 <br>

`RSA Key size = (1679 bytes + 42 bytes) * 8 = 13768`


