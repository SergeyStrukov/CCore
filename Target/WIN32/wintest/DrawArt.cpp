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

#include <CCore/inc/Array.h>

namespace CCore {
namespace Video {

/* struct CircleSpline */

CircleSpline::CircleSpline(Point center,Coord radius)
 {
  Coord x=Coord( radius/2 );
  Coord y=Coord( Algo::SqRoot<uLCoord>(Sq<uLCoord>(radius)-Sq<uLCoord>(x),radius) );
 
  buf[0]=center+Point(0,radius);
  buf[1]=center+Point(-x,y);
  buf[2]=center+Point(-y,x);
  buf[3]=center+Point(-radius,0);
  buf[4]=center+Point(-y,-x);
  buf[5]=center+Point(-x,-y);
  buf[6]=center+Point(0,-radius);
  buf[7]=center+Point(x,-y);
  buf[8]=center+Point(y,-x);
  buf[9]=center+Point(radius,0);
  buf[10]=center+Point(y,x);
  buf[11]=center+Point(x,y);
 }

/* class CommonDrawArt::WorkBuf */

void CommonDrawArt::WorkBuf::Prepare(Coord &a,Coord &b,Coord d)
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
void CommonDrawArt::WorkBuf::lineY(Coord abx,Coord ay,Coord by,Plot plot)
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
void CommonDrawArt::WorkBuf::lineX(Coord aby,Coord ax,Coord bx,Plot plot)
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
  Coord ex;
  Coord ey;
  uCoord sx;
  uCoord sy;
  
  if( !Algo::DistDir(ex,sx,a.x,b.x) )
    {
     return lineY(a.x,a.y,b.y,plot);
    }
 
  if( !Algo::DistDir(ey,sy,a.y,b.y) )
    {
     return lineX(a.y,a.x,b.x,plot);
    }

