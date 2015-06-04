/* CurveDriver.cpp */ 
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
 
#include <CCore/inc/video/CurveDriver.h>
 
namespace CCore {
namespace Video {
namespace DrawAlgo {

/* class CurveDriver */

uMCoord CurveDriver::PointDist(MPoint a,MPoint b)
 {
  return Max(IntAbs(a.x,b.x),IntAbs(a.y,b.y))>>MPoint::Precision;
 }

uMCoord CurveDriver::Fineness(PtrStepLen<const MPoint> dots)
 {
  uMCoord ret=0;
  
  for(; dots.len>1 ;++dots) Replace_max(ret,PointDist(dots[0],dots[1]));
  
  return ret; 
 }

MCoord CurveDriver::Spline(MCoord a,MCoord b,MCoord c,MCoord d)
 {
  return (b+c)/2+(b+c-a-d)/16;
 }

MPoint CurveDriver::Spline(MPoint a,MPoint b,MPoint c,MPoint d)
 {
  return MPoint(Spline(a.x,b.x,c.x,d.x),Spline(a.y,b.y,c.y,d.y));
 }

void CurveDriver::spline()
 {
  level=1;
  
  unsigned len1=Len/4;
  unsigned len2=3*len1;
  unsigned delta=2*len1;
  
  for(; level<MaxLevel && Fineness(getCurve())>=max_fineness ;level++,len1>>=1,len2>>=1,delta>>=1)
    {
     for(unsigned ind=Len-len1,last=2*Len+len1; ind<=last ;ind+=delta)
       buf[ind]=Spline(buf[ind-len2],buf[ind-len1],buf[ind+len1],buf[ind+len2]);
    }
 }

void CurveDriver::spline(MPoint a,MPoint b,MPoint c,MPoint d,MPoint p,MPoint q,MPoint r)
 {
  buf[0]=a;
  buf[Len]=b;
  buf[2*Len]=c;
  buf[3*Len]=d;
  
  buf[Len/2]=p;
  buf[Len/2+Len]=q;
  buf[Len/2+2*Len]=r;
  
  spline();
 }

void CurveDriver::spline(MPoint a_,MPoint b_,MPoint c_,MPoint d_)
 {
  MPoint a=a_,
         b=a,
         c=b_,
         d=c_;
  
  e=d_;
  
  MPoint p=Spline(a,a,b,c),
         q=Spline(a,b,c,d),
         r=Spline(b,c,d,e);
  
  spline(a,b,c,d,p,q,r); 
 }

void CurveDriver::spline(MPoint a_,MPoint b_,MPoint c_,MPoint d_,MPoint e_,MPoint f_)
 {
  MPoint a=b_,
         b=c_,
         c=d_,
         d=e_;
  
  e=f_;
  
  MPoint p=Spline(a_,a,b,c),
         q=Spline(a,b,c,d),
         r=Spline(b,c,d,e);
  
  spline(a,b,c,d,p,q,r); 
 }

void CurveDriver::shift(MPoint f)
 {
  buf[0]=buf[Len];
  buf[Len]=buf[2*Len];
  buf[2*Len]=buf[3*Len];
  buf[3*Len]=e;
  
  e=f;
  
  buf[Len/2]=buf[Len/2+Len];
  buf[Len/2+Len]=buf[Len/2+2*Len];
  buf[Len/2+2*Len]=Spline(buf[Len],buf[2*Len],buf[3*Len],e);
  
  spline();
 }

void CurveDriver::shift()
 {
  buf[0]=buf[Len];
  buf[Len]=buf[2*Len];
  buf[2*Len]=buf[3*Len];
  buf[3*Len]=e;
  
  buf[Len/2]=buf[Len/2+Len];
  buf[Len/2+Len]=buf[Len/2+2*Len];
  buf[Len/2+2*Len]=Spline(buf[Len],buf[2*Len],buf[3*Len],e);
  
  spline();
 }

} // namespace DrawAlgo
} // namespace Video
} // namespace CCore
 

