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
 
#include <CCore/inc/video/DrawAlgo.h>
 
#include <CCore/inc/algon/Partition.h>

namespace CCore {
namespace Video {
namespace DrawAlgo {

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
     delta_index=+1;
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

SolidSection::~SolidSection()
 {
 }

/* class SolidBorderSection */

SolidBorderSection::Line::Line(Point a,Point b)
 {
  if( a.y<b.y )
    {
     delta_index=-1;
     bottom=a;
     top=b;
    }
  else if( a.y>b.y )
    {
     delta_index=+1;
     bottom=b;
     top=a;
    }
  else
    {
     delta_index=0;
     bottom=b;
     top=a;
    }
 }

void SolidBorderSection::Sort(PtrLen<Line *> set)
 {
  IncrSort(set, [] (const Line *a,const Line *b) { return a->bottom.x<b->bottom.x; } );
 }

SolidBorderSection::SolidBorderSection(PtrLen<const Point> dots)
 : line_buf(dots.len),
   lines(dots.len)
 {
  bottom=top=dots[0].y;
  
  for(ulen i=1; i<dots.len ;i++)
    {
     Coord y=dots[i].y;
    
     Replace_min(bottom,y);
     Replace_max(top,y);
    }
  
  ulen i=0;
  
  for(; i<dots.len-1 ;i++) line_buf[i]=Line(dots[i],dots[i+1]); 
  
  line_buf[i]=Line(dots[i],dots[0]);
  
  for(ulen i=0; i<dots.len ;i++) lines[i]=&(line_buf[i]);
  
  split=Algon::Partition(Range(lines), [] (const Line *a) { return a->delta_index==0; } );
  
  IncrSort(Range(lines).part(split), [] (const Line *a,const Line *b) { return a->bottom.y<b->bottom.y; } );
 }

SolidBorderSection::~SolidBorderSection()
 {
 }

} // namespace DrawAlgo
} // namespace Video
} // namespace CCore
 

