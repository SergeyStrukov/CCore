/* test6.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/Win32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/ApplicationBase.h>

//#include <CCore/inc/video/DragWindow.h>
#include "DragWindow.h"
//#include <CCore/inc/video/DrawArt.h>
#include "DrawArt.h"

#include "FileReport.h"

namespace App6 {

/* using */ 

using namespace App;
using namespace CCore::Video;

/* classes */

class Client; 

class Application;

/* class Client */

class Client : public DragClient
 {
  public:
  
   Client()
    {
    }
   
   virtual ~Client()
    {
    }
   
   // drawing
   
   virtual void layout(Point size_)
    {
     Used(size_);
    }
   
   virtual void draw(FrameBuf<DesktopColor> buf,bool) const
    {
     CommonDrawArt art(buf);
     
     art.erase(Silver);
    }
 };

/* class Application */

class Application : public ApplicationBase
 {
   const CmdDisplay cmd_display;
  
   FileReport report;
   
   Client client;
   
   DragWindow main_win;
   
  private:
  
   virtual void clearException()
    {
     report.clear();
    }
   
   virtual void guardException()
    {
     report.guard();
    }
   
   virtual void showException()
    {
     if( !report.show() ) main_win.destroy();
    }
   
   virtual void prepare()
    {
     Point max_size=desktop->getScreenSize();
     
     main_win.createMain(cmd_display,max_size);
    }
   
  public: 
   
   explicit Application(CmdDisplay cmd_display_)
    : ApplicationBase(50_msec),
      cmd_display(cmd_display_),
      main_win(desktop,client)
    {
    }
   
   ~Application()
    {
    }
 };

/* testmain() */

int testmain(CmdDisplay cmd_display)
 {
  int ret;
  
  try
    {
     TaskMemStack tms(64_KByte);
    
     Application app(cmd_display);
    
     ret=app.run();
    }
  catch(CatchType)
    {
     return 1;
    }
  
  return ret;
 }
 
} // namespace App6
 
 
 


