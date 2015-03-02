/* test0102.PrintFile.cpp */ 
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

namespace Private_0102 {

/* TestPrint() */

template <class P>
void TestPrint(P &&out)
 {
  for(int i=0; i<10000 ;i++)
    Printf(out,"--- #4; ---------------------------------------\n",i);
 }

} // namespace Private_0102
 
using namespace Private_0102; 
 
/* Testit<102> */ 

template<>
const char *const Testit<102>::Name="Test102 PrintFile";

template<>
bool Testit<102>::Main() 
 { 
  TestPrint(Con);
  
  TaskEventRecorder recorder(100_MByte);
  
  {
   TickTask tick_task; 
   TaskEventHostType::StartStop event_start_stop(TaskEventHost,&recorder);
   
   PrintFile out("testPrintFile.txt");
   
   TestPrint(out);
  } 
  
  BinaryFile dev("test102.bin");
  
  dev(recorder);
  
  return true;
 }
 
} // namespace App
 
