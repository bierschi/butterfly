#!/usr/bin/python3
import os
import shutil
import requests
import tarfile

url = "http://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-amd64.tar.gz"
target_folder = "../fs"
target_file = "../fs/ubuntu-base-22.04-base-amd64.tar.gz"


def create_fs_folder(folderpath):
    """

    :return:
    """
    try:
        os.mkdir(folderpath)
    except FileExistsError as error:
        print(error)


def download_ubuntu_fs(filepath):
    """

    :return:
    """

    resp = requests.get(url, stream=True)
    if resp.status_code == 200:
        with open(filepath, 'wb') as f:
            f.write(resp.raw.read())
    else:
        print("Received invalid statuscode {} for downloading file {}".format(resp.status_code, filepath))


def extract_tar_gz(folderpath, filepath):
    """

    :param fname:
    :return:
    """

    cwd = os.getcwd()
    os.chdir(folderpath)

    if filepath.endswith("tar.gz"):
        tar = tarfile.open(filepath, "r:gz")
        tar.extractall()
        tar.close()
    elif filepath.endswith("tar"):
        tar = tarfile.open(filepath, "r:")
        tar.extractall()
        tar.close()
    else:
        print("Please provide file in tar.gz or tar format!")

    os.remove(filepath)
    os.chdir(cwd)


def prepare_fs_with_data():
    pass


def remove_fs(folderpath):
    """

    :param folderpath:
    :return:
    """
    try:
        shutil.rmtree(folderpath)
    except FileNotFoundError as error:
        print(error)


def main():
    print("Create example filesystem")
    create_fs_folder(folderpath=target_folder)
    download_ubuntu_fs(filepath=target_file)
    extract_tar_gz(folderpath=target_folder, filepath=target_file)
    #remove_fs(folderpath=target_folder)


if __name__ == '__main__':
    main()
