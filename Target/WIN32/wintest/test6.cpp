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
//#include <CCore/inc/video/WindowReport.h>
#include "WindowReport.h"
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
   DragWindow::Shape::Config &cfg;
   
   enum Param 
    {
     Frame,
     Title,
     
     BtnDx,
     BtnDy,
     
     MinDy,
     AlertDx
    };
   
   Param param = Frame ;
   
   ulen index = 0 ;
   
  public:
  
   explicit Client(DragWindow::Shape::Config &cfg_)
    : cfg(cfg_)
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
     
     art.erase(Green);
    }
   
   virtual void key(VKey vkey,KeyMod)
    {
     switch( vkey )
       {
        case VKey_F1 : param=Frame; break;
        case VKey_F2 : param=Title; break;
        case VKey_F3 : param=BtnDx; break;
        case VKey_F4 : param=BtnDy; break;
        case VKey_F5 : param=MinDy; break;
        case VKey_F6 : param=AlertDx; break;
        
        case VKey_F10 : 
         {
          Printf(NoException,"extra");
          
          Printf(Exception,"test exception #;\nsecond line",index++);
         }
        break;
       }
    }
   
   virtual void wheel(Point,MouseKey,Coord delta)
    {
     switch( param )
      {
       case Frame : cfg.frame_dxy=Cap<Coord>(3,cfg.frame_dxy+delta,100); break;
       
       case Title : cfg.title_dy=Cap<Coord>(10,cfg.title_dy+delta,100); break;
       
       case BtnDx : cfg.btn_dx=Cap<Coord>(10,cfg.btn_dx+delta,100); break;
       
       case BtnDy : cfg.btn_dy=Cap<Coord>(10,cfg.btn_dy+delta,100); break;
       
       case MinDy : cfg.min_dy=Cap<Coord>(1,cfg.min_dy+delta,100); break;
       
       case AlertDx : cfg.alert_dx=Cap<Coord>(1,cfg.alert_dx+delta,100); break;
      }
     
     cfg.update.assert();
    }
 };

/* class Application */

class Application : public ApplicationBase
 {
   const CmdDisplay cmd_display;
  
   struct Config
    {
     DragWindow::Shape::Config drag_cfg;
     WindowReport::Config report_cfg; 
    };

   Config cfg;
   
   WindowReport report;
   
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
     
     main_win.createMain(cmd_display,max_size,String("test6"));
    }
   
  public: 
   
   explicit Application(CmdDisplay cmd_display_)
    : cmd_display(cmd_display_),
      report(cfg.report_cfg),
      client(cfg.drag_cfg),
      main_win(desktop,cfg.drag_cfg,client,&report)
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
 
 
 


