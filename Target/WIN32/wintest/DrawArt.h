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

namespace CCore {
namespace Video {

/* classes */

class CommonDrawArt;

/* class CommonDrawArt */

class CommonDrawArt
 {
   class SmoothPlot : public FrameBuf<DesktopColor>
    {
     public:
     
      explicit SmoothPlot(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}
      
      void operator () (Point p,DesktopColor color)
       {
        if( p>=Null && p<getSize() ) pixel(p,color);
       }
      
      void operator () (Point p,ColorName cname,unsigned alpha) // 8-bit
       {
        if( !alpha ) return;
        
        if( p>=Null && p<getSize() ) 
          {
           if( alpha>=256 )
             pixel(p,cname);
           else
             DesktopColor::BlendTo(Blender(Clr(alpha),cname),place(p));
          }
       }
    };
  
   class WorkBuf : public FrameBuf<DesktopColor>
    {
      static void Prepare(Coord &a,Coord &b,Coord d);
    
     public:
     
      explicit WorkBuf(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}
      
      template <class Plot>
      void lineY(Coord abx,Coord ay,Coord by,Plot plot); // [a,b)
      
      template <class Plot>
      void lineX(Coord aby,Coord ax,Coord bx,Plot plot); // [a,b)
      
      template <class Plot>
      void line(Point a,Point b,Plot plot); // [a,b)
      
      void lineY(Coord abx,Coord ay,Coord by,DesktopColor color); // [a,b)
      
      void lineX(Coord aby,Coord ax,Coord bx,DesktopColor color); // [a,b)
      
      void line(Point a,Point b,DesktopColor color); // [a,b)
      
      void line_smooth(Point a,Point b,ColorName cname); // [a,b)
    };
  
   WorkBuf buf;
   
  private: 
   
   template <class Plot>
   void path(PtrStepLen<const LPoint> curve,DesktopColor color,Plot plot);
   
   void path(PtrStepLen<const LPoint> curve,DesktopColor color);
   
   void path_micro1(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify);
   
   void path_micro2(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify);
   
   void path_micro3(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify);
   
   void path_micro(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify);
   
   class SmoothPlotMicro
    {
      CommonDrawArt &art;
      Coord magnify;
      
     public:
      
      explicit SmoothPlotMicro(CommonDrawArt &art_,Coord magnify_) : art(art_),magnify(magnify_) {}
      
      void operator () (Point p,DesktopColor color)
       {
        art.gridCell(p,color,magnify);
       }
      
      void operator () (Point p,ColorName cname,unsigned alpha)
       {
        if( !alpha ) return;
        
        if( alpha>=256 )
          {
           art.gridCell(p,cname,magnify);
          } 
        else
          {
           DesktopColor color(White);
          
           color.blend(Clr(alpha),cname);
             
           art.gridCell(p,color,magnify);
          }
       }
    };
   
   void line_smooth_micro(Point a,Point b,ColorName cname,Coord magnify);
   
  public:
  
   CommonDrawArt(const FrameBuf<DesktopColor> &buf_) : buf(buf_) {}
   
   // simple
   
   void pixel(Point p,DesktopColor color);
   
   void erase(DesktopColor color);
  
   void block(Pane pane,DesktopColor color);
   
   void knob(Point p,Coord len,DesktopColor color)
    {
     Coord d=2*len+1;
     
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
   
   void path_smooth(PtrLen<const Point> dots,ColorName cname);

   template <class ... TT>
   void path_smooth(ColorName cname,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     path_smooth(Range_const(temp),cname);
    }
   
   void loop_smooth(PtrLen<const Point> dots,ColorName cname);
   
   template <class ... TT>
   void loop_smooth(ColorName cname,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     loop_smooth(Range_const(temp),cname);
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
   
   void grid(Coord cell);
   
   void gridCell(Point p,DesktopColor color,Coord magnify);
   
   void gridKnob(LPoint p,Coord len,DesktopColor color,Coord magnify);
   
   void curvePath_micro(PtrLen<const Point> dots,DesktopColor color,Point focus,Coord magnify);
   
   void path_smooth_micro(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify);
   
   // fill
   
   void fill(PtrLen<const MilliPoint> border,DesktopColor color);
   
   // stroke
   
   void stroke(PtrLen<const MilliPoint> border,DesktopColor color,Coord width_mpx);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

