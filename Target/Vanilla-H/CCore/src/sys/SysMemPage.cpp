/* SysMemPage.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-H
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysMemPage.h>

namespace CCore {
namespace Sys {

/* functions */ 

void * MemPageAlloc(ulen /*num_pages*/) noexcept
 {
  // TODO

  return 0;
 }
 
void MemPageFree(void * /*mem*/,ulen /*num_pages*/) noexcept
 {
  // TODO
 }
 
bool MemPageExtend(void * /*mem*/,ulen /*num_pages*/,ulen /*plus_num_pages*/) noexcept
 {
  // TODO
  
  return false;
 }

ulen MemPageShrink(void * /*mem*/,ulen /*num_pages*/,ulen /*minus_num_pages*/) noexcept
 {
  // TODO
  
  return 0;
 }

} // namespace Sys
} // namespace CCore
 

