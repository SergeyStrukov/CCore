/* DrawAlgo.cpp */ 
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
 
//#include <CCore/inc/video/DrawAlgo.h>
#include "DrawAlgo.h"
 
namespace CCore {
namespace Video {

/* class LineDriver */

auto LineDriver::clip(int x,int y,int ex,int ey,int dx,int dy) const -> Result
 {
  auto clip_x=Clip(x,ex,dx);
  
  Replace_min(clip_x.lim,sx);
  
  if( !clip_x ) return {0,0};
  
  auto clip_y=Clip(y,ey,dy);
  
  if( !clip_y ) return {0,0};
  
  return Inf(clip_x,clipToX(clip_y));
 }

unsigned LineDriver::clipToX(unsigned y) const
 {
  if( y>sy ) return sx;
  
  if( y==0 ) return 0;
  
  UIntFunc<unsigned>::Mul mul(sx,y);
  
  UIntFunc<unsigned>::Sub sub(mul.lo,lim);
  
  UIntFunc<unsigned>::DivMod divmod(mul.hi-sub.borrow,sub.result,sy);
  
  if( (sx&1u)!=0 && divmod.mod==0 )
    {
     return divmod.div;
    }
  else
    {
     return divmod.div+1;
    }
 }

auto LineDriver::clipToX(Result clip_y) const -> Result
 {
  return {clipToX(clip_y.off),clipToX(clip_y.lim)};
 }

auto LineDriver::Clip(int x,int e,int d) -> Result
 {
  if( e>0 )
    {
     if( x<0 )
       {
        return {IntDist(x,0),IntDist(x,d)};
       }
     else if( x<d )
       {
        return {0,IntDist(x,d)};        
       }
     else
       {
        return {0,0};
       }
    }
  else
    {
     if( x<0 )
       {
        return {0,0};
       }
     else if( x<d )
       {
        return {0,IntDist(-1,x)};
       }
     else
       {
        return {IntDist(d-1,x),IntDist(-1,x)};
       }
    }
 }

/* class CurveDriver */

uint64 CurveDriver::Fineness(PtrStepLen<const LPoint> dots)
 {
  uint64 ret=0;
  
  for(; dots.len>1 ;++dots) Replace_max(ret,PointDist(dots[0],dots[1]));
  
  return ret; 
 }

sint64 CurveDriver::Spline(sint64 a,sint64 b,sint64 c,sint64 d)
 {
  return (b+c)/2+(b+c-a-d)/16;
 }

LPoint CurveDriver::Spline(LPoint a,LPoint b,LPoint c,LPoint d)
 {
  return LPoint(Spline(a.x,b.x,c.x,d.x),Spline(a.y,b.y,c.y,d.y));
 }

void CurveDriver::spline()
 {
  level=1;
  
  ulen len1=Len/4;
  ulen len2=3*len1;
  ulen delta=2*len1;
  
  for(; level<MaxLevel ;level++,len1>>=1,len2>>=1,delta>>=1)
    {
     if( Fineness(getCurve())<MaxFineness ) break;
    
     for(ulen ind=Len-len1,last=2*Len+len1; ind<=last ;ind+=delta)
       buf[ind]=Spline(buf[ind-len2],buf[ind-len1],buf[ind+len1],buf[ind+len2]);
    }
 }

void CurveDriver::spline(LPoint a,LPoint b,LPoint c,LPoint d,LPoint p,LPoint q,LPoint r)
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

void CurveDriver::spline(Point a_,Point b_,Point c_,Point d_)
 {
  LPoint a=a_,
         b=a,
         c=b_,
         d=c_;
  
  e=d_;
  
  LPoint p=Spline(a,a,b,c),
         q=Spline(a,b,c,d),
         r=Spline(b,c,d,e);
  
  spline(a,b,c,d,p,q,r); 
 }

void CurveDriver::spline(Point a_,Point b_,Point c_,Point d_,Point e_,Point f_)
 {
  LPoint a=b_,
         b=c_,
         c=d_,
         d=e_;
  
  e=f_;
  
  LPoint p=Spline(a_,a,b,c),
         q=Spline(a,b,c,d),
         r=Spline(b,c,d,e);
  
  spline(a,b,c,d,p,q,r); 
 }

void CurveDriver::shift(Point f)
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

} // namespace Video
} // namespace CCore
 

