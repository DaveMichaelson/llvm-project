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

#ifndef LLVM_CLANG_LIB_CODEGEN_CGLOOPINFO_H
#define LLVM_CLANG_LIB_CODEGEN_CGLOOPINFO_H

#include "CodeGenModule.h"
#include "clang/AST/AttrIterator.h"
#include "clang/AST/Stmt.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/Value.h"


namespace clang {
class Attr;
class ASTContext;
class CodeGenOptions;
namespace CodeGen {

class StmtAttrsStack {
  StmtAttrsStack(const StmtAttrsStack &) = delete;
  void operator=(const StmtAttrsStack &) = delete;
public:
  StmtAttrsStack(CodeGenModule &CGM) : CGM(CGM) {}
  void push(Stmt *S);
  void pop();
  void clear_back();
  void addAttrsAsMD(llvm::Value *Value);
  void InsertHelper(llvm::Instruction *I) const;
private:
  CodeGenModule &CGM;
  llvm::SmallVector<AttrVec *, 10> stack;
};

} // end namespace CodeGen
} // end namespace clang

#endif