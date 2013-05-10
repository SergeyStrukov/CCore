/* test1024.Exception.cpp */ 
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

namespace Private_1024 {

/* testException() */

void testException()
 {
  SilentReportException report;
  
  ulen count=0;
  
  for(ulen cnt=100000; cnt ;cnt--)
    try
      {
       Printf(Exception,"some exception");
      }
    catch(CatchType)
      {
       count++;
      }
  
  Printf(Con,"count = #;\n",count);
 }

} // namespace Private_1024
 
using namespace Private_1024; 
 
/* Testit<1024> */ 

template<>
const char *const Testit<1024>::Name="Test1024 Exception";

template<>
bool Testit<1024>::Main() 
 {
  RunTasks run_tasks;
  
  run_tasks(ulen(10),testException);
  
  return true;
 }
 
} // namespace App
 
