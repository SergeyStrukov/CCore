/* ClientWindow.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_ClientWindow_h
#define CCore_inc_video_ClientWindow_h
 
#include <CCore/inc/video/SubWindow.h>

namespace CCore {
namespace Video {

/* classes */

class ClientWindow;

class ClientFromSubWindow;

/* class ClientWindow */

class ClientWindow : public MemBase_nocopy
 {
  protected:
  
   SubWindow *sub_win = 0 ; // must be initialized in a derived class constructor
   
  public:
   
   ClientWindow() {}
  
   virtual ~ClientWindow() {}
   
   SubWindow & getSubWindow() const { return *sub_win; }
   
   // base
   
   virtual void alive()
    {
     // do nothing
    }
   
   virtual void dead()
    {
     // do nothing
    }
   
   virtual bool askDestroy()
    {
     return true;
    }
 };

/* class ClientFromSubWindow */

class ClientFromSubWindow : public ClientWindow
 {
  public: 
   
   explicit ClientFromSubWindow(SubWindow &sub_win_) { sub_win=&sub_win_; }
   
   virtual ~ClientFromSubWindow() {}
 };

} // namespace Video
} // namespace CCore
 
#endif
 

