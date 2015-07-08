/* FixedWindow.cpp */ 
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
 
#include <CCore/inc/video/FixedWindow.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class FixedShape */

class FixedShape::DrawArt : public Smooth::DrawArt
 {
  public:
  
   explicit DrawArt(const DrawBuf &buf) : Smooth::DrawArt(buf) {}
 };

void FixedShape::draw_Title(DrawArt &art) const
 {
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

void FixedShape::draw_Close(DrawArt &art) const
 {
  if( +btnClose )
    {
     MPane p(btnClose);
     
     MCoord width=+cfg.width;
     
     MCoord x0=p.x;
     MCoord x1=x0+p.dx;
     
     MCoord y0=p.y;
     MCoord y1=y0+p.dy;
     
     MCoord ex=p.dy/8;
     
     FigureButton fig(x0,x1,y0,y1,ex);

     MCoord w=p.dy/8;
     MCoord bx=p.dy/4;
     
     MCoord s0=x0+bx;
     MCoord s1=x1-bx;
     
     MCoord t0=y0+bx;
     MCoord t1=y1-bx;
     
     ColorName top=+cfg.top;
     ColorName bottom=+cfg.bottom;
     ColorName btn=+cfg.btnClose;
     
     if( hit_type==HitFrame_Close )
       {
        fig.curveSolid(art,bottom);
        
        s0+=width;
        s1+=width;
        t0+=width;
        t1+=width;
        
        art.pathOf(w,btn,MPoint(s0,t0),MPoint(s1,t1));
        art.pathOf(w,btn,MPoint(s0,t1),MPoint(s1,t0));
       }
     else
       {
        fig.curveSolid(art,(hilight==HitFrame_Close)?+cfg.btnHilight:+cfg.frame);
        
        fig.getTop().curvePath(art,HalfPos,width,top);
        fig.getBottom().curvePath(art,HalfPos,width,bottom);
        
        art.pathOf(w,btn,MPoint(s0,t0),MPoint(s1,t1));
        art.pathOf(w,btn,MPoint(s0,t1),MPoint(s1,t0));
       }
    }
 }

void FixedShape::draw_Border(DrawArt &art) const
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

void FixedShape::reset(const String &title_)
 {
  has_focus=false;
  
  hilight=HitFrame_None;
  hit_type=HitFrame_None;
  
  title=title_;
 }

void FixedShape::layout(Point size_)
 {
  size=size_;
  
  Coord width=RoundUpLen(+cfg.width);
  
  Coord dxy=+cfg.frame_dxy;
  Coord tdy=+cfg.title_dy;
  
  Coord bdx=+cfg.btn_dx;
  Coord bdy=+cfg.btn_dy;
  
  if( size.x>2*dxy+2*bdx && size.y>dxy+tdy )
    {
     client=Pane(dxy,tdy,size.x-2*dxy,size.y-dxy-tdy);
     
     btnClose=Pane(size.x-dxy-bdx-bdx/2,(tdy-bdy)/2,bdx,bdy);
     
     titleBar=Extent(dxy,width,size.x-2*dxy-2*bdx,tdy-2*width);
    }
  else
    {
     client=Empty;
     titleBar=Empty;
     
     btnClose=Extent(Null,bdx,bdy);
    }
 }

void FixedShape::draw(const DrawBuf &buf) const
 {
  try
    {
     DrawArt art(buf);
     
     PaneSub sub(Extent(Null,size),client);
     
     ColorName cname=+cfg.frame;
     
     if( hilight==HitFrame_Move ) cname=+cfg.frameHilight;
     
     if( hit_type==HitFrame_Move ) cname=+cfg.frameDrag;
     
     art.block(sub.top,cname);
     art.block(sub.bottom,cname);
     art.block(sub.left,cname);
     art.block(sub.right,cname);
     
     draw_Title(art);
     
     draw_Close(art);
     
     draw_Border(art);
    }
  catch(CatchType)
    {
    }
 }

void FixedShape::draw(const DrawBuf &buf,HitFrameType hit_type) const
 {
  try
    {
     DrawArt art(buf);
    
     switch( hit_type )
       {
        case HitFrame_Close : draw_Close(art); break;
       }
    }
  catch(CatchType)
    {
    }
 }

Pane FixedShape::getPane(HitFrameType hit_type) const
 {
  switch( hit_type )
    {
     case HitFrame_Close : return btnClose;
    }
  
  return Empty;
 }

HitFrameType FixedShape::hitTest(Point point) const
 {
  if( point>=Null && point<size && !client.contains(point) )
    {
     if( btnClose.contains(point) ) return HitFrame_Close;
    
     return HitFrame_Move;
    }
  
  return HitFrame_None;
 }

} // namespace Video
} // namespace CCore
 

