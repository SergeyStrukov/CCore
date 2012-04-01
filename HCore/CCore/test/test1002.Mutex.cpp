/* test1002.Mutex.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
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

#include <CCore/inc/Random.h>

namespace App {

namespace Private_1002 {

/* ShowSemCount() */

template <class Mutex>
void ShowSemCount(Mutex &) {}
 
void ShowSemCount(Mutex &mutex) { Printf(Con,"sem_count = #;\n",mutex.getSemCount()); }

/* class Data<Mutex> */
 
template <class Mutex> 
class Data : public Funchor_nocopy
 {
   static const ulen Num = 10     ;
   static const ulen Rep = 100000 ;
  
   static const unsigned MaxDelay = 10000 ;
   
  private: 

   Mutex mutex;
   volatile ulen shared;
   
  private: 
  
   static void DelayLoop(ulen cnt_)
    {
     for(volatile ulen cnt=cnt_; cnt ; cnt--);   
    }
   
   void inc()
    {
     typename Mutex::Lock lock(mutex);
     
     shared++;
    }
    
   void loop()
    {
     Random random;
     
     for(ulen rep=Rep; rep ;rep--) 
       {
        inc();
        
        DelayLoop(random.select(MaxDelay));
        
        //Task::Sleep(1*tuMSec);
       }
    }
    
   Function<void (void)> function_loop() { return FunctionOf(this,&Data::loop); }
  
  public:
  
   Data()
    {
     shared=0;
    }
   
   void run()
    {
     RunTasks run;
    
     run(Num,function_loop());
    }
   
   void show(StrLen name)
    {
     Printf(Con,"#; : shared = #; expected = #;\n\n",name,shared,Num*Rep);
    
     ShowSemCount(mutex);
    }
 };
 
} // namespace Private_1002
 
using namespace Private_1002; 
 
/* Testit<1002> */ 

template<>
const char *const Testit<1002>::Name="Test1002 Mutex";

template<>
bool Testit<1002>::Main() 
 { 
  {
   Data<NoMutex> data;
   
   data.run();
   
   data.show("NoMutex");
  } 
 
  {
   Data<FastMutex> data;
   
   data.run();
   
   data.show("FastMutex");
  } 
  
  {
   Data<Mutex> data;
   
   data.run();
   
   data.show("Mutex");
  } 
  
  return true;
 }
 
} // namespace App
 
