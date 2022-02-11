import os
import logging
from bflyServerApp import RSADecryption, AESDecryption
from bflyServerApp import __title__


class Decryption:
    """ class Decryption to decrypt the CPrivateRSA.bin file

    USAGE:
            decryptor = Decryption(cprivatersa_str, rsabin_str, ../../masterkeys/SPrivateRSA.pem)
            cprivatersa_decrypted = decryptor.get_decrypted_cprivatersa()
    """
    def __init__(self, cprivatersa_str, rsabin_str, sprivatersa_filepath):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class Decryption')

        self.cprivatersa_str = cprivatersa_str
        self.rsabin_str = rsabin_str
        self.delimiter = b"-----END RSA PRIVATE KEY-----\n"

        if len(rsabin_str) < 2009:
            self.logger.error("Length of the RSA.bin string is smaller then 2009 bytes: {}".format(len(rsabin_str)))
        else:
            self.logger.info("Length of RSA.bin string has {} bytes".format(len(rsabin_str)))

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
        rsa_ek1 = self.rsabin_str[0:1721]
        rsa_ek2 = self.rsabin_str[1737:1993]
        return rsa_ek1, rsa_ek2

    def _get_iv_from_rsabin(self):
        """ get the rsa iv from the RSA.bin string

        :return: rsa_iv1, rsa_iv2
        """
        rsa_iv1 = self.rsabin_str[1721:1737]
        rsa_iv2 = self.rsabin_str[1993:2009]
        return rsa_iv1, rsa_iv2

    def decrypt_rsa(self):
        """ decrypt the rsa_ek1.bin with the RSA Decryption class

        :return: rsa_ek1 string
        """
        try:
            self.logger.info("Load SPrivateRSA.pem from {}".format(self.sprivatersa_filepath))
            self.rsadecryptor.load_private_key(self.sprivatersa_filepath)

            return self.rsadecryptor.decrypt(enc_msg=self.rsa_ek1_bin)

        except FileNotFoundError:
            self.logger.error("File {} not found!".format(self.sprivatersa_filepath))

        except ValueError as e:
            self.logger.error(e)

    def decrypt_aes(self, key, iv, enc):
        """ decrypt the CPrivateRSA.bin with the AES Decryption class

        :return: decrypted CPrivateRSA string
        """
        aesdecryptor = AESDecryption(key=key, iv=iv)
        return aesdecryptor.decrypt(enc_msg=enc)

    def get_decrypted_cprivatersa(self):
        """ Get the decrypted cprivatersa byte string

        :return: decrypted CPrivateRSA string
        """
        self.logger.info("Decrypt the rsa_ek1.bin with RSA")
        rsa_ek1 = self.decrypt_rsa()

        self.logger.info("Decrypt the CPrivateRSA.bin with AES")
        cprivatersa_decrypted = self.decrypt_aes(rsa_ek1, self.rsa_iv1, self.cprivatersa_str)

        if self.delimiter in cprivatersa_decrypted:
            cprivatersa_decrypted = cprivatersa_decrypted[:cprivatersa_decrypted.index(self.delimiter) + len(self.delimiter)]
            return cprivatersa_decrypted
        else:
            return cprivatersa_decrypted
