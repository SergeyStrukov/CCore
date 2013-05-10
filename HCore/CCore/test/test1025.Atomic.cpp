/* test1025.Atomic.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: HCore 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

namespace App {

namespace Private_1025 {

/* test1() */

void test1()
 {
  Atomic atomic;
  
  {
   RunTasks run_tasks;
   
   run_tasks(ulen(10), [&] () {  
                               for(ulen cnt=1000000; cnt ;cnt--) atomic++;
                              } );
  }
  
  Printf(Con,"atomic = #;\n",atomic);
 }

/* test2() */

void test2()
 {
  Atomic atomic;
  
  {
   RunTasks run_tasks;
   
   run_tasks( [&] () {
                      ulen count=0;
     
                      while( count<1000000 )
                        if( atomic.trySet(0,1)==0 ) count++;
                     } );
   
   run_tasks( [&] () {
                      ulen count=0;
                      
                      while( count<1000000 )
                        if( atomic.trySet(1,0)==1 ) count++;
                     } );
  }
 }

} // namespace Private_1025
 
using namespace Private_1025; 
 
/* Testit<1025> */ 

template<>
const char *const Testit<1025>::Name="Test1025 Atomic";

template<>
bool Testit<1025>::Main() 
 {
  test1();
  test2();
  
  return true;
 }
 
} // namespace App
 
