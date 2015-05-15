/* DrawTools.h */
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

#ifndef CCore_inc_video_DragTools_h
#define CCore_inc_video_DragTools_h

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {

/* enum SolidFlag */

enum SolidFlag
 {
  SolidOdd,
  SolidAll
 };

/* classes */

struct CircleSpline;

struct PaneBorder;

struct PaneSub;

/* struct CircleSpline */

struct CircleSpline
 {
  Point buf[12];
  
  CircleSpline(Point center,Coord radius);
  
  PtrLen<const Point> get() const { return Range(buf); }
 };

/* struct PaneBorder */

struct PaneBorder
 {
  Point buf[4];
  
  explicit PaneBorder(Pane pane);
  
  Point topLeft() const { return buf[0]; }
  
  Point bottomLeft() const { return buf[1]; }
  
  Point bottomRight() const { return buf[2]; }
  
  Point topRight() const { return buf[3]; }
  
  PtrLen<const Point> get() const { return Range(buf); }
 };

/* struct PaneSub */

struct PaneSub 
 {
  Pane top;
  Pane bottom;
  Pane left;
  Pane right;
  
  PaneSub(Pane outer,Pane inner);
 };

} // namespace Video
} // namespace CCore

#endif


