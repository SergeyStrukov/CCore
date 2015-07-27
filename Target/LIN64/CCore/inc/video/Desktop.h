/* Desktop.h */ 
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

#ifndef CCore_inc_video_Desktop_h
#define CCore_inc_video_Desktop_h
 
#include <CCore/inc/video/FrameWindow.h>

namespace CCore {
namespace Video {

/* types */

using DesktopColor = RawColor32 ;

/* functions */

void AbortMsgBox(StrLen text);

void ErrorMsgBox(StrLen text,StrLen title);

/* classes */

class DefaultDesktopPtr;

/* class DefaultDesktopPtr */

class DefaultDesktopPtr : NoCopy
 {
   Desktop *ptr;
   
  private:
   
   Desktop * getPtr() const;
   
  public:
   
   explicit DefaultDesktopPtr(Desktop *ptr_) : ptr(ptr_) {}
   
   operator Desktop * () const { return getPtr(); }
   
   Desktop * operator -> () const { return getPtr(); }
 };

/* global DefaultDesktop */

extern DefaultDesktopPtr DefaultDesktop;

} // namespace Video
} // namespace CCore
 
#endif
 

