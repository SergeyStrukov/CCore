/* test4002.gcc.cpp */ 
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

#include <CCore/inc/Timer.h>

namespace App {

namespace Private_4002 {

/* class Test */  

class Test : NoCopy
 {
   uint64 &cnt;
 
  public:
  
   explicit Test(uint64 &cnt_) : cnt(cnt_) {}
   
   ~Test() { cnt++; }
 };

/* test_int() */

void test_int()
 {
  try
    {
     throw 1;
    }
  catch(int)  
    {
    }
 }
 
/* test() */ 

void test()
 {
  uint64 cnt=0;
  uint64 dcnt=0;
  
  for(SecTimer timer; timer.less(10) ;)
    {
     try
       {
        Test t(dcnt);
       
        throw 1;
       }
     catch(int)  
       {
        cnt++;
       }
    }
    
  Printf(Con,"cnt = #; dcnt = #;\n",cnt,dcnt);  
 }
 
} // namespace Private_4002
 
using namespace Private_4002; 
 
/* Testit<4002> */ 

template<>
const char *const Testit<4002>::Name="Test4002 gcc";

template<>
bool Testit<4002>::Main() 
 { 
  uint64 x=1234567890123ull;
  
  Printf(Con,"x = #;\n",x);
  
  RunTasks run;

  for(ulen cnt=10; cnt ;cnt--) run(Function<void (void)>(test));
  
  Ticker ticker(test_int,1_msec,1_msec);
  
  return true;
 }
 
} // namespace App
 
