//===--- CGExprEmitter.h - Emit LLVM Code for Expr ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This contains code to emit Expr nodes as LLVM code.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_CODEGEN_CGEXPREMITTER_H
#define LLVM_CLANG_LIB_CODEGEN_CGEXPREMITTER_H

#include "CodeGenFunction.h"
#include "clang/AST/Expr.h"

namespace clang {

namespace CodeGen {

class ExprEmitter {
protected:
  CodeGenFunction &CGF;
private:
  bool HasAttrs;
public:

  ExprEmitter(CodeGenFunction &cgf, const Expr *E=nullptr) : CGF(cgf),
      HasAttrs(E && E->hasAttrs(CGF.getContext())) {
    if (HasAttrs) {
      CGF.AttrStackPush(E);
    }
  }

  virtual ~ExprEmitter() {
    if (HasAttrs) {
      CGF.AttrStackPop();
    }
  }

};

} // end namespace CodeGen
} // end namespace clang

#endif
