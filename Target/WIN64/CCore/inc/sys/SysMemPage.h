/* SysMemPage.h */ 
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

#ifndef CCore_inc_sys_SysMemPage_h
#define CCore_inc_sys_SysMemPage_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Sys {

/* consts */ 

const ulen MemPageLen = 4_KByte ;

static_assert( (MemPageLen%MaxAlign)==0 ,"CCore::Sys::MemPageLen is not aligned");
 
/* functions */ 

void * MemPageAlloc(ulen num_pages) noexcept;
 
void MemPageFree(void *mem,ulen num_pages) noexcept;

bool MemPageExtend(void *mem,ulen num_pages,ulen plus_num_pages) noexcept;

ulen MemPageShrink(void *mem,ulen num_pages,ulen minus_num_pages) noexcept; // return delta
 
} // namespace Sys
} // namespace CCore
 
#endif
 

