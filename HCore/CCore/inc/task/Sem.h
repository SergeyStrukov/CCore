/* Sem.h */ 
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

#ifndef CCore_inc_task_Sem_h
#define CCore_inc_task_Sem_h

#include <CCore/inc/task/FastMutex.h>
 
namespace CCore {

/* classes */ 

class Sem;

/* class Sem */  

class Sem : public Funchor_nocopy
 {
   FastMutex mutex;
   ulen count;
   ulen take_count;
   
   SlowSem sem;
   
  private:
  
   void init(ulen count);
   
   bool begin_take();
   
   bool end_take();
   
   bool begin_give();
   
   ulen begin_give_many(ulen dcount);
   
  public:
   
   // constructors
  
   explicit Sem(ulen count=0);
   
   explicit Sem(TextLabel name,ulen count=0);
   
   ~Sem();
   
   // give
   
   void give();
   
   void give_many(ulen dcount);
   
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
    
   // functions
   
   Function<void (void)> function_give() { return FunctionOf(this,&Sem::give); }
 };
 
} // namespace CCore
 
#endif
 

