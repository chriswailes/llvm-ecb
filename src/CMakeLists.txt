#######################
# Project Information #
#######################


######################
# Resource Locations #
######################

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

##################
# Subdirectories #
##################

add_subdirectory(support)

#############
# Libraries #
#############

add_library(LLVM-ECB SHARED
	llvm-ecb.c
	
	support/support.cpp
	)
