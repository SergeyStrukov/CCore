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

VColor DragShape::dragColor(DragType zone) const
 {
  if( drag_type==zone ) return +cfg.dragActive;
  
  if( hilight==zone ) return +cfg.dragHilight;
  
  return +cfg.drag;
 }

void DragShape::draw_Frame(DrawArt &art) const
 {
  VColor top=+cfg.frame;
  VColor bottom=+cfg.top;
  
  if( !client )
    {
     art.block(Pane(Null,size),top);
    
     return;
    }
  
  MPane outer(Pane(Null,size));
  MPane inner(client);

  // top
  
  {
   MCoord x0=outer.x;
   MCoord x1=outer.ex;
   
   MCoord y0=outer.y;
   MCoord y1=inner.y;
   
   FigureBox fig(x0,x1,y0,y1);
   
   fig.solid(art,TwoField({x0,y0},top,{x0,y1},bottom));
  }
  
  // bottom
  
  {
   MCoord x0=outer.x;
   MCoord x1=outer.ex;
   
   MCoord y0=inner.ey;
   MCoord y1=outer.ey;
   
   FigureBox fig(x0,x1,y0,y1);
   
   fig.solid(art,TwoField({x0,y0},top,{x0,y1},bottom));
  }
  
  // left
  
  {
   MCoord x0=outer.x;
   MCoord x1=inner.x;
   
   MCoord y0=outer.y;
   MCoord y1=inner.y;
   MCoord y2=inner.ey;
   MCoord y3=outer.ey;
   
   FigurePoints<4> fig;
   
   fig[0]={x0,y0};
   fig[1]={x1,y1};
   fig[2]={x1,y2};
   fig[3]={x0,y3};
   
   fig.solid(art,TwoField({x0,y0},top,{x1,y0},bottom));
  } 

  // right
  
  {
   MCoord x0=inner.ex;
   MCoord x1=outer.ex;
   
   MCoord y0=outer.y;
   MCoord y1=inner.y;
   MCoord y2=inner.ey;
   MCoord y3=outer.ey;
   
   FigurePoints<4> fig;
   
   fig[0]={x0,y1};
   fig[1]={x1,y0};
   fig[2]={x1,y3};
   fig[3]={x0,y2};
   
   fig.solid(art,TwoField({x0,y0},top,{x1,y0},bottom));
  }
 }

void DragShape::draw_TopLeft(DrawArt &art) const
 {
  if( +dragTopLeft )
    {
     MPane p(dragTopLeft);
     
     MCoord width=+cfg.width;
     
     p.shrink(width);
     
     FigurePoints<3> fig;
     
     fig[0]=p.getTopLeft();
     fig[1]=p.getTopRight();
     fig[2]=p.getBottomLeft();
     
     fig.solid(art,dragColor(DragType_TopLeft));
    }
 }

void DragShape::draw_Left(DrawArt &art) const
 {
  if( +dragLeft )
    {
     MPane p(dragLeft);
     
     MCoord d=p.dx/2;
     MCoord x0=p.x+d;
     
     MCoord y0=p.y+d;
     MCoord y1=p.ey-d;
     
     MCoord w=p.dx/4;
     
     art.pathOf(w,dragColor(DragType_Left),MPoint(x0,y0),MPoint(x0,y1));
    }
 }

void DragShape::draw_BottomLeft(DrawArt &art) const
 {
  if( +dragBottomLeft )
    {
     MPane p(dragBottomLeft);
     
     MCoord width=+cfg.width;
     
     p.shrink(width);
     
     FigurePoints<3> fig;
     
     fig[0]=p.getTopLeft();
     fig[1]=p.getBottomLeft();
     fig[2]=p.getBottomRight();
     
     fig.solid(art,dragColor(DragType_BottomLeft));
    }
 }

