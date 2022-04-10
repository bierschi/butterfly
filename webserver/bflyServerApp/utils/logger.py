import os
import logging
from logging.handlers import RotatingFileHandler
from bflyServerApp import ROOT_DIR


class Logger:
    """Singleton class Logger to set up a Logger instance
    USAGE:
            Logger(name='bflyServerApp')
    """
    __instance = None

    def __init__(self, name='bflyServerApp', level='info', log_folder='/var/log/bflyServerApp', log_max_bytes=10000000, backup=5):

        if Logger.__instance is not None:
            raise Exception("This class is a singleton!")
        else:
            Logger.__instance = self

        if isinstance(name, str):
            self.logger_name = name
            self.logger = logging.getLogger(name)
        else:
            raise TypeError("'name' must be type of string")

        if level == 'info':
            self.level = logging.INFO
        elif level == 'debug':
            self.level = logging.DEBUG
        elif level == 'warn':
            self.level = logging.WARN
        elif level == 'error':
            self.level = logging.ERROR
        else:
            # default level
            self.level = logging.INFO

        self.logger.setLevel(self.level)
        self.formatter = logging.Formatter('%(asctime)s - %(lineno)d@%(filename)s - %(levelname)s: %(message)s')

        self.local_log = ROOT_DIR + '/logs'

        if self.__create_log_folder(log_folder):

            info_log_file_path = log_folder + '/info.log'
            error_log_file_path = log_folder + '/error.log'
            self.set_up_handler(log_max_bytes, info_log_file_path, error_log_file_path, backup)

        elif self.__create_log_folder(self.local_log):

            info_log_file_path = self.local_log + '/info.log'
            error_log_file_path = self.local_log + '/error.log'
            self.set_up_handler(log_max_bytes, info_log_file_path, error_log_file_path, backup)

        else:
            print("Could not create a logger instance")

    @staticmethod
    def get_instance():
        """ get logger instance

        :return: Logger: logger instance
        """
        if Logger.__instance is None:
            Logger()
        return Logger.__instance

    def __create_log_folder(self, log_folder):
        """creates log folder in '/var/log/bflyServerApp'

        :return bool, True if log folder was successfully created
        """
        try:
            if log_folder.endswith('/'):
                if not os.path.exists(log_folder):
                    os.mkdir(log_folder)
                    return True
                else:
                    return True
            else:
                if not os.path.exists(log_folder):
                    os.mkdir(log_folder)
                    return True
                else:
                    return True

        except PermissionError as ex:
            print("Check permission for folder {}! Exception: {}".format(log_folder, ex))
            return False

    def set_up_handler(self, log_file_size, info_log_file_path, error_log_file_path, backup):
        """ sets up the logger handler

        """
        stream_handler = logging.StreamHandler()
        stream_handler.setLevel(self.level)
        stream_handler.setFormatter(self.formatter)

        info_rotate_handler = RotatingFileHandler(info_log_file_path, mode='a', maxBytes=log_file_size, backupCount=backup)  # 10mb
        info_rotate_handler.setFormatter(self.formatter)
        info_rotate_handler.setLevel(logging.DEBUG)  # fixed level

        error_rotate_handler = RotatingFileHandler(error_log_file_path, mode='a', maxBytes=log_file_size, backupCount=backup)  # 10mb
        error_rotate_handler.setFormatter(self.formatter)
        error_rotate_handler.setLevel(logging.WARNING)  # fixed level

        self.logger.addHandler(stream_handler)
        self.logger.addHandler(info_rotate_handler)
        self.logger.addHandler(error_rotate_handler)

    def info(self, msg):
        """logs info messages

        :param msg: string messages
        """
        self.logger.info(msg)

    def debug(self, msg):
        """logs debug messages

        :param msg: string messages
        """
        self.logger.debug(msg)

    def warning(self, msg):
        """logs warning messages

        :param msg: string messages
        """
        self.logger.warning(msg)

    def error(self, msg):
        """logs error messages

        :param msg: string messages
        """
        self.logger.error(msg)
