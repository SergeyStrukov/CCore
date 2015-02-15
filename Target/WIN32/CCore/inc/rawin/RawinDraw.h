/* RawinDraw.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_rawin_RawinDraw_h
#define CCore_inc_rawin_RawinDraw_h

#include <CCore/inc/rawin/Rawin.h>

#include <CCore/inc/FunctorType.h>
 
namespace CCore {
namespace Rawin {

/* classes */ 

class Color;

class Pen;

class Brush;

class Font;

struct FontInfo;

class EnumFontsBase;

template <class FuncInit> class EnumFontsFunc;

class DrawContext;

class MemSurface;

/* class Color */ 

class Color
 {
   Win32::Color32 color;
 
  public:
  
   Color() : color(0) {}
  
   Color(Win32::Intensity R,Win32::Intensity G,Win32::Intensity B) : color(Win32::MakeColor32(R,G,B)) {}
   
   operator Win32::Color32() const { return color; }
 };
 
/* class Pen */ 

class Pen : NoCopy
 {
   Win32::HPen hPen;
   
  public:
  
   explicit Pen(Color color,int width_px=0,unsigned style=Win32::Pen_Solid); // Win32::PenStyle
   
   ~Pen();
  
   Win32::HPen getHandle() const { return hPen; }
 };
 
/* class Brush */ 

class Brush : NoCopy
 {
   Win32::HBrush hBrush;
   
  public:
  
   explicit Brush(Color color);
   
   ~Brush();
   
   Win32::HBrush getHandle() const { return hBrush; }
 };
 
/* class Font */  

class Font : NoCopy
 {
   Win32::HFont hFont;
   
  public: 
  
   enum Flags
    {
     Bold      = 0x01,
     Italic    = 0x02,
     Underline = 0x04,
     Strikeout = 0x08
    };
  
   Font(const char *typeface,int size_px,unsigned flags=0);
   
   ~Font();
   
   Win32::HFont getHandle() const { return hFont; }
 };

/* struct FontInfo */

struct FontInfo
 {
  const char *typeface;
  const char *full_name;
  const char *style;
  const char *script;
 };

/* class EnumFontsBase */ 
 
class EnumFontsBase
 {
  public:
  
   EnumFontsBase();
   
   ~EnumFontsBase();
   
   void run(Win32::HGDevice hGD);
   
   virtual void font(FontInfo info)=0;
 };

/* class EnumFontsFunc<FuncInit> */

template <class FuncInit>
class EnumFontsFunc : public EnumFontsBase
 {
   FunctorTypeOf<FuncInit> func;
   
  private:
   
   virtual void font(FontInfo info)
    {
     func(info);
    }
   
  public:
   
   explicit EnumFontsFunc(FuncInit func_init)
    : func(func_init)
    {
    }
  
   ~EnumFontsFunc()
    {
    }
 };

/* EnumFonts() */

template <class FuncInit>
void EnumFonts(Win32::HGDevice hGD,FuncInit func_init)
 {
  EnumFontsFunc<FuncInit> func(func_init);

  func.run(hGD);
 }
 
/* class DrawContext */ 

class DrawContext : NoCopy
 {
   Win32::HGDevice hGD;
   
   Win32::HGDObject old_pen;
   bool old_pen_flag;
   
   Win32::HGDObject old_brush;
   bool old_brush_flag;
   
   Win32::HGDObject old_font;
   bool old_font_flag;
   
  public:
  
   explicit DrawContext(Win32::HGDevice hGD);
   
   ~DrawContext();
   
   // select
   
   void select(Win32::HPen hPen);
   
   void select(Win32::HBrush hBrush);
   
   void select(Win32::HFont hFont);
   
   template <class T>
   void select(const T &obj) { select(obj.getHandle()); }
   
   // line
   
   Point move(Point point);
   
   void line(Point point);
   
   // fill
   
   void fill(Pane pane);
   
   // path
   
   void beginPath();
   
   void endPath();
   
   void closeFigure();
   
   void strokePath();
   
   void fillPath();
   
   void drawPath();
   
   // text
   
   void setTextColor(Color color);
   
   void setTextRef(unsigned flags); // Win32::TextAlign|
   
   void text(Point ref_point,StrLen str);
   
   Point textSize(StrLen str);
   
   Point text(Point ref_point,StrLen str,int caret_pos[]);
 };
 
/* class MemSurface */ 

class MemSurface
 {
   ulen dx;
   ulen dy;
   ulen dline;
   
   MemColor *surface;
 
  public:
  
   MemSurface()
    {
     dx=0;
     dy=0;
     dline=0;
     surface=0;
    }
    
   explicit MemSurface(MemPaint &mem_paint);
   
   ulen getDX() const { return dx; }
   
   ulen getDY() const { return dy; }
 
   ulen getDLine() const { return dline; }
   
   MemColor * getSurface() const { return surface; }
   
   MemColor & operator () (ulen x,ulen y) const { return surface[x+y*dline]; }
 };                                             
 
} // namespace Rawin
} // namespace CCore
 
#endif
 

