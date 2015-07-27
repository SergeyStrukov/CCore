/* Desktop.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/video/Desktop.h>
 
#include <CCore/inc/Abort.h>

#include <X11/Xlib.h>
 
namespace CCore {
namespace Video {

/* functions */

void AbortMsgBox(StrLen text)
 {
 }

void ErrorMsgBox(StrLen text,StrLen title)
 {
 }

/* class DefaultDesktopPtr */

Desktop * DefaultDesktopPtr::getPtr() const
 {
  Abort("Fatal error : no desktop");
  
  return 0;
 }
  
/* global DefaultDesktop */

DefaultDesktopPtr DefaultDesktop(0); 

} // namespace Video
} // namespace CCore
 

