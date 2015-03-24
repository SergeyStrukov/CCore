/* TaskMemStack.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_TaskMemStack_h
#define CCore_inc_TaskMemStack_h
 
#include <CCore/inc/PlanInit.h>

#include <CCore/inc/MemBase.h>

#include <CCore/inc/array/ArrayAlgo.h>
 
#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* GetPlanInitNode_...() */

PlanInitNode * GetPlanInitNode_TaskMemStack();

/* functions */

void * TryTaskMemStackAlloc(ulen len) noexcept; // len!=0

void * TaskMemStackAlloc(ulen len); // len!=0

void TaskMemStackFree(void *mem); // mem!=0

/* classes */

class TaskMemStack;

class TaskMemStackAllocGuard;

template <class T,class Algo=ArrayAlgo<T> > class StackArray;

/* class TaskMemStack */

class TaskMemStack : NoCopy
 {
   struct Block : NoCopy
    {
     Block *prev;
     
     explicit Block(Block *prev_) : prev(prev_) {}
    };
   
   static const ulen DeltaBlock = Align(sizeof (Block)) ;
   
   struct Node : NoCopy
    {
     Node *prev;
     ulen node_len;
     
     Block *block;
     void *mem;
     ulen len;
     
     Node(Node *prev_,ulen node_len_) : prev(prev_),node_len(node_len_) {}
     
     void save(Block *block_,void *mem_,ulen len_)
      {
       block=block_;
       mem=mem_;
       len=len_;
      }
    };
   
   static const ulen DeltaNode = Align(sizeof (Node)) ;
   
   ulen reserve;
   Node *top;
   Node *cache;
   
   Block *block;
   void *mem;
   ulen len;
  
  private:
   
   bool provide(ulen delta);
   
   void popNode();
   
  public:
  
   explicit TaskMemStack(ulen reserve=4_KByte);
   
   ~TaskMemStack();
   
   void * alloc(ulen len); // len!=0
   
   void free(void *mem); // mem!=0
   
   static TaskMemStack * GetObject();
 };

/* class TaskMemStackAllocGuard */

class TaskMemStackAllocGuard : NoCopy
 {
   void *mem;
 
  public:
  
   explicit TaskMemStackAllocGuard(ulen count,ulen size_of) // count!=0, size_of!=0
    {
     mem=TaskMemStackAlloc(LenOf(count,size_of));
    }
   
   ~TaskMemStackAllocGuard()
    {
     if( mem ) TaskMemStackFree(mem);
    }
   
   operator void * () const { return mem; }
   
   void * disarm() { return Replace_null(mem); }
 };

/* class StackArray<T,Algo> */

template <class T,class Algo> 
class StackArray : NoCopy
 {
   T *ptr;
   ulen len;
 
  public:
  
   // constructors
   
   explicit StackArray(ulen len=0);
   
   ~StackArray();
   
   // range access
   
   T * getPtr() { return ptr; }
   
   const T * getPtr() const { return ptr; }
   
   const T * getPtr_const() const { return ptr; }
   
   ulen getLen() const { return len; }
   
   // index access
   
   T & operator [] (ulen index)
    { 
     return ptr[index]; 
    }
   
   const T & operator [] (ulen index) const
    { 
     return ptr[index]; 
    }
   
   T & at(ulen index)
    { 
     GuardIndex(index,len); 
     
     return ptr[index]; 
    }
    
   const T & at(ulen index) const
    { 
     GuardIndex(index,len); 
     
     return ptr[index]; 
    }
   
   // apply
   
   template <class FuncInit>
   void apply(FuncInit func_init) { Algon::ApplyToRange(Range(*this),func_init); }
   
   template <class FuncInit>
   void apply(FuncInit func_init) const { Algon::ApplyToRange(Range(*this),func_init); }
   
   template <class FuncInit>
   void apply_const(FuncInit func_init) const { Algon::ApplyToRange(Range(*this),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) { Algon::ApplyToRange(RangeReverse(*this),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) const { Algon::ApplyToRange(RangeReverse(*this),func_init); }
   
   template <class FuncInit>
   void applyReverse_const(FuncInit func_init) const { Algon::ApplyToRange(RangeReverse(*this),func_init); }
 };

template <class T,class Algo> 
StackArray<T,Algo>::StackArray(ulen len_)
 {
  if( len_ )
    {
     TaskMemStackAllocGuard mem(len_,sizeof (T));
  
     ptr=Algo::Create_default(PlaceAt(mem),len_).ptr;
     len=len_;
     
     mem.disarm();
    }
  else
    {
     ptr=0;
     len=0;
    }  
 }

template <class T,class Algo> 
StackArray<T,Algo>::~StackArray()
 {
  if( len )
    {
     Algo::Destroy(ptr,len);
     
     TaskMemStackFree(ptr);
    }
 }

} // namespace CCore
 
#endif
 

