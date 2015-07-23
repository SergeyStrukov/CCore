/* ShapeLib16.cpp */ 
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

/* class InfoShape */

Point InfoShape::getMinSize() const
 {
  Font font=cfg.text_font.get();
  
  Coord dx=0;
  Coord dy=0;
  
  for(ulen index=0,count=info->getLineCount(); index<count ;index++)
    {
     TextSize ts=font->text(info->getLine(index));
     
     IntGuard( !ts.overflow );
     
     Replace_max(dx,ts.full_dx);
    
     dy=IntAdd(dy,ts.dy);
    }
  
  return 2*Point::Diag(+cfg.space_dxy)+Point(dx,dy);
 }

void InfoShape::setMax()
 {
  Pane inner=pane.shrink(+cfg.space_dxy);
  
  if( +inner )
    {
     ulen count=info->getLineCount();
    
     Font font=cfg.text_font.get();
    
     FontSize fs=font->getSize();
    
     Coord dx=0;
    
     for(ulen index=0; index<count ;index++)
       {
        TextSize ts=font->text(info->getLine(index));
        
        IntGuard( !ts.overflow );
        
        Replace_max(dx,ts.full_dx);
       }
     
     if( dx>inner.dx )
       xoffMax=dx-inner.dx;
     else
       xoffMax=0;
     
     ulen h=ulen(inner.dy/fs.dy);
     
     if( count>h )
       yoffMax=count-h;
     else
       yoffMax=0;
     
     dxoff=fs.medDx();
    }
  else
    {
     xoffMax=0;
     yoffMax=0;
     dxoff=0;
    }
 }

void InfoShape::draw(const DrawBuf &buf) const
 {
  if( !pane ) return;
  
  Smooth::DrawArt art(buf);
  
  VColor text=+cfg.text;
  
  Coord dxy=+cfg.space_dxy;
  
  // decor
  
  {
   MPane p(pane);
   
   MCoord width=+cfg.width;
   MCoord len=Fraction(dxy)-width;
  
   if( focus )
     {
      art.loop(HalfPos,width,+cfg.focus,p.getTopLeft(),p.getBottomLeft(),p.getBottomRight(),p.getTopRight());
     }
   
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
   
   if( yoff>0 ) // Top
     {
      MCoord x=p.x+p.dx/2;
      MCoord y=p.y;
     
      FigurePoints<3> fig;
      
      fig[0]={x,y};
      fig[1]={x-len,y+len};
      fig[2]={x+len,y+len};
      
      fig.solid(art,text);
     }
   
   if( yoff<yoffMax ) // Bottom
     {
      MCoord x=p.x+p.dx/2;
      MCoord y=p.ey;
    
      FigurePoints<3> fig;
      
      fig[0]={x,y};
      fig[1]={x-len,y-len};
      fig[2]={x+len,y-len};
      
      fig.solid(art,text);
     }
  }
  
  // text
  
  {
   Pane inner=pane.shrink(dxy);
   
   if( !inner ) return;
   
   ulen count=info->getLineCount();
   ulen index=yoff;
   
   Font font=cfg.text_font.get();
   
   FontSize fs=font->getSize();
   
   DrawBuf tbuf=buf.cutRebase(inner);
   
   Pane tpane(-xoff,0,IntAdd(xoff,inner.dx),inner.dy);

   Coord y=fs.by;
   
   for(; index<count && y<inner.dy ;index++,y+=fs.dy)
     {
      font->text(tbuf,tpane,TextPlace(AlignX_Left,y),info->getLine(index),text);
     }
  }
 }

} // namespace Video
} // namespace CCore
 

