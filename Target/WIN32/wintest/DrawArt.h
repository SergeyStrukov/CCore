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
   
   const unsigned lim;
   const unsigned lim2;
   
   unsigned delta = 0 ;
   bool flag = false ;
   
  public:
  
   LineDriver(unsigned sx_,unsigned sy_) : sx(sx_),sy(sy_),lim(sx_-sy_),lim2(sx_/2) {} // sx >= sy > 0
   
   bool step()
    {
     bool ret=false;
     
     if( delta<lim ) 
       {
        bool next_flag=( (delta+=sy)>lim2 );
        
        ret=( flag!=next_flag );
        
        flag=next_flag;
       } 
     else
       {
        bool next_flag=( (delta-=lim)>lim2 );
        
        ret=( flag==next_flag );
        
        flag=next_flag;
       }
     
     return ret;
    }
 };

/* class CommonDrawArt */

class CommonDrawArt
 {
   class WorkBuf : public FrameBuf<DesktopColor>
    {
      static void Prepare(int &a,int &b,int d);
     
      static unsigned Shift(int a,int b) { return (unsigned)b-(unsigned)a; }
      
     public:
     
      explicit WorkBuf(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}
      
      void lineY(int abx,int ay,int by,DesktopColor color); // [a,b)
      
      void lineX(int aby,int ax,int bx,DesktopColor color); // [a,b)
      
      void line(Point a,Point b,DesktopColor color); // [a,b)
    };
  
   WorkBuf buf;
   
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
   
   // fill
   
   void fill(PtrLen<const MilliPoint> border,DesktopColor color);
   
   // stroke
   
   void stroke(PtrLen<const MilliPoint> border,DesktopColor color,int width_mpx);
 };

} // namespace Video
} // namespace CCore
 
#endif
 

