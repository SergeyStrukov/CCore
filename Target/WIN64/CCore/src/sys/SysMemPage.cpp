/* SysMemPage.cpp */ 
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
 
#include <CCore/inc/sys/SysMemPage.h>
#include <CCore/inc/sys/SysAbort.h>
 
#include <CCore/inc/win64/Win64.h>

namespace CCore {
namespace Sys {

/* functions */ 

void * MemPageAlloc(ulen num_pages) noexcept
 {
  if( num_pages>MaxULen/MemPageLen ) return 0;
 
  ulen len=num_pages*MemPageLen;
  
  return Win64::VirtualAlloc(0,len,Win64::AllocReserve|Win64::AllocCommit,Win64::PageReadWrite);
 }
 
void MemPageFree(void *mem,ulen) noexcept
 {
  AbortIf( !Win64::VirtualFree(mem,0,Win64::FreeRelease) ,"CCore::Sys::MemPageFree()");
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
 

