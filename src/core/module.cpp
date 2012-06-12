/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/11
 * Description:	Extended C bindings for the LLVM::Module class.
 */

// Standard Includes

#include <llvm-c/Core.h>
#include <llvm/Support/raw_ostream.h>

// Project Includes

// Macros

// Global Variables

// Functions

using namespace llvm;

extern "C" {
	void LLVMPrintModule(LLVMModuleRef mod, int fd) {
		raw_fd_ostream stream(fd, false, false);
		
		unwrap(mod)->print(stream, NULL);
	}
}
