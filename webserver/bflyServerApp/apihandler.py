import os
import json
import logging
from flask import Response, request
from bflyServerApp import Decryption
from bflyServerApp import __title__


class APIHandler:
    """ class APIHandler to link routes to specific handler function

    USAGE:
            api = APIHandler()

    """
    def __init__(self, sprivatersa_filepath):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class APIHandler')

        if os.path.isfile(sprivatersa_filepath):
            self.sprivatersa_filepath = sprivatersa_filepath
        else:
            raise FileExistsError("Could not find file {}".format(sprivatersa_filepath))

    def index(self):
        """

        :return:
        """
        return "hello world"

    def decrypt(self):
        """ Decrypts the CPrivateRSA.bin string

        :return: Response object
        """

        self.logger.info("POST request to route /decrypt/")

        if request.json is not None:
            if 'CPrivateRSA.bin' not in request.json:
                self.logger.error("Missing Key 'CPrivateRSA.bin 'in Request!")
                return Response(status=400, response=json.dumps("Missing Key in Request"), mimetype='application/json')

            if 'RSA.bin' not in request.json:
                self.logger.error("Missing Key 'RSA.bin 'in Request!")
                return Response(status=400, response=json.dumps("Missing Key in Request"), mimetype='application/json')

            cprivatersa_hex = request.json['CPrivateRSA.bin']
            rsabin_hex = request.json['RSA.bin']

            cprivatersa = bytes.fromhex(cprivatersa_hex)
            rsabin = bytes.fromhex(rsabin_hex)

            decryptor = Decryption(cprivatersa, rsabin, self.sprivatersa_filepath)
            cprivatersa_decrypted = decryptor.get_decrypted_cprivatersa()

            #return Response(status=200, response=json.dumps(cprivatersa_decrypted.decode('utf-8')), mimetype='application/json')
            return Response(status=200, response=cprivatersa_decrypted.decode('utf-8'), mimetype='application/json')

        elif all(key in request.form.keys() for key in ('CPrivateRSA.bin', 'RSA.bin')):
            cprivatersa_hex = request.form['CPrivateRSA.bin']
            rsabin_hex = request.form['RSA.bin']

            cprivatersa = bytes.fromhex(cprivatersa_hex)
            rsabin = bytes.fromhex(rsabin_hex)

            decryptor = Decryption(cprivatersa, rsabin, self.sprivatersa_filepath)
            cprivatersa_decrypted = decryptor.get_decrypted_cprivatersa()
            return Response(status=200, response=cprivatersa_decrypted.decode('utf-8'), mimetype='application/json')

        else:
            return Response(status=400, response=json.dumps("Not a valid json format!"), mimetype='application/json')
