/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/12
 * Description:	Extended C bindings for dealing with assembly using LLVM.
 */

// Standard Includes

#include <llvm/Support/TargetSelect.h>

#include <llvm-c/Core.h>

// Project Includes

// Macros

// Global Variables

// Functions

using namespace llvm;

extern "C" {
	void LLVMInitializeAllAsmParsers(void) {
		InitializeAllAsmParsers();
	}
	
	void LLVMInitializeAllAsmPrinters(void) {
		InitializeAllAsmPrinters();
	}
	
	void LLVMInitializeNativeTargetAsmParser(void) {
		InitializeNativeTargetAsmParser();
	}
	
	void LLVMInitializeNativeTargetAsmPrinter(void) {
		InitializeNativeTargetAsmPrinter();
	}
}