void DragShape::draw_Bottom(DrawArt &art) const
 {
  if( +dragBottom )
    {
     MPane p(dragBottom);
     
     MCoord d=p.dy/2;
     MCoord y0=p.y+d;
     
     MCoord x0=p.x+d;
     MCoord x1=p.ex-d;
     
     MCoord w=p.dy/4;
     
     art.pathOf(w,dragColor(DragType_Bottom),MPoint(x0,y0),MPoint(x1,y0));
    }
 }

void DragShape::draw_BottomRight(DrawArt &art) const
 {
  if( +dragBottomRight )
    {
     MPane p(dragBottomRight);
     
     MCoord width=+cfg.width;
     
     p.shrink(width);
     
     FigurePoints<3> fig;
     
     fig[0]=p.getTopRight();
     fig[1]=p.getBottomRight();
     fig[2]=p.getBottomLeft();
     
     fig.solid(art,dragColor(DragType_BottomRight));
    }
 }

void DragShape::draw_Right(DrawArt &art) const
 {
  if( +dragRight )
    {
     MPane p(dragRight);
     
     MCoord d=p.dx/2;
     MCoord x0=p.x+d;
     
     MCoord y0=p.y+d;
     MCoord y1=p.ey-d;
     
     MCoord w=p.dx/4;
     
     art.pathOf(w,dragColor(DragType_Right),MPoint(x0,y0),MPoint(x0,y1));
    }
 }

void DragShape::draw_TopRight(DrawArt &art) const
 {
  if( +dragTopRight )
    {
     MPane p(dragTopRight);
     
     MCoord width=+cfg.width;
     
     p.shrink(width);
     
     FigurePoints<3> fig;
     
     fig[0]=p.getTopLeft();
     fig[1]=p.getTopRight();
     fig[2]=p.getBottomRight();
     
     fig.solid(art,dragColor(DragType_TopRight));
    }
 }

void DragShape::draw_Bar(DrawArt &art) const
 {
  if( +titleBar )
    {
     MPane p(titleBar);
     
     MCoord width=+cfg.width;
     
     MCoord ex=p.dy/4;
     
     VColor top=+cfg.top;
     VColor bottom=+cfg.bottom;
     
     FigureButton fig(p,ex);
     
     fig.curveSolid(art,has_focus?+cfg.active:+cfg.inactive);
     
     fig.getTop().curvePath(art,HalfPos,width,top);
     fig.getBottom().curvePath(art,HalfPos,width,bottom);
     
     Pane pane=titleBar.shrink(RoundUpLen(ex),RoundUpLen(width));
     
     cfg.title_font.get()->text(art.getBuf(),pane,TextPlace(AlignX_Left,AlignY_Center),Range(title),+cfg.title);
    }
 }

void DragShape::draw_Alert(DrawArt &art) const
 {
  if( +btnAlert )
    {
     MPane p(btnAlert);
     
     MCoord width=+cfg.width;
     
     MCoord ex=p.dx/8;

     FigureButton fig(p,ex);
     
     MPane q=p.shrink(p.dx/5,p.dy/5);
     
     VColor top=+cfg.top;
     
     VColor alert;
     
     if( alert_type==AlertType_No )
       {
        fig.curveLoop(art,HalfPos,width,top);
        
        alert=+cfg.btnPictNoAlert;
       }
     else
       {
        if( btn_type==DragType_Alert )
          {
           fig.curveSolid(art,top);
           
           q+=MPoint::Diag(width);
          }
        else
          {
           VColor face=(hilight==DragType_Alert)?+cfg.btnFaceHilight:+cfg.btnFace;
           
           VColor bottom=+cfg.bottom;
           
           fig.curveSolid(art,face);
           
           fig.getTop().curvePath(art,HalfPos,width,top);
           fig.getBottom().curvePath(art,HalfPos,width,bottom);
          }
       
        alert=(alert_type==AlertType_Closed)?+cfg.btnPictAlert:+cfg.btnPictCloseAlert;
       }
     
     if( !alert_blink )
       {
        MCoord c=q.dy/6;
        MCoord d=4*c+(2*c)/3;
        MCoord r=(3*c)/4;
        MCoord s=q.x+q.dx/2;
        
        FigureDots<4> fig;
        
        fig[0]={{s-c,q.y+c}};
        fig[1]={{s,q.y}};
        fig[2]={{s+c,q.y+c}};
        fig[3]={{s,q.y+d},Smooth::DotBreak};
        
        fig.curveSolid(art,alert);
        
        art.ball({s,q.y+d+r},r,alert);
       }
    }
 }

