/* test7.cpp */
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

namespace App7 {

/* using */ 

using namespace App;
using namespace CCore::Video;

/* classes */

class Client; 

class Application;

/* class Client */

class Client : public DragClient
 {
   char text[TextBufLen];
   ulen len = 0 ;
   
   Point size;
   
   Pane pane[4][4];
   
   Font font;
   
   Point base;
   
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
     
     Coord dx=(2*size.x)/13;
     Coord dy=size.y/9;
     
     Coord x0=dx/2;
     Coord y0=dy;
     
     Coord delta_x=dx+dx/2;
     Coord delta_y=2*dy;
     
     if( dx>0 && dy>0 )
       {
        for(int i=0; i<4 ;i++)
          for(int j=0; j<4 ;j++)
            {
             pane[i][j]=Pane(x0+i*delta_x,y0+j*delta_y,dx,dy);
            }
       }
     else
       {
        for(int i=0; i<4 ;i++)
          for(int j=0; j<4 ;j++)
            {
             pane[i][j]=Empty;
            }
       }
    }
   
   virtual void draw(FrameBuf<DesktopColor> buf,bool) const
    {
     CommonDrawArt art(buf);
     
     art.erase(Green);
     
     AlignX align_x[4]={AlignX::Left,AlignX::Center,AlignX::Right,AlignX::Given};
     AlignY align_y[4]={AlignY::Top,AlignY::Center,AlignY::Bottom,AlignY::Given};
     
     for(int i=0; i<4 ;i++)
       for(int j=0; j<4 ;j++)
         {
          art.block(pane[i][j],White);
          
          TextPlace place(align_x[i],align_y[j]);
          
          place.x=base.x;
          place.y=base.y;
          
          font->text(buf.cut(pane[i][j]),place,StrLen(text,len),Black);
         }
    }
   
   virtual void putch(char ch)
    {
     if( ch=='\b' )
       {
        if( len ) len--;
       }
     else
       {
        if( len<DimOf(text) ) text[len++]=ch;
       }
     
     win->redraw();
    }

   virtual void clickLeft(Point point,MouseKey)
    {
     base=point-pane[3][3].getBase();
     
     win->redraw();
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
     
     main_win.createMain(cmd_display,max_size,String("test7"));
    }
   
   virtual void beforeLoop()
    {
     // do nothing
    }
   
   virtual void afterLoop()
    {
     // do nothing
    }
   
   virtual void final()
    {
     // do nothing
    }
   
  public: 
   
   explicit Application(CmdDisplay cmd_display_)
    : ApplicationBase(DefaultTickPeriod,DefaultDesktop),
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
 
} // namespace App7
 
 
 


