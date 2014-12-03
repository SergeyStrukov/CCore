/* SysConHost.h */ 
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

#ifndef CCore_inc_sys_SysConHost_h
#define CCore_inc_sys_SysConHost_h

#include <CCore/inc/SingleHost.h>

#include <CCore/inc/video/VideoConsole.h>
 
namespace CCore {
namespace Sys {

/* GetConHost() */

SingleHost<Video::VideoConsole> & GetConHost();

} // namespace Sys
} // namespace CCore
 
#endif
 