void DragShape::draw_Min(DrawArt &art) const
 {
  if( +btnMin )
    {
     MPane p(btnMin);
     
     MCoord width=+cfg.width;
     
     MCoord ex=p.dx/8;

     FigureButton fig(p,ex);
     
     MPane q=p.shrink(p.dx/5,p.dy/5);
     
     VColor top=+cfg.top;
     
     if( btn_type==DragType_Min )
       {
        fig.curveSolid(art,top);
        
        q+=MPoint::Diag(width);
       }
     else
       {
        VColor face=(hilight==DragType_Min)?+cfg.btnFaceHilight:+cfg.btnFace;
        
        VColor bottom=+cfg.bottom;
        
        fig.curveSolid(art,face);
        
        fig.getTop().curvePath(art,HalfPos,width,top);
        fig.getBottom().curvePath(art,HalfPos,width,bottom);
       }
     
     FigureBox fig_pict(q.x,q.ex,q.ey-q.dy/4,q.ey);
     
     fig_pict.solid(art,+cfg.btnPict);
    }
 }

void DragShape::draw_Max(DrawArt &art) const
 {
  if( +btnMax )
    {
     MPane p(btnMax);
     
     MCoord width=+cfg.width;
     
     MCoord ex=p.dx/8;

     FigureButton fig(p,ex);
     
     MPane q=p.shrink(p.dx/5,p.dy/5);
     
     VColor top=+cfg.top;
     
     if( btn_type==DragType_Max )
       {
        fig.curveSolid(art,top);
        
        q+=MPoint::Diag(width);
       }
     else
       {
        VColor face=(hilight==DragType_Max)?+cfg.btnFaceHilight:+cfg.btnFace;
        
        VColor bottom=+cfg.bottom;
        
        fig.curveSolid(art,face);
        
        fig.getTop().curvePath(art,HalfPos,width,top);
        fig.getBottom().curvePath(art,HalfPos,width,bottom);
       }
     
     VColor pict=+cfg.btnPict;
     
     if( max_button )
       {
        FigureBox fig_pict(q);
       
        fig_pict.solid(art,pict);
       }
     else
       {
        MCoord e=q.dy/5;
       
        FigureBox fig_pict(q.x,q.ex-q.dx/3,q.y+e,q.ey-e);
      
        fig_pict.solid(art,pict);
       }
    }
 }

void DragShape::draw_Close(DrawArt &art) const
 {
  if( +btnClose )
    {
     MPane p(btnClose);
     
     MCoord width=+cfg.width;
     
     MCoord ex=p.dx/8;

     FigureButton fig(p,ex);
     
     MPane q=p.shrink(p.dx/5,p.dy/5);
     
     VColor top=+cfg.top;
     
     if( btn_type==DragType_Close )
       {
        fig.curveSolid(art,top);
        
        q+=MPoint::Diag(width);
       }
     else
       {
        VColor face=(hilight==DragType_Close)?+cfg.btnFaceHilight:+cfg.btnFace;
        
        VColor bottom=+cfg.bottom;
        
        fig.curveSolid(art,face);
        
        fig.getTop().curvePath(art,HalfPos,width,top);
        fig.getBottom().curvePath(art,HalfPos,width,bottom);
       }

     MCoord w=p.dx/8;
     
     VColor pict=+cfg.btnPictClose;
     
     art.pathOf(w,pict,q.getTopLeft(),q.getBottomRight());
     art.pathOf(w,pict,q.getTopRight(),q.getBottomLeft());
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
     Pane pane=Pane(Null,size);
     
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
     dragBottomRight=Pane(Null,size);
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
     
     draw_Frame(art);
     
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
 

