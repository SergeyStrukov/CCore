/* ShapeLib5.cpp */ 
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

/* class LabelShape */

Point LabelShape::getMinSize() const
 {
  TextSize ts=cfg.font->text(Range(text));
  
  IntGuard( !ts.overflow );
  
  return Point(ts.full_dx,ts.dy).addXY(1);
 }

void LabelShape::draw(const DrawBuf &buf) const
 {
  cfg.font->text(buf,pane,TextPlace(align_x,align_y),Range(text),enable?cfg.text:cfg.inactive);
 }

} // namespace Video
} // namespace CCore
 

