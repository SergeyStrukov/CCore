/* test3010.AsyncFile.cpp */ 
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

#include <CCore/testip/testip.h>

#include <CCore/inc/String.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/AsyncFileToMem.h>

namespace App {

namespace Private_3010 {

/* class Test1 */  

class Test1
 {
   int number;
   
  public:
  
   explicit Test1(int number_) : number(number_) {}
   
   void operator () ()
    {
     String name=Stringf("host:test3010.#;.txt",number);
       
     PrintAsyncFile out(Range(name),Open_ToWrite|Open_AutoDelete);

     for(ulen i=0; i<1000000 ;i++)
       {
        Printf(out,"--- #5; ---------------------------------------------------\n",i);
       }
    }
 };
 
/* test1() */  

void test1()
 {
  RunTasks run;
  
  for(int number=1; number<=5 ;number++) run(Test1(number));
 }
    
/* class Test2 */  

class Test2
 {
   int number;
   
  public:
  
   explicit Test2(int number_) : number(number_) {}
   
   void operator () ()
    {
     String namea=Stringf("host:test3010.#;.a.txt",number);
     String nameb=Stringf("host:test3010.#;.b.txt",number);

     {
      PrintAsyncFile out(Range(namea));
  
      for(ulen i=0; i<10000 ;i++)
        {
         Printf(out,"--- #5; ---------------------------------------------------\n",i);
        }
     }
       
     {
      AsyncFileToMem map(Range(namea));
      PrintAsyncFile out(Range(nameb));
        
      out.put(MutatePtr<const char>(map.getPtr()),map.getLen());
     }  
     
     AsyncFileSystem::DeleteFile(Range(namea));
     AsyncFileSystem::DeleteFile(Range(nameb));
    }
 };
 
/* test2() */  

void test2()
 {
  RunTasks run;
  
  for(int number=1; number<=50 ;number++) run(Test2(number));
 }
    
} // namespace Private_3010
 
using namespace Private_3010; 
 
/* Testit<3010> */ 

template<>
const char *const Testit<3010>::Name="Test3010 AsyncFile";

template<>
bool Testit<3010>::Main() 
 { 
  IPEngine ip_engine;
  
  HostEngine host_engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));
  
  SecTimer timer;
  
  test1();
  
  Printf(Con,"time1 = #; sec\n",timer.get());
  
  timer.reset();
  
  test2();
  
  Printf(Con,"time2 = #; sec\n",timer.get());
  
  return true;
 }
 
} // namespace App
 
