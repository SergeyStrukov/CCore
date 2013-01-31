/* test0078.Optional.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Optional.h>

namespace App {

namespace Private_0078 {

/* class Test */

class Test : NoCopy
 {
   Optional optional;
   
  public:
  
   Test() : optional(100) {}
   
   ~Test() {}
   
   // members
   
   int * try_member0() { return optional.try_take<0,int>(); }
   
   int * member0() { return optional.take<0,int>(); }
   
   int * try_member20() { return optional.try_take<20,int>(); }
   
   int * member20() { return optional.take<20,int>(); }
   
   int * try_member100() { return optional.try_take<100,int>(); }
   
   int * member100() { return optional.take<100,int>(); }
 };

} // namespace Private_0078
 
using namespace Private_0078; 
 
/* Testit<78> */ 

template<>
const char *const Testit<78>::Name="Test78 Optional";

template<>
bool Testit<78>::Main() 
 {
  Test test;
  
  Printf(Con,"member0 = #;\n",*test.member0());
  Printf(Con,"member20 = #;\n",*test.member20());
  Printf(Con,"member100 = #;\n",*test.member100());
  
  *test.try_member0()=100;
  *test.try_member20()=200;
  *test.try_member100()=300;
  
  Printf(Con,"member0 = #;\n",*test.member0());
  Printf(Con,"member20 = #;\n",*test.member20());
  Printf(Con,"member100 = #;\n",*test.member100());
  
  return true;
 }
 
} // namespace App
 
