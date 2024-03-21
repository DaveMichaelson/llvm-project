//===---- CGStmtAttrs.cpp - LLVM CodeGen for statement attributes -*- C++ -*-------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "CGStmtAttrs.h"

using namespace clang::CodeGen;
using namespace llvm;

void StmtAttrsStack::push(Stmt *S) {
  stack.push_back(&S->getAttrs(CGM.getContext()));
}

void StmtAttrsStack::pop() {
  stack.pop_back();
}

void StmtAttrsStack::clear_back() {
  stack.pop_back();
  stack.push_back(nullptr);
}

void StmtAttrsStack::addAttrsAsMD(llvm::Value *Value) {
  for (typename llvm::SmallVector<AttrVec *, 10>::iterator Attrs = stack.begin(),
                                                      AttrsEnd = stack.end();
      Attrs != AttrsEnd; Attrs++) {
    for (typename AttrVec::iterator A = (*Attrs)->begin(), AEnd = (*Attrs)->end();
        A != AEnd; A++) {
      Attr *attr = *A;
      if (!attr)
        continue;
      if (attr->getKind() == attr::AttachMetadata) 
        CGM.addUserMetadataToValue(Value, cast<AttachMetadataAttr>(attr));
    }
  }
}

void StmtAttrsStack::InsertHelper(llvm::Instruction *I) const {
  addAttrsAsMD(I);
}
