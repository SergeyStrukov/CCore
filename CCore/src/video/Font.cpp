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
    
      static Point Prepare(Coord px,Coord py,TextPlace place,StrLen &str)
       {
        Coord y;
        
        switch( place.align_y )
          {
           case AlignY_Top : y=0; break;
            
           case AlignY_Center : y=(py-DefaultFont::DY)/2; break;
            
           case AlignY_Bottom : y=py-DefaultFont::DY; break;
            
           default: y=IntSub(place.y,DefaultFont::BY);
          }
        
        Coord x;
        
        switch( place.align_x )
          {
           case AlignX_Left : x=0; break;
           
           case AlignX_Right :
            {
             ulen cap=ulen(px/DefaultFont::DX)+1;
             
             if( str.len>cap ) str=str.suffix(cap);
             
             x=Coord( px-str.len*DefaultFont::DX );
            }
           break;
           
           case AlignX_Center :
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
        
        return Point(x,y);
       }
      
      void text(Point point,StrLen str,DesktopColor color)
       {
        Coord x=mapX(point.x);
        Coord y=mapY(point.y);
        
        if( y>=dy || y<=-DefaultFont::DY ) return;
        
        for(char ch : str )
          {
           if( x>=dx ) return;
          
           text(x,y,ch,color);
          
           x+=DefaultFont::DX;
          }
       }
      
      void text(Coord px,Coord py,TextPlace place,StrLen str,DesktopColor color)
       {
        if( !*this ) return;
        
        Point point=Prepare(px,py,place,str);
        
        text(point,str,color);
       }
      
      void text_update(Coord px,Coord py,TextPlace &place,StrLen str,DesktopColor color)
       {
        Point point=Prepare(px,py,place,str);
        
        if( +*this ) text(point,str,color);

        point.x+=Coord( str.len*DefaultFont::DX );
        
        place=TextPlace(point.x,point.y+DefaultFont::BY);
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
   
   virtual void text_update(DrawBuf buf,Pane pane,TextPlace &place,StrLen str,DesktopColor color)
    {
     WorkBuf out(buf.cutRebase(pane));
     
     out.text_update(pane.dx,pane.dy,place,str,color);
    }
   
   virtual void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str,DesktopColor color)
    {
     WorkBuf out(buf.cutRebase(pane));
     
     out.text(pane.dx,pane.dy,place,str,color);
    }
   
   static const ulen MaxLen = ulen(MaxCoord/DefaultFont::DX) ;
   
   virtual TextSize text(StrLen str)
    {
     TextSize ret;
     
     if( str.len>MaxLen )
       {
        ret.dx=MaxCoord;
        ret.dy=DefaultFont::DY;
        ret.by=DefaultFont::BY;
        ret.skew=0;
        ret.full_dx=ret.dx;
        ret.overflow=true;
       }
     else
       {
        ret.dx=Coord( str.len*DefaultFont::DX );
        ret.dy=DefaultFont::DY;
        ret.by=DefaultFont::BY;
        ret.skew=0;
        ret.full_dx=ret.dx;
        ret.overflow=false;
       }
     
     return ret;
    }
   
   virtual TextSize text(StrLen str1,StrLen str2)
    {
     TextSize ret;
     
     if( str1.len>MaxLen || str2.len>MaxLen-str1.len )
       {
        ret.dx=MaxCoord;
        ret.dy=DefaultFont::DY;
        ret.by=DefaultFont::BY;
        ret.skew=0;
        ret.full_dx=ret.dx;
        ret.overflow=true;
       }
     else
       {
        ulen len=str1.len+str2.len;
        
        ret.dx=Coord( len*DefaultFont::DX );
        ret.dy=DefaultFont::DY;
        ret.by=DefaultFont::BY;
        ret.skew=0;
        ret.full_dx=ret.dx;
        ret.overflow=false;
       }
     
     return ret;
    }

   virtual ulen fit(StrLen str,Coord full_dx)
    {
     ulen max_len=full_dx/DefaultFont::DX;
     
     return Min(str.len,max_len);
    }
 };

DefFont Object CCORE_INITPRI_3 ; 

} // namespace Private_Font

using namespace Private_Font;

/* class Font */

Font::Font()
 : ptr(&Object)
 {
  ptr->incRef();
 }

} // namespace Video
} // namespace CCore
 

