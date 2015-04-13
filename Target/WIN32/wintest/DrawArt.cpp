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
     LineDriver driver(sy,sx);
    
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
  
  LineSmooth(a,b,cname,SmoothPlot(*this));
 }

void CommonDrawArt::WorkBuf::segment(Segment seg,Coord y,DesktopColor color)
 {
  if( seg.a<0 ) seg.a=0;
  
  if( seg.b>=dx ) seg.b=dx-1;
  
  if( seg.a>seg.b ) return;
  
  HLine(place(Point(seg.a,y)),Coord( seg.b-seg.a+1 ),color);
 }

template <class Solid>
void CommonDrawArt::WorkBuf::solid(Solid solid,DesktopColor color)
 {
  if( !(*this) ) return;
  
  Coord bottom=solid.bottom();
  Coord top=solid.top();
  
  if( bottom<0 ) bottom=0;
  
  if( top>=dy ) top=dy-1;
  
  if( bottom>top ) return;
  
  segment(solid.set(bottom),bottom,color);
  
  while( bottom<top ) segment(solid.up(),++bottom,color);
 }

/* class CommonDrawArt */

template <class Plot>
void CommonDrawArt::path(PtrStepLen<const LPoint> curve,DesktopColor color,Plot plot)
 {
  LPoint a=curve[0];
  LPoint b=curve[1];

  curve+=2;
  
  auto end=LineFirst(a,b,color,plot);
  
  while( !end.ok )
    {
     if( !curve )
       {
        plot(a.toPoint(),color);
        plot(b.toPoint(),color);
       
        return;
       }
     
     b=*curve;
     ++curve;
     
     end=LineFirst(a,b,color,plot);
    }
  
  while( +curve ) 
    {
     a=b;
     b=*curve;
     ++curve;
     
     auto next_end=LineNext(end,a,b,color,plot);
     
     while( !next_end.ok )
       {
        if( !curve )
          {
           Point B=b.toPoint();
           
           if( B!=end.ext )
             {
              Point A=a.toPoint();
            
              if( PointNear(end.ext,B) )
                {
                 plot(end.ext,color);
                }
              else if( PointNear(end.last,A) )
                {
                 plot(A,color);
                }
              else
                {
                 plot(end.ext,color);
                 plot(A,color);
                }
             }
          
           plot(B,color);
           
           return;
          }
        
        b=*curve;
        ++curve;
        
        next_end=LineNext(end,a,b,color,plot);
       }
    
     end=next_end;
    }
  
  plot(end.ext,color);
 }

void CommonDrawArt::path(PtrStepLen<const LPoint> curve,DesktopColor color)
 {
  path(curve,color, [this] (Point p,DesktopColor color) { pixel(p,color); } );
 }

template <class Plot>
void CommonDrawArt::path_smooth(PtrStepLen<const LPoint> curve,ColorName cname,Plot plot)
 {
  LPoint a=curve[0];
  LPoint b=curve[1];

  curve+=2;
  
  Point A=a.toPoint();
  
  plot(A,cname);
  
  bool ok=LineSmooth(a,b,cname,plot);
  
  while( !ok )
    {
     if( !curve )
       {
        Point B=b.toPoint();
        
        LineSmooth(A,B,cname,plot);
        
        plot(B,cname);
       
        return;
       }
     
     b=*curve;
     ++curve;
     
     ok=LineSmooth(a,b,cname,plot);
    }
  
  while( +curve ) 
    {
     a=b;
     b=*curve;
     ++curve;
     
     bool ok=LineSmooth(a,b,cname,plot);
     
     while( !ok )
       {
        if( !curve )
          {
           Point B=b.toPoint();
          
           plot(B,cname);
          
           return;
          }
        
        b=*curve;
        ++curve;
        
        ok=LineSmooth(a,b,cname,plot);
       }
    }
  
  plot(b.toPoint(),cname);
 }

void CommonDrawArt::path_smooth(PtrStepLen<const LPoint> curve,ColorName cname)
 {
  path_smooth(curve,cname, SmoothPlot(buf) );
 }

void CommonDrawArt::path_micro1(PtrStepLen<const LPoint> curve,DesktopColor color,Coord magnify)
 {
  path(curve,color, [this,magnify] (Point p,DesktopColor color) { gridCell(p,color,magnify); } );
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

void CommonDrawArt::line_smooth_micro(Point a,Point b,ColorName cname,Coord magnify)
 {
  LineSmooth(a,b,cname, SmoothPlotMicro(*this,magnify) );
 }

void CommonDrawArt::path_smooth_micro(PtrStepLen<const LPoint> curve,ColorName cname,Coord magnify)
 {
  path_smooth(curve,cname, SmoothPlotMicro(*this,magnify) );
  
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
     StackObject<CurveDriver> driver;
     
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
     StackObject<CurveDriver> driver;
     
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
       StackObject<CurveDriver> driver;
       
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
       StackObject<CurveDriver> driver;
       
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
       StackObject<CurveDriver> driver;
       
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
       StackObject<CurveDriver> driver;
       
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
       StackObject<CurveDriver> driver;
       
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

void CommonDrawArt::solid(PtrLen<const Point> dots,DesktopColor color) // TODO
 {
  Used(dots);
  Used(color);
 }

void CommonDrawArt::curveSolid(PtrLen<const Point> dots,DesktopColor color) // TODO
 {
  Used(dots);
  Used(color);
 }

 // circle

void CommonDrawArt::ball(Point center,Coord radius,DesktopColor color) // TODO
 {
  if( radius<=0 ) return;
  
  class Solid
   {
     Point center;
     Coord radius;
     
     Coord y = 0 ;
     
    private:
     
     static LCoord Root(LCoord S) // S > 0
      {
       LCoord x=S;
       
       for(unsigned cnt=100; cnt ;cnt--)
         {
          if( Sq(x)<S ) return x;
          
          LCoord next=LCoord( (x+S/x)/2 );
          
          if( next>=x ) return x-1;
          
          x=next;
         }
       
       return x;
      }
     
     Segment cur() const
      {
       auto x=Root(Sq<LCoord>(radius+1)-Sq<LCoord>(y));
       
       return {Coord(center.x-x),Coord(center.x+x)};
      }
     
    public:
    
     Solid(Point center_,Coord radius_) : center(center_),radius(radius_) {}
     
     Coord bottom() const { return center.y-radius; }
     
     Coord top() const { return center.y+radius; }
     
     Segment set(Coord y_)
      {
       y=y_-center.y;
       
       return cur();
      }
     
     Segment up()
      {
       y++;
       
       return cur();
      }
   };
  
  buf.solid(Solid(center,radius),color);
 }

void CommonDrawArt::circle(Point center,Coord radius,DesktopColor color)
 {
  Circle(center,radius,color, [this] (Point p,DesktopColor color) { pixel(p,color); } );
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

void CommonDrawArt::path_smooth_micro(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify)
 {
  if( +dots )
    {
     focus.y-=buf.dY()/magnify;
    
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

void CommonDrawArt::curvePath_smooth_micro(PtrLen<const Point> dots,ColorName cname,Point focus,Coord magnify)
 {
  if( dots.len<4 ) return;
  
  focus.y-=buf.dY()/magnify;
  
  StackObject<CurveDriver> driver;
  
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
  
  Circle(center-focus,radius,color, [this,magnify] (Point p,DesktopColor color) { gridCell(p,color,magnify); } );
 }

} // namespace Video
} // namespace CCore
 

