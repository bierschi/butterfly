# AES Encryption/Decryption Tool

### Encrypt with `aesbfly`

<pre><code>
</code></pre>

### Decrypt with openssl cli

<pre><code>
openssl enc -aes-256-cbc -d -iter 6 -salt -md sha256 -in 5357083.pdf.bfly -K $(cat AESKeyHex.txt) -iv $(cat AESKeyHex.txt) -out 5357083.pdf
</code></pre>

### Encrypt with openssl cli

Generate the AESKey
<pre><code>
openssl rand -hex 32 > AESKeyHex.txt
</code></pre>

Generate the AESIV
<pre><code>
openssl rand -hex 16 > AESIVHex.txt
</code></pre>

Encrypt the file
<pre><code>
openssl enc -aes-256-cbc -e -iter 6 -salt -md sha256 -in ../5357083.pdf -K $(cat AESKeyHex.txt) -iv $(cat AESIVHex.txt) -out 5357083.pdf.bfly
</code></pre>

### Decrypt with `aesbfly`

<pre><code>

</code></pre>

### Encrypt with `aesbfly`

<pre><code>
</code></pre>

### Decrypt with `aesbfly`

<pre><code>
</code></pre>