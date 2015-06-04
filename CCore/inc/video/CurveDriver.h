/* CurveDriver.h */ 
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

#ifndef CCore_inc_video_CurveDriver_h
#define CCore_inc_video_CurveDriver_h

#include <CCore/inc/video/Point.h>
 
namespace CCore {
namespace Video {
namespace DrawAlgo {

/* classes */

class CurveDriver;

/* class CurveDriver */

class CurveDriver : NoCopy
 {
   static const unsigned MaxLevel = 10 ;
   
   static const unsigned Len = (1u<<MaxLevel) ;
   
   static uMCoord PointDist(MPoint a,MPoint b);

   static uMCoord Fineness(PtrStepLen<const MPoint> dots);
   
   static MCoord Spline(MCoord a,MCoord b,MCoord c,MCoord d);
 
   static MPoint Spline(MPoint a,MPoint b,MPoint c,MPoint d);
   
  private:
   
   unsigned max_fineness;
   
   MPoint buf[3*Len+1];
   unsigned level = 0 ;
   
   MPoint e;
  
  private:
   
   void spline();
   
   void spline(MPoint a,MPoint b,MPoint c,MPoint d,MPoint p,MPoint q,MPoint r);
   
  public:
   
   explicit CurveDriver(unsigned max_fineness_=5) : max_fineness(max_fineness_) {}
  
   void spline(MPoint a,MPoint b,MPoint c,MPoint d); // a - b
   
   void spline(MPoint a,MPoint b,MPoint c,MPoint d,MPoint e,MPoint f); // c - d
   
   void shift(MPoint f);
   
   void shift();
   
   PtrStepLen<const MPoint> getCurve() const { return {buf+Len,1u<<(MaxLevel-level),(1u<<level)+1}; }
 };

} // namespace DrawAlgo
} // namespace Video
} // namespace CCore
 
#endif
 

