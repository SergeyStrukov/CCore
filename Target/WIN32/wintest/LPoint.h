/* LPoint.h */ 
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

#ifndef CCore_inc_video_LPoint_h
#define CCore_inc_video_LPoint_h

#include <CCore/inc/video/Point.h>
 
namespace CCore {
namespace Video {

/* classes */

struct LPoint;

/* struct LPoint */

struct LPoint : BasePoint<LPoint,sint64>
 {
  static const unsigned Precision = 16 ;
 
  static sint64 LShift(int a,unsigned s=Precision) { return IntLShift((sint64)a,s); }
 
  static int RShift(sint64 a,unsigned s=Precision) { return (int)IntRShift(a+(1<<(s-1)),s); }
  
  // constructors
  
  using BasePoint<LPoint,sint64>::BasePoint;
  
  LPoint() {}
  
  LPoint(Point p) : BasePoint<LPoint,sint64>(LShift(p.x),LShift(p.y)) {}
  
  LPoint(MilliPoint p) : BasePoint<LPoint,sint64>(LShift(p.x,Precision-MilliPoint::Precision),LShift(p.y,Precision-MilliPoint::Precision)) {}
  
  // methods
  
  Point toPoint(unsigned s=Precision) const { return Point(RShift(x,s),RShift(y,s)); }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

