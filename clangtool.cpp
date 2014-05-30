#include "llvm/Pass.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/PassRegistry.h"
#include "llvm/PassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
// For output
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Example pass: just dumps the insns for every block.
namespace {
  struct ClangTool : public BasicBlockPass {
    static char ID;
    ClangTool() : BasicBlockPass(ID) {}
    virtual bool runOnBasicBlock(BasicBlock &BB) {
      BasicBlock::iterator i;
      errs() << "Basic Block\n";
      for( i=BB.begin(); i!=BB.end(); i++ ) {
        errs() << "  " << i->getOpcodeName() << "\n";
      }
      return false;
    }
  };
}

// Pass info
char ClangTool::ID = 0; // LLVM ignores the actual value
static RegisterPass<ClangTool> X("clangtool", "Example pass", false, false);

// Pass loading stuff
// To use, run: clang -Xclang -load -Xclang <your-pass>.so <other-args> ...

// This function is of type PassManagerBuilder::ExtensionFn
static void loadPass(const PassManagerBuilder &Builder, PassManagerBase &PM) {
  PM.add(new ClangTool());
}
// These constructors add our pass to a list of global extensions.
static RegisterStandardPasses clangtoolLoader_Ox(PassManagerBuilder::EP_OptimizerLast, loadPass);
static RegisterStandardPasses clangtoolLoader_O0(PassManagerBuilder::EP_EnabledOnOptLevel0, loadPass);

// Note: The location EP_OptimizerLast places this pass at the end of the list
// of *optimizations*. That means on -O0, it does not get run.
//
// In general, adding your pass twice will cause it to run twice, but in this
// particular case, the two are disjoint (EP_EnabledOnOptLevel0 only runs if
// you're in -O0, and EP_OptimizerLast only runs if you're not). You can check
// include/llvm/Transforms/IPO/PassManagerBuilder.h header and
// lib/Transforms/IPO/PassManagerBuilder.cpp file for the exact behavior.
