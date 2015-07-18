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
#include <CCore/inc/FunctorType.h>

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

struct TextSize;

struct TextPlace;

struct AbstractSparseString;

class SingleString;

class DoubleString;

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

/* struct TextSize */

struct TextSize
 {
  Coord dx;
  Coord dy;
  Coord by;
  Coord skew;
  Coord full_dx;
  bool overflow;
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

/* struct AbstractSparseString */

struct AbstractSparseString
 {
  // abstract
  
  virtual void restart()=0;
  
  virtual PtrLen<const char> next()=0; // string is consumed
  
  virtual void cutSuffix(ulen len)=0;
  
  virtual bool cutCenter(ulen len)=0;
  
  // helper
  
  template <class FuncInit>
  void apply(FuncInit func_init) // string is consumed
   {
    restart();
    
    FunctorTypeOf<FuncInit> func(func_init);
    
    for(;;)
      {
       PtrLen<const char> r=next();
       
       if( !r ) break;
       
       func(r);
      }
   }
  
  template <class FuncInit>
  void applyWhile(FuncInit func_init) // string is consumed
   {
    restart();
    
    FunctorTypeOf<FuncInit> func(func_init);
    
    for(;;)
      {
       PtrLen<const char> r=next();
       
       if( !r ) break;
       
       if( !func(r) ) break;
      }
   }
  
  ULenSat countLen(); // string is consumed
 };

/* class SingleString */

class SingleString : public AbstractSparseString
 {
   StrLen str;
   bool first = true ;
   
  public:
  
   explicit SingleString(StrLen str_) : str(str_) {}
   
   ~SingleString() {}
   
   // AbstractSparseString
   
   virtual void restart();
   
   virtual PtrLen<const char> next();

   virtual void cutSuffix(ulen len);
   
   virtual bool cutCenter(ulen len);
 };

/* class DoubleString */

class DoubleString : public AbstractSparseString
 {
   StrLen str1;
   StrLen str2;
   unsigned ind = 1 ;
   
  public: 
   
   DoubleString(StrLen str1_,StrLen str2_);
   
   ~DoubleString() {}
   
   // AbstractSparseString
   
   virtual void restart();
   
   virtual PtrLen<const char> next();

   virtual void cutSuffix(ulen len);
   
   virtual bool cutCenter(ulen len);
 };

/* struct AbstractFont */

struct AbstractFont
 {
  // abstract 
  
  virtual FontSize getSize()=0;
  
  virtual TextSize text(AbstractSparseString &str)=0;
  
  virtual ulen fit(AbstractSparseString &str,Coord full_dx)=0;
  
  virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,DesktopColor color)=0;
  
  // helpers
  
  TextSize text(StrLen str)
   { 
    SingleString obj(str); 
    
    return text(obj); 
   }
  
  ulen fit(StrLen str,Coord full_dx)
   { 
    SingleString obj(str); 
    
    return fit(obj,full_dx); 
   }
  
  void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str,DesktopColor color)
   { 
    SingleString obj(str); 
    
    text(buf,pane,place,obj,color); 
   }
  
  TextSize text(StrLen str1,StrLen str2)
   { 
    DoubleString obj(str1,str2); 
    
    return text(obj); 
   }
  
  ulen fit(StrLen str1,StrLen str2,Coord full_dx)
   { 
    DoubleString obj(str1,str2); 
    
    return fit(obj,full_dx); 
   }
  
  void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str1,StrLen str2,DesktopColor color)
   { 
    DoubleString obj(str1,str2); 
    
    text(buf,pane,place,obj,color); 
   }
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
   
  protected:
   
   explicit Font(FontBase *font) : ptr(font) {}
   
  public:
   
   Font(); // default font
   
   ~Font() {}
   
   AbstractFont * operator -> () const { return ptr.getPtr(); }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

