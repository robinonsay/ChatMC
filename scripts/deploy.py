import os
import shutil
import tarfile
from pathlib import Path
from utils.cmd import assert_cmd
from setupOS import PROJECT_DIR
from argparse import ArgumentParser
from datetime import datetime

BBB_IPADDR = '192.168.9.3'
BUILDS_VOLUME_PATH = Path('/ChatMC_Builds/')
SSH_ID_PATH = BUILDS_VOLUME_PATH / '.ssh' / 'id_ed25519'
CHATMC_EXE = 'chatmc'

if __name__ == '__main__':
    shutil.copytree(PROJECT_DIR / 'build', BUILDS_VOLUME_PATH / 'build', dirs_exist_ok=True)
    assert_cmd(['scp', '-o', 'StrictHostKeyChecking=accept-new', '-i', str(SSH_ID_PATH), BUILDS_VOLUME_PATH / 'build' / CHATMC_EXE, f"debian@{BBB_IPADDR}:/mnt/sd_card/"])