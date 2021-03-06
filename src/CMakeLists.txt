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
	
	core/asm.cpp
	core/module.cpp
	core/target.cpp
	core/value.cpp
	)

set_target_properties(LLVM-ECB-${LLVM_TARGET_VERSION} PROPERTIES
	LINK_FLAGS "-lLLVM-${LLVM_TARGET_VERSION} -lpthread -lrt -ldl -lcrypt -lm"
	COMPILE_FLAGS "-O3 -fPIC -Wall -D __STDC_LIMIT_MACROS=1 -D __STDC_CONSTANT_MACROS=1"
	COMPILE_FLAGS_DEBUG "-g"
	)

########################
# Installation Targets #
########################

install(TARGETS LLVM-ECB-${LLVM_TARGET_VERSION}
	LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR})

install(FILES "${PROJECT_BINARY_DIR}/src/llvm-ecb.h" DESTINATION include)

install(FILES "${PROJECT_SOURCE_DIR}/src/support/support.h" DESTINATION include/llvm-ecb)

install(FILES "${PROJECT_SOURCE_DIR}/src/core/asm.h" DESTINATION include/llvm-ecb)
install(FILES "${PROJECT_SOURCE_DIR}/src/core/module.h" DESTINATION include/llvm-ecb)
install(FILES "${PROJECT_SOURCE_DIR}/src/core/target.h" DESTINATION include/llvm-ecb)
install(FILES "${PROJECT_SOURCE_DIR}/src/core/value.h" DESTINATION include/llvm-ecb)
