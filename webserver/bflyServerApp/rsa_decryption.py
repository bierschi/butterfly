import logging
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import padding
from bflyServerApp import __title__


class RSADecryption:
    """ class RSADecryption to decrypt rsa encrypted messages

    USAGE:
            rsadecryptor = RSADecryption()
            rsadecryptor.generate_keys(keysize=2048)
            rsadecryptor.get_private_key()
    """
    def __init__(self):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class RSADecryption')

        self.private_key = None
        self.public_key = None

    def generate_keys(self, keysize=2048):
        """ generate the rsa keypair

        """
        self.private_key = rsa.generate_private_key(public_exponent=65537, key_size=keysize, backend=default_backend())
        self.public_key = self.private_key.public_key()

    def get_private_key(self):
        """ get the rsa private key string

        :return: rsa private key as string
        """
        if self.private_key is not None:
            private_key = self.private_key.private_bytes(encoding=serialization.Encoding.PEM, format=serialization.PrivateFormat.TraditionalOpenSSL, encryption_algorithm=serialization.NoEncryption())
            return str(private_key, 'utf-8')
        else:
            raise ValueError("'private_key' is not initialized! Did you invoke the generate_keys() or the load_private_key() method?")

    def get_public_key(self):
        """ get the rsa public key string

        :return: rsa public key as string
        """
        if self.public_key is not None:
            public_key = self.public_key.public_bytes(encoding=serialization.Encoding.PEM, format=serialization.PublicFormat.SubjectPublicKeyInfo)
            return str(public_key, 'utf-8')
        else:
            raise ValueError("'public_key' is not initialized! Did you invoke the generate_keys() or the load_public_key() method?")

    def load_private_key(self, private_key):
        """ loads the private key file

        :param private_key: path to the private key file
        """
        with open(private_key, 'rb') as private_key_file:
            self.private_key = serialization.load_pem_private_key(private_key_file.read(), password=None, backend=default_backend())

    def load_public_key(self, public_key):
        """ loads the public key file

        :param public_key: path to the public key file
        """
        with open(public_key, 'rb') as public_key_file:
            self.public_key = serialization.load_pem_public_key(public_key_file.read(), backend=default_backend())

    def encrypt(self, msg):
        """ encrypts the msg with the rsa public key

        :param msg: message to encrypt
        :return: encrypted byte string
        """
        if self.public_key is not None:
            return self.public_key.encrypt(msg, padding.PKCS1v15())
        else:
            raise ValueError("'public_key' is not initialized! Did you invoke the generate_keys() or the load_public_key() method?")

    def decrypt(self, enc_msg):
        """ decrypts the encrypted message with the rsa private key

        :param enc_msg: message to decrypt
        :return: decrypted byte string
        """
        if self.private_key is not None:
            return self.private_key.decrypt(enc_msg, padding=padding.PKCS1v15())
        else:
            raise ValueError("'private_key' is not initialized! Did you invoke the generate_keys() or the load_private_key() method?")


if __name__ == '__main__':

    dec = RSADecryption()
    #dec.generate_keys()
    dec.load_private_key("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem")
    with open('/home/christian/projects/butterfly/webserver/files/rsa_ek1.bin', 'rb') as f:
        encrypted = f.read()
    print(dec.decrypt(encrypted))