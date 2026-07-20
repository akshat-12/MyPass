#include "MyPass.h"

#include "llvm/IR/Module.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Plugins/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

PreservedAnalyses MyPass::run(Module &M, ModuleAnalysisManager &AM) {
    errs() << "Running MyPass on module: " << M.getName() << "\n";
    int loadInstructionsCount = 0;
    int storeInstructionsCount = 0;
    for (auto &F : M) {
        errs() << "Function name: " << F.getName() << "\n";
        for (auto &BB : F) {
            for (auto &I : BB) {
                if (isa<LoadInst>(&I)) {
                    loadInstructionsCount++;
                } else if (isa<StoreInst>(&I)) {
                    storeInstructionsCount++;
                }
            }
        }
    }
    errs() << "Total load instructions: " << loadInstructionsCount << "\n";
    errs() << "Total store instructions: " << storeInstructionsCount << "\n";
    return PreservedAnalyses::all();
}

// Plugin registration
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION,
        "MyPass",
        LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name,
                    ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "MyPass") {
                        MPM.addPass(MyPass());
                        return true;
                    }
                    return false;
                });
        }
    };
}