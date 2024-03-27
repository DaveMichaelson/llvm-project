//===---- CGStmtAttrs.h - LLVM CodeGen for statement attributes -*- C++ -*---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This is the internal state used for llvm translation for statement attributes
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_CODEGEN_CGSTMTATTRS_H
#define LLVM_CLANG_LIB_CODEGEN_CGSTMTATTRS_H

#include "clang/AST/AttrIterator.h"
#include "llvm/ADT/SmallVector.h"

namespace llvm {
class Instruction;
class Value;
class Stmt;
}

namespace clang {
class Stmt;

namespace CodeGen {
class CodeGenModule;

class StmtAttrsStack {
  StmtAttrsStack(const StmtAttrsStack &) = delete;
  void operator=(const StmtAttrsStack &) = delete;
public:
  StmtAttrsStack(CodeGenModule &CGM) : CGM(CGM) {}
  void push(const Stmt *S);
  void pop();
  void clear_back();
  void addAttrsAsMD(llvm::Value *Value) const;
  void InsertHelper(llvm::Instruction *I) const;
private:
  CodeGenModule &CGM;
  llvm::SmallVector<const AttrVec *, 10> stack;
};

} // end namespace CodeGen
} // end namespace clang

#endif
