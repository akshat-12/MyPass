#pragma once

#include "llvm/IR/PassManager.h"

class MyPass : public llvm::PassInfoMixin<MyPass> {
public:
    llvm::PreservedAnalyses run(llvm::Module &M,
                                llvm::ModuleAnalysisManager &AM);
};