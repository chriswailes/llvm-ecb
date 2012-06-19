/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/12
 * Description:	Header file for C bindings for dealing with assembly using
 *				LLVM.
 */

#ifndef ECB_ASM_H
#define ECB_ASM_H

// Standard Includes

#include <llvm-c/Core.h>

// Project Includes

// Macros

// Types

// Functions

void LLVMInitializeAllAsmParsers(void);
void LLVMInitializeAllAsmPrinters(void);
void LLVMInitializeNativeTargetAsmParser(void);
void LLVMInitializeNativeTargetAsmPrinter(void);

#endif
