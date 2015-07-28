/* ShapeLib2.h */ 
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

#ifndef CCore_inc_video_ShapeLib2_h
#define CCore_inc_video_ShapeLib2_h
 
#include <CCore/inc/video/Point.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/String.h>

namespace CCore {
namespace Video {

/* classes */

class LineEditShape;

/* class LineEditShape */

class LineEditShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
     
     RefVal<Coord> ex = 3 ;
     RefVal<Coord> cursor_dx = 3 ;
   
     RefVal<VColor> back     = Silver ;
     RefVal<VColor> bottom   =   Snow ;
     RefVal<VColor> top      =   Gray ;
     RefVal<VColor> focus    = Orange ;
     
     RefVal<VColor> text     =  Black ;
     RefVal<VColor> inactive =   Gray ;
     RefVal<VColor> select   = Yellow ;
     
     RefVal<VColor> cursor   =   Blue ;
    
     RefVal<Font> font;
   
     RefVal<unsigned> period = 10 ;
     
     Config() {}
    };
   
   const Config &cfg;
   PtrLen<char> text_buf;
   Pane pane;

   // state
   
   bool enable =  true ;
   bool focus  = false ;
   bool cursor = false ;
   ulen len    =     0 ;
   ulen pos    =     0 ;
   ulen select_off = 0 ;
   ulen select_len = 0 ;
   Coord xoff  =     0 ;
   
   Coord xoffMax = 0 ;
   Coord dxoff   = 0 ;
   
   bool drag = false ;
   Point drag_base;
   Coord xoff_base = 0 ;
   bool mouse_pos = false ;
   
   unsigned count = 0 ;
   
   // methods

   LineEditShape(PtrLen<char> text_buf_,const Config &cfg_) : cfg(cfg_),text_buf(text_buf_) {}
   
   Point getMinSize() const;
   
   void setMax();
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   bool tick()
    {
     if( ++count>=cfg.period.get() )
       {
        count=0;
        
        return true; 
       }
     
     return false;
    }
   
   void showCursor();
   
   ulen getPosition(Point point) const;
   
   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore
 
#endif
 

