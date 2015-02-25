/* DesktopStub.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: GeneralStub
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/video/Desktop.h>

#ifdef CCore_inc_video_Desktop_h_stub 

#include <CCore/inc/Abort.h>
 
namespace CCore {
namespace Video {

/* class DefaultDesktopPtr */

Desktop * DefaultDesktopPtr::getPtr()
 {
  Abort("Fatal error : no desktop");
  
  return 0;
 }
  
/* global DefaultDesktop */

DefaultDesktopPtr DefaultDesktop; 

} // namespace Video
} // namespace CCore
 
#endif


