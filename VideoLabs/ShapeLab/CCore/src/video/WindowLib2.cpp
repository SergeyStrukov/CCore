/* WindowLib2.cpp */ 
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
 
#include <CCore/inc/video/WindowLib2.h>
 
namespace CCore {
namespace Video {

/* function */

static String Clipboard;

void TextToClipboard(StrLen text)
 {
  Clipboard=String(text);
 }

ulen TextFromClipboard(PtrLen<char> buf)
 {
  auto r=Range(Clipboard);
  
  Replace_min(r.len,buf.len);
  
  r.copyTo(buf.ptr);
  
  return r.len;
 }

} // namespace Video
} // namespace CCore
 

