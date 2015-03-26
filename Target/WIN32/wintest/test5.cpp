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

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/TaskMemStack.h>

#include <CCore/inc/video/ApplicationBase.h>

#include "DragWindow.h"
#include "DrawArt.h"

namespace App5 {

/* using */ 

using namespace CCore;
using namespace CCore::Video;

/* functions */

template <class A>
void Remove(A &obj,ulen ind)
 {
  auto r=Range(obj).part(ind);
  
  for(; r.len>1 ;++r) r[0]=r[1];
  
  obj.shrink_one();
 }

template <class A,class T>
void Insert(A &obj,ulen ind,T item)
 {
  if( obj.getLen() )
    {
     obj.append_default();

     auto r=RangeReverse(Range(obj).part(ind+1));
     
     for(; r.len>1 ;++r) r[0]=r[1];
     
     r[0]=item;
    }
  else
    {
     obj.append_copy(item);
    }
 }

/* classes */

class FileReport;

class Client; 

class Application;

/* class FileReport */

class FileReport : public ReportException
 {
   PrintFile out;
   
  private: 
 
   virtual void print(StrLen str)
    {
     Putobj(out,str);
    }
   
   virtual void end()
    {
     Printf(out,"\n\n#;\n\n",TextDivider());
    }
   
  public:
  
   FileReport() : out("exception-log.txt") {}
   
   ~FileReport() {}
   
   bool show() { return true; }
 };

/* class Client */

class Client : public DragClient
 {
   DynArray<Point> dots;
   DynArray<Point> dots_based;
   Pane field;
   Point size;
   
   enum DrawType
    {
     DrawPath,
     DrawLoop,
     DrawCurvePath,
     DrawCurveLoop,
     DrawSolid,
     DrawCurveSolid
    };
   
   DrawType draw_type = DrawPath ;
   
   ulen selected = 0 ;
   
  private: 
  
   void cross(CommonDrawArt &art,Point p,DesktopColor color) const
    {
     art.path(color,Point(p.x,0),Point(p.x,size.y-1));
     art.path(color,Point(0,p.y),Point(size.x-1,p.y));
    }
   
   void select(Point point)
    {
     if( selected<dots.getLen() )
       {
        dots[selected]=point;
        dots_based[selected]=point-field.getBase();
        
        win->redraw();
       }
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
     
     for(ulen i=0,len=dots.getLen(); i<len ;i++) dots_based[i]=dots[i]-field.getBase();
    }
   
   virtual void draw(FrameBuf<DesktopColor> buf,bool) const
    {
     CommonDrawArt art(buf);
     
     art.erase(Silver);
     
     art.block(field,White);
     
     if( selected<dots.getLen() ) cross(art,dots[selected],Green);
     
     CommonDrawArt field_art(buf.cut(field));
     
     switch( draw_type )
       {
        case DrawPath       : field_art.path(Range_const(dots_based),Red); break;
        case DrawLoop       : field_art.loop(Range_const(dots_based),Red); break;
        case DrawCurvePath  : field_art.curvePath(Range_const(dots_based),Red); break;
        case DrawCurveLoop  : field_art.curveLoop(Range_const(dots_based),Red); break;
        case DrawSolid      : field_art.solid(Range_const(dots_based),Red); break;
        case DrawCurveSolid : field_art.curveSolid(Range_const(dots_based),Red); break;
       }
    }
   
   virtual void key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_F1 :
         {
          draw_type=DrawPath;
          
          win->redraw();
         }
        break;
        
        case VKey_F2 :
         {
          draw_type=DrawLoop;
          
          win->redraw();
         }
        break; 
        
        case VKey_F3 :
         {
          draw_type=DrawCurvePath;
          
          win->redraw();
         }
        break; 
        
        case VKey_F4 :
         {
          draw_type=DrawCurveLoop;
          
          win->redraw();
         }
        break; 
        
        case VKey_F5 :
         {
          draw_type=DrawSolid;
          
          win->redraw();
         }
        break; 
        
        case VKey_F6 :
         {
          draw_type=DrawCurveSolid;
          
          win->redraw();
         }
        break;
        
        case VKey_Tab :
         {
          if( ulen len=dots.getLen() )
            {
             if( kmod&KeyMod_Shift )
               {
                if( selected ) selected--; else selected=len-1;
               }
             else
               {
                if( ++selected >= len ) selected=0;
               }
            
             win->redraw();
            }
         }
        break;
        
        case VKey_Home :
         {
          if( dots.getLen() )
            {
             selected=0;
            
             win->redraw();
            }
         }
        break; 
        
        case VKey_Delete :
         {
          ulen ind=selected;
          ulen len=dots.getLen();
          
          if( ind<len )
            {
             Remove(dots,ind);
             Remove(dots_based,ind);
             
             if( ind==len-1 && ind>0 ) selected=ind-1;
            
             win->redraw();
            }
         }
        break; 
       }
    }
   
   virtual void clickLeft(Point point,MouseKey mkey)
    {
     if( mkey&MouseKey_Shift )
       {
        dots.reserve(1);
        dots_based.reserve(1);
       
        Insert(dots,selected,point);
        Insert(dots_based,selected,point-field.getBase());
        
        if( dots.getLen()>1 ) selected++;
        
        win->redraw();
       }
     else
       {
        select(point);
       }
    }

   virtual void move(Point point,MouseKey mkey)
    {
     if( mkey&MouseKey_Left )
       {
        if( win->getToken() ) return;
        
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
     TaskMemStack tms;
    
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
 
 
 


