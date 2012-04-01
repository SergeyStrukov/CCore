/* test0021.Replace.cpp */ 
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

namespace App {

namespace Private_0021 {

 
} // namespace Private_0021
 
using namespace Private_0021; 
 
/* Testit<21> */ 

template<>
const char *const Testit<21>::Name="Test21 Replace";

template<>
bool Testit<21>::Main() 
 { 
  int x=2;
  
  int y=Replace_gen( [] (int x) -> int { return x*5; } ,x);
  
  Printf(Con,"x = #; y = #;\n",x,y);
 
  return true;
 }
 
} // namespace App
 
