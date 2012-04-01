/* FastMutex.h */ 
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

#ifndef CCore_inc_task_FastMutex_h
#define CCore_inc_task_FastMutex_h

#include <CCore/inc/task/Atomic.h>
#include <CCore/inc/task/SlowSem.h>
#include <CCore/inc/task/MutexSpinCount.h>
 
namespace CCore {

/* classes */ 

class FastMutex;

struct FastMutexBase;

/* class FastMutex */ 

class FastMutex : NoCopy
 {
   unsigned spin_count;
   
   Atomic entry;
   SlowSem sem;
   
  public: 
  
   explicit FastMutex(unsigned spin_count=MutexSpinCount());
   
   ~FastMutex();
   
   void lock()
    {
     for(unsigned cnt=spin_count; cnt ;cnt--) if( !entry ) break;
       
     if( (entry++)!=0 )
       {
        sem.take();
       }
    }
  
   void unlock()
    {
     if( (entry--)!=1 )
       {
        sem.give();
       }
    }
  
   typedef LockObject<FastMutex> Lock;
 };
 
/* struct FastMutexBase */ 

struct FastMutexBase : NoCopy
 {
  FastMutex mutex;
  
  class Lock : NoCopy
   {
     FastMutex &mutex;
     
    public: 
    
     explicit Lock(FastMutexBase &obj) : mutex(obj.mutex) { mutex.lock(); }
     
     ~Lock() { mutex.unlock(); }
   };
 };
 
} // namespace CCore
 
#endif
 

