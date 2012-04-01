/* MultiSem.h */ 
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

#ifndef CCore_inc_task_MultiSem_h
#define CCore_inc_task_MultiSem_h
 
#include <CCore/inc/task/TaskList.h>

namespace CCore {

/* classes */ 

class MultiSemBase;

template <ulen Len> class MultiSem;

/* class MultiSemBase */ 

class MultiSemBase : public Funchor_nocopy
 {
   TextLabel name;
   PtrLen<ulen> counts;
   ulen base;
   TaskList list;
   
  private:
  
   static AutoTextNameType ObjName;
    
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
   
   void init(PtrLen<ulen> counts); 
   
   void putIndex(ulen index);
   
   ulen nextIndex(ulen index) { return (index+1<counts.len)?index+1:0; }
   
   template <class T,class F>
   void give_locked(T cur,F Release,ulen index);
   
   ulen try_take_locked();

   ulen take_locked(MSec timeout);
   
  protected:
   
   explicit MultiSemBase(PtrLen<ulen> counts);
   
   MultiSemBase(TextLabel name,PtrLen<ulen> counts);
   
   ~MultiSemBase();
   
  public: 
   
   TextLabel getName() const { return name; }
   
   // give
  
   void give(ulen index); // [1,Len]
   
   void give_int(ulen index); // [1,Len]
   
   void give_any(ulen index); // [1,Len]
   
   // take
   
   ulen try_take(); // [0,Len]
   
   ulen take(); // [1,Len]
   
   ulen take(MSec timeout); // [0,Len]
   
   ulen take(TimeScope time_scope); // [0,Len]
   
   // give<Index>
   
   template <ulen Index> // [1,Len]
   void give_index() { give(Index); }
   
   template <ulen Index> // [1,Len]
   void give_index_int() { give_int(Index); }
   
   template <ulen Index> // [1,Len]
   void give_index_any() { give_any(Index); }
   
   // functions
   
   template <ulen Index>
   Function<void (void)> function_give() { return FunctionOf(this,&MultiSemBase::give_index<Index>); }
   
   template <ulen Index>
   Function<void (void)> function_give_int() { return FunctionOf(this,&MultiSemBase::give_index_int<Index>); }
   
   template <ulen Index>
   Function<void (void)> function_give_any() { return FunctionOf(this,&MultiSemBase::give_index_any<Index>); }
 };
 
/* class MultiSem<ulen Len> */ 

template <ulen Len> 
class MultiSem : public MultiSemBase
 {
   ulen counts[Len];
   
  public:
  
   MultiSem() : MultiSemBase(Range(counts)) {}
   
   explicit MultiSem(TextLabel name) : MultiSemBase(name,Range(counts)) {}
   
   ~MultiSem() {}
 };
 
} // namespace CCore
 
#endif
 

