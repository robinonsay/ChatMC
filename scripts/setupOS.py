import os
from pathlib import Path
from utils.cmd import assert_cmd

deps = ['gcc', 'g++', 'make', 'cmake', 'lcov', 'socat', 'wget', 'xz-utils', 'ssh']
PROJECT_DIR = Path(__file__).parent.parent
sudo = ['sudo'] if os.getuid() != 0 else []

if __name__ == '__main__':
    os.chdir(PROJECT_DIR)
    assert_cmd(sudo + "apt-get update".split())
    assert_cmd(sudo + "apt-get upgrade -y".split())
    assert_cmd(sudo + "apt-get install -y".split() + deps)
