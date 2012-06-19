/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/12
 * Description:	Header file for C bindings for various functions involving
 *				LLVM targets.
 */

#ifndef ECB_TARGET_H
#define ECB_TARGET_H

// Standard Includes

#include <llvm-c/Core.h>

// Project Includes

// Macros

// Types

typedef struct LLVMOpaqueTarget* LLVMTargetRef;
typedef struct LLVMOpaqueTriple* LLVMTripleRef;

// Functions

extern "C" {

LLVMTripleRef	LLVMGetHostTriple(void);
char*		LLVMGetHostTripleString(void);

LLVMTripleRef	LLVMTripleCreate(char* string);

void LLVMECBInitializeAllTargets(void);
void LLVMECBInitializeNativeTarget(void);

LLVMTargetRef LLVMGetTargetFromName(char* name);
LLVMTargetRef LLVMGetTargetFromTriple(LLVMTripleRef triple);

}

LLVMTripleRef	LLVMGetHostTriple(void);
char*		LLVMGetHostTripleString(void);

LLVMTripleRef	LLVMTripleCreate(char* string);

void LLVMECBInitializeAllTargets(void);
void LLVMECBInitializeNativeTarget(void);

LLVMTargetRef LLVMGetTargetFromName(char* name);
LLVMTargetRef LLVMGetTargetFromTriple(LLVMTripleRef triple);

namespace llvm {
	
	// Target
	inline Target* unwrap(LLVMTargetRef t) {
		return reinterpret_cast<Target*>(t);
	}
	
	inline LLVMTargetRef wrap(const Target* t) {
		return reinterpret_cast<LLVMTargetRef>(const_cast<Target*>(t));
	}
	
	// Triple
	inline Triple* unwrap(LLVMTripleRef t) {
		return reinterpret_cast<Triple*>(t);
	}
	
	inline LLVMTripleRef wrap(const Triple* t) {
		return reinterpret_cast<LLVMTripleRef>(const_cast<Triple*>(t));
	}
}

#endif
