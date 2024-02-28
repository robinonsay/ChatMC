from pathlib import Path
from setupOS import sudo, PROJECT_DIR
from deploy import SSH_ID_PATH, BBB_IPADDR
from utils.cmd import assert_cmd
import argparse

deps = ['gcc', 'g++', 'make', 'cmake', 'lcov', 'socat', 'wget', 'xz-utils', 'ssh', 'python3', 'python3-venv']


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--bbb', action='store_true')
    args = parser.parse_args()
    if args.bbb:
        for service in ['cloud9.service', 'bonescript.service', 'bonescript.socket', 'bonescript-autorun.service', 'avahi-daemon.service']:
            assert_cmd(sudo + f"systemctl disable {service}".split(), prompt=True)
        assert_cmd(sudo + "apt-get update".split(), prompt=True)
        assert_cmd(sudo + "apt-get upgrade -y".split(), prompt=True)
        assert_cmd(sudo + "apt-get install -y".split() + deps, prompt=True)
        assert_cmd(sudo + "mv /boot/uEnv.txt /boot/uEnv.txt.backup".split(), prompt=True)
        assert_cmd(sudo + "mv /home/debian/os_setup/uEnv.txt /boot/uEnv.txt".split(), prompt=True)
        assert_cmd(sudo + "mv /home/debian/os_setup/issue.net /etc/issue.net".split(), prompt=True)
        assert_cmd(sudo + ["bash", "-c", "'(echo /dev/mmcblk0p2  /mnt/sd_card  auto  defaults 0  0 >> /etc/fstab)'"], prompt=True)
    else:
        assert_cmd(['ssh-copy-id', '-i', f"{SSH_ID_PATH}.pub", f"debian@{BBB_IPADDR}"], prompt=True)
        assert_cmd(['scp', '-i', f"{SSH_ID_PATH}", '-r', f"{PROJECT_DIR / 'os_setup'}", f"debian@{BBB_IPADDR}:~"], prompt=True)
        assert_cmd(['scp', '-i', f"{SSH_ID_PATH}", '-r', f"{PROJECT_DIR / 'scripts'}", f"debian@{BBB_IPADDR}:~"], prompt=True)
        assert_cmd(['ssh', '-t', '-i', str(SSH_ID_PATH), f"debian@{BBB_IPADDR}", f"bash -c 'passwd'"], prompt=True)
        assert_cmd(['ssh', '-t', '-i', str(SSH_ID_PATH), f"debian@{BBB_IPADDR}", f"bash -c 'python3 ~/scripts/setupOS_BBB.py --bbb'"], prompt=True)
