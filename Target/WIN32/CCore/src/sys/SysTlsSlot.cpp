/* SysTlsSlot.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysTlsSlot.h>
#include <CCore/inc/sys/SysAbort.h>
 
#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* struct TlsSlot */ 

auto TlsSlot::Alloc() noexcept -> AllocType
 {
  TlsSlot::AllocType ret;
  
  ret.index=Win32::TlsAlloc();
  
  ret.error=ErrorIf( ret.index==Win32::TlsNoIndex );
  
  return ret;
 }
  
void TlsSlot::Free(Type index) noexcept
 {
  AbortIf( !Win32::TlsFree(index) ,"CCore::Sys::TlsSlot::Free()");
 }
  
void * TlsSlot::Get(Type index) noexcept
 {
  return Win32::TlsGetValue(index);
 }
  
void TlsSlot::Set(Type index,void *value) noexcept
 {
  Win32::TlsSetValue(index,value);
 }
 
} // namespace Sys
} // namespace CCore
 

