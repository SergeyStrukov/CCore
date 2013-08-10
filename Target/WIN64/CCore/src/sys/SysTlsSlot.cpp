/* SysTlsSlot.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysTlsSlot.h>
#include <CCore/inc/sys/SysAbort.h>
 
#include <CCore/inc/win64/Win64.h>

namespace CCore {
namespace Sys {

/* struct TlsSlot */ 

auto TlsSlot::Alloc() noexcept -> AllocType
 {
  TlsSlot::AllocType ret;
  
  ret.index=Win64::TlsAlloc();
  
  ret.error=ErrorIf( ret.index==Win64::TlsNoIndex );
  
  return ret;
 }
  
void TlsSlot::Free(Type index) noexcept
 {
  AbortIf( !Win64::TlsFree(index) ,"CCore::Sys::TlsSlot::Free()");
 }
  
void * TlsSlot::Get(Type index) noexcept
 {
  return Win64::TlsGetValue(index);
 }
  
void TlsSlot::Set(Type index,void *value) noexcept
 {
  Win64::TlsSetValue(index,value);
 }
 
} // namespace Sys
} // namespace CCore
 

