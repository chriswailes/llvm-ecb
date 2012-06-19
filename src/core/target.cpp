/*
 * Author:		Chris Wailes <chris.wailes@gmail.com>
 * Project:		LLVM-ECB
 * Date:			2012/06/12
 * Description:	Extended C bindings for various functions involving LLVM
 *				targets.
 */

// Standard Includes

#include <llvm/PassManager.h>
#include <llvm/ADT/Triple.h>
#include <llvm/MC/SubtargetFeature.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Target/TargetMachine.h>

#include <llvm-c/Core.h>

// Project Includes

#include "llvm-ecb.h"
#include "core/target.h"

// Macros

// Global Variables

// Functions

using namespace llvm;

inline char* make_c_str(std::string str) {
	char* cstr;
	
	cstr = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), cstr);
	cstr[str.size()] = '\0';
	
	return cstr;
}

extern "C" {
	
	// Utility
	
	char* LLVMBuildFeatureString(char** attrs, int num_attrs) {
		SubtargetFeatures features;
		
		while (num_attrs--) {
			features.AddFeature(attrs[num_attrs]);
		}
		
		return make_c_str(features.getString());
	}
	
	void LLVMCompileModuleToFile(LLVMModuleRef mod, LLVMTargetMachineRef machine, LLVMPassManagerRef pm, char* file_name, compile_type ctype, uint opt_level, uint no_verify) {
		uint oflags = 0;
		
		CodeGenOpt::Level OLvl;
		TargetMachine::CodeGenFileType cpp_ctype;
		
		PassManager* cpp_pm;
		TargetMachine* cpp_machine = unwrap(machine);
		
		std::string error;
		tool_output_file* ofile;
		formatted_raw_ostream* ostream;
		
		/*
		 * Open the output file.
		 */
		
		if (ctype == OBJ) oflags |= raw_fd_ostream::F_Binary;
		
		// FIXME Handle errors in opening the tool output file.
		ofile	= new tool_output_file(file_name, error, oflags);
		ostream	= new formatted_raw_ostream(ofile->os());
		
		// Select the optimization level.
		switch (opt_level) {
			case 0:
				OLvl = CodeGenOpt::None;
				break;
			
			case 1:
				OLvl = CodeGenOpt::Less;
				break;
			
			case 2:
				OLvl = CodeGenOpt::Default;
				break;
			
			case 3:
			default:
				OLvl = CodeGenOpt::Aggressive;
				break;
		}
		
		// Select the cpp_ctype.
		cpp_ctype = (ctype == ASM) ? TargetMachine::CGFT_AssemblyFile : TargetMachine::CGFT_ObjectFile;
		
		// Create a new pass manager if one isn't provided.
		cpp_pm = (pm == NULL) ? new PassManager() : unwrap<PassManager>(pm);
		
		// Add the target data to the pass manager.
		// FIXME Handle the case where the target machine doesn't have target data?
		cpp_pm->add(new TargetData(*(cpp_machine->getTargetData())));
		
		// Tell the target to add necessary passes for code generation.
		// FIXME Handle error where the target doesn't support generation of a given file type.
		cpp_machine->addPassesToEmitFile(*cpp_pm, *ostream, cpp_ctype, OLvl, no_verify);
		
		// Run the pass manager, generating the output file.
		cpp_pm->run(*unwrap(mod));
		
		// Declare success, whatever that means.
		ofile->keep();
		
		// Clean up the pass manager if we created it.
		if (pm == NULL) delete cpp_pm;
	}
	
	void LLVMECBInitializeAllTargets(void) {
		InitializeAllTargets();
		InitializeAllTargetInfos();
		InitializeAllTargetMCs();
	}
	
	void LLVMECBInitializeNativeTarget(void) {
		InitializeNativeTarget();
	}
	
	// Target
	
	LLVMTargetRef LLVMGetTargetFromName(char* cname) {
		std::string name(cname);
		
		const Target* target = NULL;
		
		for (TargetRegistry::iterator it = TargetRegistry::begin(), ie = TargetRegistry::end(); it != ie; ++it) {
			if (name == it->getName()) {
				target = &*it;
				break;
			}
		}
		
		// FIXME Handle errors where the target couldn't be found from the name.
		
		return wrap(target);
	}
	
	LLVMTargetRef LLVMGetTargetFromTriple(LLVMTripleRef triple) {
		std::string error;
		
		// FIXME Handle errors where the target can't be found from the triple.
		return wrap(TargetRegistry::lookupTarget(unwrap(triple)->getTriple(), error));
	}
	
	// Target Machine
	
	LLVMTargetMachineRef LLVMCreateTargetMachine(LLVMTargetRef target, char* triple,  char* mcpu, char* features, reloc_model rmodel, code_model cmodel) {
		CodeModel::Model	cpp_cmodel;
		Reloc::Model		cpp_rmodel;
		
		switch (rmodel) {
			case STATIC:
				cpp_rmodel = Reloc::Static;
				break;
				
			case PIC:
				cpp_rmodel = Reloc::PIC_;
				break;
				
			case DYNAMIC_NO_PIC:
				cpp_rmodel = Reloc::DynamicNoPIC;
				break;
			
			case DEFAULT_RMODEL:
			default:
				cpp_rmodel = Reloc::Default;
				break;
		}
		
		switch (cmodel) {
			case KERNEL:
				cpp_cmodel = CodeModel::Kernel;
				break;
				
			case SMALL:
				cpp_cmodel = CodeModel::Small;
				break;
				
			case MEDIUM:
				cpp_cmodel = CodeModel::Medium;
				break;
				
			case LARGE:
				cpp_cmodel = CodeModel::Large;
				break;
				
			case DEFAULT_CMODEL:
			default:
				cpp_cmodel = CodeModel::Default;
				break;
		}
		
		// FIXME Handle errors in allocating the target machine.
		return wrap(unwrap(target)->createTargetMachine(triple, mcpu, features, cpp_rmodel, cpp_cmodel));
	}
	
	void LLVMSetTargetMachineASMVerbosity(LLVMTargetMachineRef machine, int boolean) {
		unwrap(machine)->setAsmVerbosityDefault(boolean);
	}
	
	// Triple
	
	LLVMTripleRef LLVMGetHostTriple(void) {
		return wrap(new Triple(sys::getHostTriple()));
	}
	
	char* LLVMGetHostTripleString(void) {
		return make_c_str(sys::getHostTriple());
	}
	
	char* LLVMGetTripleString(LLVMTripleRef triple) {
		return make_c_str(unwrap(triple)->getTriple());
	}

	LLVMTripleRef LLVMTripleCreate(char* string) {
		return wrap(new Triple(string));
	}
}
