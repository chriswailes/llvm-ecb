/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/12
 * Description:	Extended C bindings for various functions involving LLVM
 *				targets.
 */

// Standard Includes

#include <llvm/ADT/Triple.h>
#include <llvm/Support/Host.h>
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetMachine.h"

#include <llvm-c/Core.h>

// Project Includes

#include "core/target.h"

// Macros

// Global Variables

// Functions

using namespace llvm;

extern "C" {
	LLVMTripleRef	LLVMGetHostTriple(void) {
		return wrap(new Triple(sys::getHostTriple()));
	}
	
	char* LLVMGetHostTripleString(void) {
		char* ret_string;
		
		std::string host_triple = sys::getHostTriple();
		
		ret_string = new char[host_triple.size() + 1];
		std::copy(host_triple.begin(), host_triple.end(), ret_string);
		ret_string[host_triple.size()] = '\0';
		
		return ret_string;
	}
	
	LLVMTargetRef LLVMGetTargetFromName(char* cname) {
		std::string name(cname);
		
		const Target* target = NULL;
		
		for (TargetRegistry::iterator it = TargetRegistry::begin(), ie = TargetRegistry::end(); it != ie; ++it) {
			if (name == it->getName()) {
				target = &*it;
				break;
			}
		}
		
		return wrap(target);
	}
	
	LLVMTargetRef LLVMGetTargetFromTriple(LLVMTripleRef triple) {
		std::string error;
		
		return wrap(TargetRegistry::lookupTarget(unwrap(triple)->getTriple(), error));
	}

	LLVMTripleRef LLVMTripleCreate(char* string) {
		return wrap(new Triple(string));
	}
	
	void LLVMECBInitializeAllTargets(void) {
		InitializeAllTargets();
		InitializeAllTargetInfos();
		InitializeAllTargetMCs();
	}
	
	void LLVMECBInitializeNativeTarget(void) {
		InitializeNativeTarget();
	}
}
