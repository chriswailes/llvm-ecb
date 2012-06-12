/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/11
 * Description:	Header file for C bindings for the LLVM::module class.
 */

#ifndef MODULE_H
#define MODULE_H

// Standard Includes

#include <llvm-c/Core.h>

// Project Includes

// Macros

// Types

// Functions

void LLVMPrintModule(LLVMModuleRef mod, int fd);

#endif
