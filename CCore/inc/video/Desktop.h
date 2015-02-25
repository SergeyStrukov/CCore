/* Desktop.h */ 
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

#ifndef CCore_inc_video_Desktop_h
#define CCore_inc_video_Desktop_h
#define CCore_inc_video_Desktop_h_stub
 
#include <CCore/inc/video/FrameWindow.h>

namespace CCore {
namespace Video {

/* types */

using DesktopColor = RawColor32 ;

/* classes */

class DefaultDesktopPtr;

/* class DefaultDesktopPtr */

class DefaultDesktopPtr : NoCopy
 {
  private:
  
   Desktop * getPtr();
  
  public:
   
   DefaultDesktopPtr() {}
   
   operator Desktop * () const { return getPtr(); }
   
   Desktop * operator -> () const { return getPtr(); }
 };

/* global DefaultDesktop */

extern DefaultDesktopPtr DefaultDesktop; 

} // namespace Video
} // namespace CCore
 
#endif
 

