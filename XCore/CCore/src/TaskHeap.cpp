/* TaskHeap.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/TaskHeap.h>

#include <CCore/inc/MemSpaceHeap.h>
 
namespace CCore {

/* struct TaskHeapControl */

class TaskHeapControl::ObjectType : public MemBase_nocopy   
 {
   SpaceHeap heap;
   
  private: 
   
   union Prefix
    {
     ObjectType *heap;
     Prefix *next;
     
     explicit Prefix(ObjectType *heap_) : heap(heap_) {}
     
     ObjectType * getHeap() const
      {
       ObjectType *ret=heap;
       
       if( ret==TryGetTaskObject<TaskHeapControl>() ) return ret;
       
       return 0;
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
  
   explicit ObjectType(ulen mem_len) : heap(mem_len) {}
   
   ~ObjectType()
    {
     freeList();
    }
   
   void destroy() { delete this; }
 
   // methods
   
   void * alloc(ulen len) noexcept
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
     
     if( ObjectType *heap=prefix->getHeap() )
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
     
     if( ObjectType *heap=prefix->getHeap() )
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
     
     if( ObjectType *heap=prefix->getHeap() )
       {
        heap->free(prefix);
       }
     else
       {
        prefix->heap->foreign_free(prefix);
       }
    }
 };

auto TaskHeapControl::BuilderType::create() -> ObjectType *
 {
  return new ObjectType(mem_len);
 }
     
/* class TaskHeap */
   
TaskHeap::TaskHeap(ulen mem_len)
 : TaskObjectBuild<TaskHeapControl>(TaskObjectHard,mem_len)
 {
 }
   
TaskHeap::~TaskHeap()
 {
 }
   
void * TaskHeap::TryMemAlloc(ulen len) noexcept
 {
  TaskHeapControl::ObjectType *obj=TryGetTaskObject<TaskHeapControl>();
  
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
  return TaskHeapControl::ObjectType::MemExtend(mem,len);
 }

bool TaskHeap::MemShrink(void *mem,ulen len)
 {
  return TaskHeapControl::ObjectType::MemShrink(mem,len);
 }
    
void TaskHeap::MemFree(void *mem)
 {
  TaskHeapControl::ObjectType::Free(mem);
 }

} // namespace CCore
 

