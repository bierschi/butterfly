# Hybrid Encryption/Decryption Mechanism

## Attacker

Attacker posses the rsa private masterkey `SPrivateRSA.pem` (KB) file on the hidden server

## Victim

Victim has the rsa public masterkey `SPublic.pem` (KA) embedded in the ransomware application


## Encryption

- ransomware creates infection specific RSA-2048 keypair
    - `CPrivateRSA.pem` (Ks)
    - `CPublic.pem` (Kp)

- `SPublic.pem` (KA) encrypts `CPrivateRSA.pem` (Ks) => `CPrivateRSA.bin` <br>
- Save `CPublic.pem` key file in Memory => `CPublic.pem` <br>
- Create random aes key and iv for data encryption
- Encrypt all user files with AES-256-CBC  => files.txt.bfly (Binary data)
- Encrypting AES key with `CPublic.pem` String => `AESKey.bin`
- Until this step no internet access is necessary!


## Decryption

After the ransom was paid
- Send the `CPrivateRSA.bin` to the attacker server and get the decrypted `CPrivateRSA.pem` string/file
- Decrypt `AESKeys.bin` with `CPrivateRSA.pem` and `CPublic.pem` => `AESKeys (S1, S2, ...SN)`
- (Decrypt user data files with S1, S2, ..., SN)
- Decrypt AESKey.bin with CPrivateRSA.pem => AESKey.txt
- Decrypt files.txt.bfly with AESKey.txt => file.txt



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
