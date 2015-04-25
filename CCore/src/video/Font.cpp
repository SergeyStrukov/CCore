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

#include <CCore/inc/video/SimpleConsole.h>
 
namespace CCore {
namespace Video {

namespace Private_Font {

class DefFont : public FontBase
 {
  private:
  
   class WorkBuf : public FrameBuf<DesktopColor>
    {
     public:
    
      explicit WorkBuf(FrameBuf<DesktopColor> buf) : FrameBuf<DesktopColor>(buf) {}
      
      template <class Pattern>
      static void Line(Raw *ptr,Pattern pat,Coord len,DesktopColor color)
       {
        Coord gx=0;
        
        if( pat[gx] ) color.copyTo(ptr);
        
        while( ++gx<len ) 
          {
           ptr=NextX(ptr);
          
           if( pat[gx] ) color.copyTo(ptr);
          }
       }
      
      template <class Pattern>
      static void Line(Raw *ptr,Pattern pat,Coord gx,Coord len,DesktopColor color)
       {
        Coord lim=gx+len;
        
        if( pat[gx] ) color.copyTo(ptr);
        
        while( ++gx<lim ) 
          {
           ptr=NextX(ptr);
          
           if( pat[gx] ) color.copyTo(ptr);
          }
       }
      
      void text(Coord x,Coord y,char ch,DesktopColor color)
       {
        if( x>=dx || x<=-DefaultFont::DX ) return;
        
        DefaultFont glyph(ch);
        
        Coord gy;
        Coord lim;
        
        if( y<0 ) 
          {
           gy=-y;
           y=0;
           
           lim=(dy<DefaultFont::DY)?Min<Coord>(DefaultFont::DY,dy+gy):DefaultFont::DY; // > gy
          }
        else
          {
           gy=0;
           
           lim=Min<Coord>(DefaultFont::DY,dy-y); // > gy
          }
        
        if( x>=0 )
          {
           Coord len=Min<Coord>(DefaultFont::DX,dx-x); // > 0
           
           Raw *ptr=place(Point(x,y));
           
           Line(ptr,glyph[gy],len,color);
           
           while( ++gy<lim )
             {
              ptr=nextY(ptr);
             
              Line(ptr,glyph[gy],len,color);
             }
          } 
        else
          {
           Coord gx=-x;
           
           Coord len=Min<Coord>(DefaultFont::DX-gx,dx); // > 0
          
           Raw *ptr=place(Point(0,y));
           
           Line(ptr,glyph[gy],gx,len,color);
           
           while( ++gy<lim )
             {
              ptr=nextY(ptr);
             
              Line(ptr,glyph[gy],gx,len,color);
             }
          }
       }
    
      void text(TextPlace place,StrLen str,DesktopColor color)
       {
        if( !*this ) return;
        
        Coord y;
        
        switch( place.align_y )
          {
           case AlignY::Top : y=0; break;
            
           case AlignY::Center : y=(dy-DefaultFont::DY)/2; break;
            
           case AlignY::Bottom : y=dy-DefaultFont::DY; break;
            
           default: y=IntSub(place.y,DefaultFont::BY);
          }
        
        Coord x;
        
        switch( place.align_x )
          {
           case AlignX::Left : x=0; break;
           
           case AlignX::Right :
            {
             ulen cap=ulen(dx/DefaultFont::DX)+1;
             
             if( str.len>cap ) str=str.suffix(cap);
             
             x=Coord( dx-str.len*DefaultFont::DX );
            }
           break;
           
           case AlignX::Center :
            {
             ulen cap=ulen(dx/DefaultFont::DX)+1;
             
             if( str.len>cap ) 
               {
                ulen delta=(str.len-cap)/2;
               
                str=str.inner(delta,delta);
               }
             
             x=Coord( dx-str.len*DefaultFont::DX )/2;
            }
           break;
           
           default: x=place.x;
          }
        
        if( y>=dy || y<=-DefaultFont::DY ) return;
        
        if( x>=dx ) return;
        
        for(char ch : str )
          {
           text(x,y,ch,color);
          
           x+=DefaultFont::DX;
          }
       }
    };
  
  public:
  
   DefFont() {}
  
   virtual ~DefFont() {}
   
   // AbstractFont
   
   virtual void text(FrameBuf<DesktopColor> buf,TextPlace place,StrLen str,DesktopColor color)
    {
     WorkBuf out(buf);
     
     out.text(place,str,color);
    }
 };

} // namespace Private_Font

using namespace Private_Font;

/* class Font */

Font::Font()
 : ptr(new DefFont())
 {
 }

} // namespace Video
} // namespace CCore
 

