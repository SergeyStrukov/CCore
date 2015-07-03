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

#include <CCore/inc/video/CommonDrawArt.h>

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

class DragShape::DrawArt : public CommonDrawArt
 {
  public:
  
   explicit DrawArt(const DrawBuf &buf) : CommonDrawArt(buf) {}
   
   void box(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     PaneBorder border(pane);
     
     block(pane,inner);
     
     loop(border.get(),edge);
    }
   
   void boxX(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     PaneBorder border(pane);
     
     block(pane,inner);
     
     path(edge,border.topLeft(),border.topRight());
     path(edge,border.bottomLeft(),border.bottomRight());
    }
   
   void boxY(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     PaneBorder border(pane);
     
     block(pane,inner);
     
     path(edge,border.topLeft(),border.bottomLeft());
     path(edge,border.topRight(),border.bottomRight());
    }
   
   Pane btn(Pane pane,ColorName face,ColorName edge)
    {
     Coord px=pane.dx/4;
     Coord py=pane.dy/8;
     
     Coord x0=pane.x+py;
     Coord x1=pane.x+px;
     Coord x2=pane.x+pane.dx-1-px;
     Coord x3=pane.x+pane.dx-1-py;
     
     Coord y0=pane.y+py;
     Coord y1=pane.y+px;
     Coord y2=pane.y+pane.dy-1-px;
     Coord y3=pane.y+pane.dy-1-py;
     
     const Point dots[]={Point(x1,y0),
                         Point(x2,y0),
                         Point(x3,y1),
                         Point(x3,y2),
                         Point(x2,y3),
                         Point(x1,y3),
                         Point(x0,y2),
                         Point(x0,y1)};
     
     curveSolid(Range(dots),SolidAll,face);
     
     curveLoop_smooth(Range(dots),edge);
     
     return Shrink(pane,px,px);
    }
   
   Pane title(Pane pane,ColorName up,ColorName down)
    {
     Coord px1=pane.dy/4;
     Coord px0=px1/3;
     
     Coord y0=pane.y;
     Coord y1=pane.y+pane.dy/4;
     Coord y2=pane.y+(pane.dy-1)/2;
     Coord y3=pane.y+pane.dy-1-pane.dy/4;
     Coord y4=pane.y+pane.dy-1;
     
     Coord x0=pane.x;
     Coord x1=pane.x+pane.dx-1;
     
     curvePath_smooth(up,Point(x0+px1,y4),
                         Point(x0+px0,y3),
                         Point(x0    ,y2),
                         Point(x0+px0,y1),
                         Point(x0+px1,y0));
     
     path(up,Point(x0+px1,y0),Point(x1-px1,y0));
     
     curvePath_smooth(down,Point(x1-px1,y4),
                           Point(x1-px0,y3),
                           Point(x1    ,y2),
                           Point(x1-px0,y1),
                           Point(x1-px1,y0));
     
     path(down,Point(x0+px1,y4),Point(x1-px1,y4));
     
     return Shrink(pane,2*px1,1);
    }
 };

void DragShape::draw_TopLeft(DrawArt &art) const
 {
  if( +dragTopLeft )
    {
     Pane pane=dragTopLeft;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=accentColor(DragType_TopLeft);
     
     PaneBorder border(Shrink(pane,1,1));
   
     art.solid(SolidAll,cname,border.topLeft(),border.topRight(),border.bottomLeft());
    }
 }

void DragShape::draw_Left(DrawArt &art) const
 {
  if( +dragLeft )
    {
     Pane pane=dragLeft;
    
     art.boxY(pane,cfg.edge,cfg.frame);
     
     ColorName cname=accentColor(DragType_Left);
     
     Coord delta=cfg.frame_dxy/2;
     
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+delta,pane.y+pane.dy-1-delta));
    }
 }

void DragShape::draw_BottomLeft(DrawArt &art) const
 {
  if( +dragBottomLeft )
    {
     Pane pane=dragBottomLeft;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=accentColor(DragType_BottomLeft);
   
     PaneBorder border(Shrink(pane,1,1));
     
     art.solid(SolidAll,cname,border.topLeft(),border.bottomRight(),border.bottomLeft());
    }
 }

void DragShape::draw_Bottom(DrawArt &art) const
 {
  if( +dragBottom )
    {
     Pane pane=dragBottom;
   
     art.boxX(pane,cfg.edge,cfg.frame);
    
     ColorName cname=accentColor(DragType_Bottom);
    
     Coord delta=cfg.frame_dxy/2;
    
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+pane.dx-1-delta,pane.y+delta));
    }
 }

