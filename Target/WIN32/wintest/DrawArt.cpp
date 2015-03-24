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

void CommonDrawArt::WorkBuf::lineY(int abx,int ay,int by,DesktopColor color)
 {
  if( abx>=0 && abx<dx && dy>0 )
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
  if( aby>=0 && aby<dy && dx>0 )
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
  
  if( a.x<b.x )
    {
     ex=1;
     sx=Shift(a.x,b.x);
    }
  else if( a.x>b.x )
    {
     ex=-1;
     sx=Shift(b.x,a.x);
    }
  else
    {
     return lineY(a.x,a.y,b.y,color);
    }
  
  if( a.y<b.y )
    {
     ey=1;
     sy=Shift(a.y,b.y);
    }
  else if( a.y>b.y )
    {
     ey=-1;
     sy=Shift(b.y,a.y);
    }
  else
    {
     return lineX(a.y,a.x,b.x,color);
    }
  
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
 

