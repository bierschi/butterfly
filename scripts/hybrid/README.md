## Hybrid (RSA & AES) Encryption and Decryption

### Encryption
Generate private master key
<pre><code>openssl genrsa -out SPrivateRSA.pem 13768</code></pre>

Generate public master key
<pre><code>openssl rsa -in SPrivateRSA.pem -pubout -out SPublic.pem</code></pre>

Generate RSA private key
<pre><code>openssl genrsa -out CPrivateRSA.pem 2048</code></pre>

Generate public key from RSA private key
<pre><code>openssl rsa -in CPrivateRSA.pem -pubout -out CPublic.pem</code></pre>

Encrypt the CPrivateRSA.pem with the embedded SPublic.pem
<pre><code>openssl rsautl -encrypt -oaep -inkey SPublic.pem -pubin -in CPrivateRSA.pem -out CPrivateRSA.bin</code></pre>

Generate random AES key
<pre><code>
openssl rand -base64 128 > AESKey.txt
</code></pre>

Encrypt 5357083.pdf with AES-256-CBC
<pre><code>openssl enc -aes-256-cbc -md sha512 -pbkdf2 -iter 100000 -salt -kfile AESKey.txt -in ../../docs/5357083.pdf -out 5357083.bin</code></pre>

Encrypt AESKey.txt with CPublic.pem
<pre><code>openssl rsautl -encrypt -oaep -inkey CPublic.pem -pubin -in AESKey.txt -out AESKey.bin</code></pre>


### Decryption

Decrypt the CPrivateRSA.bin with the SPrivateRSA.pem file
<pre><code>openssl rsautl -decrypt -oaep -inkey SPrivateRSA.pem -in CPrivateRSA.bin -out CPrivateRSA.pem.dec</code></pre>

Decrypt AESKey.bin with CPrivateRSA.pem.dec
<pre><code>openssl rsautl -decrypt -oaep -inkey CPrivateRSA.pem.dec -in AESKey.bin -out AESKey.txt.dec</code></pre>

Decrypt 5357083.bin with AES-256-CBC
<pre><code>openssl enc -aes-256-cbc -md sha512 -pbkdf2 -iter 100000 -salt -d -kfile AESKey.txt.dec -in 5357083.bin -out 5357083.pdf.dec</code></pre>


### Validation

Check md5sum from CPrivateRSA.pem and CPrivateRSA.pem.dec
<pre><code>md5sum CPrivateRSA.pem CPrivateRSA.pem.dec</code></pre>

Check md5sum from AESKey.txt and AESKey.txt.dec
<pre><code>md5sum AESKey.txt AESKey.txt.dec</code></pre>

Check md5sum from 5357083.pdf and 5357083.pdf.dec
<pre><code>md5sum ../../docs/5357083.pdf 5357083.pdf.dec</code></pre>


## Block Diagram
<pre><code>
+---------------------+      +--------------------+
|                     |      |                    |
| generate random key |      |   the large file   |
|        (R)          |      |        (F)         |
|                     |      |                    |
+--------+--------+---+      +----------+---------+
         |        |                     |
         |        +------------------+  |
         |                           |  |
         v                           v  v
+--------+------------+     +--------+--+------------+
|                     |     |                        |
| encrypt (R) with    |     | encrypt (F)            |
| your RSA public key |     | with symmetric key (R) |
|                     |     |                        |
|  ASym(PublicKey, R) |     |     EF = Sym(F, R)     |
|                     |     |                        |
+----------+----------+     +------------+-----------+
           |                             |
           +------------+ +--------------+
                        | |
                        v v
         +--------------+-+---------------+
         |                                |
         |   send this files to the peer  |
         |                                |
         |     ASym(PublicKey, R) + EF    |
         |                                |
         +--------------------------------+

</code></pre>

Decryption

<pre><code>
+----------------+        +--------------------+
   |                |        |                    |
   | EF = Sym(F, R) |        | ASym(PublicKey, R) |
   |                |        |                    |
   +-----+----------+        +---------+----------+
         |                             |
         |                             |
         |                             v
         |   +-------------------------+-----------------+
         |   |                                           |
         |   |             restore key (R)               |
         |   |                                           |
         |   | R <= ASym(PrivateKey, ASym(PublicKey, R)) |
         |   |                                           |
         |   +---------------------+---------------------+
         |                         |
         v                         v
     +---+-------------------------+---+
     |                                 |
     |       restore the file (F)      |
     |                                 |
     |      F <= Sym(Sym(F, R), R)     |
     |                                 |
     +---------------------------------+
</code></pre>