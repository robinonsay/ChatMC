cmake_minimum_required(VERSION 3.20)
project(ChatMC CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
option(IS_TARGET "Compile ChatMC Library locally" ON)
aux_source_directory(${ChatMC_SOURCE_DIR}/src/chatmc/ CHATMC_LIB_SRCS)
if(IS_TARGET)
    add_subdirectory(external/mraa)
endif(IS_TARGET)
add_library(chatmcLib STATIC ${CHATMC_LIB_SRCS})
target_link_libraries(chatmcLib mraa)
target_include_directories(chatmcLib PRIVATE external/mraa/api ${ChatMC_SOURCE_DIR}/inc)
