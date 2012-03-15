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

#############
# Libraries #
#############

add_library(LLVM-ECB-${LLVM_TARGET_VERSION} SHARED
	llvm-ecb.c
	
	support/support.cpp
	)

########################
# Installation Targets #
########################

install(TARGETS LLVM-ECB-${LLVM_TARGET_VERSION}
	LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR})

install(FILES "${PROJECT_BINARY_DIR}/src/llvm-ecb.h" DESTINATION include)
install(FILES "${PROJECT_SOURCE_DIR}/src/support/support.h" DESTINATION include/llvm-ecb)
