import json
import logging
from flask import Response, request
from bflyServerApp import __title__


class APIHandler:
    """ class APIHandler to link routes to specific handler function

    USAGE:
            api = APIHandler()

    """
    def __init__(self):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class APIHandler')

    def index(self):
        """

        :return:
        """
        return "hello world"

    def decrypt(self):
        """

        :return:
        """

        self.logger.info("POST request to route /decrypt/")

        return Response(status=200, response=json.dumps("Test"), mimetype='application/json')
