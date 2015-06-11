/* SmoothDrawArt.cpp */ 
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
 
#include <CCore/inc/video/SmoothDrawArt.h>

namespace CCore {
namespace Video {
namespace Smooth {

/* enum DotType */

const char * GetTextDesc(DotType type)
 {
  switch( type )
    {
     case DotSimple : return "Simple";
     case DotBreak  : return "Break";
   
     default: return "???";
    }
 }

/* class DrawArt */

 // simple

void DrawArt::pixel(Point p,DesktopColor color)
 {
  buf.pixel_safe(buf.map(p),color);
 }

void DrawArt::erase(DesktopColor color)
 {
  buf.erase(color);
 }

void DrawArt::block(Pane pane,DesktopColor color)
 {
  buf.block_safe(buf.map(pane),color);
 }

} // namespace Smooth
} // namespace Video
} // namespace CCore
 