  if( sx>sy )
    {
     Algo::LineDriver driver(sx,sy);
     
     auto clip=driver.clip(a.x,a.y,ex,ey,dx,dy);
     
     if( +clip )
       {
        uCoord off=clip.off;
        uCoord count=clip.lim-clip.off;
        
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
     Algo::LineDriver driver(sy,sx);
    
     auto clip=driver.clip(a.y,a.x,ey,ex,dy,dx);
     
     if( +clip )
       {
        uCoord off=clip.off;
        uCoord count=clip.lim-clip.off;
        
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

void CommonDrawArt::WorkBuf::lineY(Coord abx,Coord ay,Coord by,DesktopColor color)
 {
  lineY(abx,ay,by, [color] (Raw *ptr) { color.copyTo(ptr); } );
 }

void CommonDrawArt::WorkBuf::lineX(Coord aby,Coord ax,Coord bx,DesktopColor color)
 {
  lineX(aby,ax,bx, [color] (Raw *ptr) { color.copyTo(ptr); } );
 }

void CommonDrawArt::WorkBuf::line(Point a,Point b,DesktopColor color)
 {
  line(a,b, [color] (Raw *ptr) { color.copyTo(ptr); } );
 }

void CommonDrawArt::WorkBuf::line_smooth(Point a,Point b,ColorName cname)
 {
  if( a.x==b.x )
    {
     return lineY(a.x,a.y,b.y,DesktopColor(cname));
    }
 
  if( a.y==b.y )
    {
     return lineX(a.y,a.x,b.x,DesktopColor(cname));
    }
  
  Algo::LineSmooth(a,b,SmoothPlot(*this,cname));
 }

/* class CommonDrawArt */

template <class Plot>
void CommonDrawArt::path(PtrStepLen<const LPoint> curve,Plot plot)
 {
  LPoint a=curve[0];
  LPoint b=curve[1];

  curve+=2;
  
  auto end=Algo::LineFirst(a,b,plot);
  
  while( !end.ok )
    {
     if( !curve )
       {
        plot(a.toPoint());
        plot(b.toPoint());
       
        return;
       }
     
     b=*curve;
     ++curve;
     
     end=Algo::LineFirst(a,b,plot);
    }
  
  while( +curve ) 
    {
     a=b;
     b=*curve;
     ++curve;
     
     auto next_end=Algo::LineNext(end,a,b,plot);
     
     while( !next_end.ok )
       {
        if( !curve )
          {
           Point B=b.toPoint();
           
           if( B!=end.ext )
             {
              Point A=a.toPoint();
            
              if( Algo::PointNear(end.ext,B) )
                {
                 plot(end.ext);
                }
              else if( Algo::PointNear(end.last,A) )
                {
                 plot(A);
                }
              else
                {
                 plot(end.ext);
                 plot(A);
                }
             }
          
           plot(B);
           
           return;
          }
        
        b=*curve;
        ++curve;
        
        next_end=Algo::LineNext(end,a,b,plot);
       }
    
     end=next_end;
    }
  
  plot(end.ext);
 }

void CommonDrawArt::path(PtrStepLen<const LPoint> curve,DesktopColor color)
 {
  path(curve,HPlot(buf,color));
 }

template <class Plot>
void CommonDrawArt::path_smooth(PtrStepLen<const LPoint> curve,Plot plot)
 {
  LPoint a=curve[0];
  LPoint b=curve[1];

  curve+=2;
  
  Point A=a.toPoint();
  
  plot(A);
  
  bool ok=Algo::LineSmooth(a,b,plot);
  
  while( !ok )
    {
     if( !curve )
       {
        Point B=b.toPoint();
        
        Algo::LineSmooth(A,B,plot);
        
        plot(B);
       
        return;
       }
     
     b=*curve;
     ++curve;
     
     ok=Algo::LineSmooth(a,b,plot);
    }
  
  while( +curve ) 
    {
     a=b;
     b=*curve;
     ++curve;
     
     bool ok=Algo::LineSmooth(a,b,plot);
     
     while( !ok )
       {
        if( !curve )
          {
           Point B=b.toPoint();
          
           plot(B);
          
           return;
          }
        
        b=*curve;
        ++curve;
        
        ok=Algo::LineSmooth(a,b,plot);
       }
    }
  
  plot(b.toPoint());
 }

void CommonDrawArt::path_smooth(PtrStepLen<const LPoint> curve,ColorName cname)
 {
  path_smooth(curve,SmoothPlot(buf,cname));
 }

void CommonDrawArt::path_micro1(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify)
 {
  path(curve, [this,color,magnify] (Point p) { gridCell(p,color,magnify); } );
 }

void CommonDrawArt::path_micro2(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify)
 {
  gridKnob(*curve,GridKnobBigLen,color,magnify);
  
  for(++curve; curve.len>1 ;++curve) gridKnob(*curve,GridKnobLen,color,magnify);
  
  gridKnob(*curve,GridKnobBigLen,color,magnify);
 }

void CommonDrawArt::path_micro3(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify)
 {
  LPoint lim=buf.getSize()/magnify;
  
  LPoint a=*curve;
  
  for(++curve; +curve ;++curve)
    {
     LPoint b=*curve;

     if( a>=Null && a<lim && b>=Null && b<lim ) 
       {
        Point A=(a*magnify).toPoint();
        Point B=(b*magnify).toPoint();
       
        buf.line(A,B,color);
       }
     
     a=b;
    }
 }

void CommonDrawArt::path_micro(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify)
 {
  path_micro1(curve,color,magnify);
  
  path_micro2(curve,GridKnob,magnify);
  path_micro3(curve,GridBaseline,magnify);
 }

void CommonDrawArt::path_smooth_micro1(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify)
 {
  if( +dots )
    {
     Point a=*dots-focus;
     
     for(++dots; +dots ;++dots)
       {
        Point b=*dots-focus;
        
        line_smooth_micro(a,b,cname,magnify);
        
        a=b;
       }
     
     gridCell(a,cname,magnify);
    }
 }

void CommonDrawArt::path_smooth_micro2(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify)
 {
  for(; +dots ;++dots) gridKnob(*dots-focus,GridKnobBigLen,cname,magnify);
 }

void CommonDrawArt::path_smooth_micro3(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify)
 {
  Point lim=Point::Max()/magnify;
  
  Point a=*dots-focus;
  
  for(++dots; +dots ;++dots)
    {
     Point b=*dots-focus;

     if( a>=-lim && a<lim && b>=-lim && b<lim ) 
       {
        Point A=a*magnify;
        Point B=b*magnify;
       
        buf.line(A,B,(DesktopColor)cname);
       }
     
     a=b;
    }
 }

void CommonDrawArt::line_smooth_micro(Point a,Point b,ColorName cname,Coord magnify)
 {
  Algo::LineSmooth(a,b,SmoothPlotMicro(*this,cname,magnify));
 }

void CommonDrawArt::path_smooth_micro(PtrStepLen<const LPoint> curve,ColorName cname,Coord magnify)
 {
  path_smooth(curve,SmoothPlotMicro(*this,cname,magnify));
  
  path_micro2(curve,GridKnob,magnify);
  path_micro3(curve,GridBaseline,magnify);
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

 // path

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
     
     if( dots.len==1 )
       {
        pixel(a,color);
        
        return;
       }
     
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
     StackObject<Algo::CurveDriver> driver;
     
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
     StackObject<Algo::CurveDriver> driver;
     
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
       StackObject<Algo::CurveDriver> driver;
       
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
       StackObject<Algo::CurveDriver> driver;
       
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
       StackObject<Algo::CurveDriver> driver;
       
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
       StackObject<Algo::CurveDriver> driver;
       
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
       StackObject<Algo::CurveDriver> driver;
       
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

 // path smooth

void CommonDrawArt::path_smooth(PtrLen<const Point> dots,ColorName cname)
 {
  if( +dots )
    {
     Point a=*dots;
     
     for(++dots; +dots ;++dots)
       {
        Point b=*dots;
        
        buf.line_smooth(a,b,cname);
        
        a=b;
       }
     
     pixel(a,cname);
    }
 }

void CommonDrawArt::loop_smooth(PtrLen<const Point> dots,ColorName cname)
 {
  if( +dots )
    {
     Point a=*dots;
     
     if( dots.len==1 )
       {
        pixel(a,cname);
        
        return;
       }
     
     Point o=a;
     
     for(++dots; +dots ;++dots)
       {
        Point b=*dots;
        
        buf.line_smooth(a,b,cname);
        
        a=b;
       }
     
     buf.line_smooth(a,o,cname);
    }
 }

void CommonDrawArt::curvePath_smooth(PtrLen<const Point> dots,ColorName cname)
 {
  if( dots.len>=4 )
    {
     StackObject<Algo::CurveDriver> driver;
     
     driver->spline(dots[0],dots[1],dots[2],dots[3]);
    
     path_smooth(driver->getCurve(),cname); 
     
     for(dots+=4; +dots ;++dots)
       {
        driver->shift(dots[0]);
        
        path_smooth(driver->getCurve(),cname); 
       }
     
     driver->shift();
     
     path_smooth(driver->getCurve(),cname);
     
     driver->shift();
     
     path_smooth(driver->getCurve(),cname); 
    }
  else if( dots.len==3 )
    {
     StackObject<Algo::CurveDriver> driver;
     
     driver->spline(dots[0],dots[1],dots[2],dots[2]);
    
     path_smooth(driver->getCurve(),cname); 
     
     driver->shift();
     
     path_smooth(driver->getCurve(),cname); 
    }
  else
    {
     path_smooth(dots,cname);
    }
 }

void CommonDrawArt::curveLoop_smooth(PtrLen<const Point> dots,ColorName cname)
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
       pixel(dots[0],cname);
      }
     break;
     
     case 2 :
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1];
      
       driver->spline(a,b,a,b,a,b);
       
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(a);
      
       path_smooth(driver->getCurve(),cname);
      }
     break;
     
     case 3 :
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2];
      
