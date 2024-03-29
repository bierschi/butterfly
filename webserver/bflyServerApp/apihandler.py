import os
import json
import string
import logging
from flask import Response, request
from bflyServerApp import Decryption
from bflyServerApp.exceptions import RSADecryptionError, AESDecryptionError
from bflyServerApp import __title__, __version__


class APIHandler:
    """ class APIHandler to link routes to specific handler function

    USAGE:
            api = APIHandler(sprivatersa_filepath=../../masterkeys/SPrivateRSA.pem)

    """
    def __init__(self, sprivatersa_filepath):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class APIHandler')
        self.decryption_counter = 0

        if os.path.isfile(sprivatersa_filepath):
            self.sprivatersa_filepath = sprivatersa_filepath
        else:
            raise FileExistsError("Could not find file {}".format(sprivatersa_filepath))

    def _is_hex(self, s):
        """ checks if given string is in hex format

        :param s: string to check
        :return: True if the string is in hex, else False
        """
        hex_digits = set(string.hexdigits)
        return all(c in hex_digits for c in s)

    def _decryption(self, cprivatersa, rsabin, rsakeysize):
        """ decrypts the cprivatersa string

        :param cprivatersa: cprivate rsa string
        :param rsabin: rsa bin string
        :param rsakeysize: rsa keysize
        :return: Response object
        """
        try:
            if self._is_hex(cprivatersa):
                cprivatersa = bytes.fromhex(cprivatersa)
            if self._is_hex(rsabin):
                rsabin = bytes.fromhex(rsabin)

            decryptor = Decryption(cprivatersa, rsabin, self.sprivatersa_filepath, rsakeysize)
            cprivatersa_decrypted = decryptor.get_decrypted_cprivatersa()

            self.logger.info("Returning the decrypted CPrivateRSA.pem string!")
            return Response(status=200, response=cprivatersa_decrypted.decode('utf-8'), mimetype='application/json')

        except ValueError as e:
            self.logger.error(e)
            return Response(status=500, response="Internal Server Error at the Decryption Process occurred!", mimetype='application/json')

        except RSADecryptionError as e:
            self.logger.error(e)
            return Response(status=500, response="Internal Server Error at the RSA Decryption Process occurred!", mimetype='application/json')

        except AESDecryptionError as e:
            self.logger.error(e)
            return Response(status=500, response="Internal Server Error at the AES Decryption Process occurred!", mimetype='application/json')

    def index(self):
        """ index page

        :return: string
        """
        return "Butterfly Server Application for a secure remote Decryption of the Client's CPrivateRSA.bin File"

    def route_decrypt(self):
        """ decrypts the CPrivateRSA.bin string

        :return: Response object
        """

        self.logger.info("{} request to route {}".format(request.method, request.path))

        if request.form:

            if all(key in request.form.keys() for key in ('CPrivateRSA.bin', 'RSA.bin', 'RSAKeySize')):
                self.logger.info("Processing form request")

                cprivate_rsa = request.form['CPrivateRSA.bin']
                rsa_bin = request.form['RSA.bin']
                rsa_keysize = request.form['RSAKeySize']

                self.decryption_counter += 1

                return self._decryption(cprivate_rsa, rsa_bin, rsa_keysize)
            else:
                self.logger.error("Missing key in form request")
                return Response(status=400, response=json.dumps("Missing Key in Form Request"), mimetype='application/json')

        elif request.json:

            if all(key in request.json.keys() for key in ('CPrivateRSA.bin', 'RSA.bin', 'RSAKeySize')):
                self.logger.info("Processing json request")

                cprivate_rsa = request.json['CPrivateRSA.bin']
                rsa_bin = request.json['RSA.bin']
                rsa_keysize = request.json['RSAKeySize']

                self.decryption_counter += 1

                return self._decryption(cprivate_rsa, rsa_bin, rsa_keysize)
            else:
                self.logger.error("Missing key in json request")
                return Response(status=400, response=json.dumps("Missing Key in JSON Request"), mimetype='application/json')

        else:
            self.logger.error("Not a valid reqeust format!")
            return Response(status=400, response=json.dumps("Not a valid request format!"), mimetype='application/json')

    def route_decryption_counter(self):
        """ requesting the decryption counter

        :return: Response object
        """

        self.logger.info("{} request to route {}".format(request.method, request.path))

        return Response(status=200, response=str(self.decryption_counter), mimetype='text/plain')

    def route_version(self):
        """ requesting the current version of the app

        :return: Response object
        """

        self.logger.info("{} request to route {}".format(request.method, request.path))

        return Response(status=200, response=__version__, mimetype='text/plain')
