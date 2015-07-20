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
 
#include <CCore/inc/video/ShapeLib2.h>
 
#include <CCore/inc/video/SmoothDrawArt.h>
#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class InfoFromString */

StrLen InfoFromString::Impl::CutLine(StrLen &str)
 {
  for(StrLen next=str; +next ;++next)
    {
     char ch=*next;
     
     if( ch=='\r' || ch=='\n' )
       {
        StrLen ret=str.prefix(next);
        
        ++next;
        
        if( ch=='\r' && +next && *next=='\n' ) ++next;
        
        str=next;
        
        return ret;
       }
    }
  
  return Replace_null(str);
 }

InfoFromString::Impl::Impl(StrLen str)
 : buf(DoReserve,100)
 {
  while( +str )
    {
     StrLen line=CutLine(str);
     
     buf.append_fill(line);
    }
  
  buf.shrink_extra();
 }

InfoFromString::Impl::~Impl()
 {
 }

ulen InfoFromString::Impl::getLineCount() const
 {
  return buf.getLen();
 }

StrLen InfoFromString::Impl::getLine(ulen index) const
 {
  return Range(buf.at(index));
 }

InfoFromString::InfoFromString(StrLen str)
 : Info(new Impl(str))
 {
 }

InfoFromString::~InfoFromString()
 {
 }

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
  
  return 2*Point::Diag(+cfg.border_dxy)+Point(dx,dy);
 }

void InfoShape::setMax()
 {
  Coord dxy=+cfg.border_dxy;
  
  Pane inner=pane.shrink(dxy);
  
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
    }
  else
    {
     xoffMax=0;
     yoffMax=0;
    }
 }

void InfoShape::draw(const DrawBuf &buf) const
 {
  if( !pane ) return;
  
  Smooth::DrawArt art(buf);
  
  if( has_focus )
    {
     MPane p(pane);
    
     art.loop(HalfPos,+cfg.width,+cfg.focus,p.getTopLeft(),p.getBottomLeft(),p.getBottomRight(),p.getTopRight());
    }
  
  ulen count=info->getLineCount();
  ulen index=yoff;
  
  Font font=cfg.text_font.get();
  VColor text=+cfg.text;
  
  FontSize fs=font->getSize();
  Coord dxy=+cfg.border_dxy;
  
  Pane inner=pane.shrink(dxy);
  
  if( !inner ) return;
  
  DrawBuf tbuf=buf.cutRebase(inner);
  
  Pane tpane(-xoff,0,IntAdd(xoff,inner.dx),inner.dy);

  Coord y=fs.by;
  
  for(; index<count && y<inner.dy ;index++,y+=fs.dy)
    {
     font->text(tbuf,tpane,TextPlace(AlignX_Left,y),info->getLine(index),text);
    }
 }

} // namespace Video
} // namespace CCore
 

