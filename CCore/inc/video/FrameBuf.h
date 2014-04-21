/* FrameBuf.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FrameBuf_h
#define CCore_inc_video_FrameBuf_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Video {

/* classes */

struct Color565;

template <class Color> struct FrameBuf;

/* struct Color565 */

struct Color565
 {
  using Raw = uint16 ;
  
  static const ulen RawCount = 1 ;
 };

/* struct FrameBuf<Color> */

template <class Color> 
struct FrameBuf
 {
  typename Color::Raw *base;
  ulen dx;
  ulen dline;
  ulen dy;
  
  FrameBuf() {}
  
  FrameBuf(typename Color::Raw *base_,ulen dx_,ulen dy_) : base(base_),dx(dx_),dline(dx_*Color::RawCount),dy(dy_) {}
  
  FrameBuf(typename Color::Raw *base_,ulen dx_,ulen dline_,ulen dy_) : base(base_),dx(dx_),dline(dline_),dy(dy_) {}
 };

} // namespace Video
} // namespace CCore
 
#endif
 

