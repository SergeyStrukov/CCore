/* TaskHeap.h */ 
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

#ifndef CCore_inc_TaskHeap_h
#define CCore_inc_TaskHeap_h

#include <CCore/inc/MemPageHeap.h>
#include <CCore/inc/PlanInit.h>
#include <CCore/inc/Task.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_TaskHeap();

/* classes */

class TaskHeap;

template <class Algo> struct TaskHeapMemAlgo;

/* class TaskHeap */

class TaskHeap : NoCopy
 {
  private:
  
   class LocalHeap;
   
   static TaskHeap * Active;
  
   static LocalHeap * GetLocalHeap(); 

  private:
   
   ulen min_page_alloc_len;
   
   Mutex mutex;
   
   LocalHeap *list;
   
  private: 
   
   LocalHeap * create();
   
  public:
  
   explicit TaskHeap(ulen min_page_alloc_len=0);
   
   ~TaskHeap();
   
   static void * TryMemAlloc(ulen len) noexcept;
   
   static void * MemAlloc(ulen len);
   
   static bool MemExtend(void *mem,ulen len);

   static bool MemShrink(void *mem,ulen len);
    
   static void MemFree(void *mem);
 };

/* struct TaskHeapMemAlgo<Algo> */

template <class Algo> 
struct TaskHeapMemAlgo : Algo
 {
  static void * MemAlloc(ulen len) { return TaskHeap::MemAlloc(len); }

  static bool MemExtend(void *mem,ulen len) { return TaskHeap::MemExtend(mem,len); }

  static bool MemShrink(void *mem,ulen len) { return TaskHeap::MemShrink(mem,len); }
  
  static void MemFree(void *mem) { TaskHeap::MemFree(mem); }
 };

} // namespace CCore
 
#endif
 

