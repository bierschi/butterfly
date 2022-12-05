#!/usr/bin/python3
import os
import glob
import shutil
import requests
import tarfile
import argparse

url = "http://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-amd64.tar.gz"
image_url = "https://releases.ubuntu.com/22.04/ubuntu-22.04.1-desktop-amd64.iso"
target_folder = "../fs"
target_file = "../fs/ubuntu-base-22.04-base-amd64.tar.gz"


def create_fs_folder(folderpath):
    """ creates the filesystem folder fs/

    """
    try:
        os.mkdir(folderpath)
    except FileExistsError as error:
        print(error)


def download_ubuntu_fs(filepath):
    """ downloads the ubuntu fs tar.gz folder

    """

    resp = requests.get(url, stream=True)
    if resp.status_code == 200:
        with open(filepath, 'wb') as f:
            f.write(resp.raw.read())
    else:
        print("Received invalid statuscode {} for downloading file {}".format(resp.status_code, filepath))


def download_ubuntu_image():
    """

    :return:
    """
    resp = requests.get(image_url, stream=True)
    if resp.status_code == 200:
        with open("data/ubuntu-22.04.1-desktop-amd64.iso", 'wb') as f:
            f.write(resp.raw.read())
    else:
        print("Received invalid statuscode {} for downloading ubuntu image".format(resp.status_code))


def extract_tar_gz(extractpath, filepath):
    """ extracts the tar.gz/tar folder to folderpath

    :param extractpath: folderpath to extract the tar.gz file
    :param filepath: filepath to the tar.gz file
    """

    cwd = os.getcwd()
    os.chdir(extractpath)

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


def prepare_fs_with_data(folderpath):
    """ prepares the folderpath for data content

    """

    # create butterfly home directory
    home_dir = folderpath + '/home/butterfly'
    data_dir = home_dir + '/data'
    big_dir = data_dir + '/big'
    big_dir_sub = big_dir + '/subfolder'
    small_dir = data_dir + '/small'
    small_dir_sub = small_dir + '/subfolder'

    create_fs_folder(home_dir)
    create_fs_folder(data_dir)
    create_fs_folder(big_dir)
    create_fs_folder(big_dir_sub)
    create_fs_folder(small_dir)
    create_fs_folder(small_dir_sub)

    for file in glob.glob('data/file*'):
        shutil.copy(file, small_dir)
        shutil.copy(file, small_dir_sub)

    for file in glob.glob('data/zip*'):
        shutil.copy(file, small_dir)
    for file in glob.glob('data/*.exe'):
        shutil.copy(file, small_dir)

    for file in glob.glob('data/*'):
        shutil.copy(file, big_dir)

    for file in glob.glob('data/file*'):
        shutil.copy(file, big_dir_sub)


def remove_fs(folderpath):
    """ removes the filesystem folder fs/

    :param folderpath: path to the fs/ folder
    """
    try:
        shutil.rmtree(folderpath)
    except FileNotFoundError as error:
        print(error)


def main():

    usage1 = "USAGE: \n\t./createFilesystem.py"

    usage2 = "./createFileSystem.py "

    description = "Creates the ubuntu filesystem and prepares the data content in home directory. \n\n {}\n        {}".format(usage1, usage2)

    # parse arguments
    parser = argparse.ArgumentParser(description=description, formatter_class=argparse.RawDescriptionHelpFormatter)

    # arguments
    #parser.add_argument('-f', '--file', type=str, help='')

    # parse all arguments
    args = parser.parse_args()

    print("Create example filesystem")
    #create_fs_folder(folderpath=target_folder)
    #download_ubuntu_fs(filepath=target_file)
    #extract_tar_gz(extractpath=target_folder, filepath=target_file)
    #prepare_fs_with_data(folderpath=target_folder)
    #remove_fs(folderpath=target_folder)


if __name__ == '__main__':
    main()
