/* MemAllocGuard.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_MemAllocGuard_h
#define CCore_inc_MemAllocGuard_h
 
#include <CCore/inc/MemBase.h>

namespace CCore {

/* classes */ 

class MemAllocGuard;

/* class MemAllocGuard */ 

class MemAllocGuard : NoCopy
 {
   void *mem;
 
  public:
  
   explicit MemAllocGuard(ulen len)
    {
     mem=MemAlloc(len);
    }
   
   MemAllocGuard(ulen count,ulen size_of,ulen extra=0)
    {
     mem=MemAlloc(LenOf(count,size_of,extra));
    }
   
   ~MemAllocGuard()
    {
     if( mem ) MemFree(mem);
    }
   
   operator void * () const { return mem; }
   
   void * disarm() { return Replace_null(mem); }
 };
 
} // namespace CCore
 
#endif
 

