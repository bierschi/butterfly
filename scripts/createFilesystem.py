#!/usr/bin/python3
import os
import glob
import shutil
import requests
import tarfile
import argparse


def create_fs_folder(folderpath):
    """ creates the filesystem folder fs/

    """
    try:
        os.mkdir(folderpath)
    except FileExistsError as error:
        pass


def download_ubuntu_rootfs(folderpath):
    """ downloads the ubuntu fs tar.gz folder

    """
    ubuntu_rootfs_url = "http://cdimage.ubuntu.com/ubuntu-base/releases/22.04/release/ubuntu-base-22.04-base-amd64.tar.gz"

    resp = requests.get(ubuntu_rootfs_url, stream=True)
    if resp.status_code == 200:
        with open(folderpath + '/ubuntu-base-22.04-base-amd64.tar.gz', 'wb') as f:
            f.write(resp.raw.read())
    else:
        print("Received invalid statuscode {} for downloading file {}".format(resp.status_code, ubuntu_rootfs_url))


def download_ubuntu_image():
    """ downloads the ubuntu iso image file

    """
    ubuntu_image_url = "https://releases.ubuntu.com/22.04/ubuntu-22.04.1-desktop-amd64.iso"

    resp = requests.get(ubuntu_image_url, stream=True)
    if resp.status_code == 200:
        print("Downloading large file...")
        with open("../data/ubuntu-22.04.1-desktop-amd64.iso", 'wb') as f:
            shutil.copyfileobj(resp.raw, f)
    else:
        print("Received invalid statuscode {} for downloading ubuntu image".format(resp.status_code))


def download_exe_file():
    """ downloads the vlc exe file

    """
    vlc_exe_url = "https://get.videolan.org/vlc/3.0.18/win32/vlc-3.0.18-win32.exe"

    resp = requests.get(vlc_exe_url, stream=True)
    if resp.status_code == 200:
        with open("../data/vlc-3.0.18-win32.exe", 'wb') as f:
            f.write(resp.raw.read())
    else:
        print("Received invalid statuscode {} for downloading ubuntu image".format(resp.status_code))


def extract_tar_gz(extractpath):
    """ extracts the tar.gz/tar folder to folderpath

    :param extractpath: folderpath to extract the tar.gz file
    """

    cwd = os.getcwd()
    os.chdir(extractpath)
    file_list = os.listdir(extractpath)
    filepath = file_list[0]

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

    #os.remove(filepath)
    os.chdir(cwd)


def prepare_big_data_folder(folderpath):
    """ prepares the folderpath for big data content

    """

    # create butterfly home directory
    home_dir = folderpath + '/home/butterfly'
    data_dir = home_dir + '/data'
    big_dir = data_dir + '/big'
    big_dir_sub = big_dir + '/subfolder'

    create_fs_folder(home_dir)
    create_fs_folder(data_dir)
    create_fs_folder(big_dir)
    create_fs_folder(big_dir_sub)

    for file in glob.glob('../data/file*'):
        shutil.copy(file, big_dir)
        shutil.copy(file, big_dir_sub)

    for file in glob.glob('../data/*.iso'):
        shutil.copy(file, big_dir)

    for file in glob.glob('../data/*.exe'):
        shutil.copy(file, big_dir)


def prepare_small_data_folder(folderpath):
    """ prepares the folderpath for small data content

    """
    home_dir = folderpath + '/home/butterfly'
    data_dir = home_dir + '/data'
    small_dir = data_dir + '/small'
    small_dir_sub = small_dir + '/subfolder'

    create_fs_folder(home_dir)
    create_fs_folder(data_dir)
    create_fs_folder(small_dir)
    create_fs_folder(small_dir_sub)

    for file in glob.glob('../data/file*'):
        shutil.copy(file, small_dir)
        shutil.copy(file, small_dir_sub)

    for file in glob.glob('../data/*.zip'):
        shutil.copy(file, small_dir)

    for file in glob.glob('../data/*.exe'):
        shutil.copy(file, small_dir)


def create_fs_from_scratch(fs_folder):
    """ creates the filesystem in fs_folder from scratch

    """
    print("Creating fs/ folder")
    create_fs_folder(folderpath=fs_folder)
    print("Downloading ubuntu rootfs")
    download_ubuntu_rootfs(folderpath=fs_folder)
    print("Extracting ubuntu rootfs from tar.gz file")
    extract_tar_gz(extractpath=fs_folder)


def remove_folder(folderpath):
    """ removes the folder in folderpath

    :param folderpath: path to the folder
    """
    try:
        shutil.rmtree(folderpath)
    except FileNotFoundError as error:
        print(error)


def main():

    usage1 = "USAGE: \n\t./createFilesystem.py --big"

    usage2 = "./createFileSystem.py --small"
    usage3 = "./createFileSystem.py --recreate --small"
    usage4 = "./createFileSystem.py --delete"
    description = "Creates the ubuntu filesystem and prepares the data content in home directory. \n\n {}\n        {}\n        {}\n        {}".format(usage1, usage2, usage3, usage4)

    # parse arguments
    parser = argparse.ArgumentParser(description=description, formatter_class=argparse.RawDescriptionHelpFormatter)

    # arguments
    parser.add_argument('-b', '--big', action='store_true', help='Prepares big data folder')
    parser.add_argument('-s', '--small', action='store_true', help='Prepares small data folder')
    parser.add_argument('-r', '--recreate', action='store_true', help='Recreates the data folder')
    parser.add_argument('-d', '--delete', action='store_true', help='Deletes the fs/ folder')

    # parse all arguments
    args = parser.parse_args()

    fs_folder = os.getcwd() + '/../fs'
    ubuntu_image = os.getcwd() + '/../data/ubuntu-22.04.1-desktop-amd64.iso'
    vlc_file = os.getcwd() + '/../data/vlc-3.0.18-win32.exe'

    if args.small and not args.recreate:
        if not os.path.isdir(fs_folder):
            create_fs_from_scratch(fs_folder)

        if not os.path.isfile(vlc_file):
            print("Download vlc exe file")
            download_exe_file()

        print("Prepare fs/ with small data content")
        prepare_small_data_folder(folderpath=fs_folder)

    elif args.big and not args.recreate:
        if not os.path.isdir(fs_folder):
            create_fs_from_scratch(fs_folder)

        if not os.path.isfile(ubuntu_image):
            print("Download ubuntu image")
            download_ubuntu_image()
        if not os.path.isfile(vlc_file):
            print("Download vlc exe file")
            download_exe_file()

        print("Prepare fs/ with big data content")
        prepare_big_data_folder(folderpath=fs_folder)

    elif args.recreate:
        print("Removing /home/butterfly/data folder")
        remove_folder(folderpath=fs_folder + '/home/butterfly/data')
        if args.small:
            print("Prepare fs/ with small data content")
            prepare_small_data_folder(fs_folder)
        elif args.big:
            print("Prepare fs/ with big data content")
            prepare_big_data_folder(fs_folder)
        else:
            print("Prepare fs/ with small data content")
            prepare_small_data_folder(fs_folder)

    elif args.delete:
        print("Removing fs/ folder")
        remove_folder(folderpath=fs_folder)

    else:
        print("Invalid usage of the argument parser!")


if __name__ == '__main__':
    main()
