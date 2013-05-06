/* SysMemPage.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
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

#include <sys/mman.h>
#include <stdlib.h>

namespace CCore {
namespace Sys {

/* functions */ 

void * MemPageAlloc(ulen num_pages) noexcept
 {
#if 0
  
  if( num_pages>MaxULen/MemPageLen ) return 0;
  
  ulen len=num_pages*MemPageLen;

  return mmap(0,len,PROT_READ|PROT_WRITE,MAP_ANONYMOUS,-1,0);
  
#else
  
  if( num_pages>MaxULen/MemPageLen ) return 0;
  
  ulen len=num_pages*MemPageLen;
  
  return malloc(len);
  
#endif  
 }
 
void MemPageFree(void *mem,ulen num_pages) noexcept
 {
#if 0
  
  ulen len=num_pages*MemPageLen;
  
  AbortIf( munmap(mem,len)!=0 ,"CCore::Sys::MemPageFree()");
  
#else
  
  free(mem);
  
#endif  
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
 

