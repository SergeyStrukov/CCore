/* test.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: Regen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Printf.h>

using namespace CCore;

#if 1

#include "Test.gen.h"

namespace Private_test {

struct RW
 {
  template <class UInt> 
  void set(uint32,UInt) {}

  template <class UInt> 
  UInt get(uint32) { return 0; }
 };

void test()
 {
  Test<RW> t;

  auto isr=t.get_ISR();

  t.set_ICR(isr);
 }

} // namespace Private_test

#endif
