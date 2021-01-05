## Hybrid (RSA & AES) Encryption and Decryption

Get RSA Public Key
<pre><cocde>
openssl rsa -in id_rsa -outform pem > id_rsa.pem
openssl rsa -in id_rsa -pubout -outform pem > id_rsa.pub.pem
</cocde></pre>

Generate random key
<pre><cocde>
openssl rand -base64 32 > key.bin
</cocde></pre>

Encrypt the key
<pre><cocde>
openssl rsautl -encrypt -inkey id_rsa.pub.pem -pubin -in key.bin -out key.bin.enc
</cocde></pre>

Actually encrypt the large data file
<pre><cocde>
openssl enc -aes-256-cbc -salt -in SECRET_FILE -out SECRET_FILE.enc -pass file:./key.bin
</cocde></pre>

----------SEND DATA--------------

Decrypt the random key
<pre><cocde>
openssl rsautl -decrypt -inkey id_rsa.pem -in key.bin.enc -out key.bin
</cocde></pre>

Decrypt large data file with the decrypted random key
<pre><cocde>
openssl enc -d -aes-256-cbc -in SECRET_FILE.enc -out SECRET_FILE -pass file:./key.bin
</cocde></pre>



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