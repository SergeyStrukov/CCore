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

template <class T> struct PtrDeltaLen;

struct LPoint;

class LineDriver;

class CommonDrawArt;

/* struct PtrDeltaLen<T> */

template <class T> 
struct PtrDeltaLen
 {
 };

/* struct LPoint */

struct LPoint : BasePoint<LPoint,sint64>
 {
  using BasePoint<LPoint,sint64>::BasePoint;
  
  LPoint() {}
  
  LPoint(Point p) : BasePoint<LPoint,sint64>(p.x,p.y) {}
 };

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
   
   static int RShift(sint64 a,unsigned s) { return int( ( a+(1<<(s-1)) )>>s ); }
   
   static Point RShift(LPoint a,unsigned s) { return Point(RShift(a.x,s),RShift(a.y,s)); }
   
   static const unsigned Precision = 16 ;
   
   static LPoint LShift(Point p,unsigned s) { return LPoint(p)<<s; }
   
   static unsigned Diameter(sint64 a,sint64 b);
   
   static unsigned Diameter(LPoint a,LPoint b);
   
   static unsigned Diameter(const LPoint *ptr,ulen count,ulen delta);
   
   static sint64 Spline(sint64 a,sint64 b,sint64 c,sint64 d);

   static LPoint Spline(LPoint a,LPoint b,LPoint c,LPoint d);
   
  private: 
   
   void path(const LPoint *ptr,ulen count,ulen delta,DesktopColor color);
   
   static const unsigned MaxLevel = 10 ;
   
   static const unsigned MaxDiameter = 5 ;
   
   struct SplineBuf : NoCopy
    {
     static const ulen Len = (1u<<MaxLevel) ; 
     
     LPoint buf[3*Len+1];
     unsigned level;
     
     void spline(LPoint a,LPoint b,LPoint c,LPoint d,LPoint p,LPoint q,LPoint r);
     
     const LPoint * getPtr() const { return buf+Len; }
     
     ulen getCount() const { return (1u<<level)+1; }
     
     ulen getDelta() const { return 1u<<(MaxLevel-level); }
    };

   void curve(SplineBuf &buf,LPoint a,LPoint b,LPoint c,LPoint d,LPoint p,LPoint q,LPoint r,DesktopColor color);
   
  public:
  
   CommonDrawArt(const FrameBuf<DesktopColor> &buf_) : buf(buf_) {}
   
   // simple methods
   
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
   
   // fill
   
   void fill(PtrLen<const MilliPoint> border,DesktopColor color);
   
   // stroke
   
   void stroke(PtrLen<const MilliPoint> border,DesktopColor color,int width_mpx);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

