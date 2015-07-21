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

void FixedShape::draw_Frame(DrawArt &art) const
 {
  VColor top=+cfg.frame;
  VColor bottom=+cfg.top;
  
  if( hilight==HitFrame_Move ) top=+cfg.frameHilight;
  
  if( hit_type==HitFrame_Move ) top=+cfg.frameDrag;
  
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

void FixedShape::draw_Title(DrawArt &art) const
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

void FixedShape::draw_Close(DrawArt &art) const
 {
  if( +btnClose )
    {
     MPane p(btnClose);
     
     MCoord width=+cfg.width;
     
     MCoord ex=p.dx/8;

     FigureButton fig(p,ex);
     
     MPane q=p.shrink(p.dx/5,p.dy/5);
     
     VColor top=+cfg.top;
     
     if( hit_type==HitFrame_Close )
       {
        fig.curveSolid(art,top);
        
        q+=MPoint::Diag(width);
       }
     else
       {
        VColor face=(hilight==HitFrame_Close)?+cfg.btnFaceHilight:+cfg.btnFace;
        
        VColor bottom=+cfg.bottom;
        
        fig.curveSolid(art,face);
        
        fig.getTop().curvePath(art,HalfPos,width,top);
        fig.getBottom().curvePath(art,HalfPos,width,bottom);
       }

     MCoord w=p.dx/8;
     
     VColor pict=+cfg.btnPictClose;
     
     art.path(w,pict,q.getTopLeft(),q.getBottomRight());
     art.path(w,pict,q.getBottomLeft(),q.getTopRight());
    }
 }

Point FixedShape::getDeltaSize() const
 {
  Coord dxy=+cfg.frame_dxy;
  Coord tdy=+cfg.title_dy;
  
  return Point(2*dxy,dxy+tdy);
 }

Coord FixedShape::getMinDx(StrLen title) const
 {
  Coord width=RoundUpLen(+cfg.width);
  Coord tdy=+cfg.title_dy;
  
  MCoord ex=Fraction(tdy-2*width)/4;
  
  Coord dxy=+cfg.frame_dxy;
  Coord bdx=+cfg.btn_dx;
  
  TextSize ts=cfg.title_font.get()->text(title);
  
  return IntAdd(ts.full_dx,2*RoundUpLen(ex)+2*dxy+2*bdx);
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
     
     titleBar=Pane(dxy,width,size.x-2*dxy-2*bdx,tdy-2*width);
    }
  else
    {
     client=Empty;
     titleBar=Empty;
     
     btnClose=Pane(Null,bdx,bdy);
    }
 }

void FixedShape::draw(const DrawBuf &buf) const
 {
  try
    {
     DrawArt art(buf);
     
     draw_Frame(art);
     
     draw_Title(art);
     
     draw_Close(art);
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
 

