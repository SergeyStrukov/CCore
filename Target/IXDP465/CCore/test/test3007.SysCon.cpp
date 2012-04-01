/* test3007.SysCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

#include <CCore/inc/sys/SysCon.h>

namespace App {

namespace Private_3007 {

/* class TestPrint */

class TestPrint : NoCopy
 {
   ulen number;
   ulen count;
   
  public: 
  
   TestPrint(ulen number_,ulen count_) : number(number_),count(count_) {}
   
   template <class P>
   void print(P &out) const
    {
     for(ulen i=0; i<count ;i++)
       {
        Printf(out,"--- #2;:#6; ----------------------------------------------\n",number,i);
       } 
    }
 };
 
/* struct Test */

struct Test
 {
  ulen number;
  ulen count;
  
  Test(ulen number_,ulen count_) : number(number_),count(count_) {}
  
  void operator () ()
   {
    TestPrint test(number,count);
    
    Putobj(Con,test);
   }
 };
 
} // namespace Private_3007
 
using namespace Private_3007; 
 
/* Testit<3007> */ 

template<>
const char *const Testit<3007>::Name="Test3007 SysCon";

template<>
bool Testit<3007>::Main() 
 { 
  {
   RunTasks run;
   
   const unsigned number = 1 ;
   const unsigned count = 1000 ;
   
   for(unsigned i=1; i<=number ;i++) run(Test(i,count));
  }
  
  Task::Sleep(3_sec);
  
  Sys::ShowConStat();
 
  return true;
 }
 
} // namespace App
 
