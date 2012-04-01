/* Sem.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
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

#include <CCore/inc/task/TaskList.h>
 
namespace CCore {

/* classes */ 

class Sem;

/* class Sem */ 

class Sem : public Funchor_nocopy
 {
   TextLabel name;
   ulen count;
   TaskList list;
  
  private:
  
   static AutoTextNameType ObjName;
    
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(ulen count);
   
   void inc();
   
   void add(ulen dcount);
   
   template <class T,class F>
   void give_locked(T cur,F Release);
   
   template <class T,class F>
   void give_many_locked(T cur,F Release,ulen dcount);
   
   bool take_locked(MSec timeout);
   
  public:
   
   // constructors
  
   explicit Sem(ulen count=0);
   
   explicit Sem(TextLabel name,ulen count=0);
   
   ~Sem();
   
   TextLabel getName() const { return name; }
   
   // give
   
   void give();
   
   void give_int();
   
   void give_any();
   
   void give_many(ulen dcount);
   
   void give_many_int(ulen dcount);
   
   void give_many_any(ulen dcount);
   
   // take
   
   bool try_take();
   
   void take();
   
   bool take(MSec timeout);
   
   bool take(TimeScope time_scope);
   
   // functions
   
   Function<void (void)> function_give() { return FunctionOf(this,&Sem::give); }
   
   Function<void (void)> function_give_int() { return FunctionOf(this,&Sem::give_int); }
   
   Function<void (void)> function_give_any() { return FunctionOf(this,&Sem::give_any); }
 };
 
} // namespace CCore
 
#endif
 

