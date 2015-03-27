/* DrawArt.cpp */ 
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
 
#include "DrawArt.h"

#include <CCore/inc/Swap.h>

namespace CCore {
namespace Video {

/* class LineDriver */

unsigned LineDriver::step(unsigned count)
 {
  if( sy==sx ) return count;
  
  UIntFunc<unsigned>::Mul mul(count,sy);
  UIntFunc<unsigned>::DivMod divmod(mul.hi,mul.lo,sx);

  return divmod.div+do_step(divmod.mod);
 }

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

/* class CommonDrawArt::WorkBuf */

void CommonDrawArt::WorkBuf::Prepare(int &a,int &b,int d)
 {
  if( a<=b )
    {
     if( a<0 ) a=0;
     
     if( b>d ) b=d;
    }
  else
    {
     Swap(a,b);
     
     if( a<0 ) a=0; else a++;
     
     if( b<d ) b++; else b=d;
    }
 }

bool CommonDrawArt::WorkBuf::DistDir(int &e,unsigned &s,int a,int b)
 {
  if( a<b )
    {
     e=1;
     s=IntDist(a,b);
     
     return true;
    }
  
  if( a>b )
    {
     e=-1;
     s=IntDist(b,a);
     
     return true;
    }
  
  return false;
 }

void CommonDrawArt::WorkBuf::lineY(int abx,int ay,int by,DesktopColor color)
 {
  if( abx>=0 && abx<dx )
    {
     Prepare(ay,by,dy);

     if( ay<by )
       {
        auto raw=place(Point(abx,ay));
          
        for(; ay<by ;raw=nextY(raw),ay++) color.copyTo(raw);
       }
    }
 }

void CommonDrawArt::WorkBuf::lineX(int aby,int ax,int bx,DesktopColor color)
 {
  if( aby>=0 && aby<dy )
    {
     Prepare(ax,bx,dx);
      
     if( ax<bx )
       {
        auto raw=place(Point(ax,aby));
        
        for(; ax<bx ;raw=NextX(raw),ax++) color.copyTo(raw);
       }
    }
 }

void CommonDrawArt::WorkBuf::line(Point a,Point b,DesktopColor color)
 {
  int ex;
  int ey;
  unsigned sx;
  unsigned sy;
  
  if( !DistDir(ex,sx,a.x,b.x) )
    {
     return lineY(a.x,a.y,b.y,color);
    }
 
  if( !DistDir(ey,sy,a.y,b.y) )
    {
     return lineX(a.y,a.x,b.x,color);
    }

#if 0
  
  if( sx>sy )
    {
     LineDriver driver(sx,sy);
    
     for(auto count=sx; count>0 ;count--)
       {
        if( getPane().contains(a) ) pixel(a,color);
        
        if( driver.step() ) a.y+=ey;
        
        a.x+=ex;
       }
    }
  else
    {
     LineDriver driver(sy,sx);
    
     for(auto count=sy; count>0 ;count--)
       {
        if( getPane().contains(a) ) pixel(a,color);
        
        if( driver.step() ) a.x+=ex;
        
        a.y+=ey;
       }
    }
  
#else
  
  if( sx>sy )
    {
     LineDriver driver(sx,sy);
     
     auto clip=driver.clip(a.x,a.y,ex,ey,dx,dy);
     
     if( +clip )
       {
        unsigned off=clip.off;
        unsigned count=clip.lim-clip.off;
        
        if( off ) 
          {
           a.y=IntMove(a.y,ey,driver.step(off));
           a.x=IntMove(a.x,ex,off);
          }
        
#if 0
        
        for(; count ;count--)
          {
           pixel(a,color);
           
           if( driver.step() ) a.y+=ey;
           
           a.x+=ex;
          }
        
#else

        if( ex>0 )
          {
           if( ey>0 )
             {
              for(auto raw=place(a);;)
                {
                 color.copyTo(raw);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   {
                    raw=nextXnextY(raw);
                   }
                 else
                   {
                    raw=NextX(raw);
                   }
                }
             }
           else
             {
              for(auto raw=place(a);;)
                {
                 color.copyTo(raw);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   {
                    raw=nextXprevY(raw);
                   }
                 else
                   {
                    raw=NextX(raw);
                   }
                }
             }
          }
        else
          {
           if( ey>0 )
             {
              for(auto raw=place(a);;)
                {
                 color.copyTo(raw);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   {
                    raw=prevXnextY(raw);
                   }
                 else
                   {
                    raw=PrevX(raw);
                   }
                }
             }
           else
             {
              for(auto raw=place(a);;)
                {
                 color.copyTo(raw);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   {
                    raw=prevXprevY(raw);
                   }
                 else
                   {
                    raw=PrevX(raw);
                   }
                }
             }
          }
        
#endif        
       }
    }
  else
    {
     LineDriver driver(sy,sx);
    
     auto clip=driver.clip(a.y,a.x,ey,ex,dy,dx);
     
     if( +clip )
       {
        unsigned off=clip.off;
        unsigned count=clip.lim-clip.off;
        
        if( off ) 
          {
           a.x=IntMove(a.x,ex,driver.step(off));
           a.y=IntMove(a.y,ey,off);
          }
        
#if 0
        
        for(; count ;count--)
          {
           pixel(a,color);
           
           if( driver.step() ) a.x+=ex;
           
           a.y+=ey;
          }
        
#else
        
        if( ey>0 )
          {
           if( ex>0 )
             {
              for(auto raw=place(a);;)
                {
                 color.copyTo(raw);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   {
                    raw=nextXnextY(raw);
                   }
                 else
                   {
                    raw=nextY(raw);
                   }
                }
             }
           else
             {
              for(auto raw=place(a);;)
                {
                 color.copyTo(raw);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   {
                    raw=prevXnextY(raw);
                   }
                 else
                   {
                    raw=nextY(raw);
                   }
                }
             }
          }
        else
          {
           if( ex>0 )
             {
              for(auto raw=place(a);;)
                {
                 color.copyTo(raw);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   {
                    raw=nextXprevY(raw);
                   }
                 else
                   {
                    raw=prevY(raw);
                   }
                }
             }
           else
             {
              for(auto raw=place(a);;)
                {
                 color.copyTo(raw);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   {
                    raw=prevXprevY(raw);
                   }
                 else
                   {
                    raw=prevY(raw);
                   }
                }
             }
          }
        
#endif        
       }
    }
  
#endif  
 }

/* class CommonDrawArt */

unsigned CommonDrawArt::Diameter(sint64 a,sint64 b)
 {
  return unsigned( ( (a<=b)?(b-a):(a-b) )>>Precision );
 }

unsigned CommonDrawArt::Diameter(LPoint a,LPoint b)
 {
  return Max(Diameter(a.x,b.x),Diameter(a.y,b.y));
 }

unsigned CommonDrawArt::Diameter(const LPoint *ptr,ulen count,ulen delta)
 {
  unsigned ret=0;
  
  for(; count>1 ;count--,ptr+=delta) Replace_max(ret,Diameter(ptr[0],ptr[delta]));
  
  return ret; 
 }

sint64 CommonDrawArt::Spline(sint64 a,sint64 b,sint64 c,sint64 d)
 {
  return (b+c)/2+(b+c-a-d)/16;
 }

LPoint CommonDrawArt::Spline(LPoint a,LPoint b,LPoint c,LPoint d)
 {
  return LPoint(Spline(a.x,b.x,c.x,d.x),Spline(a.y,b.y,c.y,d.y));
 }

void CommonDrawArt::path(const LPoint *ptr,ulen count,ulen delta,DesktopColor color)
 {
#if 0
  
  for(; count ;count--,ptr+=delta) pixel(RShift(*ptr,Precision),Blue);
  
#endif  
  
#if 1 
 
  Point a=RShift(*ptr,Precision);
  
  for(count--,ptr+=delta; count ;count--,ptr+=delta)
    {
     Point b=RShift(*ptr,Precision);
     
     buf.line(a,b,color);
     
     a=b;
    }
  
  pixel(a,color);
  
#endif  
 }

void CommonDrawArt::SplineBuf::spline(LPoint a,LPoint b,LPoint c,LPoint d,LPoint p,LPoint q,LPoint r)
 {
  buf[0]=a;
  buf[Len]=b;
  buf[2*Len]=c;
  buf[3*Len]=d;
  
  buf[Len/2]=p;
  buf[Len/2+Len]=q;
  buf[Len/2+2*Len]=r;
  
  level=1;
  
  ulen len1=Len/4;
  ulen len2=3*len1;
  ulen delta=2*len1;
  
  for(; level<MaxLevel ;level++,len1>>=1,len2>>=1,delta>>=1)
    {
     // check diameter
    
     if( Diameter(buf+Len,(1u<<level)+1,delta)<MaxDiameter ) break;
    
     // next level
    
     for(ulen ind=Len-len1,last=2*Len+len1; ind<=last ;ind+=delta)
       buf[ind]=Spline(buf[ind-len2],buf[ind-len1],buf[ind+len1],buf[ind+len2]);
    }
 }

void CommonDrawArt::curve(SplineBuf &buf,LPoint a,LPoint b,LPoint c,LPoint d,LPoint p,LPoint q,LPoint r,DesktopColor color)
 {
  buf.spline(a,b,c,d,p,q,r);
  
  path(buf.getPtr(),buf.getCount(),buf.getDelta(),color);
 }

void CommonDrawArt::pixel(Point p,DesktopColor color)
 {
  if( buf.getPane().contains(p) ) buf.pixel(p,color);
 }

void CommonDrawArt::erase(DesktopColor color)
 {
  buf.erase(color);
 }

void CommonDrawArt::block(Pane pane,DesktopColor color)
 {
  buf.block(Inf(buf.getPane(),pane),color);
 }

void CommonDrawArt::path(PtrLen<const Point> dots,DesktopColor color)
 {
  if( +dots )
    {
     Point a=*dots;
     
     for(++dots; +dots ;++dots)
       {
        Point b=*dots;
        
        buf.line(a,b,color);
        
        a=b;
       }
     
     pixel(a,color);
    }
 }

void CommonDrawArt::loop(PtrLen<const Point> dots,DesktopColor color)
 {
  if( +dots )
    {
     Point a=*dots;
     Point o=a;
     
     for(++dots; +dots ;++dots)
       {
        Point b=*dots;
        
        buf.line(a,b,color);
        
        a=b;
       }
     
     buf.line(a,o,color);
    }
 }

void CommonDrawArt::curvePath(PtrLen<const Point> dots,DesktopColor color)
 {
  if( dots.len>=4 )
    {
     StackObject<SplineBuf> buf;
    
     LPoint a=LShift(dots[0],Precision),
            b=a,
            c=LShift(dots[1],Precision),
            d=LShift(dots[2],Precision),
            e=LShift(dots[3],Precision);
     
     LPoint p=Spline(a,a,b,c),
            q=Spline(a,b,c,d),
            r=Spline(b,c,d,e);
    
     curve(*buf,a,b,c,d,p,q,r,color);
     
     for(dots+=4; +dots ;++dots)
       {
        a=b;
        b=c;
        c=d;
        d=e;
        e=LShift(dots[0],Precision);
        
        p=q;
        q=r;
        r=Spline(b,c,d,e);
        
        curve(*buf,a,b,c,d,p,q,r,color);
       }
     
     LPoint s=Spline(c,d,e,e);
     
     curve(*buf,b,c,d,e,q,r,s,color);
     
     curve(*buf,c,d,e,e,r,s,Spline(d,e,e,e),color);
    }
  else if( dots.len==3 )
    {
     StackObject<SplineBuf> buf;
     
     LPoint a=LShift(dots[0],Precision),
            b=LShift(dots[1],Precision),
            c=LShift(dots[2],Precision);
            
     LPoint q=Spline(a,a,b,c),
            r=Spline(a,b,c,c);
     
     curve(*buf,a,a,b,c,Spline(a,a,a,b),q,r,color);
     curve(*buf,a,b,c,c,q,r,Spline(b,c,c,c),color);
    }
  else
    {
     path(dots,color);
    }
 }

void CommonDrawArt::curveLoop(PtrLen<const Point> dots,DesktopColor color)
 {
  Used(dots);
  Used(color);
 }

void CommonDrawArt::solid(PtrLen<const Point> dots,DesktopColor color)
 {
  Used(dots);
  Used(color);
 }

void CommonDrawArt::curveSolid(PtrLen<const Point> dots,DesktopColor color)
 {
  Used(dots);
  Used(color);
 }

} // namespace Video
} // namespace CCore
 

