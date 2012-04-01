/* SysWait.h */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysWait_h
#define CCore_inc_sys_SysWait_h
 
namespace CCore {
namespace Sys {

/* enum WaitResult */

enum WaitResult
 {
  Wait_error     = -1,
  Wait_timeout   = -2,
  Wait_interrupt = -3
 };

} // namespace Sys
} // namespace CCore
 
#endif
 

