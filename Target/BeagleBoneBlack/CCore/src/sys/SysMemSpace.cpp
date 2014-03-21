/* SysMemSpace.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysMemSpace.h>
 
#include <__std_init.h>

namespace CCore {
namespace Sys {

/* functions */ 

Space AllocHeapSpace()
 {
  unsigned len=__std_get_heap_len();
  void *mem=__std_alloc(len);
 
  return Space(mem,len);
 }
 
Space AllocHeapSpace_int()
 {
  unsigned len=__std_get_heap_int_len();
  void *mem=__std_alloc(len);
 
  return Space(mem,len);
 }
 
Space AllocHeapSpace_shared()
 {
  return Space(__std_get_shared_mem(),__std_get_shared_mem_len());
 }
 
Space AllocLogSpace()
 {
  unsigned len=__std_get_syslog_len();
  void *mem=__std_alloc(len);

  return Space(mem,len);
 }
 
} // namespace Sys
} // namespace CCore
 

