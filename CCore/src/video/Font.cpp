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
  
   class WorkBuf : public DrawBuf
    {
     public:
    
      explicit WorkBuf(DrawBuf buf) : DrawBuf(buf) {}
      
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
        if( x<=-DefaultFont::DX ) return;
        
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
    
      void text(Coord px,Coord py,TextPlace place,StrLen str,DesktopColor color)
       {
        if( !*this ) return;
        
        Coord y;
        
        switch( place.align_y )
          {
           case AlignY::Top : y=0; break;
            
           case AlignY::Center : y=(py-DefaultFont::DY)/2; break;
            
           case AlignY::Bottom : y=py-DefaultFont::DY; break;
            
           default: y=IntSub(place.y,DefaultFont::BY);
          }
        
        Coord x;
        
        switch( place.align_x )
          {
           case AlignX::Left : x=0; break;
           
           case AlignX::Right :
            {
             ulen cap=ulen(px/DefaultFont::DX)+1;
             
             if( str.len>cap ) str=str.suffix(cap);
             
             x=Coord( px-str.len*DefaultFont::DX );
            }
           break;
           
           case AlignX::Center :
            {
             ulen cap=ulen(px/DefaultFont::DX)+1;
             
             if( str.len>cap ) 
               {
                ulen delta=(str.len-cap)/2;
               
                str=str.inner(delta,delta);
               }
             
             x=Coord( px-str.len*DefaultFont::DX )/2;
            }
           break;
           
           default: x=place.x;
          }
        
        x=mapX(x);
        y=mapY(y);
        
        if( y>=dy || y<=-DefaultFont::DY ) return;
        
        for(char ch : str )
          {
           if( x>=dx ) return;
          
           text(x,y,ch,color);
          
           x+=DefaultFont::DX;
          }
       }
    };
  
  public:
  
   DefFont() {}
  
   virtual ~DefFont() {}
   
   // AbstractFont
   
   virtual FontSize getSize()
    {
     FontSize ret;
     
     ret.min_dx=DefaultFont::DX;
     ret.max_dx=DefaultFont::DX;
     ret.dy=DefaultFont::DY;
     ret.by=DefaultFont::BY;
     ret.skew=0;
     
     return ret;
    }
   
   virtual void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str,DesktopColor color)
    {
     WorkBuf out(buf.cutRebase(pane));
     
     out.text(pane.dx,pane.dy,place,str,color);
    }
   
   virtual TextSize text(StrLen str)
    {
     TextSize ret;
     
     ret.dx=Coord( str.len*DefaultFont::DX );
     ret.dy=DefaultFont::DY;
     ret.by=DefaultFont::BY;
     ret.skew=0;
     ret.overflow=( str.len>ulen(MaxCoord/DefaultFont::DX) );
     
     return ret;
    }

   virtual ulen fit(StrLen str,Coord dx)
    {
     ulen max_len=dx/DefaultFont::DX;
     
     return Min(str.len,max_len);
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
 

