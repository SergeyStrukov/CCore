/* DrawArt.h */ 
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

#ifndef CCore_inc_video_DrawArt_h
#define CCore_inc_video_DrawArt_h

#include <CCore/inc/video/FrameBuf.h>
#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/TaskMemStack.h>

//#include <CCore/inc/video/LPoint.h>
#include "LPoint.h"

namespace CCore {
namespace Video {

/* classes */

class CommonDrawArt;

/* class CommonDrawArt */

class CommonDrawArt
 {
   class WorkBuf : public FrameBuf<DesktopColor>
    {
      static void Prepare(int &a,int &b,int d);
    
     public:
     
      explicit WorkBuf(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}
      
      template <class Plot>
      void lineY(int abx,int ay,int by,Plot plot); // [a,b)
      
      template <class Plot>
      void lineX(int aby,int ax,int bx,Plot plot); // [a,b)
      
      template <class Plot>
      void line(Point a,Point b,Plot plot); // [a,b)
      
      void lineY(int abx,int ay,int by,DesktopColor color); // [a,b)
      
      void lineX(int aby,int ax,int bx,DesktopColor color); // [a,b)
      
      void line(Point a,Point b,DesktopColor color); // [a,b)
    };
  
   WorkBuf buf;
   
  private: 
   
   template <class Plot>
   void path(PtrStepLen<const LPoint> curve,DesktopColor color,Plot plot);
   
   void path(PtrStepLen<const LPoint> curve,DesktopColor color);
   
   void path_micro1(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify);
   
   void path_micro2(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify);
   
   void path_micro3(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify);
   
   void path_micro(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify);
   
  public:
  
   CommonDrawArt(const FrameBuf<DesktopColor> &buf_) : buf(buf_) {}
   
   // simple
   
   void pixel(Point p,DesktopColor color);
   
   void erase(DesktopColor color);
  
   void block(Pane pane,DesktopColor color);
   
   void knob(Point p,int len,DesktopColor color)
    {
     int d=2*len+1;
     
     block(Pane(p.x-len,p.y-len,d,d),color);
    }
   
   void path(PtrLen<const Point> dots,DesktopColor color);
   
   template <class ... TT>
   void path(DesktopColor color,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     path(Range_const(temp),color);
    }

   void loop(PtrLen<const Point> dots,DesktopColor color);
   
   template <class ... TT>
   void loop(DesktopColor color,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     loop(Range_const(temp),color);
    }
   
   void curvePath(PtrLen<const Point> dots,DesktopColor color);
   
   template <class ... TT>
   void curvePath(DesktopColor color,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     curvePath(Range_const(temp),color);
    }
   
   void curveLoop(PtrLen<const Point> dots,DesktopColor color);
   
   template <class ... TT>
   void curveLoop(DesktopColor color,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     curveLoop(Range_const(temp),color);
    }
   
   void solid(PtrLen<const Point> dots,DesktopColor color);
   
   template <class ... TT>
   void solid(DesktopColor color,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     solid(Range_const(temp),color);
    }
   
   void curveSolid(PtrLen<const Point> dots,DesktopColor color);
   
   template <class ... TT>
   void curveSolid(DesktopColor color,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     curveSolid(Range_const(temp),color);
    }
   
   // special
   
   void grid(int cell);
   
   void gridCell(Point p,DesktopColor color,int magnify);
   
   void curvePath_micro(PtrLen<const Point> dots,DesktopColor color,Point focus,int magnify);
   
   // fill
   
   void fill(PtrLen<const MilliPoint> border,DesktopColor color);
   
   // stroke
   
   void stroke(PtrLen<const MilliPoint> border,DesktopColor color,int width_mpx);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

