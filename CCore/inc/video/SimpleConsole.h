/* SimpleConsole.h */ 
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

#ifndef CCore_inc_video_SimpleConsole_h
#define CCore_inc_video_SimpleConsole_h

#include <CCore/inc/video/FrameBuf.h>
 
namespace CCore {
namespace Video {

/* classes */

class DefaultFont;

template <class Color> class CharPanel;

template <class Color> class SimpleConsole;

/* class DefaultFont */

class DefaultFont
 {
   static const bool Table[];
   static const bool NoCharTable[];
   static const bool Marker[];
   
   const bool *pixel; // DX*DY
   
  public:
  
   static const unsigned DX = 10 ;
   static const unsigned DY = 18 ;

   DefaultFont()
    {
     pixel=Marker;
    }
   
   explicit DefaultFont(char ch)
    {
     unsigned index=(unsigned char)ch;
     
     if( index>=32 && index<128 )
       pixel=Table+(index-32)*DX*DY;
     else
       pixel=NoCharTable;
    }
  
   // properties
   
   unsigned dX() const { return DX; }
  
   unsigned dY() const { return DY; }
   
   class Pattern
    {
      const bool *pixel;
      
     public: 
      
      explicit Pattern(const bool *pixel_) : pixel(pixel_) {}
     
      // properties
     
      unsigned dX() const { return DX; }
      
      bool operator [] (unsigned x) const { return pixel[x]; }
    };
  
   Pattern operator [] (unsigned y) const { return Pattern(pixel+(y*DX)); }
 };

/* class CharPanel<Color> */

template <class Color> 
class CharPanel : NoCopy
 {
   FrameBuf<Color> out;
   
   ColorName back = Black ;
   ColorName fore = Silver ;
   ColorName line = Gray ;
   ColorName marker = Green ;
   
   unsigned dx = 0 ;
   unsigned dy = 0 ;
   
   Color backup[DefaultFont::DX*DefaultFont::DY];
   
  public:
 
   CharPanel() {}
   
   ~CharPanel() {}
   
   // properties
   
   bool operator + () const { return dy; }
   
   bool operator ! () const { return !dy; }
   
   unsigned dX() const { return dx; }
   
   unsigned dY() const { return dy; }
   
   // methods
   
   void init(FrameBuf<Color> out);
   
   void eraseLine(unsigned y);
   
   void eraseLineLine(unsigned y);
   
   void operator () (unsigned x,unsigned y,char ch);
   
   void setMarker(unsigned x,unsigned y);
   
   void clearMarker(unsigned x,unsigned y);
 };

template <class Color> 
void CharPanel<Color>::init(FrameBuf<Color> out_)
 {
  out=out_;
  
  dx=out.dX()/DefaultFont::DX;
  dy=out.dY()/DefaultFont::DY;
  
  out.erase(back);
 }

template <class Color> 
void CharPanel<Color>::eraseLine(unsigned y)
 {
  out.block(0,y*DefaultFont::DY,out.dX(),DefaultFont::DY,back);
 }

template <class Color> 
void CharPanel<Color>::eraseLineLine(unsigned y)
 {
  out.block(0,y*DefaultFont::DY,out.dX(),DefaultFont::DY-1,back);
  
  out.block(0,y*DefaultFont::DY+DefaultFont::DY-1,out.dX(),1,line);
 }

template <class Color> 
void CharPanel<Color>::operator () (unsigned x,unsigned y,char ch)
 {
  out.glyph(x*DefaultFont::DX,y*DefaultFont::DY,DefaultFont(ch),back,fore);
 }

template <class Color> 
void CharPanel<Color>::setMarker(unsigned x,unsigned y)
 {
  out.save(x*DefaultFont::DX,y*DefaultFont::DY,DefaultFont::DX,DefaultFont::DY,backup);
  
  out.glyph(x*DefaultFont::DX,y*DefaultFont::DY,DefaultFont(),marker);
 }

template <class Color> 
void CharPanel<Color>::clearMarker(unsigned x,unsigned y)
 {
  out.load(x*DefaultFont::DX,y*DefaultFont::DY,DefaultFont::DX,DefaultFont::DY,backup);
 }

/* class SimpleConsole<Color> */

template <class Color> 
class SimpleConsole : NoCopy
 {
   CharPanel<Color> panel;
   
   unsigned x = 0 ;
   unsigned y = 0 ;
   
   bool marker = false ;
 
  private:
 
   void newLine();
   
   void printChar(char ch);
 
  public:
 
   SimpleConsole() {}
   
   ~SimpleConsole() {}
   
   // properties
   
   bool operator + () const { return panel; }
   
   bool operator ! () const { return !panel; }
   
   // methods
   
   void init(FrameBuf<Color> out);
   
   void print(PtrLen<const char> str);
   
   void toggleMarker();
 };

template <class Color> 
void SimpleConsole<Color>::newLine()
 {
  x=0;
  
  if( ++y>=panel.dY() )
    {
     y=0;
    }
  
  if( y+1<panel.dY() )
    {
     panel.eraseLine(y);
     
     panel.eraseLineLine(y+1);
    }
  else
    {
     panel.eraseLine(y);
     
     panel.eraseLineLine(0);
    }
 }

template <class Color> 
void SimpleConsole<Color>::printChar(char ch)
 {
  switch( ch )
    {
     case '\r' : x=0; break;
     
     case '\n' : newLine(); break;
     
     case '\b' : if( x>0 ) x--; break;
      
     default:
      {
       panel(x,y,ch);
       
       if( ++x>=panel.dX() ) newLine();
      }
    }
 }

template <class Color> 
void SimpleConsole<Color>::init(FrameBuf<Color> out)
 {
  x=0;
  y=0;
  marker=false;
  
  panel.init(out);
 }

template <class Color> 
void SimpleConsole<Color>::print(PtrLen<const char> str)
 {
  if( !panel ) return;
  
  if( marker ) panel.clearMarker(x,y);
  
  for(char ch : str ) printChar(ch);
  
  if( marker ) panel.setMarker(x,y);
 }

template <class Color> 
void SimpleConsole<Color>::toggleMarker()
 {
  if( !panel ) return;
  
  if( marker )
    {
     marker=false;
     
     panel.clearMarker(x,y);
    }
  else
    {
     marker=true;
     
     panel.setMarker(x,y);
    }
 }

} // namespace Video
} // namespace CCore
 
#endif
 

