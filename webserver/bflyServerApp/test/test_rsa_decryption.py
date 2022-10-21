import unittest
from bflyServerApp import RSADecryption


class TestRSADecryption(unittest.TestCase):

    def setUp(self) -> None:
        self.rsadecryptor = RSADecryption()
        self.rsadecryptor.generate_keys(keysize=2048)

    def tearDown(self) -> None:
        pass

    def test_get_private_key(self):
        key = self.rsadecryptor.get_private_key()
        print(key)

    def test_get_public_key(self):
        pass

    def test_encrypt(self):
        pass

    def test_decrypt(self):
        pass


if __name__ == '__main__':
    unittest.main()
