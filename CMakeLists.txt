#######################
# Project Information #
#######################

cmake_minimum_required(VERSION 2.8)
project(LLVM-ECB)

set(PACKAGE_VERSION "3.0.0")

set(PACKAGE_NAME LLVM-ECB)
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "chris.wailes+llvm-ecb@gmail.com")

set(LLVM_ECB_VERSION 0)

set(LLVM_TARGET_VERSION_MAJOR 3)
set(LLVM_TARGET_VERSION_MINOR 0)

######################
# File Configuration #
######################

configure_file(src/llvm-ecb.h.in src/llvm-ecb.h)

######################
# Resource Locations #
######################

include_directories (${CMAKE_BINARY_DIR}/src)
include_directories(~/software/llvm-3.0.src/include/)

##################
# Subdirectories #
##################

add_subdirectory(src)