       driver->spline(a,b,c,a,b,c);
       
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(a);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(b);
      
       path_smooth(driver->getCurve(),cname);
      }
     break;
     
     case 4 :
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3];
      
       driver->spline(a,b,c,d,a,b);
       
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(c);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(d);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(a);
      
       path_smooth(driver->getCurve(),cname);
      }
     break;
     
     case 5 :
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3],
             e=dots[4];
      
       driver->spline(a,b,c,d,e,a);
       
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(b);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(c);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(d);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(e);
      
       path_smooth(driver->getCurve(),cname);
      }
     break;
     
     default:
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3],
             e=dots[4],
             f=dots[5];
      
       driver->spline(a,b,c,d,e,f);
       
       path_smooth(driver->getCurve(),cname);
       
       for(dots+=6; +dots ;++dots)
         {
          driver->shift(dots[0]);
         
          path_smooth(driver->getCurve(),cname); 
         }

       driver->shift(a);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(b);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(c);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(d);
      
       path_smooth(driver->getCurve(),cname);
       
       driver->shift(e);
      
       path_smooth(driver->getCurve(),cname);
      }
    }
 }

 // solid

void CommonDrawArt::solid(PtrLen<const Point> dots,SolidFlag flag,DesktopColor color)
 {
  Algo::Solid(dots,flag,HPlot(buf,color));
 }

