/* Mutex.h */ 
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

#ifndef CCore_inc_task_Mutex_h
#define CCore_inc_task_Mutex_h

#include <CCore/inc/task/Atomic.h>
#include <CCore/inc/task/SlowSem.h>
#include <CCore/inc/task/MutexSpinCount.h>

namespace CCore {

/* classes */ 

class Mutex;

/* class Mutex */ 

class Mutex : NoCopy
 {
   unsigned spin_count;
   
   Atomic entry;
   Atomic task_id;
   unsigned reentry;
   
   SlowSem sem;
   unsigned sem_count;
   
  private:
  
   void init(unsigned spin_count);
   
  public: 
  
   explicit Mutex(unsigned spin_count=MutexSpinCount());
   
   explicit Mutex(TextLabel name,unsigned spin_count=MutexSpinCount());
   
   ~Mutex();
   
   void lock();
  
   void unlock();
  
   unsigned getSemCount();
   
   typedef LockObject<Mutex> Lock;
 };
 
} // namespace CCore
 
#endif
 

