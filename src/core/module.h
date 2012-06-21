/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/11
 * Description:	Header file for C bindings for the LLVM::module class.
 */

#ifndef ECB_MODULE_H
#define ECB_MODULE_H

// Standard Includes

#include <llvm-c/Core.h>

// Project Includes

// Macros

// Types

// Functions

LLVMModuleRef LLVMLoadModuleFromIRFile(char* file_name, LLVMContextRef context);

void LLVMPrintModule(LLVMModuleRef mod, int fd);

#endif
