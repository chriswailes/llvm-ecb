/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/11
 * Description:	Extended C bindings for the LLVM::Module class.
 */

// Standard Includes

#include <llvm/LLVMContext.h>
#include <llvm/Support/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>

#include <llvm-c/Core.h>

// Project Includes

// Macros

// Global Variables

// Functions

using namespace llvm;

extern "C" {
	LLVMModuleRef LLVMLoadModuleFromIRFile(char* file_name, LLVMContextRef context) {
		SMDiagnostic error;
		
		return wrap(ParseIRFile(file_name, error, *unwrap(context)));
	}
	
	void LLVMPrintModule(LLVMModuleRef mod, int fd) {
		raw_fd_ostream stream(fd, false, false);
		
		unwrap(mod)->print(stream, NULL);
	}
}
