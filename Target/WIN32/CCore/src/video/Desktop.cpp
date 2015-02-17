/* Desktop.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/win32/Win32gui.h>
 
namespace CCore {
namespace Video {

namespace Private {

/* class WindowsControl */

class WindowsControl : public WinControl
 {
  public:
  
   WindowsControl() {}
   
   virtual ~WindowsControl() {}
   
   // WinControl
   // create/destroy
   
   virtual void createMain(Point max_size);
   
   virtual void createMain(Pane pane,Point max_size); // screen
   
   virtual void create(Pane pane,Point max_size); // screen
   
   virtual void create(WinControl *parent,Pane pane,Point max_size); // screen
   
   virtual void destroy();
   
   // operations
   
   virtual void show();
   
   virtual void hide();
   
   virtual void update();
   
   virtual void invalidate(Pane pane);
   
   virtual void invalidate();
   
   virtual void captureMouse();
   
   virtual void releaseMouse();
   
   virtual void setFocus();
   
   virtual void setMouseShape(MouseShape mshape);
   
   virtual void move(Pane pane); // screen
   
   virtual void moveTop();
 };

/* class WindowsDesktop */

class WindowsDesktop : public Desktop
 {
  public:
  
   WindowsDesktop() {}
   
   ~WindowsDesktop() {}
   
   // Desktop
   
   virtual WinControl * createControl() { return new WindowsControl(); }
   
   virtual Point getScreenSize();
   
   virtual bool pump(unsigned lim);
   
   virtual void wait();
   
   virtual void wait(MSec timeout);
 };

} // namespace Private

using namespace Private;

/* global DefaultDesktop */

static WindowsDesktop DesktopObject;

DefaultDesktopPtr DefaultDesktop(&DesktopObject); 

} // namespace Video
} // namespace CCore
 

