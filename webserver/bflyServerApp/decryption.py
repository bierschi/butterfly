import os
import logging
from bflyServerApp import RSADecryption, AESDecryption
from bflyServerApp.exceptions import RSADecryptionError, AESDecryptionError
from bflyServerApp import __title__


class Decryption:
    """ class Decryption to decrypt the CPrivateRSA.bin file

    USAGE:
            decryptor = Decryption(cprivatersa_str, rsabin_str, ../../masterkeys/SPrivateRSA.pem, 2048)
            cprivatersa_decrypted = decryptor.get_decrypted_cprivatersa()
    """
    def __init__(self, cprivatersa_str, rsabin_str, sprivatersa_filepath, rsa_keysize):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class Decryption')

        self.cprivatersa_str = cprivatersa_str
        self.rsabin_str = rsabin_str
        self.rsa_pkey_delimiter = b"-----END RSA PRIVATE KEY-----\n"
        self.pkey_delimiter = b"-----END PRIVATE KEY-----\n"

        self.logger.info("Length of CPrivateRSA.bin string is {} bytes".format(len(self.cprivatersa_str)))
        self.logger.info("Length of RSA.bin string is {} bytes".format(len(self.rsabin_str)))

        if isinstance(rsa_keysize, str):
            if rsa_keysize.isdecimal():
                self.rsa_key_length = int(int(rsa_keysize)/8)
                self.logger.info("Setting rsa_key_length to {}".format(self.rsa_key_length))
            else:
                self.logger.error("Setting rsa_key_length to 256 as default value!")
                self.rsa_key_length = 256
        else:
            self.rsa_key_length = int(int(rsa_keysize)/8)

        if len(rsabin_str) < (self.rsa_key_length + 16 + 16):
            self.logger.error("RSA.bin string is smaller than {}+16+16!".format(self.rsa_key_length))

        self.rsabin_str_length = len(self.rsabin_str)
        self.iv_length = 16

        self.rsa_ek1_bin, self.rsa_ek2_bin = self._get_ekbin_from_rsabin()
        self.rsa_iv1, self.rsa_iv2 = self._get_iv_from_rsabin()

        self.rsadecryptor = RSADecryption()

        if os.path.isfile(sprivatersa_filepath):
            self.sprivatersa_filepath = sprivatersa_filepath
        else:
            raise FileExistsError("Could not find file {}".format(sprivatersa_filepath))

    def _get_ekbin_from_rsabin(self):
        """ get the rsa ek from the RSA.bin string

        :return: rsa_ek1, rsa_ek2
        """

        rsa_ek1 = self.rsabin_str[0 : (self.rsabin_str_length - 2*self.iv_length - self.rsa_key_length)]
        rsa_ek2 = self.rsabin_str[(self.rsabin_str_length - self.iv_length - self.rsa_key_length) : (self.rsabin_str_length - self.iv_length)]

        return rsa_ek1, rsa_ek2

    def _get_iv_from_rsabin(self):
        """ get the rsa iv from the RSA.bin string

        :return: rsa_iv1, rsa_iv2
        """

        rsa_iv1 = self.rsabin_str[(self.rsabin_str_length - 2*self.iv_length - self.rsa_key_length) : (self.rsabin_str_length - self.iv_length - self.rsa_key_length)]
        rsa_iv2 = self.rsabin_str[(self.rsabin_str_length - self.iv_length) : self.rsabin_str_length]
        return rsa_iv1, rsa_iv2

    def decrypt_rsa(self):
        """ decrypt the rsa_ek1.bin with the RSA Decryption class

        :return: rsa_ek1 string
        """
        try:
            self.logger.info("Load SPrivateRSA.pem from {}".format(self.sprivatersa_filepath))
            self.rsadecryptor.load_private_key(self.sprivatersa_filepath)

            return self.rsadecryptor.decrypt(enc_msg=self.rsa_ek1_bin)

        except FileNotFoundError as e:
            self.logger.error("File {} not found!".format(self.sprivatersa_filepath))
            raise RSADecryptionError("RSADecryptionError: {}".format(e))

        except ValueError as e:
            self.logger.error(e)
            raise RSADecryptionError("RSADecryptionError: {}".format(e))

    def decrypt_aes(self, key, iv, enc):
        """ decrypt the CPrivateRSA.bin with the AES Decryption class

        :return: decrypted CPrivateRSA string
        """
        try:
            aesdecryptor = AESDecryption(key=key, iv=iv)
            return aesdecryptor.decrypt(enc_msg=enc)
        except Exception as e:
            self.logger.error(e)
            raise AESDecryptionError("AESDecryptionError: {}".format(e))

    def get_decrypted_cprivatersa(self):
        """ Get the decrypted cprivatersa byte string

        :return: decrypted CPrivateRSA string
        """
        self.logger.info("Decrypt the rsa_ek1.bin with RSA")
        rsa_ek1 = self.decrypt_rsa()

        self.logger.info("Decrypt the CPrivateRSA.bin with AES")
        cprivatersa_decrypted = self.decrypt_aes(rsa_ek1, self.rsa_iv1, self.cprivatersa_str)

        if self.rsa_pkey_delimiter in cprivatersa_decrypted:
            cprivatersa_decrypted = cprivatersa_decrypted[:cprivatersa_decrypted.index(self.rsa_pkey_delimiter) + len(self.rsa_pkey_delimiter)]
            return cprivatersa_decrypted
        elif self.pkey_delimiter in cprivatersa_decrypted:
            cprivatersa_decrypted = cprivatersa_decrypted[:cprivatersa_decrypted.index(self.pkey_delimiter) + len(self.pkey_delimiter)]
            return cprivatersa_decrypted
        else:
            return cprivatersa_decrypted
