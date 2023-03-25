import logging
from flask import Flask
from bflyServerApp import __title__


class Router:
    """ class Router to add multiple endpoints to the flask application

    USAGE:
            router = Router(name="TestApp")
            router.add_endpoint(endpoint='/', endpoint_name="index", method="GET", handler=<function>)
            router.run()
    """

    def __init__(self, name):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class Router')

        self.name = name
        self.app = Flask(self.name)

    def run(self, host='0.0.0.0', port=None, debug=None):
        """ runs the development flask server

        :param host: default hostname
        :param port: the port of the webserver
        :param debug: run with debug output
        """
        self.app.run(host=host, port=port, debug=debug)

    def add_endpoint(self, endpoint=None, endpoint_name=None, method=None, handler=None, strict_slashes=False):
        """ adds an endpoint to the application

        :param endpoint: specific endpoint for the app
        :param endpoint_name: endpoint name for the app
        :param method: method for handler call (POST, PUT, DELETE, GET)
        :param handler: handler function/method to execute
        :param strict_slashes: add strict slashes check
        """
        if method == "POST":
            self.app.add_url_rule(endpoint, endpoint_name, handler, methods=["POST"], strict_slashes=strict_slashes)
        elif method == "PUT":
            self.app.add_url_rule(endpoint, endpoint_name, handler, methods=["PUT"], strict_slashes=strict_slashes)
        elif method == "DELETE":
            self.app.add_url_rule(endpoint, endpoint_name, handler, methods=["DELETE"], strict_slashes=strict_slashes)
        else:
            self.app.add_url_rule(endpoint, endpoint_name, handler, strict_slashes=strict_slashes)
