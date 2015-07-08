/* DragWindow.cpp */ 
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
 
#include <CCore/inc/video/DragWindow.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* DragPane() */

void DragPane(Pane &place,Point delta,DragType drag_type)
 {
  switch( drag_type )
    {
     case DragType_Top :
      {
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break; 
     
     case DragType_TopLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case DragType_Left :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
      }
     break;
     
     case DragType_BottomLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case DragType_Bottom :
      {
       place.dy+=delta.y;
      }
     break;
     
     case DragType_BottomRight :
      {
       place.dx+=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case DragType_Right :
      {
       place.dx+=delta.x;
      }
     break;
     
     case DragType_TopRight :
      {
       place.dx+=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case DragType_Bar :
      {
       place.x+=delta.x;
       
       place.y+=delta.y;
      }
     break;
    }
 }

/* class DragShape */

class DragShape::DrawArt : public Smooth::DrawArt
 {
  public:
  
   DrawArt(const DrawBuf &buf) : Smooth::DrawArt(buf) {}
 };

ColorName DragShape::dragColor(DragType zone) const
 {
  if( drag_type==zone ) return +cfg.dragActive;
  
  if( hilight==zone ) return +cfg.dragHilight;
  
  return +cfg.drag;
 }

void DragShape::draw_TopLeft(DrawArt &art) const
 {
  if( +dragTopLeft )
    {
     art.block(dragTopLeft,+cfg.frame);
 
     MPane p(dragTopLeft);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     x0+=width;
     x1-=width;
     
     y0+=width;
     y1-=width;
     
     FigurePoints<3> fig;
     
     fig[0]={x0,y0};
     fig[1]={x0,y1};
     fig[2]={x1,y0};
     
     fig.solid(art,dragColor(DragType_TopLeft));
    }
 }

void DragShape::draw_Left(DrawArt &art) const
 {
  if( +dragLeft )
    {
     art.block(dragLeft,+cfg.frame);
     
     MPane p(dragLeft);
     
     MCoord d=p.dx/2;
     MCoord x0=p.x+d;
     
     MCoord y0=p.y+d;
     MCoord y1=p.y+p.dy-d;
     
     MCoord w=p.dx/4;
     
     art.pathOf(w,dragColor(DragType_Left),MPoint(x0,y0),MPoint(x0,y1));
    }
 }

void DragShape::draw_BottomLeft(DrawArt &art) const
 {
  if( +dragBottomLeft )
    {
     art.block(dragBottomLeft,+cfg.frame);
 
     MPane p(dragBottomLeft);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     x0+=width;
     x1-=width;
     
     y0+=width;
     y1-=width;
     
     FigurePoints<3> fig;
     
     fig[0]={x0,y0};
     fig[1]={x0,y1};
     fig[2]={x1,y1};
     
     fig.solid(art,dragColor(DragType_BottomLeft));
    }
 }

void DragShape::draw_Bottom(DrawArt &art) const
 {
  if( +dragBottom )
    {
     art.block(dragBottom,+cfg.frame);
     
     MPane p(dragBottom);
     
     MCoord d=p.dy/2;
     MCoord y0=p.y+d;
     
     MCoord x0=p.x+d;
     MCoord x1=p.x+p.dx-d;
     
     MCoord w=p.dy/4;
     
     art.pathOf(w,dragColor(DragType_Bottom),MPoint(x0,y0),MPoint(x1,y0));
    }
 }

void DragShape::draw_BottomRight(DrawArt &art) const
 {
  if( +dragBottomRight )
    {
     art.block(dragBottomRight,+cfg.frame);
 
     MPane p(dragBottomRight);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     x0+=width;
     x1-=width;
     
     y0+=width;
     y1-=width;
     
     FigurePoints<3> fig;
     
     fig[0]={x1,y0};
     fig[1]={x0,y1};
     fig[2]={x1,y1};
     
     fig.solid(art,dragColor(DragType_BottomRight));
    }
 }

void DragShape::draw_Right(DrawArt &art) const
 {
  if( +dragRight )
    {
     art.block(dragRight,+cfg.frame);
     
     MPane p(dragRight);
     
     MCoord d=p.dx/2;
     MCoord x0=p.x+d;
     
     MCoord y0=p.y+d;
     MCoord y1=p.y+p.dy-d;
     
     MCoord w=p.dx/4;
     
     art.pathOf(w,dragColor(DragType_Right),MPoint(x0,y0),MPoint(x0,y1));
    }
 }

void DragShape::draw_TopRight(DrawArt &art) const
 {
  if( +dragTopRight )
    {
     art.block(dragTopRight,+cfg.frame);
 
     MPane p(dragTopRight);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     x0+=width;
     x1-=width;
     
     y0+=width;
     y1-=width;
     
     FigurePoints<3> fig;
     
     fig[0]={x0,y0};
     fig[1]={x1,y0};
     fig[2]={x1,y1};
     
     fig.solid(art,dragColor(DragType_TopRight));
    }
 }

void DragShape::draw_Alert(DrawArt &art) const
 {
  if( +btnAlert )
    {
     art.block(btnAlert,+cfg.frame);
     
     MPane p(btnAlert);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     MCoord ex=p.dx/8;

     FigureButton fig(x0,x1,y0,y1,ex);
     
     MCoord dx=p.dx/5;
     
     MCoord s0=x0+dx;
     MCoord s1=x1-dx;
     
     MCoord dy=p.dy/5;
     
     MCoord t0=y0+dy;
     MCoord t1=y1-dy;
     
     ColorName alert;
     
     if( alert_type==AlertType_No )
       {
        fig.curveLoop(art,HalfPos,+cfg.width,+cfg.btnEdge);
        
        alert=+cfg.btnPictNoAlert;
       }
     else
       {
        if( btn_type==DragType_Alert )
          {
           fig.curveSolid(art,+cfg.bottom);
           
           s0+=width;
           s1+=width;
           t0+=width;
           t1+=width;
          }
        else
          {
           ColorName top=+cfg.btnFaceTop;
           ColorName bottom=(hilight==DragType_Alert)?+cfg.btnFaceHilight:+cfg.btnFace;
           
           fig.curveSolid(art,TwoField({x0,y0},top,{x0,y1},bottom));
           
           fig.curveLoop(art,HalfPos,width,+cfg.btnEdge);
          }
       
        alert=(alert_type==AlertType_Closed)?+cfg.btnPictAlert:+cfg.btnPictCloseAlert;
       }
     
     if( !alert_blink )
       {
        MCoord c=(t1-t0)/6;
        MCoord d=4*c+(2*c)/3;
        MCoord r=(3*c)/4;
        MCoord s=s0+(s1-s0)/2;
        
        FigureDots<4> fig;
        
        fig[0]={{s-c,t0+c}};
        fig[1]={{s,t0}};
        fig[2]={{s+c,t0+c}};
        fig[3]={{s,t0+d},Smooth::DotBreak};
        
        fig.curveSolid(art,alert);
        
        art.ball({s,t0+d+r},r,alert);
       }
    }
 }

void DragShape::draw_Min(DrawArt &art) const
 {
  if( +btnMin )
    {
     art.block(btnMin,+cfg.frame);
     
     MPane p(btnMin);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     MCoord ex=p.dx/8;

     FigureButton fig(x0,x1,y0,y1,ex);
     
     MCoord dx=p.dx/5;
     
     MCoord s0=x0+dx;
     MCoord s1=x1-dx;
     
     MCoord dy=p.dy/5;
     
     MCoord t0=y0+dy;
     MCoord t1=y1-dy;
     
     if( btn_type==DragType_Min )
       {
        fig.curveSolid(art,+cfg.bottom);
        
        s0+=width;
        s1+=width;
        t0+=width;
        t1+=width;
       }
     else
       {
        ColorName top=+cfg.btnFaceTop;
        ColorName bottom=(hilight==DragType_Min)?+cfg.btnFaceHilight:+cfg.btnFace;
        
        fig.curveSolid(art,TwoField({x0,y0},top,{x0,y1},bottom));
        
        fig.curveLoop(art,HalfPos,width,+cfg.btnEdge);
       }
     
     FigureBox fig_pict(s0,s1,t1-(t1-t0)/4,t1);
     
     fig_pict.solid(art,+cfg.btnPict);
    }
 }

void DragShape::draw_Max(DrawArt &art) const
 {
  if( +btnMax )
    {
     art.block(btnMax,+cfg.frame);
     
     MPane p(btnMax);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     MCoord ex=p.dx/8;

     FigureButton fig(x0,x1,y0,y1,ex);
     
     MCoord dx=p.dx/5;
     
     MCoord s0=x0+dx;
     MCoord s1=x1-dx;
     
     MCoord dy=p.dy/5;
     
     MCoord t0=y0+dy;
     MCoord t1=y1-dy;
     
     if( btn_type==DragType_Max )
       {
        fig.curveSolid(art,+cfg.bottom);
        
        s0+=width;
        s1+=width;
        t0+=width;
        t1+=width;
       }
     else
       {
        ColorName top=+cfg.btnFaceTop;
        ColorName bottom=(hilight==DragType_Max)?+cfg.btnFaceHilight:+cfg.btnFace;
        
        fig.curveSolid(art,TwoField({x0,y0},top,{x0,y1},bottom));
        
        fig.curveLoop(art,HalfPos,width,+cfg.btnEdge);
       }
     
     if( max_button )
       {
        FigureBox fig_pict(s0,s1,t0,t1);
       
        fig_pict.solid(art,+cfg.btnPict);
       }
     else
       {
        MCoord e=(t1-t0)/5;
       
        FigureBox fig_pict(s0,s1-(s1-s0)/3,t0+e,t1-e);
      
        fig_pict.solid(art,+cfg.btnPict);
       }
    }
 }

void DragShape::draw_Close(DrawArt &art) const
 {
  if( +btnClose )
    {
     art.block(btnClose,+cfg.frame);
     
     MPane p(btnClose);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     MCoord ex=p.dx/8;

     FigureButton fig(x0,x1,y0,y1,ex);
     
     MCoord dx=p.dx/5;
     
     MCoord s0=x0+dx;
     MCoord s1=x1-dx;
     
     MCoord dy=p.dy/5;
     
     MCoord t0=y0+dy;
     MCoord t1=y1-dy;
     
     if( btn_type==DragType_Close )
       {
        fig.curveSolid(art,+cfg.bottom);
        
        s0+=width;
        s1+=width;
        t0+=width;
        t1+=width;
       }
     else
       {
        ColorName top=+cfg.btnFaceTop;
        ColorName bottom=(hilight==DragType_Close)?+cfg.btnFaceHilight:+cfg.btnFace;
        
        fig.curveSolid(art,TwoField({x0,y0},top,{x0,y1},bottom));
        
        fig.curveLoop(art,HalfPos,width,+cfg.btnEdge);
       }

     MCoord w=p.dx/8;
     
     ColorName pict=+cfg.btnPictClose;
     
     art.pathOf(w,pict,MPoint(s0,t0),MPoint(s1,t1));
     art.pathOf(w,pict,MPoint(s0,t1),MPoint(s1,t0));
    }
 }

void DragShape::draw_Bar(DrawArt &art) const
 {
  art.block(dragBar,+cfg.frame);
  
  if( +titleBar )
    {
     MPane p(titleBar);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     MCoord ex=p.dy/4;
     
     ColorName top=+cfg.top;
     ColorName bottom=+cfg.bottom;
     
     FigureButton fig(x0,x1,y0,y1,ex);
     
     fig.curveSolid(art,has_focus?+cfg.active:+cfg.inactive);
     
     fig.getTop().curvePath(art,HalfPos,width,bottom);
     fig.getBottom().curvePath(art,HalfPos,width,top);
     
     Pane pane=Shrink(titleBar,RoundUpLen(ex),RoundUpLen(width));
     
     cfg.title_font.get()->text(art.getBuf(),pane,TextPlace(AlignX_Left,AlignY_Center),Range(title),+cfg.title);
    }
 }

void DragShape::draw_Border(DrawArt &art) const
 {
  MCoord width=+cfg.width;
  ColorName top=+cfg.top;
  ColorName bottom=+cfg.bottom;
  
  if( size>Null )
    {
     MPane outer(Extent(Null,size));
     
     MCoord x0=outer.x;
     MCoord x1=x0+outer.dx;
     
     MCoord y0=outer.y;
     MCoord y1=y0+outer.dy;
  
     FigureTopBorder fig_top(x0,x1,y0,y1,width);
     
     fig_top.solid(art,top);
     
     FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);
     
     fig_bottom.solid(art,bottom);
    }
  
  if( +client )
    {
     MPane inner(client);
    
     MCoord x0=inner.x;
     MCoord x1=x0+inner.dx;
     
     MCoord y0=inner.y;
     MCoord y1=y0+inner.dy;
     
     x0-=width;
     x1+=width;
     y0-=width;
     y1+=width;
     
     FigureTopBorder fig_top(x0,x1,y0,y1,width);
     
     fig_top.solid(art,bottom);
     
     FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);
     
     fig_bottom.solid(art,top);
    }
 }