void CommonDrawArt::curveSolid(PtrLen<const Point> dots,SolidFlag flag,DesktopColor color)
 {
  Collector<Point> temp;
  
  auto plot = [&temp] (Point p) { temp.append_copy(p); } ;
  
  switch( dots.len )
    {
     case 0 :
      {
       // do nothing
      }
     return;
     
     case 1 :
      {
       pixel(dots[0],color);
      }
     return;
     
     case 2 :
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1];
      
       driver->spline(a,b,a,b,a,b);
       
       path(driver->getCurve(),plot);
       
       driver->shift(a);
      
       path(driver->getCurve(),plot);
      }
     break;
     
     case 3 :
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2];
      
       driver->spline(a,b,c,a,b,c);
       
       path(driver->getCurve(),plot);
       
       driver->shift(a);
      
       path(driver->getCurve(),plot);
       
       driver->shift(b);
      
       path(driver->getCurve(),plot);
      }
     break;
     
     case 4 :
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3];
      
       driver->spline(a,b,c,d,a,b);
       
       path(driver->getCurve(),plot);
       
       driver->shift(c);
      
       path(driver->getCurve(),plot);
       
       driver->shift(d);
      
       path(driver->getCurve(),plot);
       
       driver->shift(a);
      
       path(driver->getCurve(),plot);
      }
     break;
     
     case 5 :
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3],
             e=dots[4];
      
       driver->spline(a,b,c,d,e,a);
       
       path(driver->getCurve(),plot);
       
       driver->shift(b);
      
       path(driver->getCurve(),plot);
       
       driver->shift(c);
      
       path(driver->getCurve(),plot);
       
       driver->shift(d);
      
       path(driver->getCurve(),plot);
       
       driver->shift(e);
      
       path(driver->getCurve(),plot);
      }
     break;
     
     default:
      {
       StackObject<Algo::CurveDriver> driver;
       
       Point a=dots[0],
             b=dots[1],
             c=dots[2],
             d=dots[3],
             e=dots[4],
             f=dots[5];
      
       driver->spline(a,b,c,d,e,f);
       
       path(driver->getCurve(),plot);
       
       for(dots+=6; +dots ;++dots)
         {
          driver->shift(dots[0]);
         
          path(driver->getCurve(),plot); 
         }

       driver->shift(a);
      
       path(driver->getCurve(),plot);
       
       driver->shift(b);
      
       path(driver->getCurve(),plot);
       
       driver->shift(c);
      
       path(driver->getCurve(),plot);
       
       driver->shift(d);
      
       path(driver->getCurve(),plot);
       
       driver->shift(e);
      
       path(driver->getCurve(),plot);
      }
    }

  Algo::SolidBorder(Range_const(temp.flat()),flag,HPlot(buf,color));
 }

 // circle

