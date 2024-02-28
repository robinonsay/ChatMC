cmake_minimum_required(VERSION 3.20)
project(ChatMC CXX)


aux_source_directory(${ChatMC_SOURCE_DIR}/src CHATMC_SRCS)
add_subdirectory(external/mraa)
add_executable(chatmc ${CHATMC_SRCS})
target_link_libraries(chatmc mraa)
target_include_directories(chatmc PRIVATE external/mraa/api ${ChatMC_SOURCE_DIR}/inc)
