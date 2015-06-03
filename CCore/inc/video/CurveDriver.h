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
   
   static uLCoord Fineness(PtrStepLen<const LPoint> dots);
   
   static LCoord Spline(LCoord a,LCoord b,LCoord c,LCoord d);
 
   static LPoint Spline(LPoint a,LPoint b,LPoint c,LPoint d);
   
   static uLCoord PointDist(LPoint a,LPoint b);

  private:
   
   unsigned max_fineness;
   
   LPoint buf[3*Len+1];
   unsigned level = 0 ;
   
   LPoint e;
  
  private:
   
   void spline();
   
   void spline(LPoint a,LPoint b,LPoint c,LPoint d,LPoint p,LPoint q,LPoint r);
   
  public:
   
   explicit CurveDriver(unsigned max_fineness_=5) : max_fineness(max_fineness_) {}
  
   void spline(LPoint a,LPoint b,LPoint c,LPoint d);
   
   void spline(LPoint a,LPoint b,LPoint c,LPoint d,LPoint e,LPoint f);
   
   void shift(LPoint f);
   
   void shift();
   
   PtrStepLen<const LPoint> getCurve() const { return {buf+Len,1u<<(MaxLevel-level),(1u<<level)+1}; }
 };

} // namespace DrawAlgo
} // namespace Video
} // namespace CCore
 
#endif
 