void DragShape::draw_BottomRight(DrawArt &art) const
 {
  if( +dragBottomRight )
    {
     Pane pane=dragBottomRight;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=accentColor(DragType_BottomRight);
     
     PaneBorder border(Shrink(pane,1,1));
   
     art.solid(SolidAll,cname,border.topRight(),border.bottomLeft(),border.bottomRight());
    }
 }

void DragShape::draw_Right(DrawArt &art) const
 {
  if( +dragRight )
    {
     Pane pane=dragRight;
    
     art.boxY(pane,cfg.edge,cfg.frame);
     
     ColorName cname=accentColor(DragType_Right);
     
     Coord delta=cfg.frame_dxy/2;
     
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+delta,pane.y+pane.dy-1-delta));
    }
 }

void DragShape::draw_TopRight(DrawArt &art) const
 {
  if( +dragTopRight )
    {
     Pane pane=dragTopRight;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=accentColor(DragType_TopRight);
   
     PaneBorder border(Shrink(pane,1,1));
     
     art.solid(SolidAll,cname,border.topLeft(),border.bottomRight(),border.topRight());
    }
 }

void DragShape::draw_Alert(DrawArt &art) const
 {
  if( +btnAlert )
    {
     ColorName cname=btnColor(DragType_Alert);
     
     Pane pane=art.btn(btnAlert,cname,cfg.btnEdge);
     
     if( !alert_blink )
       {
        ColorName cname=(alert_type==AlertType_No)?cfg.noAlert:( (alert_type==AlertType_Closed)?cfg.alert:cfg.closeAlert );
        
        cfg.title_font->text(art.getBuf(),pane,TextPlace(AlignX_Center,AlignY_Center),StrLen("!",1),cname);
       } 
    }
 }

void DragShape::draw_Min(DrawArt &art) const
 {
  if( +btnMin )
    {
     ColorName cname=btnColor(DragType_Min);
     
     Pane pane=art.btn(btnMin,cname,cfg.btnEdge);
     
     if( pane.dx>0 && pane.dy>=cfg.min_dy )
       {
        Pane fig=SplitY(pane,cfg.min_dy);
       
        art.block(fig,cfg.btnPict);
       }
    }
 }

void DragShape::draw_Max(DrawArt &art) const
 {
  if( +btnMax )
    {
     ColorName cname=btnColor(DragType_Max);
       
     Pane pane=art.btn(btnMax,cname,cfg.btnEdge);

     if( pane.dx>0 && pane.dy>=cfg.min_dy )
       {
        if( max_button )
          art.block(pane,cfg.btnPict);
        else
          art.block(Shrink(pane,pane.dx/4,pane.dy/4),cfg.btnPict);
       }
    }
 }

void DragShape::draw_Close(DrawArt &art) const
 {
  if( +btnClose )
    {
     ColorName cname=btnColor(DragType_Close);
       
     Pane pane=art.btn(btnClose,cname,cfg.btnEdge);
     
     if( +pane )
       {
        PaneBorder border(pane);
       
        art.path_smooth(cfg.btnClose,border.topLeft(),border.bottomRight());
        art.path_smooth(cfg.btnClose,border.topRight(),border.bottomLeft());
       } 
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

void DragShape::layout(Point size)
 {
  Coord dxy=cfg.frame_dxy;
  Coord tdy=cfg.title_dy;
  Coord bdx=cfg.btn_dx;
  Coord bdy=cfg.btn_dy;
  
  if( size>Point(2*dxy+5*bdx+bdx/2+Max(dxy,tdy),dxy+Max<Coord>(2*dxy,tdy)) )
    {
     Pane pane(0,0,size.x,size.y);
     
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
     
     titleBar=Pane(dragBar.x+bdx/4,2,tx-bdx/2,tdy-4);
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
     
     draw_TopLeft(art);
     draw_Left(art);
     draw_BottomLeft(art);
     draw_Bottom(art);
     draw_BottomRight(art);
     draw_Right(art);
     draw_TopRight(art);
     
     if( +dragBar )
       {
        Pane pane=dragBar;
    
        art.boxX(pane,cfg.edge, has_focus?cfg.active:cfg.inactive );
       }
     
     if( +titleBar )
       {
        Pane pane=art.title(titleBar, has_focus?cfg.titleActiveUp:cfg.titleUp , has_focus?cfg.titleActiveDown:cfg.titleDown );
        
        cfg.title_font->text(buf,pane,TextPlace(AlignX_Left,AlignY_Center),Range(title),cfg.title);
       }
     
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
 

