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

#####################
# Project Variables #
#####################

# Compute default library install directory.
set (_DEFAULT_LIBRARY_INSTALL_DIR lib)

if (EXISTS "${CMAKE_INSTALL_PREFIX}/lib/" AND CMAKE_SIZEOF_VOID_P EQUAL 4)
	set (_DEFAULT_LIBRARY_INSTALL_DIR lib)
elseif (EXISTS "${CMAKE_INSTALL_PREFIX}/lib64/" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	set (_DEFAULT_LIBRARY_INSTALL_DIR lib64)
endif ()

# Set the library install directory.
set(LIBRARY_INSTALL_DIR "${_DEFAULT_LIBRARY_INSTALL_DIR}" CACHE PATH "Installation directory for libraries")
if(NOT IS_ABSOLUTE "${LIBRARY_INSTALL_DIR}")
  set(LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${LIBRARY_INSTALL_DIR}")
endif()

######################
# File Configuration #
######################

configure_file(src/llvm-ecb.h.in src/llvm-ecb.h)

######################
# Resource Locations #
######################

if (NOT $ENV{CPLUS_INCLUDE_PATH}  STREQUAL "")
   string (REPLACE ":" " " INCLUDES $ENV{CPLUS_INCLUDE_PATH})
   string (REPLACE "//" "/" INCLUDES ${INCLUDES})
   string(REGEX MATCHALL "[^ ]+" LIST_INCLUDES ${INCLUDES})
endif () 

include_directories(LIST_INCLUDES) 

include_directories(${CMAKE_BINARY_DIR}/src)

##################
# Subdirectories #
##################

add_subdirectory(src)
