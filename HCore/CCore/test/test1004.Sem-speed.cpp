/* test1004.Sem-speed.cpp */ 
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

#include <CCore/inc/Task.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_1004 {

/* class NoSem */

class NoSem : NoCopy
 {
  public:
  
   NoSem()
    {
    }
   
   ~NoSem()
    {
    }
   
   void give()
    {
    }
   
   void take()
    {
    }
 };

/* class AtomicNoSem */

class AtomicNoSem : NoCopy
 {
   Atomic count;
   
  public:
  
   AtomicNoSem()
    {
    }
   
   ~AtomicNoSem()
    {
    }
   
   void give()
    {
     count++;
    }
   
   void take()
    {
     count--;
    }
 };

/* test<Sem>() */
 
template <class Sem> 
void test(StrLen name)
 {
  const unsigned Rep = 10000 ;
 
  Sem sem;
  
  {
   TimeStat<ClockTimer::ValueType> stat;
   
   for(unsigned rep=Rep; rep ;rep--)
     {
      ClockTimer timer;
      
      sem.give();
      
      stat.add(timer.get());
     }
     
   Printf(Con,"#; give: #;\n",name,stat);  
  } 
 
  {
   TimeStat<ClockTimer::ValueType> stat;
   
   for(unsigned rep=Rep; rep ;rep--)
     {
      ClockTimer timer;
      
      sem.take();
      
      stat.add(timer.get());
     }
     
   Printf(Con,"#; take: #;\n\n",name,stat);  
  } 
 }
 
} // namespace Private_1004
 
using namespace Private_1004; 
 
/* Testit<1004> */ 

template<>
const char *const Testit<1004>::Name="Test1004 Sem speed";

template<>
bool Testit<1004>::Main() 
 { 
  test<NoSem>("NoSem");
  test<AtomicNoSem>("AtomicNoSem");
  test<SlowSem>("SlowSem");
  test<Sem>("Sem");
  
  return true;
 }
 
} // namespace App
 
