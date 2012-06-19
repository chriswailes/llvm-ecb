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

#include <sys/types.h>

#include <llvm-c/Core.h>

// Project Includes

// Macros

// Types

typedef enum {
	DEFAULT_CMODEL,
	KERNEL,
	SMALL,
	MEDIUM,
	LARGE
} code_model;

typedef enum {
	DEFAULT_RMODEL,
	STATIC,
	PIC,
	DYNAMIC_NO_PIC
} reloc_model;

typedef enum {
	ASM,
	OBJ
} compile_type;

typedef struct LLVMOpaqueTarget*		LLVMTargetRef;
typedef struct LLVMOpaqueTargetMachine*	LLVMTargetMachineRef;
typedef struct LLVMOpaqueTriple*		LLVMTripleRef;

// Functions

#ifdef __cplusplus
extern "C" {
#endif
	
	// Utility
	
	char*				LLVMBuildFeaturesString(char** attrs, int num_attrs);
	
	void					LLVMCompileModuleToFile(LLVMModuleRef mod, LLVMTargetMachineRef machine, LLVMPassManagerRef pm, char* file_name, compile_type ctype, uint opt_level, uint no_verify);
	
	void					LLVMECBInitializeAllTargets(void);
	void					LLVMECBInitializeNativeTarget(void);
	
	// Target
	
	LLVMTargetRef			LLVMGetTargetFromName(char* name);
	LLVMTargetRef			LLVMGetTargetFromTriple(LLVMTripleRef triple);
	
	// Target Machine
	
	LLVMTargetMachineRef	LLVMCreateTargetMachine(LLVMTargetRef target, char* triple,  char* mcpu, char* features, reloc_model rmodel, code_model cmodel);
	void					LLVMSetTargetMachineASMVerbosity(LLVMTargetMachineRef machine, int boolean);
	
	// Triple
	
	LLVMTripleRef			LLVMGetHostTriple(void);
	char*				LLVMGetHostTripleString(void);
	char*				LLVMGetTripleString(LLVMTripleRef triple);

	LLVMTripleRef			LLVMTripleCreate(char* string);

#ifdef __cplusplus
}
#endif

namespace llvm {
	
	// Target
	inline Target* unwrap(LLVMTargetRef t) {
		return reinterpret_cast<Target*>(t);
	}
	
	inline LLVMTargetRef wrap(const Target* t) {
		return reinterpret_cast<LLVMTargetRef>(const_cast<Target*>(t));
	}
	
	// TargetMachine
	inline TargetMachine* unwrap(LLVMTargetMachineRef t) {
		return reinterpret_cast<TargetMachine*>(t);
	}
	
	inline LLVMTargetMachineRef wrap(const TargetMachine* t) {
		return reinterpret_cast<LLVMTargetMachineRef>(const_cast<TargetMachine*>(t));
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
