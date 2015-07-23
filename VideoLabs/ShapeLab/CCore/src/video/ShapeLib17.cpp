/* ShapeLib17.cpp */ 
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
 
#include <CCore/inc/video/ShapeLib2.h>
 
#include <CCore/inc/video/SmoothDrawArt.h>
#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class LineEditShape */

Point LineEditShape::getMinSize() const
 {
  Font font=cfg.font.get();
  
  MCoord width=+cfg.width;
  
  FontSize fs=font->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4+Fraction(+cfg.ex);
  
  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);
  
  TextSize ts=font->text("Sample");
  
  IntGuard( !ts.overflow );
  
  return Point(ts.full_dx,ts.dy)+2*Point(dx,dy);
 }

void LineEditShape::setMax()
 {
  Font font=cfg.font.get();
  
  MCoord width=+cfg.width;
  
  FontSize fs=font->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4+Fraction(+cfg.ex);
  
  Coord dx=RoundUpLen(ex);
  Coord dy=RoundUpLen(width);
  
  Pane inner=pane.shrink(dx,dy);
  
  TextSize ts=font->text(text_buf.prefix(len));
  
  IntGuard( !ts.overflow );
  
  Coord tx=IntAdd(ts.full_dx,+cfg.cursor_dx);
  
  tx=IntAdd(tx,fs.max_dx); 
  
  tx=IntAdd(tx,IntAbs(ts.skew));
  
  if( tx>inner.dx )
    xoffMax=tx-inner.dx;
  else
    xoffMax=0;
  
  dxoff=fs.medDx();  
 }

void LineEditShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  Font font=cfg.font.get();
  
  // figure
  
  MCoord width=+cfg.width;
  
  FontSize fs=font->getSize();
  
  MCoord ex=(Fraction(fs.dy)+2*width)/4+Fraction(+cfg.ex);
  
  VColor text=enable?+cfg.text:+cfg.inactive;
  
  FigureButton fig(p,ex);
  
  // body
  
  fig.curveSolid(art,+cfg.back);
  
  // border
  
  if( focus )
    {
     fig.curveLoop(art,HalfPos,width,+cfg.focus);
    }
  else
    {
     auto fig_top=fig.getTop();
     
     fig_top.curvePath(art,HalfPos,width,+cfg.top);
     
     auto fig_bottom=fig.getBottom();
     
     fig_bottom.curvePath(art,HalfPos,width,+cfg.bottom);
    }
  
  // arrows
  
  {
   MCoord len=ex-width;

   if( xoff>0 ) // Left
     {
      MCoord x=p.x;
      MCoord y=p.y+p.dy/2;
     
      FigurePoints<3> fig;
      
      fig[0]={x,y};
      fig[1]={x+len,y-len};
      fig[2]={x+len,y+len};
      
      fig.solid(art,text);
     }
   
   if( xoff<xoffMax ) // Right
     {
      MCoord x=p.ex;
      MCoord y=p.y+p.dy/2;
      
      FigurePoints<3> fig;
      
      fig[0]={x,y};
      fig[1]={x-len,y-len};
      fig[2]={x-len,y+len};
      
      fig.solid(art,text);
     }
  }
  
  // text
  
  {
   Coord dx=RoundUpLen(ex);
   Coord dy=RoundUpLen(width);
   
   Pane inner=pane.shrink(dx,dy);
   
   DrawBuf tbuf=buf.cutRebase(inner);
   
   Pane tpane(-xoff,0,IntAdd(xoff,inner.dx),inner.dy);
   
   TextSize ts=font->text(text_buf.prefix(pos));
   
   Coord cursor_dx=+cfg.cursor_dx;
   
   Coord x1=IntAbs(ts.skew);
   Coord x2=x1+ts.dx;
   Coord x3=x2+cursor_dx;
   
   font->text(tbuf,tpane,TextPlace(x1,AlignY_Center),text_buf.prefix(pos),text);
   
   font->text(tbuf,tpane,TextPlace(x3,AlignY_Center),text_buf.part(pos,len-pos),text);
   
   if( enable && cursor )
     {
      Smooth::DrawArt art(tbuf);
      
      art.block(Pane(x2-xoff,0,cursor_dx,inner.dy),+cfg.cursor);
     }
  }
 }

} // namespace Video
} // namespace CCore
 

