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

#include "DragWindow.h"
#include "DrawArt.h"

#include <CCore/inc/Array.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/TaskMemStack.h>

#include "FileReport.h"

namespace App5 {

/* using */ 

using namespace App;
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

class Client; 

class Application;

/* class Client */

class Client : public DragClient
 {
  public: 
  
   struct Config
    {
     Coord knob_len =  3 ;
     Coord magnify  = 32 ;
    
     ColorName back  = Silver ;
     ColorName field =  White ;
     ColorName knob  =  Black ;
     ColorName cross =  Green ;
     ColorName path  =    Red ;
     
     Config() {}
    };
  
  private:
  
   Config cfg;

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
     DrawCurveSolid,
     DrawPathSmooth,
     DrawLoopSmooth,
     DrawCurvePathSmooth,
     DrawCurveLoopSmooth
    };
   
   DrawType draw_type = DrawCurvePathSmooth ;
   
   ulen selected = 0 ;
   
   bool magnify = false ;
   Point focus;
   
   mutable PrintFile out;
   
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
   
   static const char * GetTextDesc(DrawType draw_type)
    {
     switch( draw_type )
       {
        case DrawPath            : return "Path"; 
        case DrawLoop            : return "Loop"; 
        case DrawCurvePath       : return "CurvePath"; 
        case DrawCurveLoop       : return "CurveLoop"; 
        case DrawSolid           : return "Solid"; 
        case DrawCurveSolid      : return "CurveSolid";
        case DrawPathSmooth      : return "PathSmooth";
        case DrawLoopSmooth      : return "LoopSmooth";
        case DrawCurvePathSmooth : return "CurvePathSmooth";
        case DrawCurveLoopSmooth : return "CurveLoopSmooth";
        
        default: return "???";
       }
    }
   
  public:
  
   explicit Client(Config cfg_={})
    : cfg(cfg_),
      out("time.txt")
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
     if( magnify )
       {
        CommonDrawArt art(buf);
        
        art.grid(cfg.magnify);
        
        switch( draw_type )
          {
           case DrawCurvePath       : art.curvePath_micro(Range_const(dots),cfg.path,focus,cfg.magnify); break;
           
           case DrawPathSmooth      : art.path_smooth_micro(Range_const(dots),cfg.path,focus,cfg.magnify); break;
           
           case DrawCurvePathSmooth : art.curvePath_smooth_micro(Range_const(dots),cfg.path,focus,cfg.magnify); break;
          }
       }
     else
       {
        CommonDrawArt art(buf);
        
        art.erase(cfg.back);
        
        art.block(field,cfg.field);
        
        for(auto p : dots ) art.knob(p,cfg.knob_len,cfg.knob);
        
        if( selected<dots.getLen() ) cross(art,dots[selected],cfg.cross);
        
        CommonDrawArt field_art(buf.cut(field));
        
        ClockTimer timer;
        
        switch( draw_type )
          {
           case DrawPath            : field_art.path(Range_const(dots_based),cfg.path); break;
           case DrawLoop            : field_art.loop(Range_const(dots_based),cfg.path); break;
           case DrawCurvePath       : field_art.curvePath(Range_const(dots_based),cfg.path); break;
           case DrawCurveLoop       : field_art.curveLoop(Range_const(dots_based),cfg.path); break;
           case DrawSolid           : field_art.solid(Range_const(dots_based),cfg.path); break;
           case DrawCurveSolid      : field_art.curveSolid(Range_const(dots_based),cfg.path); break;
           case DrawPathSmooth      : field_art.path_smooth(Range_const(dots_based),cfg.path); break;
           case DrawLoopSmooth      : field_art.loop_smooth(Range_const(dots_based),cfg.path); break;
           case DrawCurvePathSmooth : field_art.curvePath_smooth(Range_const(dots_based),cfg.path); break;
           case DrawCurveLoopSmooth : field_art.curveLoop_smooth(Range_const(dots_based),cfg.path); break;
          }
        
        auto time=timer.get();
        
        Printf(out,"#;[#;] #;\n",GetTextDesc(draw_type),dots.getLen(),time);
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
          draw_type=DrawPathSmooth;
          
          win->redraw();
         }
        break; 
        
        case VKey_F6 :
         {
          draw_type=DrawLoopSmooth;
          
          win->redraw();
         }
        break;
        
        case VKey_F7 :
         {
          draw_type=DrawCurvePathSmooth;
          
          win->redraw();
         }
        break; 
        
        case VKey_F8 :
         {
          draw_type=DrawCurveLoopSmooth;
          
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

   virtual void move(Point point,MouseKey mkey)
    {
     if( magnify )
       {
        focus=point;
        
        win->redraw();
       }
     else
       {
        if( mkey&MouseKey_Left )
          {
           if( win->getToken() ) return;
           
           select(point);
          }
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
 
   virtual void wheel(Point,MouseKey,int delta)
    {
     if( magnify )
       {
        cfg.magnify=(Coord)Cap<int>(5,cfg.magnify+delta,100);
       
        win->redraw();
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
  
  cmd_display=CmdDisplay_Maximized;
  
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
 
 
 


