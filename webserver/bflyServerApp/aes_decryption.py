import logging
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from bflyServerApp import __title__


class AESDecryption:
    """ class AESDecryption to decrypt aes encrypted messages

    USAGE:
            aesdecryptor = AESDecryption(key=key, iv=iv)
            decrypted = aesdecryptor.decrypt(enc_msg)
    """
    def __init__(self, key, iv):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class AESDecryption')

        self.key = key
        self.iv  = iv
        self.cipher = Cipher(algorithm=algorithms.AES(self.key), mode=modes.CBC(self.iv), backend=default_backend())
        self.encryptor = self.cipher.encryptor()
        self.decryptor = self.cipher.decryptor()

    def encrypt(self, msg):
        """ encrypts the msg with aes

        :param msg: message to encrypt
        :return: aes encrypted message
        """
        return self.encryptor.update(msg) + self.encryptor.finalize()

    def decrypt(self, enc_msg):
        """ decrypts the aes encrypted message

        :param enc_msg: encrypted message
        :return: aes decrypted message as byte string
        """
        return self.decryptor.update(enc_msg) + self.decryptor.finalize()


if __name__ == '__main__':
    #key = os.urandom(32)
    #iv = os.urandom(16)
    with open('/home/christian/projects/butterfly/webserver/files/rsa_ek1.txt', 'rb') as f:
        key = f.read()
    with open('/home/christian/projects/butterfly/webserver/files/rsa_iv1.txt', 'rb') as f:
        iv = f.read()
    with open('/home/christian/projects/butterfly/webserver/files/CPrivateRSA.bin', 'rb') as f:
        enc = f.read()
    aes = AESDecryption(key, iv)
    #enc = aes.encrypt(b"a secret messagea")
    dec = aes.decrypt(enc)
    print(dec.decode())

    #cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    #encryptor = cipher.encryptor()
    #ct = encryptor.update(b"a secret message") + encryptor.finalize()
    #print(ct)
    #decryptor = cipher.decryptor()
    #dec = decryptor.update(ct) + decryptor.finalize()
    #print(dec)
