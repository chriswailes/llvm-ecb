/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/11
 * Description:	Header file for C bindings for the LLVM::Value class.
 */

#ifndef VALUE_H
#define VALUE_H

// Standard Includes

#include <llvm-c/Core.h>

// Project Includes

// Macros

// Types

// Functions

void LLVMPrintValue(LLVMValueRef val, int fd);

#endif
