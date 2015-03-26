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

namespace CCore {
namespace Video {

/* classes */

class LineDriver;

class CommonDrawArt;

/* class LineDriver */

class LineDriver
 {
   const unsigned sx;
   const unsigned sy;
   
   const unsigned ty;
   const unsigned lim;
   
   unsigned delta = 0 ;
   bool flag = false ;
  
  private:
   
   bool do_step(unsigned s,unsigned t) // t == sx-s
    {
     bool ret=false;
     
     if( delta<t ) 
       {
        bool next_flag=( (delta+=s)>lim );
        
        ret=( flag!=next_flag );
        
        flag=next_flag;
       } 
     else
       {
        bool next_flag=( (delta-=t)>lim );
        
        ret=( flag==next_flag );
        
        flag=next_flag;
       }
     
     return ret;
    }

   bool do_step(unsigned s) { return do_step(s,sx-s); }
   
  public:
  
   LineDriver(unsigned sx_,unsigned sy_) : sx(sx_),sy(sy_),ty(sx_-sy_),lim(sx_/2) {} // sx >= sy > 0
   
   bool step() { return do_step(sy,ty); }
   
   unsigned step(unsigned count);
   
   struct Result
    {
     unsigned off;
     unsigned lim;
     
     bool operator + () const { return off<lim; }
     
     bool operator ! () const { return off>=lim; }
    };
   
   static Result Inf(Result a,Result b) { return {Max(a.off,b.off),Min(a.lim,b.lim)}; }
   
   Result clip(int x,int y,int ex,int ey,int dx,int dy) const;

   unsigned clipToX(unsigned y) const;
   
   Result clipToX(Result clip_y) const;
   
   static Result Clip(int x,int e,int d);
 };

/* class CommonDrawArt */

class CommonDrawArt
 {
   class WorkBuf : public FrameBuf<DesktopColor>
    {
      static void Prepare(int &a,int &b,int d);
      
      static bool DistDir(int &e,unsigned &s,int a,int b);
     
     public:
     
      explicit WorkBuf(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}
      
      void lineY(int abx,int ay,int by,DesktopColor color); // [a,b)
      
      void lineX(int aby,int ax,int bx,DesktopColor color); // [a,b)
      
      void line(Point a,Point b,DesktopColor color); // [a,b)
    };
  
   WorkBuf buf;
   
  private: 
   
   static Point Double(Point a) { return Point(2*a.x,2*a.y); }
   
   static Point LShift(Point a,unsigned level) { return Point(a.x<<level,a.y<<level); }
   
   static Point RShift(Point a,unsigned level) { return Point(a.x>>level,a.y>>level); }
   
   static int Spline(int a,int b,int c,int d);

   static Point Spline(Point a,Point b,Point c,Point d);
   
   static unsigned Diameter(int a,int b);
   
   static unsigned Diameter(Point a,Point b);
   
   static unsigned Diameter(PtrLen<const Point> dots);
   
  private: 
   
   void curvePath(PtrLen<const Point> dots,unsigned level,DesktopColor color);
   
  public:
  
   CommonDrawArt(const FrameBuf<DesktopColor> &buf_) : buf(buf_) {}
   
   // simple methods
   
   void pixel(Point p,DesktopColor color);
   
   void erase(DesktopColor color);
  
   void block(Pane pane,DesktopColor color);
   
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
   
   // fill
   
   void fill(PtrLen<const MilliPoint> border,DesktopColor color);
   
   // stroke
   
   void stroke(PtrLen<const MilliPoint> border,DesktopColor color,int width_mpx);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

