/* DrawBuf.h */ 
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

#ifndef CCore_inc_video_DrawBuf_h
#define CCore_inc_video_DrawBuf_h

#include <CCore/inc/video/FrameBuf.h>
#include <CCore/inc/video/Desktop.h>
 
namespace CCore {
namespace Video {

/* classes */

class DrawBuf;

/* class DrawBuf */

class DrawBuf : public FrameBuf<DesktopColor>
 {
  public:
  
   Point origin; // in FrameBuf coord
  
   DrawBuf() {}
   
   DrawBuf(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}
   
   DrawBuf(const FrameBuf<DesktopColor> &buf,Point origin_) : FrameBuf<DesktopColor>(buf),origin(origin_) {}
   
   DrawBuf cut(Pane pane) const;
   
   DrawBuf cutRebase(Pane pane) const;
   
   // to FrameBuf coord
   
   template <class T>
   T map(T obj) const { return obj+origin; }
   
   Coord mapX(Coord x) const { return IntAdd(x,origin.x); }
   
   Coord mapY(Coord y) const { return IntAdd(y,origin.y); }
   
   class Mapper
    {
      Point origin;
      
     public:
      
      explicit Mapper(Point origin_) : origin(origin_) {}
     
      template <class T>
      T operator () (T obj) const { return obj+origin; }
    };
   
   Mapper getMapper() const { return Mapper(origin); }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

