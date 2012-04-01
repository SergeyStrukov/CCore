/* SysMemPage.cpp */ 
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
 
#include <CCore/inc/sys/SysMemPage.h>
#include <CCore/inc/sys/SysAbort.h>
 
#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* functions */ 

void * MemPageAlloc(ulen num_pages) noexcept
 {
  if( num_pages>MaxULen/MemPageLen ) return 0;
 
  ulen len=num_pages*MemPageLen;
 
  return Win32::VirtualAlloc(0,len,Win32::AllocReserve|Win32::AllocCommit,Win32::PageReadWrite);
 }
 
void MemPageFree(void *mem,ulen) noexcept
 {
  AbortIf( !Win32::VirtualFree(mem,0,Win32::FreeRelease) ,"CCore::Sys::MemPageFree()");
 }
 
bool MemPageExtend(void *,ulen,ulen) noexcept
 {
  // no OS support
  
  return false;
 }

ulen MemPageShrink(void *,ulen,ulen) noexcept
 {
  // no OS support
  
  return 0;
 }

} // namespace Sys
} // namespace CCore
 

