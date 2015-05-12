/* Font.h */ 
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

#ifndef CCore_inc_video_Font_h
#define CCore_inc_video_Font_h

#include <CCore/inc/video/DrawBuf.h>

#include <CCore/inc/RefPtr.h>
#include <CCore/inc/MemBase.h>

#include <CCore/inc/task/Atomic.h>
 
namespace CCore {
namespace Video {

/* consts */

enum AlignX
 {
  AlignX_Left,
  AlignX_Center,
  AlignX_Right,
  AlignX_Given
 };

enum AlignY
 {
  AlignY_Top,
  AlignY_Center,
  AlignY_Bottom,
  AlignY_Given
 };

/* classes */

struct FontSize;

struct TextPlace;

struct TextSize;

struct AbstractFont;

class FontBase;

class Font;

/* struct FontSize */

struct FontSize
 {
  Coord min_dx;
  Coord max_dx;
  Coord dy;
  Coord by;
  Coord skew;
 };

/* struct TextPlace */

struct TextPlace
 {
  AlignX align_x;
  AlignY align_y;
  Coord x = 0 ;
  Coord y = 0 ;
  
  TextPlace(AlignX align_x_,AlignY align_y_) : align_x(align_x_),align_y(align_y_) {}
  
  TextPlace(AlignX align_x_,Coord y_) : align_x(align_x_),align_y(AlignY_Given),y(y_) {}
  
  TextPlace(Coord x_,AlignY align_y_) : align_x(AlignX_Given),align_y(align_y_),x(x_) {}
  
  TextPlace(Coord x_,Coord y_) : align_x(AlignX_Given),align_y(AlignY_Given),x(x_),y(y_) {}
 };

/* struct TextSize */

struct TextSize
 {
  Coord dx;
  Coord dy;
  Coord by;
  Coord skew;
  bool overflow;
 };

/* struct AbstractFont */

struct AbstractFont
 {
  virtual FontSize getSize()=0;
  
  virtual void text_update(DrawBuf buf,Pane pane,TextPlace &place,StrLen str,DesktopColor color)=0;
  
  virtual void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str,DesktopColor color)=0;
  
  virtual TextSize text(StrLen str)=0;
  
  virtual ulen fit(StrLen str,Coord dx)=0;
 };

/* class FontBase */

class FontBase : public MemBase_nocopy , public AbstractFont
 {
   Atomic refs;
  
  public:
  
   FontBase() { refs=1; }
  
   virtual ~FontBase() {}
   
   void incRef() { refs++; }
   
   bool decRef() { return (refs--)==1; }
   
   void destroy() { delete this; }
 };

/* class Font */

class Font 
 {
   RefPtr<FontBase> ptr;
   
  public:
   
   Font(); // default font, may throw
   
   explicit Font(FontBase *font) : ptr(font) {}
   
   ~Font() {}
   
   AbstractFont * operator -> () const { return ptr.getPtr(); }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

