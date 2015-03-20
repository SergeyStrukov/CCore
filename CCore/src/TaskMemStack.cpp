/* TaskMemStack.cpp */ 
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
 
#include <CCore/inc/TaskMemStack.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/TlsSlot.h>
 
namespace CCore {

/* GetPlanInitNode_...() */

namespace Private_TaskMemStack {

struct Slot : TlsSlot
 {
  Slot() : TlsSlot("TaskMemStack") {}
 };

Slot Object CCORE_INITPRI_1;

} // namespace Private_TaskMemStack

using namespace Private_TaskMemStack;

PlanInitNode * GetPlanInitNode_TaskMemStack() { return &Object; }

/* functions */

void * TryTaskMemStackAlloc(ulen len) noexcept
 {
  auto *obj=TaskMemStack::GetObject();
  
  if( !obj ) 
    {
     Printf(NoException,"CCore::TryTaskMemStackAlloc(...) : no TaskMemStack object");
     
     return 0;
    }
  
  return obj->alloc(len);
 }

void * TaskMemStackAlloc(ulen len)
 {
  void *ret=TryTaskMemStackAlloc(len);
  
  if( !ret ) GuardNoMem(len);
  
  return ret;
 }

void TaskMemStackFree(void *mem)
 {
  auto *obj=TaskMemStack::GetObject();
  
  if( !obj )
    {
     Abort("Fatal error : no TaskMemStack object on free");
    }
  
  obj->free(mem);
 }

/* class TaskMemStack */

bool TaskMemStack::provide(ulen delta)
 {
  if( delta>MaxULen-DeltaNode ) return false;
   
  if( cache && DeltaNode+delta<=cache->node_len )
    {
     if( top ) top->save(block,mem,len);
     
     cache->prev=top;
       
     top=Replace_null(cache);
     
     block=0;
     mem=PtrAdd(top,DeltaNode);
     len=top->node_len-DeltaNode;
     
     return true;
    }
  else
    {
     MemFree(Replace_null(cache));
    
     ulen node_len=Max<ulen>(DeltaNode+delta,top?2*top->node_len:reserve);
    
     void *node_mem=TryMemAlloc(node_len);
     
     if( !node_mem ) return false;
     
     if( top ) top->save(block,mem,len);
       
     auto place=PlaceAt(node_mem);
     
     top=new(place) Node(top,node_len);
     
     block=0;
     mem=place+DeltaNode;
     len=node_len-DeltaNode;
     
     return true;
    }
 }

void TaskMemStack::popNode()
 {
  Node *todel=top;
  
  top=top->prev;
  
  MemFree(cache);
  
  cache=todel;
  
  if( top )
    {
     block=top->block;
     mem=top->mem;
     len=top->len;
    }
  else
    {
     block=0;
     mem=0;
     len=0;
    }
 }

TaskMemStack::TaskMemStack(ulen reserve_)
 : reserve(reserve_),
   top(0),
   cache(0),
   block(0),
   mem(0),
   len(0)
 {
  void *obj=Object.get();
  
  if( obj )
    {
     Printf(Exception,"CCore::TaskMemStack::TaskMemStack(...) : already set");
    }
  
  Object.set(this);
 }
   
TaskMemStack::~TaskMemStack()
 {
  // cleanup
  
  void *obj=Object.get();
  
  if( obj!=this )
    {
     Abort("Fatal error : wrong TaskMemStack object on exit");
    }
  
  Object.set(0);
  
  // release
  
  if( block )
    {
     Abort("Fatal error : TaskMemStack memory leak on exit");
    }
  
  MemFree(cache);
 }
   
void * TaskMemStack::alloc(ulen alloc_len)
 {
  if( alloc_len>AlignDown(MaxULen-DeltaBlock) ) return 0;
  
  ulen delta=DeltaBlock+Align(alloc_len);
  
  if( delta>len )
    {
     if( !provide(delta) ) return 0;
    }
  
  auto place=PlaceAt(mem);
  
  block=new(place) Block(block); 
  
  void *ret=place+DeltaBlock;
  
  mem=place+delta;
  len-=delta;
  
  return ret;
 }
   
void TaskMemStack::free(void *mem_)
 {
  if( !block || PtrAdd(block,DeltaBlock)!=mem_ )
    {
     Abort("Fatal error : TaskMemStack bad ptr");
    }

  len+=PtrDist(block,mem);
  mem=block;
  
  block=block->prev;
  
  if( !block ) popNode();
 }

TaskMemStack * TaskMemStack::GetObject()
 {
  return static_cast<TaskMemStack *>(Object.get());
 }
   
} // namespace CCore
 

