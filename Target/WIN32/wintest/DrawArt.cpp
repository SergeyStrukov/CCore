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
 
//#include <CCore/inc/video/DrawArt.h>
#include "DrawArt.h"

//#include <CCore/inc/video/DrawAlgo.h>
#include "DrawAlgo.h"

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

template <class Plot>
void CommonDrawArt::WorkBuf::lineY(int abx,int ay,int by,Plot plot)
 {
  if( abx>=0 && abx<dx )
    {
     Prepare(ay,by,dy);

     if( ay<by )
       {
        for(auto ptr=place(Point(abx,ay));;)
          {
           plot(ptr);
           
           ay++;
           
           if( ay>=by ) break;
           
           ptr=nextY(ptr);
          }
       }
    }
 }

template <class Plot>
void CommonDrawArt::WorkBuf::lineX(int aby,int ax,int bx,Plot plot)
 {
  if( aby>=0 && aby<dy )
    {
     Prepare(ax,bx,dx);
      
     if( ax<bx )
       {
        for(auto ptr=place(Point(ax,aby));;)
          {
           plot(ptr);
           
           ax++;
           
           if( ax>=bx ) break;
           
           ptr=NextX(ptr);
          }
       }
    }
 }

template <class Plot>
void CommonDrawArt::WorkBuf::line(Point a,Point b,Plot plot)
 {
  int ex;
  int ey;
  unsigned sx;
  unsigned sy;
  
  if( !DistDir(ex,sx,a.x,b.x) )
    {
     return lineY(a.x,a.y,b.y,plot);
    }
 
  if( !DistDir(ey,sy,a.y,b.y) )
    {
     return lineX(a.y,a.x,b.x,plot);
    }

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

        if( ex>0 )
          {
           if( ey>0 )
             {
              for(auto ptr=place(a);;)
                {
                 plot(ptr);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   ptr=nextXnextY(ptr);
                 else
                   ptr=NextX(ptr);
                }
             }
           else
             {
              for(auto ptr=place(a);;)
                {
                 plot(ptr);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   ptr=nextXprevY(ptr);
                 else
                   ptr=NextX(ptr);
                }
             }
          }
        else
          {
           if( ey>0 )
             {
              for(auto ptr=place(a);;)
                {
                 plot(ptr);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   ptr=prevXnextY(ptr);
                 else
                   ptr=PrevX(ptr);
                }
             }
           else
             {
              for(auto ptr=place(a);;)
                {
                 plot(ptr);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   ptr=prevXprevY(ptr);
                 else
                   ptr=PrevX(ptr);
                }
             }
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
        
        if( ey>0 )
          {
           if( ex>0 )
             {
              for(auto ptr=place(a);;)
                {
                 plot(ptr);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   ptr=nextXnextY(ptr);
                 else
                   ptr=nextY(ptr);
                }
             }
           else
             {
              for(auto ptr=place(a);;)
                {
                 plot(ptr);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   ptr=prevXnextY(ptr);
                 else
                   ptr=nextY(ptr);
                }
             }
          }
        else
          {
           if( ex>0 )
             {
              for(auto ptr=place(a);;)
                {
                 plot(ptr);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   ptr=nextXprevY(ptr);
                 else
                   ptr=prevY(ptr);
                }
             }
           else
             {
              for(auto ptr=place(a);;)
                {
                 plot(ptr);
                  
                 if( !--count ) break;
                 
                 if( driver.step() )
                   ptr=prevXprevY(ptr);
                 else
                   ptr=prevY(ptr);
                }
             }
          }
       }
    }
 }

void CommonDrawArt::WorkBuf::lineY(int abx,int ay,int by,DesktopColor color)
 {
  lineY(abx,ay,by, [color] (Raw *ptr) { color.copyTo(ptr); } );
 }

void CommonDrawArt::WorkBuf::lineX(int aby,int ax,int bx,DesktopColor color)
 {
  lineX(aby,ax,bx, [color] (Raw *ptr) { color.copyTo(ptr); } );
 }

void CommonDrawArt::WorkBuf::line(Point a,Point b,DesktopColor color)
 {
  line(a,b, [color] (Raw *ptr) { color.copyTo(ptr); } );
 }

/* class CommonDrawArt */

template <class Plot>
void CommonDrawArt::path(PtrStepLen<const LPoint> curve,DesktopColor color,Plot plot) // TODO
 {
  LPoint a=curve[0];
  LPoint b=curve[1];

  Point A=a.toPoint();
  Point B=b.toPoint();
  
  plot(A,color);
  
  curve+=2;
  
  while( PointNear(A,B) )
    {
     if( !curve )
       {
        plot(B,color);
       
        return;
       }
     
     b=*curve;
     B=b.toPoint();
     
     ++curve;
    }
  
  auto end=LineFirst(a,b,color,plot);
  
  while( +curve ) 
    {
     a=b;
     A=B;
    
     b=*curve;
     B=b.toPoint();
     
     ++curve;
     
     while( PointNear(A,B) )
       {
        if( !curve )
          {
           plot(A,color);
           plot(B,color);
          
           return;
          }
        
        b=*curve;
        B=b.toPoint();
        
        ++curve;
       }
    
     end=LineNext(end,a,b,color,plot);
    }
  
  plot(B,color);
 }

void CommonDrawArt::path(PtrStepLen<const LPoint> curve,DesktopColor color) // TODO
 {
  path(curve,color, [this] (Point p,DesktopColor color) { pixel(p,color); } );
 }

void CommonDrawArt::path_micro1(PtrStepLen<const LPoint> curve,DesktopColor color,int magnify) // TODO
 {
  auto plot = [this,magnify] (Point p,DesktopColor color) { gridCell(p,color,magnify); } ;

  path(curve,color,plot);
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

  for(int x=cell/2; x<buf.dX() ;x+=cell) buf.lineY(x,0,buf.dY(),DesktopColor(Blue));
  
  for(int y=cell/2; y<buf.dY() ;y+=cell) buf.lineX(y,0,buf.dX(),DesktopColor(Blue));
 }

void CommonDrawArt::gridCell(Point p,DesktopColor color,int magnify)
 {
  knob(p*magnify,magnify/2-1,color);
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
 

