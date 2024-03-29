# Use an image that includes cross-compilation tools for ARM32, like Ubuntu
FROM ubuntu:22.04
VOLUME [ "/ChatMC_Builds/"]

# Install required packages
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y \
    cmake \
    make \
    git \
    wget \
    xz-utils\
    python3
WORKDIR /opt
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-a/8.2-2018.08/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf.tar.xz
RUN tar -xf gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf.tar.xz
RUN apt-get install -y build-essential swig3.0 python-dev-is-python3 python2-dev libnode-dev cmake libjson-c-dev
ENV CROSS_COMPILE=/opt/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
ENV CC=${CROSS_COMPILE}gcc
ENV CXX=${CROSS_COMPILE}g++
# Optional: Create a CMake toolchain file for ARM32 inside the project directory
# This step depends on the specifics of your project and cross-compilation requirements
# Here is a basic example of what the toolchain file (`arm32-toolchain.cmake`) might look like:
RUN echo "set(CMAKE_SYSTEM_NAME Linux)\n\
set(CMAKE_SYSTEM_PROCESSOR arm)\n\
set(CMAKE_C_COMPILER /opt/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)\n\
set(CMAKE_CXX_COMPILER /opt/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)\n\
SET(CMAKE_FIND_ROOT_PATH		/opt/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf/arm-linux-gnueabihf)" > /opt/arm32-toolchain.cmake
# RUN git clone https://github.com/eclipse/mraa.git
# ENV MRAA_DIR=/opt/mraa
# RUN mkdir /opt/mraa/build
# WORKDIR /opt/mraa/build
# RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=/opt/arm32-toolchain.cmake
# RUN make
# RUN make install
# RUN ldconfig /usr/bin/local
WORKDIR /
# Set the environment variable for the ARM32 cross-compiler

# Create a directory for your project
WORKDIR /project

# Add your project files to the Docker image
COPY . /project

# Configure CMake to use the toolchain file for cross-compilation
RUN cmake -Bbuild -H. -DCMAKE_TOOLCHAIN_FILE=/opt/arm32-toolchain.cmake

# Build your project
RUN cmake --build build
CMD python3 scripts/deploy.py
