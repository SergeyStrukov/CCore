/* SlowSem.h */ 
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

#ifndef CCore_inc_task_SlowSem_h
#define CCore_inc_task_SlowSem_h

#include <CCore/inc/TextLabel.h>
#include <CCore/inc/TimeScope.h>

#include <CCore/inc/sys/SysSem.h>
 
namespace CCore {

/* classes */ 

class SlowSem;

/* class SlowSem */ 

class SlowSem : public Funchor_nocopy
 {
   Sys::Sem sem;
   
  private:
  
   void init(ulen count);
   
  public: 
   
   // constructors
  
   explicit SlowSem(ulen count=0);
   
   explicit SlowSem(TextLabel name,ulen count=0);
   
   ~SlowSem() { sem.exit(); }
   
   // give
   
   void give() { sem.give(); }
   
   void give_many(ulen dcount) { sem.give_many(dcount); }
   
   // take
   
   bool try_take() { return sem.try_take(); }
   
   void take() { sem.take(); }
   
   bool take(MSec timeout) { return sem.take(timeout); }
   
   bool take(TimeScope time_scope) 
    {
     auto timeout=time_scope.get();
     
     if( !timeout ) return false;
     
     return sem.take(timeout); 
    }
    
   // functions
   
   Function<void (void)> function_give() { return FunctionOf(this,&SlowSem::give); }
 };
 
} // namespace CCore
 
#endif
 