void CommonDrawArt::ball(Point center,Coord radius,DesktopColor color)
 {
  Algo::Ball(center,radius,HPlot(buf,color));  
 }

void CommonDrawArt::ballSpline(Point center,Coord radius,DesktopColor color)
 {
  CircleSpline spline(center,radius);
  
  curveSolid(spline.get(),SolidAll,color);
 }

void CommonDrawArt::circle(Point center,Coord radius,DesktopColor color)
 {
  Algo::Circle(center,radius,HPlot(buf,color));
 }

void CommonDrawArt::circleSpline(Point center,Coord radius,DesktopColor color)
 {
  CircleSpline spline(center,radius); 
  
  curveLoop(spline.get(),color);
 }

void CommonDrawArt::circleSpline_smooth(Point center,Coord radius,ColorName cname)
 {
  CircleSpline spline(center,radius); 
  
  curveLoop_smooth(spline.get(),cname);
 }

 // special

void CommonDrawArt::grid(Coord cell)
 {
  erase(GridBack);

  for(Coord x=cell/2; x<buf.dX() ;x+=cell) buf.lineY(x,0,buf.dY(),DesktopColor(GridLine));
  
  for(Coord y=cell/2; y<buf.dY() ;y+=cell) buf.lineX(y,0,buf.dX(),DesktopColor(GridLine));
 }

void CommonDrawArt::gridCell(Point p,DesktopColor color,Coord magnify)
 {
  if( p>=Null && p<buf.getSize()/magnify ) 
    knob(p*magnify,magnify/2-1,color);
 }

DesktopColor CommonDrawArt::probeCell(Point p,Coord magnify)
 {
  if( p>=Null && p<buf.getSize()/magnify )
    {
     return buf.pixel(p*magnify+Point(ProbeDisp,ProbeDisp));
    }
  
  return White;
 }

void CommonDrawArt::gridKnob(LPoint p,Coord len,DesktopColor color,Coord magnify)
 {
  if( p>=Null && p<buf.getSize()/magnify ) 
    knob((p*magnify).toPoint(),len,color);
 }

void CommonDrawArt::curvePath_micro(PtrLen<const Point> dots,DesktopColor color,Point focus,Coord magnify)
 {
  if( dots.len<4 ) return;
  
  focus.y-=buf.dY()/magnify;
  
  StackObject<Algo::CurveDriver> driver;
  
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

void CommonDrawArt::path_smooth_micro(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify)
 {
  focus.y-=buf.dY()/magnify;
 
  path_smooth_micro1(dots,cname,focus,magnify);
  path_smooth_micro2(dots,GridKnob,focus,magnify);
  path_smooth_micro3(dots,GridBaseline,focus,magnify);
 }

void CommonDrawArt::curvePath_smooth_micro(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify)
 {
  if( dots.len<4 ) return;
  
  focus.y-=buf.dY()/magnify;
  
  StackObject<Algo::CurveDriver> driver;
  
  driver->spline(dots[0]-focus,dots[1]-focus,dots[2]-focus,dots[3]-focus);
 
  path_smooth_micro(driver->getCurve(),cname,magnify); 
  
  for(dots+=4; +dots ;++dots)
    {
     driver->shift(dots[0]-focus);
     
     path_smooth_micro(driver->getCurve(),cname,magnify);
    }
  
  driver->shift();
  
  path_smooth_micro(driver->getCurve(),cname,magnify);
  
  driver->shift();
  
  path_smooth_micro(driver->getCurve(),cname,magnify);
 }

void CommonDrawArt::circle_micro(Point center,Coord radius,DesktopColor color,Point focus,Coord magnify)
 {
  focus.y-=buf.dY()/magnify;
  
  Algo::Circle(center-focus,radius, [this,color,magnify] (Point p) { gridCell(p,color,magnify); } );
 }

} // namespace Video
} // namespace CCore
 

