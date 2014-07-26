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
   
  private: 
   
   union Prefix
    {
     LocalHeap *heap;
     Prefix *next;
     
     Prefix(LocalHeap *heap_) : heap(heap_) {}
     
     LocalHeap * getHeap() const
      {
       void *obj=heap;
       void *cur=Object.get();
       
       if( obj==cur ) return heap;
       
       return 0;
      }
     
     LocalHeap * getForeignHeap() const
      {
       return heap;
      }
    };
   
   static const ulen Delta = Align(sizeof (Prefix)) ;
   static const ulen MaxAllocLen = MaxULen-Delta ;
   
   static Prefix * GetPrefix(void *mem) { return static_cast<Prefix *>(PtrSub(mem,Delta)); }
   
  private: 

   Mutex mutex;
   
   Prefix *list = 0 ;
   
   Atomic flag;
   
  private: 
   
   void freeList()
    {
     Prefix *ptr;
     
     {
      Mutex::Lock lock(mutex);
      
      ptr=Replace_null(list);
      
      flag=0;
     }
     
     while( ptr )
       {
        Prefix *next=ptr->next;
        
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
     if( len>MaxAllocLen ) return 0;
     
     if( flag ) freeList();
     
     if( void *mem=heap.alloc(len+Delta) ) 
       {
        new(PlaceAt(mem)) Prefix(this);
       
        return PtrAdd(mem,Delta);
       }
      
     return 0; 
    }
   
   bool extend(Prefix *prefix,ulen len)
    {
     return heap.extend(prefix,len);
    }
   
   bool shrink(Prefix *prefix,ulen len)
    {
     return heap.shrink(prefix,len);
    }
   
   void free(Prefix *prefix)
    {
     heap.free(prefix);
    }
   
   void foreign_free(Prefix *prefix)
    {
     Mutex::Lock lock(mutex);
     
     prefix->next=list;
     
     list=prefix;
     
     flag=1;
    }

   // global
   
   static bool MemExtend(void *mem,ulen len)
    {
     if( !mem || len>MaxAllocLen ) return false;
     
     Prefix *prefix=GetPrefix(mem);
     
     if( LocalHeap *heap=prefix->getHeap() )
       {
        return heap->extend(prefix,len+Delta);
       }
     else
       {
        return false;
       }
    }

   static bool MemShrink(void *mem,ulen len)
    {
     if( !mem || len>MaxAllocLen ) return false;
     
     Prefix *prefix=GetPrefix(mem);
     
     if( LocalHeap *heap=prefix->getHeap() )
       {
        return heap->shrink(prefix,len+Delta);
       }
     else
       {
        return false;
       }
    }
   
   static void Free(void *mem)
    {
     if( !mem ) return;
     
     Prefix *prefix=GetPrefix(mem);
     
     if( LocalHeap *heap=prefix->getHeap() )
       {
        heap->free(prefix);
       }
     else
       {
        prefix->heap->foreign_free(prefix);
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
 

