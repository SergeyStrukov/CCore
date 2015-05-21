/* CommonDrawArt.cpp */ 
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
 
#include <CCore/inc/video/CommonDrawArt.h>
#include <CCore/inc/video/DrawAlgo.h>

namespace CCore {
namespace Video {

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
  
  Algo::LineSmooth(a,b,SPlot(*this,cname));
 }

/* class CommonDrawArt */

 // simple

void CommonDrawArt::pixel(Point p,DesktopColor color)
 {
  buf.pixel_safe(buf.map(p),color);
 }

void CommonDrawArt::erase(DesktopColor color)
 {
  buf.erase(color);
 }

void CommonDrawArt::block(Pane pane,DesktopColor color)
 {
  buf.block_safe(buf.map(pane),color);
 }

 // path

void CommonDrawArt::path(PtrLen<const Point> dots,DesktopColor color)
 {
  if( +dots )
    {
     Point a=buf.map(*dots);
     
     for(++dots; +dots ;++dots)
       {
        Point b=buf.map(*dots);
        
        buf.line(a,b,color);
        
        a=b;
       }
     
     buf.pixel_safe(a,color);
    }
 }

void CommonDrawArt::loop(PtrLen<const Point> dots,DesktopColor color)
 {
  if( +dots )
    {
     Point a=buf.map(*dots);
     
     if( dots.len==1 )
       {
        buf.pixel_safe(a,color);
        
        return;
       }
     
     Point o=a;
     
     for(++dots; +dots ;++dots)
       {
        Point b=buf.map(*dots);
        
        buf.line(a,b,color);
        
        a=b;
       }
     
     buf.line(a,o,color);
    }
 }

void CommonDrawArt::curvePath(PtrLen<const Point> dots,DesktopColor color)
 {
  if( dots.len>=3 )
    {
     Algo::CurvePath(dots,buf.getMapper(),HPlot(buf,color));
    } 
  else
    {
     path(dots,color);
    }
 }

void CommonDrawArt::curveLoop(PtrLen<const Point> dots,DesktopColor color)
 {
  Algo::CurveLoop(dots,buf.getMapper(),HPlot(buf,color));
 }

 // path smooth

void CommonDrawArt::path_smooth(PtrLen<const Point> dots,ColorName cname)
 {
  if( +dots )
    {
     Point a=buf.map(*dots);
     
     for(++dots; +dots ;++dots)
       {
        Point b=buf.map(*dots);
        
        buf.line_smooth(a,b,cname);
        
        a=b;
       }
     
     buf.pixel_safe(a,cname);
    }
 }

void CommonDrawArt::loop_smooth(PtrLen<const Point> dots,ColorName cname)
 {
  if( +dots )
    {
     Point a=buf.map(*dots);
     
     if( dots.len==1 )
       {
        buf.pixel_safe(a,cname);
        
        return;
       }
     
     Point o=a;
     
     for(++dots; +dots ;++dots)
       {
        Point b=buf.map(*dots);
        
        buf.line_smooth(a,b,cname);
        
        a=b;
       }
     
     buf.line_smooth(a,o,cname);
    }
 }

void CommonDrawArt::curvePath_smooth(PtrLen<const Point> dots,ColorName cname)
 {
  if( dots.len>=3 )
    {
     Algo::CurvePathSmooth(dots,buf.getMapper(),SPlot(buf,cname));
    }
  else
    {
     path_smooth(dots,cname);
    }
 }

void CommonDrawArt::curveLoop_smooth(PtrLen<const Point> dots,ColorName cname)
 {
  Algo::CurveLoopSmooth(dots,buf.getMapper(),SPlot(buf,cname));
 }

 // solid

void CommonDrawArt::solid(PtrLen<const Point> dots,SolidFlag flag,DesktopColor color)
 {
  Algo::Solid(dots,buf.getMapper(),flag,HPlot(buf,color));
 }

void CommonDrawArt::curveSolid(PtrLen<const Point> dots,SolidFlag flag,DesktopColor color)
 {
  Algo::CurveBorder border(dots,buf.getMapper());

  Algo::SolidBorder(border.complete(),flag,HPlot(buf,color));
 }

 // circle

void CommonDrawArt::ball(Point center,Coord radius,DesktopColor color)
 {
  Algo::Ball(buf.map(center),radius,HPlot(buf,color));  
 }

void CommonDrawArt::ballSpline(Point center,Coord radius,DesktopColor color)
 {
  CircleSpline spline(center,radius);
  
  curveSolid(spline.get(),SolidAll,color);
 }

void CommonDrawArt::circle(Point center,Coord radius,DesktopColor color)
 {
  Algo::Circle(buf.map(center),radius,HPlot(buf,color));
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

} // namespace Video
} // namespace CCore
 

