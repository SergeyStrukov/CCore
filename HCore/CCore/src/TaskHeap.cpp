/* TaskHeap.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/TaskHeap.h>

#include <CCore/inc/TlsSlot.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/Exception.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

namespace Private_TaskHeap {

struct Slot : TlsSlot
 {
  Slot() : TlsSlot("TaskHeap") {}
 };
 
Slot Object CCORE_INITPRI_1 ;

} // namespace Private_TaskHeap
 
using namespace Private_TaskHeap;
 
PlanInitNode * GetPlanInitNode_TaskHeap() { return &Object; }
 
/* class TaskHeap::LocalHeap */

class TaskHeap::LocalHeap : public MemBase_nocopy   
 {
   LocalHeap *next;
   
   PageHeap heap;
   
   Mutex mutex;
   
   void *list = 0 ;
   
  private: 
   
   struct Prefix
    {
     void *ptr;
     
     Prefix(void *ptr_) : ptr(ptr_) {}
    };
   
   static const ulen Delta = Align(sizeof (Prefix)) ;
   
   void freeList()
    {
     void *ptr;
     
     {
      Mutex::Lock lock(mutex);
      
      ptr=Replace_null(list);
     }
     
     while( ptr )
       {
        void *next=static_cast<Prefix *>(ptr)->ptr;
        
        heap.free(ptr);
        
        ptr=next;
       }
    }
   
  public:
  
   explicit LocalHeap(LocalHeap *next_) : next(next_) {}
   
   LocalHeap(LocalHeap *next_,ulen min_page_alloc_len) : next(next_),heap(min_page_alloc_len) {}
   
   ~LocalHeap() 
    {
     freeList();
    }
   
   LocalHeap * destroy()
    {
     LocalHeap *ret=next;
     
     delete this;
     
     return ret;
    }
 
   // methods
   
   void * alloc(ulen len)
    {
     if( len>MaxULen-Delta ) return 0;
     
     freeList();
     
     if( void *mem=heap.alloc(len+Delta) ) 
       {
        new(PlaceAt(mem)) Prefix(this);
       
        return PtrAdd(mem,Delta);
       }
      
     return 0; 
    }
   
   bool extend(void *mem,ulen len)
    {
     return heap.extend(mem,len);
    }
   
   bool shrink(void *mem,ulen len)
    {
     return heap.shrink(mem,len);
    }
   
   void free(void *mem)
    {
     heap.free(mem);
    }
   
   void foreign_free(void *mem)
    {
     Mutex::Lock lock(mutex);
     
     static_cast<Prefix *>(mem)->ptr=list;
     
     list=mem;
    }

   // global
   
   static bool MemExtend(void *mem,ulen len)
    {
     if( !mem || len>MaxULen-Delta ) return false;
     
     mem=PtrSub(mem,Delta);
     
     void *obj=static_cast<Prefix *>(mem)->ptr;
     
     void *cur=Object.get();
     
     if( obj==cur )
       {
        return static_cast<LocalHeap *>(obj)->extend(mem,len+Delta);
       }
     else
       {
        // TODO
       
        return false;
       }
    }

   static bool MemShrink(void *mem,ulen len)
    {
     if( !mem || len>MaxULen-Delta ) return false;
     
     mem=PtrSub(mem,Delta);
     
     void *obj=static_cast<Prefix *>(mem)->ptr;
     
     void *cur=Object.get();
     
     if( obj==cur )
       {
        return static_cast<LocalHeap *>(obj)->shrink(mem,len+Delta);
       }
     else
       {
        // TODO
       
        return false;
       }
    }
   
   static void Free(void *mem)
    {
     if( !mem ) return;
     
     mem=PtrSub(mem,Delta);
     
     void *obj=static_cast<Prefix *>(mem)->ptr;
     
     void *cur=Object.get();
     
     if( obj==cur )
       {
        static_cast<LocalHeap *>(obj)->free(mem);
       }
     else
       {
        static_cast<LocalHeap *>(obj)->foreign_free(mem);
       }
    }
 };

/* class TaskHeap */

TaskHeap * TaskHeap::Active = 0 ;

auto TaskHeap::GetLocalHeap() -> LocalHeap *
 {
  void *ptr=Object.get();
  
  if( ptr ) return static_cast<LocalHeap *>(ptr);

  if( !Active ) return 0; 
  
  LocalHeap *ret=Active->create();
  
  Object.set(ret);
  
  return ret;
 }

auto TaskHeap::create() -> LocalHeap *
 {
  Mutex::Lock lock(mutex);

  if( min_page_alloc_len )
    {
     LocalHeap *ret=new LocalHeap(list,min_page_alloc_len);
     
     list=ret;
     
     return ret;
    }
  else
    {
     LocalHeap *ret=new LocalHeap(list);
     
     list=ret;
     
     return ret;
    }
 }
   
TaskHeap::TaskHeap(ulen min_page_alloc_len_)
 : min_page_alloc_len(min_page_alloc_len_),
   list(0)
 {
  if( Active )
    {
     Printf(Exception,"CCore::TaskHeap::TaskHeap(...) : already active");
    }
   
  Active=this;
 }
   
TaskHeap::~TaskHeap()
 {
  for(LocalHeap *obj=list; obj ;) obj=obj->destroy();
  
  Active=0;
 }
   
void * TaskHeap::TryMemAlloc(ulen len) noexcept
 {
  LocalHeap *obj=GetLocalHeap();
  
  if( !obj ) return 0;
  
  return obj->alloc(len);
 }
   
void * TaskHeap::MemAlloc(ulen len)
 {
  void *ret=TryMemAlloc(len);
  
  if( !ret ) GuardNoMem(len);
  
  return ret;
 }
   
bool TaskHeap::MemExtend(void *mem,ulen len)
 {
  return LocalHeap::MemExtend(mem,len);
 }

bool TaskHeap::MemShrink(void *mem,ulen len)
 {
  return LocalHeap::MemShrink(mem,len);
 }
    
void TaskHeap::MemFree(void *mem)
 {
  LocalHeap::Free(mem);
 }

} // namespace CCore
 

