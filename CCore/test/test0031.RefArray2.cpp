/* test0031.RefArray2.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testArray.h>

namespace App {

namespace Private_0031 {

 
} // namespace Private_0031
 
using namespace Private_0031; 
 
/* Testit<31> */ 

template<>
const char *const Testit<31>::Name="Test31 RefArray2";

template<>
bool Testit<31>::Main() 
 { 
  const int buf[]={1,2,3,4,5};
  
  RefArray<int> a;
  RefArray<int> b(a);
  
  show(a);
  
  a.extend_default(2);
  
  show(a);
  
  a.extend_fill(5,23);
 
  show(a);
  
  a.extend_copy(5,buf);
 
  show(a);
  
  show(b);
  
  b=a;
  
  a.extend_default(5);
  
  show(a);
  show(b);
  
  b=a;
  
  a.shrink(12);
  
  show(a);
  show(b);
  
  b=a;
  
  a.modify().set(13);
  
  show(a);
  show(b);

  return true;
 }
 
} // namespace App
 
