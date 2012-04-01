/* MultiEvent.h */ 
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

#ifndef CCore_inc_task_MultiEvent_h
#define CCore_inc_task_MultiEvent_h

#include <CCore/inc/task/Sem.h>
 
namespace CCore {

/* classes */ 

class MultiEventBase;

template <ulen Len> class MultiEvent;

/* class MultiEventBase */ 

class MultiEventBase : public Funchor_nocopy
 {
   FastMutex mutex;
   PtrLen<bool> flags;
   ulen base;
   
   Sem sem;
   
  private:
  
   void init(PtrLen<bool> flags_);

   bool putIndex(ulen index);
   
   ulen nextIndex(ulen index) { return (index+1<flags.len)?index+1:0; }
   
   ulen getIndex();
  
  protected:
   
   explicit MultiEventBase(PtrLen<bool> flags);
   
   MultiEventBase(TextLabel name,PtrLen<bool> flags);
   
   ~MultiEventBase();
   
  public:
   
   // trigger
  
   bool trigger(ulen index); // [1,Len]
   
   // wait
   
   ulen try_wait(); // [0,Len]
   
   ulen wait(); // [1,Len]
   
   ulen wait(MSec timeout); // [0,Len]
   
   ulen wait(TimeScope time_scope) // [0,Len]
    {
     auto timeout=time_scope.get();
     
     if( !timeout ) return 0; 
     
     return wait(timeout);
    }
   
   // trigger<Index>
   
   template <ulen Index> // [1,Len]
   void trigger_index() { trigger(Index); }
   
   // functions
   
   template <ulen Index>
   Function<void (void)> function_trigger() { return FunctionOf(this,&MultiEventBase::trigger_index<Index>); }
 };
 
/* class MultiEvent<ulen Len> */ 

template <ulen Len> 
class MultiEvent : public MultiEventBase
 {
   bool flags[Len];
   
  public:
  
   MultiEvent() : MultiEventBase(Range(flags)) {}
   
   explicit MultiEvent(TextLabel name) : MultiEventBase(name,Range(flags)) {}
   
   ~MultiEvent() {}
 };
 
} // namespace CCore
 
#endif
 

