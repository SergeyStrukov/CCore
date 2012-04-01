/* SpecialMemBase.cpp */ 
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
 
#include <CCore/inc/SpecialMemBase.h>
 
#include <CCore/inc/MemSpaceHeap.h>
#include <CCore/inc/Task.h>

#include <CCore/inc/sys/SysMemSpace.h>

namespace CCore {

/* init/exit() */ 

namespace Private_SpecialMemBase {

/* class IntHeap */

class IntHeap : FastMutexBase
 {
   RadixHeap<MemSpace> heap;
   MemStatData stat;
   MemStatData peak;
  
  private:
  
   void addStat(ulen len)
    {
     stat.add(len);
     peak.setMax(stat);
    }
 
   void delStat(ulen len)
    {
     stat.del(len);
    }
  
  public:
  
   IntHeap();
   
   ~IntHeap();
   
   void * alloc(ulen len);
  
   void free(void *mem);
  
   void getStat(MemStatData &ret);
  
   void getPeak(MemStatData &ret);
 };
 
IntHeap::IntHeap()
 : heap(Sys::AllocHeapSpace_int())
 {
 }
   
IntHeap::~IntHeap()
 {
 }
   
void * IntHeap::alloc(ulen len)
 {
  Lock lock(*this);

  Space ret=heap.alloc(len);
  
  if( ret.len )
    {
     addStat(ret.len);

     return ret.mem;
    }
  
  return 0;
 }
  
void IntHeap::free(void *mem)
 {
  if( !mem ) return;
  
  Lock lock(*this);
 
  ulen len=heap.free(mem);
  
  delStat(len);
 }
  
void IntHeap::getStat(MemStatData &ret)
 {
  Lock lock(*this);
  
  ret=stat;
 }
  
void IntHeap::getPeak(MemStatData &ret)
 {
  Lock lock(*this);
  
  ret=peak;
 }
 
/* class SharedHeap */

class SharedHeap : FastMutexBase
 {
   RadixHeap<MemSpace> heap;
  
  public:
  
   SharedHeap();
   
   ~SharedHeap();
   
   void * alloc(ulen len);
  
   void free(void *mem);
 };
 
SharedHeap::SharedHeap()
 : heap(Sys::AllocHeapSpace_shared())
 {
 }
   
SharedHeap::~SharedHeap()
 {
 }
   
void * SharedHeap::alloc(ulen len)
 {
  Lock lock(*this);

  return heap.alloc(len).mem;
 }
  
void SharedHeap::free(void *mem)
 {
  if( !mem ) return;
  
  Lock lock(*this);
 
  heap.free(mem);
 }

/* objects */

InitExitObject<IntHeap> Object_int={};

InitExitObject<SharedHeap> Object_shared={};
 
} // namespace Private_SpecialMemBase
 
using namespace Private_SpecialMemBase;
 
/* init/exit functions */ 

void Init_SpecialMem()
 {
  Object_int.init();
  Object_shared.init();
 }
 
void Exit_SpecialMem()
 {
  Object_shared.exit();
  Object_int.exit();
 }
 
/* Mem..._int() functions */  

void * TryMemAlloc_int(ulen len) noexcept
 {
  return Object_int->alloc(len);
 }
 
void MemFree_int(void *mem)
 {
  Object_int->free(mem);
 }
 
/* Mem..._shared() functions */ 

void * TryMemAlloc_shared(ulen len) noexcept
 {
  return Object_shared->alloc(len);
 }
 
void MemFree_shared(void *mem)
 {
  Object_shared->free(mem);
 }
 
/* struct MemStat_int */  

MemStat_int::MemStat_int()
 {
  Object_int->getStat(*this);
 }
  
/* struct MemPeak_int */ 

MemPeak_int::MemPeak_int()
 {
  Object_int->getPeak(*this);
 }
 
} // namespace CCore
 

