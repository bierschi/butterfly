# BFLY AES Decryption

File was encrypted with the `butterfly` application and the AES KeyPair was saved unencrypted to file `AES.bin.unencrypted`<br>


### Get AESKey and AESIV from `AES.bin.unencrypted`

Size of `AES.bin.unencrypted` = 48 Bytes <br>
AESKey = 1 - 32 Bytes <br>
<pre><code>
xxd -l 32 -p AES.bin.unencrypted
</code></pre>
AESIV  = 32-48 Bytes <br>
<pre><code>
xxd -l 16 -s 32 -p AES.bin.unencrypted
</code></pre>

### AES Decryption of BFLY Files
<pre><code>
openssl enc -aes-256-cbc -d -iter 6 -salt -md sha256 -in 5357083.pdf.bfly -K '8801c08a28789564a0e23f35ab1b997bfe27ed4efe55ead2bc6458e650c46b7c' -iv 'd3ac02b9a0314873eacdf06a582a8df8' -out 5357083.dec.pdf
</code></pre>