void DragShape::reset(const String &title_,bool max_button_)
 {
  has_focus=false;
  max_button=max_button_;
  
  drag_type=DragType_None;
  hilight=DragType_None;
  btn_type=DragType_None;
  alert_type=AlertType_No;
  alert_blink=false;
  
  title=title_;
 }

void DragShape::layout(Point size_)
 {
  size=size_;
  
  Coord dxy=+cfg.frame_dxy;
  Coord tdy=+cfg.title_dy;
  Coord bdx=+cfg.btn_dx;
  Coord bdy=+cfg.btn_dy;
  
  if( size>Point(2*dxy+5*bdx+bdx/2+Max(dxy,tdy),dxy+Max<Coord>(2*dxy,tdy)) )
    {
     Pane pane=Extent(Null,size);
     
     Pane left=SplitX(dxy,pane);
     Pane right=SplitX(pane,dxy);
    
     dragTopLeft=SplitY(dxy,left);
     dragBottomLeft=SplitY(left,dxy);
     dragLeft=left;
     
     dragTopRight=SplitY(dxy,right);
     dragBottomRight=SplitY(right,dxy);
     dragRight=right;
     
     dragBar=SplitY(tdy,pane);
     dragBottom=SplitY(pane,dxy);
     client=pane;
     
     Coord yb=(tdy-bdy)/2;
     
     Coord tx=dragBar.dx-5*bdx; 
     
     Coord xb0=dragBar.x+tx;
     Coord xb1=xb0+bdx+bdx/8;
     Coord xb2=xb1+bdx+bdx/8;
     Coord xb3=xb2+bdx+bdx/2;
     
     btnAlert=Pane(xb0,yb,bdx,bdy);
     btnMin=Pane(xb1,yb,bdx,bdy);
     btnMax=Pane(xb2,yb,bdx,bdy);
     btnClose=Pane(xb3,yb,bdx,bdy);
     
     Coord w=RoundUpLen(+cfg.width);
     
     titleBar=Pane(dragBar.x,w,tx-bdx/4,tdy-2*w);
    }
  else
    {
     dragTopLeft=Empty;
     dragBottomLeft=Empty;
     dragLeft=Empty;
     
     dragTopRight=Empty;
     dragBottomRight=Extent(Null,size);
     dragRight=Empty;
     
     dragBar=Empty;
     dragBottom=Empty;
     client=Empty;
     
     btnAlert=Empty;
     btnMin=Empty;
     btnMax=Empty;
     btnClose=Empty;
     
     titleBar=Empty;
    }
 }

