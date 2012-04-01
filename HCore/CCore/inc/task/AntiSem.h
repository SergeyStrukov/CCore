/* AntiSem.h */ 
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

#ifndef CCore_inc_task_AntiSem_h
#define CCore_inc_task_AntiSem_h

#include <CCore/inc/task/FastMutex.h>
 
namespace CCore {

/* classes */ 

class AntiSem;

/* class AntiSem */ 

class AntiSem : public Funchor_nocopy
 {
   ulen level;
   
   FastMutex mutex;
   ulen count;
   ulen wait_count;
   
   SlowSem sem;
 
  private:
  
   void init(ulen level);
   
   bool begin_wait();
   
   bool end_wait();
   
   ulen begin_sub(ulen dcount);
   
  public:
   
   // constructors
  
   explicit AntiSem(ulen level=0);
   
   explicit AntiSem(TextLabel name,ulen level=0);
   
   ~AntiSem();
   
   // add/sub
   
   void add(ulen dcount);
   
   void sub(ulen dcount);
   
   // inc/dec
   
   void inc() { add(1); }
   
   void dec() { sub(1); }
   
   // wait
   
   bool try_wait();
   
   void wait();
   
   bool wait(MSec timeout);
   
   bool wait(TimeScope time_scope)
    {
     auto timeout=time_scope.get();
     
     if( !timeout ) return false; 
      
     return wait(timeout);
    }
    
   // functions
   
   Function<void (void)> function_inc() { return FunctionOf(this,&AntiSem::inc); }
   
   Function<void (void)> function_dec() { return FunctionOf(this,&AntiSem::dec); }
 };
 
} // namespace CCore
 
#endif
 

