//===--- array.cc - test input file for iwyu ------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Tests that we handle correctly identify a[i] as a full use of a.

#include "tests/direct.h"

class A {
  // IWYU: IndirectClass needs a declaration
  IndirectClass *getIndirectClass(int i) {
    // IWYU: IndirectClass is...*indirect.h
    (void) sizeof(_b[i]);     // requires full type
    // IWYU: IndirectClass needs a declaration
    // IWYU: IndirectClass is...*indirect.h
    (void) sizeof(&(_b[i]));  // requires full type
    // IWYU: IndirectClass is...*indirect.h
    return &(_b[i]);
  }
  // IWYU: IndirectClass needs a declaration
  IndirectClass *_b;
};


/**** IWYU_SUMMARY

tests/array.cc should add these lines:
#include "tests/indirect.h"

tests/array.cc should remove these lines:
- #include "tests/direct.h"  // lines XX-XX

The full include-list for tests/array.cc:
#include "tests/indirect.h"  // for IndirectClass

***** IWYU_SUMMARY */