void DragShape::draw(const DrawBuf &buf) const
 {
  try
    {
     DrawArt art(buf);
     
     draw_TopLeft(art);
     draw_Left(art);
     draw_BottomLeft(art);
     draw_Bottom(art);
     draw_BottomRight(art);
     draw_Right(art);
     draw_TopRight(art);
     
     draw_Bar(art);
     
     draw_Alert(art);
     draw_Min(art);
     draw_Max(art);
     draw_Close(art);
     
     draw_Border(art);
    }
  catch(CatchType)
    {
    }
 }

void DragShape::draw(const DrawBuf &buf,DragType drag_type) const
 {
  try
    {
     DrawArt art(buf);
     
     switch( drag_type )
       {
        case DragType_TopLeft     : draw_TopLeft(art); break; 
        case DragType_Left        : draw_Left(art); break;
        case DragType_BottomLeft  : draw_BottomLeft(art); break;
        case DragType_Bottom      : draw_Bottom(art); break;
        case DragType_BottomRight : draw_BottomRight(art); break; 
        case DragType_Right       : draw_Right(art); break;
        case DragType_TopRight    : draw_TopRight(art); break;
        
        case DragType_Alert       : draw_Alert(art); break;
        case DragType_Min         : draw_Min(art); break;
        case DragType_Max         : draw_Max(art); break;
        case DragType_Close       : draw_Close(art); break;
       }
     
     draw_Border(art);
    }
  catch(CatchType)
    {
    }
 }

