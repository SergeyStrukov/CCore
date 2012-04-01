/* SpecialMemBase.h */ 
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

#ifndef CCore_inc_SpecialMemBase_h
#define CCore_inc_SpecialMemBase_h

#include <CCore/inc/MemBase.h>
 
namespace CCore {

/* init/exit functions */ 

void Init_SpecialMem();

void Exit_SpecialMem();

/* Mem..._int() functions */  

void * TryMemAlloc_int(ulen len) noexcept;

void MemFree_int(void *mem);

/* Mem..._shared() functions */ 

void * TryMemAlloc_shared(ulen len) noexcept;

void MemFree_shared(void *mem);

/* classes */ 

struct MemStat_int;

struct MemPeak_int;

/* struct MemStat_int */  

struct MemStat_int : MemStatData
 {
  MemStat_int();
 };
 
/* struct MemPeak_int */ 

struct MemPeak_int : MemStatData
 {
  MemPeak_int();
 };
 
} // namespace CCore
 
#endif
 

