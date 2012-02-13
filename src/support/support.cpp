/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/02/13
 * Description:	Extended C bindings for the LLVM::Support namespace.
 */

// Standard Includes

#include <llvm/Support/DynamicLibrary.h>

// Project Includes

// Macros

// Global Variables

// Functions

extern "C" {
	int LLVMLoadLibraryPermanently(const char* filename) {
		return llvm::sys::DynamicLibrary::LoadLibraryPermanently(filename);
	}
}