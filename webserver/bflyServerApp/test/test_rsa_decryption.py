import unittest
import os
from bflyServerApp import RSADecryption


class TestRSADecryption(unittest.TestCase):

    def setUp(self) -> None:
        self.rsadecryptor = RSADecryption()
        self.rsadecryptor.generate_keys(keysize=2048)

    def tearDown(self) -> None:
        pass

    def test_get_private_key(self):

        private_key = self.rsadecryptor.get_private_key()
        self.assertTrue(private_key.startswith("-----BEGIN RSA PRIVATE KEY-----"))

    def test_get_public_key(self):

        public_key = self.rsadecryptor.get_public_key()
        self.assertTrue(public_key.startswith("-----BEGIN PUBLIC KEY-----"))

    def test_load_private_key(self):

        with self.assertRaises(FileNotFoundError):
            self.rsadecryptor.load_private_key("testPrivateKey.pem")

    def test_load_public_key(self):

        with self.assertRaises(FileNotFoundError):
            self.rsadecryptor.load_public_key("testPublicKey.pem")

    def test_encrypt_decrypt(self):

        # encrypt message
        encrypted_msg = self.rsadecryptor.encrypt(b"testMessage")
        # save private key to decrypt the message with different instance
        private_key = self.rsadecryptor.get_private_key()
        with open("privateKey.pem", "w") as file:
            file.write(private_key)

        self.assertIsInstance(encrypted_msg, bytes)

        # create second instance and load private key
        rsadecryptor = RSADecryption()
        rsadecryptor.load_private_key("privateKey.pem")
        # decrypt message
        deccrypted_msg = rsadecryptor.decrypt(encrypted_msg)

        self.assertIsInstance(deccrypted_msg, bytes)
        self.assertEqual(deccrypted_msg, b"testMessage")

        os.remove("privateKey.pem")


if __name__ == '__main__':
    unittest.main()
