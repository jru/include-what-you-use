//===--- typedef_in_template.cc - test input file for iwyu ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "tests/cxx/typedef_in_template-d1.h"

template<class T>
class Container {
 public:
  // Should not be an iwyu violation for T
  typedef T value_type;

  // C++11 alias declaration, should not be an iwyu violation for T
  using alias_type = T;

  // IWYU: Pair is...*typedef_in_template-i2.h
  typedef Pair<T,T> pair_type;
};


void Declarations() {
  // TODO: Close bug #431

  // None of these need the full type for Class in the template parameter,
  // but they still require the full type for the constructed value.

  // IWYU: Class needs a declaration
  Container<Class>::value_type
  // IWYU: Class is defined in .+template-i1.h
  vt;
  // IWYU: Class needs a declaration
  Container<Class>::pair_type
  // IWYU: Pair is defined in .+template-i2.h
  pt;
  // IWYU: Class needs a declaration
  Container<Class>::alias_type
  // IWYU: Class is defined in .+template-i1.h
  at;

  // None of these need the full type for Class in the template parameter,
  // nor a declaration for the values because they are just pointers.

  // IWYU: Class needs a declaration
  Container<Class>::value_type* 
  pvt;
  // IWYU: Class needs a declaration
  Container<Class>::pair_type* 
  ppt;
  // IWYU: Class needs a declaration
  Container<Class>::alias_type*
  pat;
}


/**** IWYU_SUMMARY

tests/cxx/typedef_in_template.cc should add these lines:
#include "tests/cxx/typedef_in_template-i1.h"
#include "tests/cxx/typedef_in_template-i2.h"

tests/cxx/typedef_in_template.cc should remove these lines:
- #include "tests/cxx/typedef_in_template-d1.h"  // lines XX-XX

The full include-list for tests/cxx/typedef_in_template.cc:
#include "tests/cxx/typedef_in_template-i1.h"  // for Class
#include "tests/cxx/typedef_in_template-i2.h"  // for Pair

***** IWYU_SUMMARY */
