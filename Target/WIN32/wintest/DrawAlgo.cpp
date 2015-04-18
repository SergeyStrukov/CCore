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
 
#include <CCore/inc/algon/SortUnique.h>

namespace CCore {
namespace Video {
namespace Algo {

/* class LineDriver */

auto LineDriver::clip(Coord x,Coord y,Coord ex,Coord ey,Coord dx,Coord dy) const -> Result
 {
  auto clip_x=Clip(x,ex,dx);
  
  Replace_min(clip_x.lim,sx);
  
  if( !clip_x ) return {0,0};
  
  auto clip_y=Clip(y,ey,dy);
  
  if( !clip_y ) return {0,0};
  
  return Inf(clip_x,clipToX(clip_y));
 }

uCoord LineDriver::clipToX(uCoord y) const
 {
  if( y>sy ) return sx;
  
  if( y==0 ) return 0;
  
  UIntFunc<uCoord>::Mul mul(sx,y);
  
  UIntFunc<uCoord>::Sub sub(mul.lo,lim);
  
  UIntFunc<uCoord>::DivMod divmod(mul.hi-sub.borrow,sub.result,sy);
  
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

auto LineDriver::Clip(Coord x,Coord e,Coord d) -> Result
 {
  if( e>0 )
    {
     if( x<0 )
       {
        return {IntDist<Coord>(x,0),IntDist(x,d)};
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
        return {0,IntDist<Coord>(-1,x)};
       }
     else
       {
        return {IntDist<Coord>(d-1,x),IntDist<Coord>(-1,x)};
       }
    }
 }

/* class CurveDriver */

uLCoord CurveDriver::Fineness(PtrStepLen<const LPoint> dots)
 {
  uLCoord ret=0;
  
  for(; dots.len>1 ;++dots) Replace_max(ret,PointDist(dots[0],dots[1]));
  
  return ret; 
 }

LCoord CurveDriver::Spline(LCoord a,LCoord b,LCoord c,LCoord d)
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
  
  unsigned len1=Len/4;
  unsigned len2=3*len1;
  unsigned delta=2*len1;
  
  for(; level<MaxLevel ;level++,len1>>=1,len2>>=1,delta>>=1)
    {
     if( Fineness(getCurve())<MaxFineness ) break;
    
     for(unsigned ind=Len-len1,last=2*Len+len1; ind<=last ;ind+=delta)
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

/* class SolidSection */

SolidSection::Line::Line(Dot a_,Dot b_)
 : a(a_.dot),b(b_.dot) 
 {
  if( a_.sect<b_.sect )
    {
     delta_index=-1;
     bottom=a_.sect;
     top=b_.sect;
    }
  else if( a_.sect>b_.sect )
    {
     delta_index=1;
     bottom=b_.sect;
     top=a_.sect;
    }
  else
    {
     delta_index=0;
     bottom=b_.sect;
     top=a_.sect;
    }
  
  DistDir(ex,sx,a.x,b.x);
  DistDir(ey,sy,a.y,b.y);
  
  if( sx && sy ) 
    {
     if( sx>sy )
       {
        CreateAt(driver.obj,sx,sy);
        
        if( a.y<b.y )
          {
           if( ex>0 )
             {
              x0=a.x;
              
              x1=IntMovePos(x0,driver.obj.stepUp());
             }
           else
             {
              x1=a.x;
              
              x0=IntMoveNeg(x1,driver.obj.stepUp());
             } 
          }
        else
          {
           if( ex<0 )
             {
              x0=b.x;
             
              x1=IntMovePos(x0,driver.obj.backDown());
             }
           else
             {
              x1=b.x;
              
              x0=IntMoveNeg(x1,driver.obj.backDown());
             } 
          }
       }
     else
       {
        CreateAt(driver.obj,sy,sx);
        
        if( a.y<b.y )
          x1=x0=a.x;
        else
          x1=x0=b.x;
       }
    }
  else
    {
     x1=x0=a.x;
    }
 }

void SolidSection::Line::step()
 {
  if( sx>sy )
    {
     if( a.y<b.y )
       {
        if( ex>0 )
          {
           x0=x1+1;
           
           x1=IntMovePos(x0,driver.obj.stepUp());
          }
        else
          {
           x1=x0-1;
          
           x0=IntMoveNeg(x1,driver.obj.stepUp());
          } 
       }
     else
       {
        if( ex<0 )
          {
           x0=x1+1;
          
           x1=IntMovePos(x0,driver.obj.backDown());
          }
        else
          {
           x1=x0-1;

           x0=IntMoveNeg(x1,driver.obj.backDown());
          } 
       }
    }
  else if( sx )
    {
     if( a.y<b.y )
       {
        if( driver.obj.step() ) x0+=ex;
       }
     else
       {
        if( driver.obj.back() ) x0-=ex;
       }
    
     x1=x0;
    }
 }

void SolidSection::Sort(PtrLen<Line *> set)
 {
  IncrSort(set, [] (const Line *a,const Line *b) { return a->x0<b->x0; } );
 }

void SolidSection::Step(PtrLen<Line *> set)
 {
  for(Line *line : set ) line->step();
 }

SolidSection::SolidSection(PtrLen<const Point> dots)
 : path(dots.len),
   sect(dots.len),
   line_buf(dots.len),
   lines(dots.len)
 {
  for(ulen i=0; i<dots.len ;i++) 
    {
     Point d=dots[i];
     
     path[i].dot=d;
     sect[i].set(d.y,i);
    }
  
  Algon::SortThenApplyUniqueRange(Range(sect), [&] (PtrLen<Sect> r) 
                                                   {
                                                    ulen i=sect_count++;
                                                    
                                                    for(Sect s : r ) path[s.dot].sect=i;
   
                                                    sect[i]=r[0];
                                                    
                                                   } );

  ulen i=0;
  
  for(; i<dots.len-1 ;i++) line_buf[i]=Line(path[i],path[i+1]); 
  
  line_buf[i]=Line(path[i],path[0]);
  
  IncrSort(Range(line_buf), [] (const Line &a,const Line &b) { return a.bottom<b.bottom; } );
  
  for(ulen i=0; i<dots.len ;i++) lines[i]=&(line_buf[i]); 
 }

SolidSection::~SolidSection()
 {
 }

} // namespace Algo
} // namespace Video
} // namespace CCore
 

