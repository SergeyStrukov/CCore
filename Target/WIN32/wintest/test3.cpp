/* test3.cpp */
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

#include "DragWindow.h"
#include "DrawArt.h"

#include "FileReport.h"

namespace App3 {

/* using */ 

using namespace App;
using namespace CCore::Video;

/* classes */

class Client; 

class Application;

/* class Client */

class Client : public DragClient
 {
   Point a;
   Point b;
   Pane field;
   Point size;
   
   bool select_a = true ;
   
  private: 
  
   void cross(CommonDrawArt &art,Point p,DesktopColor color) const
    {
     art.path(color,Point(p.x,0),Point(p.x,size.y-1));
     art.path(color,Point(0,p.y),Point(size.x-1,p.y));
    }
   
   void select(Point point)
    {
     if( select_a )
       a=point;
     else
       b=point;
     
     win->redraw();
    }
   
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
     size=size_;
     
     field=Pane(size.x/4,size.y/4,size.x/2,size.y/2);
    }
   
   virtual void draw(FrameBuf<DesktopColor> buf,bool) const
    {
     CommonDrawArt art(buf);
     
     art.erase(Silver);
     
     art.block(field,White);
     
     if( select_a )
       cross(art,a,Blue);
     else
       cross(art,b,Green);
     
     CommonDrawArt(buf.cut(field)).path(Red,a-field.getBase(),b-field.getBase());
    }
   
   virtual void key(VKey vkey,KeyMod)
    {
     if( vkey==VKey_Tab )
       {
        select_a=!select_a;
        
        win->redraw();
       }
    }
   
   virtual void clickLeft(Point point,MouseKey)
    {
     select(point);
    }

   virtual void move(Point point,MouseKey mkey)
    {
     if( mkey&MouseKey_Left )
       {
        select(point);
       }
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
   
   virtual void do_tick()
    {
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
     Application app(cmd_display);
    
     ret=app.run();
    }
  catch(CatchType)
    {
     return 1;
    }
  
  return ret;
 }
 
} // namespace App3
 
 
 


