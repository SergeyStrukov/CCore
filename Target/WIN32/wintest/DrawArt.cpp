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

/* class CurveDriver */

sint64 CurveDriver::Fineness(PtrStepLen<const LPoint> dots)
 {
  sint64 ret=0;
  
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
     // check diameter
    
     if( Fineness(getCurve())<MaxFineness ) break;
    
     // next level
    
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

/* class CommonDrawArt::WorkBuf */

void CommonDrawArt::Prepare(int &a,int &b,int d)
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

bool CommonDrawArt::DistDir(int &e,unsigned &s,int a,int b)
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

void CommonDrawArt::path(PtrStepLen<const LPoint> curve,DesktopColor color)
 {
  Point a=curve->toPoint();
  
  for(++curve; +curve ;++curve)
    {
     Point b=curve->toPoint();
     
     buf.line(a,b,color);
     
     a=b;
    }
  
  pixel(a,color);
 }

void CommonDrawArt::path_micro1(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify)
 {
  Point A=curve->toPoint();
  
  int ext=magnify/2-1;
  
  for(++curve; +curve ;++curve)
    {
     Point B=curve->toPoint();
     
     {
      Point a=A;
      Point b=B;
      int dx=buf.dX();
      int dy=buf.dY();
       
      int ex;
      int ey;
      unsigned sx;
      unsigned sy;
      
      if( !DistDir(ex,sx,a.x,b.x) )
        {
         int abx=a.x;
         int ay=a.y;
         int by=b.y;
         
         if( abx>=0 && abx<dx )
           {
            Prepare(ay,by,dy);
 
            for(; ay<by ;ay++)
              {
               knob(Point(abx,ay)*magnify,ext,color);
              } 
           }
        }
      else if( !DistDir(ey,sy,a.y,b.y) )
        {
         int aby=a.y;
         int ax=a.x;
         int bx=b.x;
         
         if( aby>=0 && aby<dy )
           {
            Prepare(ax,bx,dx);
             
            for(; ax<bx ;ax++) 
              {
               knob(Point(ax,aby)*magnify,ext,color);
              }
           }
        }
      else if( sx>sy )
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
            
            for(; count ;count--)
              {
               knob(a*magnify,ext,color);
               
               if( driver.step() ) a.y+=ey;
               
               a.x+=ex;
              }
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
            
            for(; count ;count--)
              {
               knob(a*magnify,ext,color);
              
               if( driver.step() ) a.x+=ex;
               
               a.y+=ey;
              }
           }
        }
     }
     
     A=B;
    }
 }

void CommonDrawArt::path_micro2(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify)
 {
  Point a=((*curve)*magnify).toPoint();
  
  knob(a,5,color);
  
  for(++curve; +curve ;++curve)
    {
     Point b=((*curve)*magnify).toPoint();
     
     knob(b,3,color);
     
     a=b;
    }
  
  knob(a,5,color);
 }

void CommonDrawArt::path_micro3(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify)
 {
  Point a=((*curve)*magnify).toPoint();
  
  for(++curve; +curve ;++curve)
    {
     Point b=((*curve)*magnify).toPoint();
     
     buf.line(a,b,color);
     
     a=b;
    }
  
  pixel(a,color);
 }

void CommonDrawArt::path_micro(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify)
 {
  path_micro1(curve,Silver,magnify);
  path_micro2(curve,Black,magnify);
  path_micro3(curve,color,magnify);
 }

 // simple

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
     StackObject<CurveDriver> driver;
     
     driver->spline(dots[0],dots[1],dots[2],dots[3]);
    
     path(driver->getCurve(),color); 
     
     for(dots+=4; +dots ;++dots)
       {
        driver->shift(dots[0]);
        
        path(driver->getCurve(),color); 
       }
     
     driver->shift();
     
     path(driver->getCurve(),color);
     
     driver->shift();
     
     path(driver->getCurve(),color); 
    }
  else if( dots.len==3 )
    {
     StackObject<CurveDriver> driver;
     
     driver->spline(dots[0],dots[1],dots[2],dots[2]);
    
     path(driver->getCurve(),color); 
     
     driver->shift();
     
     path(driver->getCurve(),color); 
    }
  else
    {
     path(dots,color);
    }
 }

