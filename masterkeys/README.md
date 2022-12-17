## Masterkeys for the Encryption & Decryption process

`SPublic.pem`: is embedded in the butterfly application and used to encrypt 
the **CPrivateRSA.pem** with keysize of **RSA-2048** (default size)

`SPrivateRSA.pem`: is downloaded by the [bflyServerApp](https://github.com/bierschi/butterfly/tree/master/webserver) from the secure remote attacker server after successful ransom payment 

### Calculate the Masterkey size

#### RSA-2048
Length of the `CPrivateRSA.pem` file is max of **1679 Bytes** (`openssl genrsa -out CPrivateRSA.pem 2048` and verify byte size) <br>
Padding Size for PCKS: **11 Bytes** <br>
RSA factor: **8** <br>

`RSA Key size = (1679 bytes + 11 bytes) * 8 = 13520`

Create private master key
<pre><code>
openssl genrsa -out SPrivateRSA.pem 13520
</code></pre>

Create public master key
<pre><code>
openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem
</code></pre>
