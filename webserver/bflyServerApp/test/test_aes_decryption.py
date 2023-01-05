import unittest
from bflyServerApp import AESDecryption


class TestAESDecryption(unittest.TestCase):

    def setUp(self) -> None:

        self.aesdecryption = AESDecryption(key=b'12345678912345678912345678912345', iv=b'1234567812345678')
        self.dec_msg = b'a secret message'
        self.enc_msg = b'l\xef\xfd\xaa\x8e\xcd\xc0\x0b\x07\x0c\xc2\nQ\xfb1T'

    def tearDown(self) -> None:
        pass

    def test_encrypt(self):

        enc_msg = self.aesdecryption.encrypt(msg=self.dec_msg)
        self.assertTrue(enc_msg, self.enc_msg)

    def test_decrypt(self):

        dec_msg = self.aesdecryption.decrypt(enc_msg=self.enc_msg)
        self.assertTrue(dec_msg, self.dec_msg)


if __name__ == '__main__':
    unittest.main()
