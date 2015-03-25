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

#include <CCore/inc/Exception.h>
 
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

} // namespace Video
} // namespace CCore
 

