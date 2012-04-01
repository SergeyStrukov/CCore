/* ResSem.h */ 
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

#ifndef CCore_inc_task_ResSem_h
#define CCore_inc_task_ResSem_h
 
#include <CCore/inc/task/FastMutex.h>

namespace CCore {

/* classes */ 

class ResSem;

/* class ResSem */ 

class ResSem : public Funchor_nocopy
 {
   ulen max_count;
   
   FastMutex mutex;
   ulen count;
   ulen take_count;
   ulen wait_count;
 
   SlowSem take_sem;
   SlowSem wait_sem;
   
  private:
  
   void init(ulen max_count);
   
   bool begin_take();
   bool begin_wait();
   
   bool end_take();
   bool end_wait();
   
   struct Result
    {
     bool take;
     ulen wait;
     
     Result(bool take_,ulen wait_) : take(take_),wait(wait_) {}
    };
   
   Result begin_give();
   
  public:
   
   // constructors
  
   explicit ResSem(ulen max_count);
   
   ResSem(TextLabel name,ulen max_count);
   
   ~ResSem();
   
   // give
   
   void give();
   
   // take
  
   bool try_take();
  
   void take();
  
   bool take(MSec timeout);
  
   bool take(TimeScope time_scope)
    {
     auto timeout=time_scope.get();
     
     if( !timeout ) return false;
     
     return take(timeout);
    }
   
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
   
   Function<void (void)> function_give() { return FunctionOf(this,&ResSem::give); }
 };
 
} // namespace CCore
 
#endif
 

