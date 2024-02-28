import subprocess
import os
from typing import Tuple

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def assert_cmd(cmd: list, prompt=False) -> Tuple[str, str]:
    if prompt:
        resp = input(f"Executing cmd: \"{bcolors.OKGREEN}{' '.join(cmd)}{bcolors.ENDC}\". Continue?[yes|no|skip or [Enter]]: ").lower()
        if resp == 'skip' or resp == '' or resp is None:
            return('Skipped', '')
        elif resp == 'yes':
            pass
        else:
            exit(0)
    ret = subprocess.run(cmd)
    assert(ret.returncode == 0)
    return (ret.stdout, ret.stderr)
