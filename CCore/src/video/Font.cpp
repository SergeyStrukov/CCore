/* Font.cpp */ 
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
 
#include <CCore/inc/video/Font.h>
 
namespace CCore {
namespace Video {

namespace Private_Font {

class DefaultFont : public FontBase
 {
  public:
  
   DefaultFont() {}
  
   virtual ~DefaultFont() {}
   
   // AbstractFont
   
   virtual void text(FrameBuf<DesktopColor> buf,TextPlace place,StrLen str) // TODO
    {
    }
 };

} // namespace Private_Font

using namespace Private_Font;

/* class Font */

Font::Font()
 : ptr(new DefaultFont())
 {
 }

} // namespace Video
} // namespace CCore
 

