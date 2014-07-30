/* TaskHeap.h */ 
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

#ifndef CCore_inc_TaskHeap_h
#define CCore_inc_TaskHeap_h

#include <CCore/inc/PerTask.h>
#include <CCore/inc/Array.h>
 
namespace CCore {

/* classes */

struct TaskHeapControl;

class TaskHeap;

template <class Algo> struct TaskHeapMemAlgo;

template <class T,class Flags=NoThrowFlags<T> > struct TaskHeapArrayAlgo;

/* struct TaskHeapControl */

struct TaskHeapControl
 {
  class ObjectType;

  class BuilderType
   {
     ulen mem_len;
    
    public:
    
     explicit BuilderType(ulen mem_len_) : mem_len(mem_len_) {}
     
     ObjectType * create();
   };
 };

/* class TaskHeap */

class TaskHeap : TaskObjectBuild<TaskHeapControl>
 {
  public:
  
   explicit TaskHeap(ulen mem_len=1_MByte);
   
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

/* struct TaskHeapArrayAlgo<T,Flags> */

template <class T,class Flags>
struct TaskHeapArrayAlgo : TaskHeapMemAlgo<ArrayAlgo<T,Flags> > {};

} // namespace CCore
 
#endif
 

