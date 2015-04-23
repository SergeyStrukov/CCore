/* test5.cpp */
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

#include <CCore/inc/Array.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/TaskMemStack.h>

#include "FileReport.h"

namespace App5 {

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
  
   struct Config
    {
     Coord magnify  = 32 ;
     
     ColorName back   = Silver ;
     ColorName field  =  White ;
     
     ColorName ball   =   Blue ;
     ColorName spline =    Red ;
     
     Config() {}
    };
  
  private:
  
   Config cfg;

   Pane field;
   Point size;
   
   Point center;
   Coord radius = 1;
   
   bool magnify = false ;
   Point focus;
   
   bool ball          =  true ;
   bool circle        = false ;
   bool spline        = false ;
   bool spline_smooth = false ;
   
  public:
  
   explicit Client(Config cfg_={})
    : cfg(cfg_)
    {
    }
   
   virtual ~Client()
    {
    }
   
   // drawing
   
   virtual void layout(Point size_)
    {
     size=size_;
     
     field=Pane(size.x/4,size.y/4,size.x/2,size.y/2);
    }
   
   virtual void draw(FrameBuf<DesktopColor> buf,bool) const
    {
     if( magnify )
       {
        CommonDrawArt art(buf);
       
        art.grid(cfg.magnify);
        
        art.circle_micro(center,radius,cfg.ball,focus,cfg.magnify);
       }
     else
       {
        CommonDrawArt art(buf);
        
        art.erase(cfg.back);
        
        CommonDrawArt field_art(buf.cut(field));
        
        field_art.erase(cfg.field);
        
        Point a=center-field.getBase();
        
        if( ball )
          {
           field_art.ball(a,radius,cfg.ball);
          }
        
        if( circle )
          {
           field_art.circle(a,radius,cfg.ball);
          }
        
        if( spline )
          {
           field_art.circleSpline(a,radius,cfg.spline);
          }
        
        if( spline_smooth )
          {
           field_art.circleSpline_smooth(a,radius,cfg.spline);
          }
       }
    }
   
   virtual void key(VKey vkey,KeyMod)
    {
     switch( vkey )
       {
        case VKey_F1 :
         {
          ball=!ball;
          
          win->redraw();
         }
        break;
        
        case VKey_F2 :
         {
          circle=!circle;
          
          win->redraw();
         }
        break;
        
        case VKey_F3 :
         {
          spline=!spline;
          
          win->redraw();
         }
        break;
        
        case VKey_F4 :
         {
          spline_smooth=!spline_smooth;
          
          win->redraw();
         }
        break;
       }
    }
   
   virtual void clickLeft(Point point,MouseKey)
    {
     center=point;
     
     win->redraw();
    }

   virtual void clickRight(Point point,MouseKey)
    {
     magnify=true;
     focus=point;
     
     win->redraw();
    }
   
   virtual void upRight(Point,MouseKey)
    {
     if( magnify )
       {
        magnify=false;
       
        win->redraw();
       }
    }

   virtual void move(Point point,MouseKey)
    {
     if( magnify )
       {
        focus=point;
        
        win->redraw();
       }
    }
 
   virtual void leave()
    {
     if( magnify )
       {
        magnify=false;
     
        win->redraw();
       } 
    }

   virtual void wheel(Point,MouseKey,Coord delta)
    {
     if( magnify )
       {
        cfg.magnify=(Coord)Cap<int>(5,cfg.magnify+delta,100);
       
        win->redraw();
       }
     else
       {
        radius=Cap<Coord>(1,radius+delta,1000);
        
        win->redraw();
       }
    }
 };

/* class Application */

class Application : public ApplicationBase
 {
   const CmdDisplay cmd_display;
  
   FileReport report;
   
   DragWindow::Shape::Config cfg;
   
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
      main_win(desktop,cfg,client)
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
 
} // namespace App5
 
 
 


