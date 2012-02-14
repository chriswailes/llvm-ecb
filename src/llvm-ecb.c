/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/02/13
 * Description:	Main header file for LLVM-ECB.
 */

// Standard Includes
#include <stdio.h>
#include <stdlib.h>

// Project Includes
#include "llvm-ecb.h"

// Macros

#define VERSION_BUFFER_SIZE 16

// Global Variables

// Functions

char* LLVMECBVersion(void) {
	char* buffer;
	
	buffer = (char*)malloc(VERSION_BUFFER_SIZE);
	
	snprintf(buffer, VERSION_BUFFER_SIZE, "%s-%d.%d", LLVM_TARGET_VERSION, LLVM_ECB_VERSION_MAJOR, LLVM_ECB_VERSION_MINOR);
	
	return buffer;
}

char* LLVMTargetVersion(void) {
	char* buffer;
	
	buffer = (char*)malloc(VERSION_BUFFER_SIZE);
	
	snprintf(buffer, VERSION_BUFFER_SIZE, "%s", LLVM_TARGET_VERSION);
	
	return buffer;
}
