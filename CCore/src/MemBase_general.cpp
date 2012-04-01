/* MemBase_general.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/MemBase.h>
 
#include <CCore/inc/Exception.h>

#include <new>

namespace CCore {

/* functions */ 

class NoMemCatchType : public CatchType , public std::bad_alloc {};

void GuardNoMem(ulen len)
 {
  PrintCustomException<NoMemCatchType> out;
  
  Printf(out,"CCore::GuardNoMem(len=#;) : no memory",len);
 }

/* class MemScope */ 

MemScope::~MemScope()
 {
  MemStat on_exit;
  
  if( on_init!=on_exit )
    {
     Printf(NoException,"CCore::MemScope mismatch: on_init=#; on_exit=#;",on_init,on_exit);
    } 
 }
 
/* Mem...() */  

void * MemAlloc(ulen len)
 {
  void *ret=TryMemAlloc(len);
  
  if( !ret ) GuardNoMem(len);
  
  return ret;
 }

} // namespace CCore
 

