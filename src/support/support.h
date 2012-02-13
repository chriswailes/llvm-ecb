/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/02/13
 * Description:	Header file for C bindings for the LLVM::Support namespace.
 */

#ifndef SUPPORT_H
#define SUPPORT_H

// Standard Includes

// Project Includes

// Macros

// Types

// Functions

extern "C" {
	int LLVMLoadLibraryPermanently(const char* filename);
}

#endif
