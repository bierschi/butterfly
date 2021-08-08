# Hybrid Encryption Mechanism

## Attacker

Attacker posses the rsa private masterkey `SPrivateRSA.pem` (KB) file

## Victim

Victim has the rsa public masterkey `SPublic.pem` (KA) embedded in the ransomware application


## Encryption

ransomware creates infection specific RSA-2048 keypair
- `CPrivateRSA.pem` (Ks)
- `CPublic.pem` (Kp)

`SPublic.pem` (KA) encrypts `CPrivateRSA.pem` (Ks) => `CPrivateRSA.bin` <br>
Save `CPublic.pem` key file => `CPublic.pem` <br>
Encrypting all AES keys with `CPublic.pem` => `AESKeys.bin`

## Decryption

After the ransom was paid
- Send `SPrivateRSA.pem` to victim and decrypt `CPrivateRSA.bin` with `SPublic.pem` => `CPrivateRSA.pem`
- Decrypt `AESKeys.bin` with `CPrivateRSA.pem` and `CPublic.pem` => `AESKeys (S1, S2, ...SN)`
- Decrypt user data files with S1, S2, ..., SN