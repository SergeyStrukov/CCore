/* ShapeLib14.cpp */ 
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
 
#include <CCore/inc/video/ShapeLib.h>

#include <CCore/inc/video/SmoothDrawArt.h>
#include <CCore/inc/video/FigureLib.h>
 
namespace CCore {
namespace Video {

/* class YScrollShape */

Point YScrollShape::getMinSize() const
 {
  Coord w=RoundUpLen(cfg.width);
  
  return 2*Point::Diag(w)+Point(8,40);
 }

ScrollType YScrollShape::getType(MPoint point) const
 {
  MPane p(pane);
  
  if( !p || page>=total || !enable ) return ScrollType_None;
  
  MPoint a=pane.getBase();
  MPoint s=p.getSize();
  
  MCoord x0=a.x;
  MCoord x1=x0+s.x;
  
  if( point.x<x0 || point.x>x1 ) return ScrollType_None;
   
  MCoord y0=a.y;
  MCoord y1=y0+s.x;
  MCoord y5=y0+s.y;
  MCoord y4=y5-s.x;
  
  if( point.y<y0 || point.y>y5 ) return ScrollType_None;
  
  if( point.y<y1 ) return ScrollType_Down;
  
  if( point.y>y4 ) return ScrollType_Up;
  
  ulen cap=total-page;
  ulen pos_=Min(pos,cap);
  
  MCoord len=Max(Position(page,total,0,y4-y1),s.x);
  
  MCoord y2=Position(pos_,cap,y1,y4-len);
  MCoord y3=y2+len;
  
  if( point.y<y2 ) return ScrollType_DownPage;
  
  if( point.y>y3 ) return ScrollType_UpPage;
  
  return ScrollType_Drag;
 }

void YScrollShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  MPoint a=p.getBase();
  MPoint s=p.getSize();
  
  art.block(pane,cfg.back);
  
  if( s.y<5*s.x ) return;
  
  MCoord x0=a.x;
  MCoord x1=x0+s.x;
  
  MCoord y0=a.y;
  MCoord y1=y0+s.x;
  MCoord y5=y0+s.y;
  MCoord y4=y5-s.x;
  
  bool enable_=enable;
  
  MCoord y2;
  MCoord y3;
  
  if( page>=total )
    {
     enable_=false;
     
     y2=y1;
     y3=y4;
    }
  else
    {
     ulen cap=total-page;
     ulen pos_=Min(pos,cap);
     
     MCoord len=Max(Position(page,total,0,y4-y1),s.x);
     
     y2=Position(pos_,cap,y1,y4-len);
     y3=y2+len;
    }
  
  MCoord width=cfg.width;
  MCoord d=Max<MCoord>(s.x/6,width);
  
  // down
  
  if( down==ScrollType_Down )
    {
     FigureBox fig_box(x0,x1,y0,y1);
     
     fig_box.solid(art,cfg.bottom);
      
     FigureUpArrow fig(x0+d,x1-d,y0+d,y1-d);
     
     fig.transform(Smooth::DotShift(MPoint::Diag(width)));

     fig.curveSolid(art,enable_?cfg.face:cfg.bottom);
    }
  else
    {
     FigureTopBorder fig_top(x0,x1,y0,y1,width);
       
     fig_top.solid(art,focus?cfg.focus:cfg.top);
     
     FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);
     
     fig_bottom.solid(art,cfg.bottom);
     
     FigureUpArrow fig(x0+d,x1-d,y0+d,y1-d);
     
     ColorName cname;
     
     if( enable_ )
       {
        if( mover==ScrollType_Down )
          cname=cfg.faceUp;
        else
          cname=cfg.face;
       }
     else
       {
        cname=cfg.bottom;
       }

     fig.curveSolid(art,cname);
    }
  
  // up
  
