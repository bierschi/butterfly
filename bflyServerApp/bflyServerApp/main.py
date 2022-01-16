import logging
import argparse

from bflyServerApp import Router
from bflyServerApp import APIHandler
from bflyServerApp.utils import Logger
from bflyServerApp import __version__, __title__


class BFLYServerApp:
    """

    """
    def __init__(self):
        self.logger = logging.getLogger(__title__)
        self.logger.info('Create class BFLYServerApp')

        # create the APIHandler instance
        self.api = APIHandler()

        # router instance for specific endpoints
        self.router = Router(name=__title__)
        self.router.add_endpoint('/', 'index', method="GET", handler=self.api.index)

    def run(self, host='0.0.0.0', port=None, debug=None):
        """

        :return:
        """
        self.router.run(host=host, port=port, debug=debug)


def main():

    usage1 = ""
    usage2 = ""

    description = "Butterfly Server Application to decrypt the Client's CPrivateRSA.bin File\n\n {}\n         {}".format(usage1, usage2)

    # parse arguments
    parser = argparse.ArgumentParser(description=description, formatter_class=argparse.RawDescriptionHelpFormatter)

    # argument for the current version
    parser.add_argument('-v', '--version',      action='version', version=__version__, help='Shows the current version')

    # parse all arguments
    args = parser.parse_args()

    # set up logger instance
    logger = Logger(name=__title__, level='info', log_folder='/var/log/bflyServerApp')
    logger.info("Start Application bflyServerApp with version {}".format(__version__))

    # create application instance
    bflyServerApp = BFLYServerApp()
    bflyServerApp.run(host='127.0.0.1', port=5000)


if __name__ == '__main__':
    main()
