## Masterkeys (from attacker) for the Encryption & Decryption process

`SPublic.pem`: is embedded in the ransomware application and used to encrypt 
the CPrivateRSA.pem with keysize of RSA-2048 (default size)

`SPrivateRSA.pem`: will be provided from the attacker server when the ransom 
was paid successfully

### Calculate the master key size

#### RSA-512
Length of the CPrivateRSA.pem file is max of 497 bytes <br>
Padding Size for OAEP: 42 Bytes <br>
RSA factor: 8 <br>

`RSA Key size = (497 bytes + 42 bytes) * 8 = 4312`

Create private master key
<pre><code>openssl genrsa -out SPrivateRSA.pem 4312</code></pre>

Create public master key
<pre><code>openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem</code></pre>

#### RSA-1024
Length of the CPrivateRSA.pem file is max of 910 bytes <br>
Padding Size for OAEP: 42 Bytes <br>
RSA factor: 8 <br>

`RSA Key size = (910 bytes + 42 bytes) * 8 = 7616`

Create private master key
<pre><code>openssl genrsa -out SPrivateRSA.pem 7616</code></pre>

Create public master key
<pre><code>openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem</code></pre>

#### RSA-2048
Length of the CPrivateRSA.pem file is max of 1679 bytes <br>
Padding Size for OAEP: 42 Bytes <br>
RSA factor: 8 <br>

`RSA Key size = (1679 bytes + 42 bytes) * 8 = 13768`


Create private master key
<pre><code>openssl genrsa -out SPrivateRSA.pem 13768</code></pre>

Create public master key
<pre><code>openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem</code></pre>

<
