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

add_library(llvm-ecb SHARED llvm-ecb.c)

target_link_libraries(llvm-ecb support/support.a)
