/* test0094.PerTask.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

#include <CCore/inc/PerTask.h>

namespace App {

namespace Private_0094 {

/* struct Acc */

struct Acc
 {
  class ObjectType : public MemBase_nocopy
   {
     unsigned acc;
    
    public:
    
     explicit ObjectType(unsigned start) : acc(start) {}
     
     ~ObjectType()
      {
       Printf(Con,"acc = #;\n",acc);
      }
     
     void inc() { acc++; }
     
     void destroy() { delete this; }
   };

  class BuilderType
   {
     unsigned start;
     
    public:
    
     explicit BuilderType(unsigned start_) : start(start_) {}
    
     ObjectType * create() { return new ObjectType(start); }
   };
 };

/* test() */

void test()
 {
  for(ulen cnt=10000000; cnt ;cnt--) GetTaskObject<Acc>()->inc();
 }

} // namespace Private_0094
 
using namespace Private_0094; 
 
/* Testit<94> */ 

template<>
const char *const Testit<94>::Name="Test94 PerTask";

template<>
bool Testit<94>::Main() 
 {
  DestroyPerTask dpt;
  
  {
   TaskObjectBuild<Acc> task_object(TaskObjectHard,100);
   
   RunTasks run;
   
   run(ulen(10),test);
  }
  
  {
   TaskObjectBuild<Acc> task_object(TaskObjectSoft,200);
   
   RunTasks run;
   
   run(ulen(10),test);
   
   test();
  }
  
  return true;
 }
 
} // namespace App
 
