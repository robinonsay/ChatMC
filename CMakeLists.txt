cmake_minimum_required(VERSION 3.20)
project(ChatMC CXX)

aux_source_directory(${ChatMC_SOURCE_DIR}/src CHATMC_SRCS)

add_executable(chatmc ${CHATMC_SRCS})