void CommonDrawArt::curveLoop(PtrLen<const Point> dots,DesktopColor color)
 {
  switch( dots.len )
    {
     case 0 :
      {
       // do nothing
      }
     break;
     
     case 1 :
      {
       pixel(dots[0],color);
      }
     break;
     
     case 2 :
      {
       StackObject<CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1];
      
       driver->spline(a,b,a,b,a,b);
       
       path(driver->getCurve(),color);
       
       driver->shift(a);
      
       path(driver->getCurve(),color);
      }
     break;
     
     case 3 :
      {
       StackObject<CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2];
      
       driver->spline(a,b,c,a,b,c);
       
       path(driver->getCurve(),color);
       
       driver->shift(a);
      
       path(driver->getCurve(),color);
       
       driver->shift(b);
      
       path(driver->getCurve(),color);
      }
     break;
     
     case 4 :
      {
       StackObject<CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3];
      
       driver->spline(a,b,c,d,a,b);
       
       path(driver->getCurve(),color);
       
       driver->shift(c);
      
       path(driver->getCurve(),color);
       
       driver->shift(d);
      
       path(driver->getCurve(),color);
       
       driver->shift(a);
      
       path(driver->getCurve(),color);
      }
     break;
     
     case 5 :
      {
       StackObject<CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3],
             e=dots[4];
      
       driver->spline(a,b,c,d,e,a);
       
       path(driver->getCurve(),color);
       
       driver->shift(b);
      
       path(driver->getCurve(),color);
       
       driver->shift(c);
      
       path(driver->getCurve(),color);
       
       driver->shift(d);
      
       path(driver->getCurve(),color);
       
       driver->shift(e);
      
       path(driver->getCurve(),color);
      }
     break;
     
     default:
      {
       StackObject<CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3],
             e=dots[4],
             f=dots[5];
      
       driver->spline(a,b,c,d,e,f);
       
       path(driver->getCurve(),color);
       
       for(dots+=6; +dots ;++dots)
         {
          driver->shift(dots[0]);
         
          path(driver->getCurve(),color); 
         }

       driver->shift(a);
      
       path(driver->getCurve(),color);
       
       driver->shift(b);
      
       path(driver->getCurve(),color);
       
       driver->shift(c);
      
       path(driver->getCurve(),color);
       
       driver->shift(d);
      
       path(driver->getCurve(),color);
       
       driver->shift(e);
      
       path(driver->getCurve(),color);
      }
    }
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

 // special

void CommonDrawArt::grid(int cell)
 {
  erase(White);

  for(int x=cell/2; x<buf.dX() ;x+=cell) buf.lineY(x,0,buf.dY(),Blue);
  
  for(int y=cell/2; y<buf.dY() ;y+=cell) buf.lineX(y,0,buf.dX(),Blue);
 }

void CommonDrawArt::curvePath_micro(PtrLen<const Point> dots,DesktopColor color,Point focus,int magnify)
 {
  if( dots.len<4 ) return;
  
  grid(magnify);
  
  focus.y-=buf.dY()/magnify;
  
  StackObject<CurveDriver> driver;
  
  driver->spline(dots[0]-focus,dots[1]-focus,dots[2]-focus,dots[3]-focus);
 
  path_micro(driver->getCurve(),color,magnify); 
  
  for(dots+=4; +dots ;++dots)
    {
     driver->shift(dots[0]-focus);
     
     path_micro(driver->getCurve(),color,magnify);
    }
  
  driver->shift();
  
  path_micro(driver->getCurve(),color,magnify);
  
  driver->shift();
  
  path_micro(driver->getCurve(),color,magnify);
 }

} // namespace Video
} // namespace CCore
 

