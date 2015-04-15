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

/* enum SolidFlag */

enum SolidFlag
 {
  SolidOdd,
  SolidAll
 };

/* classes */

struct Segment;

struct CircleSpline;

class CommonDrawArt;

/* struct CircleSpline */

struct CircleSpline
 {
  Point buf[12];
  
  CircleSpline(Point center,Coord radius);
  
  PtrLen<const Point> get() const { return Range(buf); }
 };

/* class CommonDrawArt */

class CommonDrawArt
 {
   class SmoothPlot : public FrameBuf<DesktopColor>
    {
     public:
     
      explicit SmoothPlot(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}
      
      void test(LPoint,Coord,DesktopColor) {}
      
      void operator () (Point p,DesktopColor color)
       {
        if( p>=Null && p<getSize() ) pixel(p,color);
       }
      
      void operator () (Point p,ColorName cname,unsigned alpha)
       {
        if( !alpha ) return;
        
        if( p>=Null && p<getSize() ) 
          {
           if( alpha>=(1u<<ClrBits) )
             pixel(p,cname);
           else
             DesktopColor::BlendTo(Blender(Clr(alpha),cname),place(p));
          }
       }
    };
   
   class HPlot : public FrameBuf<DesktopColor>
    {
     public:
     
      explicit HPlot(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}
      
      void operator () (Point a,DesktopColor color)
       {
        if( getPane().contains(a) ) pixel(a,color);
       }
      
      void operator () (Coord y,Coord a,Coord b,DesktopColor color) // [a,b]
       {
        if( y<0 || y>=dy ) return;
        
        if( a>b ) Swap(a,b);
        
        if( a<0 ) a=0;

        if( b>=dx ) b=dx-1;
        
        if( a>b ) return;
        
        Raw *ptr=place(Point(a,y));
        
        for(; a<b ;a++,ptr=NextX(ptr)) color.copyTo(ptr);
        
        color.copyTo(ptr);
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
   
   template <class Plot>
   void path_smooth(PtrStepLen<const LPoint> curve,ColorName cname,Plot plot);
   
   void path_smooth(PtrStepLen<const LPoint> curve,ColorName cname);
   
  private: 
   
   static const Coord ProbeDisp = 6 ;
   static const Coord GridKnobBigLen = 5 ;
   static const Coord GridKnobLen = 3 ;
   
   static const ColorName GridBack = White ;
   static const ColorName GridLine = Blue ;
   static const ColorName GridKnob = Black ;
   static const ColorName GridBaseline = Blue ;
   
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
      
      void test(LPoint p,Coord len,DesktopColor color)
       {
        art.gridKnob(p,len,color,magnify);
       }
      
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
           DesktopColor color=art.probeCell(p,magnify);
          
           color.blend(Clr(alpha),cname);
             
           art.gridCell(p,color,magnify);
          }
       }
    };
   
   void line_smooth_micro(Point a,Point b,ColorName cname,Coord magnify);
   
   void path_smooth_micro(PtrStepLen<const LPoint> curve,ColorName cname,Coord magnify);
   
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
   
   // path
   
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
   
   // path smooth
   
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
   
   void curvePath_smooth(PtrLen<const Point> dots,ColorName cname);
   
   template <class ... TT>
   void curvePath_smooth(ColorName cname,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     curvePath_smooth(Range_const(temp),cname);
    }
   
   void curveLoop_smooth(PtrLen<const Point> dots,ColorName cname);
   
   template <class ... TT>
   void curveLoop_smooth(ColorName cname,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     curveLoop_smooth(Range_const(temp),cname);
    }
   
   // solid
   
   void solid(PtrLen<const Point> dots,SolidFlag flag,DesktopColor color);
   
   template <class ... TT>
   void solid(SolidFlag flag,DesktopColor color,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     solid(Range_const(temp),flag,color);
    }
   
   void curveSolid(PtrLen<const Point> dots,SolidFlag flag,DesktopColor color);
   
   template <class ... TT>
   void curveSolid(SolidFlag flag,DesktopColor color,TT ... tt)
    {
     Point temp[sizeof ... (TT)]={ tt... };
     
     curveSolid(Range_const(temp),flag,color);
    }
   
   // circle
   
   void ball(Point center,Coord radius,DesktopColor color);
   
   void ballSpline(Point center,Coord radius,DesktopColor color);
   
   void circle(Point center,Coord radius,DesktopColor color);
   
   void circleSpline(Point center,Coord radius,DesktopColor color);
   
   void circleSpline_smooth(Point center,Coord radius,ColorName cname);
   
   // special
   
   void grid(Coord cell);
   
   void gridCell(Point p,DesktopColor color,Coord magnify);
   
   DesktopColor probeCell(Point p,Coord magnify);
   
   void gridKnob(LPoint p,Coord len,DesktopColor color,Coord magnify);
   
   void curvePath_micro(PtrLen<const Point> dots,DesktopColor color,Point focus,Coord magnify);
   
   void path_smooth_micro(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify);
   
   void curvePath_smooth_micro(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify);
   
   void circle_micro(Point center,Coord radius,DesktopColor color,Point focus,Coord magnify);
   
   // fill
   
   void fill(PtrLen<const MilliPoint> border,DesktopColor color);
   
   // stroke
   
   void stroke(PtrLen<const MilliPoint> border,DesktopColor color,Coord width_mpx);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

