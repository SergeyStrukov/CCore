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

void CommonDrawArt::WorkBuf::Order(int &a,int &b)
 {
  if( a>b )
    {
     Swap(a,b);
     
     a++;
     b++;
    }
 }

void CommonDrawArt::WorkBuf::lineY(int abx,int ay,int by,DesktopColor color)
 {
  if( abx>=0 && abx<dx && dy>0 )
    {
     Order(ay,by);
     
     if( by>0 && ay<dy )
       {
        if( ay<0 ) ay=0;
        
        if( by>dy ) by=dy;
        
        auto raw=place(Point(abx,ay));
        
        for(; ay<by ;raw=nextY(raw),ay++) color.copyTo(raw);
       }
    }
 }

void CommonDrawArt::WorkBuf::lineX(int aby,int ax,int bx,DesktopColor color)
 {
  if( aby>=0 && aby<dy )
    {
     Order(ax,bx);
      
     if( bx>0 && ax<dx && dx>0 )
       {
        if( ax<0 ) ax=0;
        
        if( bx>dx ) bx=dx;
        
        auto raw=place(Point(ax,aby));
        
        for(; ax<bx ;raw=NextX(raw),ax++) color.copyTo(raw);
       }
    }
 }

void CommonDrawArt::WorkBuf::line(Point a,Point b,DesktopColor color)
 {
  int ex;
  int ey;
  int sx;
  int sy;
  
  if( a.x<b.x )
    {
     ex=1;
     sx=b.x-a.x;
    }
  else if( a.x>b.x )
    {
     ex=-1;
     sx=a.x-b.x;
    }
  else
    {
     return lineY(a.x,a.y,b.y,color);
    }
  
  if( a.y<b.y )
    {
     ey=1;
     sy=b.y-a.y;
    }
  else if( a.y>b.y )
    {
     ey=-1;
     sy=a.y-b.y;
    }
  else
    {
     return lineX(a.y,a.x,b.x,color);
    }
  
  if( sx>sy )
    {
     int delta=0;
     int lim=sx/2;
    
     for(int count=sx; count>0 ;count--)
       {
        if( getPane().contains(a) ) pixel(a,color);
        
        if( (delta+=sy)>lim ) 
          {
           a.y+=ey;
           
           delta-=sx;
          }
        
        a.x+=ex;
       }
    }
  else
    {
     int delta=0;
     int lim=sy/2;
    
     for(int count=sy; count>0 ;count--)
       {
        if( getPane().contains(a) ) pixel(a,color);
        
        if( (delta+=sx)>lim ) 
          {
           a.x+=ex;
           
           delta-=sy;
          }
        
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
 