  if( down==ScrollType_Up )
    {
     FigureBox fig_box(x0,x1,y4,y5);
   
     fig_box.solid(art,cfg.bottom);
     
     FigureDownArrow fig(x0+d,x1-d,y4+d,y5-d);
    
     fig.transform(Smooth::DotShift(MPoint::Diag(width)));

     fig.curveSolid(art,enable_?cfg.face:cfg.bottom);
    }
  else
    {
     FigureTopBorder fig_top(x0,x1,y4,y5,width);
      
     fig_top.solid(art,focus?cfg.focus:cfg.top);
    
     FigureBottomBorder fig_bottom(x0,x1,y4,y5,width);
      
     fig_bottom.solid(art,cfg.bottom);
    
     FigureDownArrow fig(x0+d,x1-d,y4+d,y5-d);
     
     ColorName cname;
     
     if( enable_ )
       {
        if( mover==ScrollType_Up )
          cname=cfg.faceUp;
        else
          cname=cfg.face;
       }
     else
       {
        cname=cfg.bottom;
       }
     
     fig.curveSolid(art,cname);
    }
  
  // down page
  
  {
   FigureBox fig_top(x0,x0+width,y1,y2);
   
   fig_top.solid(art,focus?cfg.focus:cfg.top);
   
   FigureBox fig_bottom(x1-width,x1,y1,y2);
   
   fig_bottom.solid(art,cfg.bottom);
  }
  
  if( down==ScrollType_DownPage )
    {
     MCoord e=(5*s.x)/12;
    
     FigureBox fig(x0+e,x1-e,y1,y2);
     
     fig.solid(art,cfg.face);
    }
  else
    {
     MCoord e=(3*s.x)/8;
     
     FigureBox fig(x0+e,x1-e,y1,y2);
     
     ColorName cname;
     
     if( enable_ )
       {
        if( mover==ScrollType_DownPage )
          cname=cfg.faceUp;
        else
          cname=cfg.face;
       }
     else
       {
        cname=cfg.bottom;
       }

     fig.solid(art,cname);
    }
  
  // up page
  
  {
   FigureBox fig_top(x0,x0+width,y3,y4);
   
   fig_top.solid(art,focus?cfg.focus:cfg.top);
   
   FigureBox fig_bottom(x1-width,x1,y3,y4);
   
   fig_bottom.solid(art,cfg.bottom);
  }
  
  if( down==ScrollType_UpPage )
    {
     MCoord e=(5*s.x)/12;
   
     FigureBox fig(x0+e,x1-e,y3,y4);
     
     fig.solid(art,cfg.face);
    }
  else
    {
     MCoord e=(3*s.x)/8;
     
     FigureBox fig(x0+e,x1-e,y3,y4);
     
     ColorName cname;
     
     if( enable_ )
       {
        if( mover==ScrollType_UpPage )
          cname=cfg.faceUp;
        else
          cname=cfg.face;
       }
     else
       {
        cname=cfg.bottom;
       }

     fig.solid(art,cname);
    }
  
  // drag
  
  {
   FigureBox fig(x0,x1,y2,y3);
   
   fig.solid(art,TwoField({x0,y0},cfg.top,{x1,y0},cfg.bottom));
  }
  
  {
   MCoord e=s.x/3;
   
   MCoord a1=x0+e;
   MCoord a2=x0+s.x/2;
   MCoord a3=x1-e;
   
   MCoord b0=y2+width;
   MCoord b1=y2+(y3-y2)/2;
   MCoord b2=y3-width;
   
   FigurePoints<4> fig;
   
   fig[0]={a1,b1};
   fig[1]={a2,b0};
   fig[2]={a3,b1};
   fig[3]={a2,b2};
   
   ColorName cname;
   
   if( enable_ )
     {
      if( mover==ScrollType_Drag )
        cname=cfg.faceUp;
      else
        cname=cfg.face;
     }
   else
     {
      cname=cfg.bottom;
     }

   fig.solid(art,cname);
  }
 }

} // namespace Video
} // namespace CCore
 