Pane DragShape::getPane(DragType drag_type) const
 {
  switch( drag_type )
    {
     case DragType_TopLeft     : return dragTopLeft; 
     case DragType_Left        : return dragLeft;
     case DragType_BottomLeft  : return dragBottomLeft;
     case DragType_Bottom      : return dragBottom;
     case DragType_BottomRight : return dragBottomRight; 
     case DragType_Right       : return dragRight;
     case DragType_TopRight    : return dragTopRight;
     
     case DragType_Alert       : return btnAlert;
     case DragType_Min         : return btnMin;
     case DragType_Max         : return btnMax;
     case DragType_Close       : return btnClose;
     
     default: return Empty;
    }
 }

DragType DragShape::dragTest(Point point) const
 {
  if( dragTopLeft.contains(point) ) return DragType_TopLeft;

  if( dragLeft.contains(point) ) return DragType_Left;
  
  if( dragBottomLeft.contains(point) ) return DragType_BottomLeft;
  
  if( dragBottom.contains(point) ) return DragType_Bottom;
  
  if( dragBottomRight.contains(point) ) return DragType_BottomRight;
  
  if( dragRight.contains(point) ) return DragType_Right;
  
  if( dragTopRight.contains(point) ) return DragType_TopRight;
  
  if( dragBar.contains(point) ) 
    {
     if( btnAlert.contains(point) ) return DragType_Alert;
      
     if( btnMin.contains(point) ) return DragType_Min;
    
     if( btnMax.contains(point) ) return DragType_Max;
    
     if( btnClose.contains(point) ) return DragType_Close;
     
     return DragType_Bar;
    }
  
  return DragType_None;
 }

} // namespace Video
} // namespace CCore
 

