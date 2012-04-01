/* MultiSem.h */ 
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

#ifndef CCore_inc_task_MultiSem_h
#define CCore_inc_task_MultiSem_h
 
#include <CCore/inc/task/Sem.h>

namespace CCore {

/* classes */ 

class MultiSemBase;

template <ulen Len> class MultiSem;

/* class MultiSemBase */ 

class MultiSemBase : public Funchor_nocopy
 {
   FastMutex mutex;
   PtrLen<ulen> counts;
   ulen base;
   
   Sem sem;
   
  private:
  
   void init(PtrLen<ulen> counts);

   void putIndex(ulen index);
   
   ulen nextIndex(ulen index) { return (index+1<counts.len)?index+1:0; }
   
   ulen getIndex();
  
  protected:
   
   explicit MultiSemBase(PtrLen<ulen> counts);
   
   MultiSemBase(TextLabel name,PtrLen<ulen> counts);
   
   ~MultiSemBase();
   
  public: 
   
   // give
  
   void give(ulen index); // [1,Len]
   
   // take
   
   ulen try_take(); // [0,Len]
   
   ulen take(); // [1,Len]
   
   ulen take(MSec timeout); // [0,Len]
   
   ulen take(TimeScope time_scope) // [0,Len]
    {
     auto timeout=time_scope.get();
     
     if( !timeout ) return 0; 

     return take(timeout);
    }
   
   // give<Index>
   
   template <ulen Index> // [1,Len]
   void give_index() { give(Index); }
   
   // functions
   
   template <ulen Index>
   Function<void (void)> function_give() { return FunctionOf(this,&MultiSemBase::give_index<Index>); }
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
 

