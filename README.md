# ChatMC
A Morse Code chat bot for hams to learn Morse Code

## Setup
```sh
mkdir ~/local
cd ~/local
sudo apt update && sudo apt upgrade -y
sudo apt install -y git build-essential swig3.0 python-dev nodejs-dev cmake libjson-c-dev
git clone https://github.com/eclipse/mraa.git
cd mraa
mkdir build && cd build
cmake ..
make
sudo make install
sudo ldconfig /usr/local/lib
```
