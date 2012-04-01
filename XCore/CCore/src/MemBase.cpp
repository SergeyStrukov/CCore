/* MemBase.cpp */ 
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
 
#include <CCore/inc/MemBase.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/MemSpaceHeap.h>
#include <CCore/inc/HeapEngine.h>

#include <CCore/inc/sys/SysMemSpace.h>

namespace CCore {

/* GetPlanInitNode_...() */ 

namespace Private_MemBase {

class MainHeap : public HeapEngine<RadixHeap<MemSpace> >
 {
  public:
   
   MainHeap() : HeapEngine<RadixHeap<MemSpace> >("!MainHeap",Sys::AllocHeapSpace()) {}
   
   ~MainHeap() {}
   
   static const char * GetTag() { return "MemBase"; }
 };
   
PlanInitObject<MainHeap,PlanInitReq<GetPlanInitNode_Exception>
                       ,PlanInitReq<GetPlanInitNode_TaskCore> 
                       > Object CCORE_INITPRI_1 ;

} // namespace Private_MemBase
 
using namespace Private_MemBase; 
 
PlanInitNode * GetPlanInitNode_MemBase() { return &Object; }
 
/* struct MemStat */  

MemStat::MemStat()
 {
  Object->getStat(*this);
 }
 
/* struct MemPeak */ 

MemPeak::MemPeak()
 {
  Object->getPeak(*this);
 }
 
/* Mem...() functions */  

void * TryMemAlloc(ulen len) noexcept { return Object->alloc(len); }
 
ulen MemLen(const void *mem) { return Object->getLen(mem); }
 
bool MemExtend(void *mem,ulen len) { return Object->extend(mem,len); }
 
bool MemShrink(void *mem,ulen len) { return Object->shrink(mem,len); }
 
void MemFree(void *mem) { Object->free(mem); }
 
void MemLim(ulen limit) { Object->setLim(limit); }
 
} // namespace CCore
 

