/* ShapeLib.h */ 
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

#ifndef CCore_inc_video_ShapeLib_h
#define CCore_inc_video_ShapeLib_h

#include <CCore/inc/video/Point.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>
#include <CCore/inc/video/Info.h>

#include <CCore/inc/String.h>
 
namespace CCore {
namespace Video {

/* classes */

class ButtonShape;

class KnobShape;

class CheckShape;

class RadioShape;

class LabelShape;

class TextShape;

class SingleLineShape;

class XSingleLineShape;

class YSingleLineShape;

class DoubleLineShape;

class XDoubleLineShape;

class YDoubleLineShape;

class ContourShape;

class TextContourShape;

class SwitchShape;

class LightShape;

class ScrollShape;

class XScrollShape;

class YScrollShape;

class ProgressShape;

class InfoShape;

/* class ButtonShape */

class ButtonShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
    
     RefVal<VColor> border =   Blue ;
     RefVal<VColor> focus  = Orange ;
     
     RefVal<VColor> bottom =   Gray ;
     RefVal<VColor> topUp  =  Green ;
     RefVal<VColor> top    =   Snow ;
     RefVal<VColor> text   =  Black ;
     
     RefVal<Font> font;
    
     Config() {}
    };
   
   // parameters
   
   using FaceType = String ;
   
   const Config &cfg;
   FaceType face;
   Pane pane;
   
   // state
   
   bool enable =  true ;
   bool focus  = false ;
   bool mover  = false ;
   bool down   = false ;
   
   bool mouse  = false ; 
   
   // methods
   
   ButtonShape(const Config &cfg_,const FaceType &face_) : cfg(cfg_),face(face_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

/* class KnobShape */

class KnobShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
     
     RefVal<VColor> border =   Blue ;
     RefVal<VColor> focus  = Orange ;
     
     RefVal<VColor> bottom =   Gray ;
     RefVal<VColor> topUp  =  Green ;
     RefVal<VColor> top    =   Snow ;
     RefVal<VColor> face   =  Black ;
     
     Config() {}
    };
   
   // parameters
   
   enum FaceType
    {
     FaceOk,
     FacePlus,
     FaceMinus,
     FaceCross,
     FaceAsterisk,
     FaceExclamation,
     FaceQuestion,
     FaceLeft,
     FaceRight,
     FaceUp,
     FaceDown,
     FaceStop,
     FaceRightRight,
     FaceLeftLeft
    };
   
   const Config &cfg;
   FaceType face;
   Pane pane;
   
   // state
   
   bool enable =  true ;
   bool focus  = false ;
   bool mover  = false ;
   bool down   = false ;
   
   bool mouse  = false ; 
   
   // methods
   
   KnobShape(const Config &cfg_,const FaceType &face_) : cfg(cfg_),face(face_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

/* class CheckShape */

class CheckShape
 {
  public:
  
   struct Config
    {
     RefVal<VColor> border   =   Blue ;
     RefVal<VColor> focus    = Orange ;
     
     RefVal<VColor> bottomUp =  Green ;
     RefVal<VColor> bottom   =   Snow ;
     RefVal<VColor> top      =   Gray ;
     RefVal<VColor> mark     =  Black ;
     
     Config() {}
    };
   
   const Config &cfg;
   Pane pane;
   
   // state
   
   bool enable =  true ;
   bool focus  = false ;
   bool mover  = false ;
   bool check  = false ;
   
   // methods
   
   explicit CheckShape(const Config &cfg_,bool check_=false) : cfg(cfg_),check(check_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

/* class RadioShape */

class RadioShape
 {
  public:
  
   struct Config
    {
     RefVal<VColor> border   =   Blue ;
     RefVal<VColor> focus    = Orange ;
     
     RefVal<VColor> bottomUp =  Green ;
     RefVal<VColor> bottom   =   Snow ;
     RefVal<VColor> top      =   Gray ;
     RefVal<VColor> mark     =  Black ;
     
     Config() {}
    };
   
   const Config &cfg;
   Pane pane;
   
   // state
   
   bool enable =  true ;
   bool focus  = false ;
   bool mover  = false ;
   bool check  = false ;
   
   // methods
   
   explicit RadioShape(const Config &cfg_,bool check_=false) : cfg(cfg_),check(check_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

/* class LabelShape */

class LabelShape
 {
  public:
  
   struct Config
    {
     RefVal<VColor> inactive =  Gray ;
     RefVal<VColor> text     = Black ;
    
     RefVal<Font> font;
    
     Config() {}
    };
   
   const Config &cfg;
   String text;
   AlignX align_x;
   AlignY align_y;
   Pane pane;

   // state
   
   bool enable = true ;
   
   // methods
   
   LabelShape(const Config &cfg_,const String &text_,AlignX align_x_=AlignX_Center,AlignY align_y_=AlignY_Center)
    : cfg(cfg_),text(text_),align_x(align_x_),align_y(align_y_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

/* class TextShape */

class TextShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
   
     RefVal<VColor> bottom   =   Snow ;
     RefVal<VColor> top      =   Gray ;
     RefVal<VColor> back     = Silver ;
     RefVal<VColor> text     =  Black ;
     RefVal<VColor> inactive =   Gray ;  
    
     RefVal<Font> font;
    
     Config() {}
    };
   
   const Config &cfg;
   String text;
   AlignX align_x;
   AlignY align_y;
   Pane pane;

   // state
   
   bool enable = true ;
   
   // methods
   
   TextShape(const Config &cfg_,const String &text_,AlignX align_x_=AlignX_Center,AlignY align_y_=AlignY_Center)
    : cfg(cfg_),text(text_),align_x(align_x_),align_y(align_y_) {}
   
   explicit TextShape(const Config &cfg_,AlignX align_x_=AlignX_Center,AlignY align_y_=AlignY_Center)
    : cfg(cfg_),align_x(align_x_),align_y(align_y_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

/* class SingleLineShape */

class SingleLineShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
   
     RefVal<VColor> line = Gray ;
    
     Config() {}
    };
   
   const Config &cfg;
   Pane pane;
 
   // methods
  
   explicit SingleLineShape(const Config &cfg_) : cfg(cfg_) {}
 };

/* class XSingleLineShape */

class XSingleLineShape : public SingleLineShape
 {
  public:
  
   // methods
  
   explicit XSingleLineShape(const Config &cfg) : SingleLineShape(cfg) {}
  
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
  
   void draw(const DrawBuf &buf) const;
 };

/* class YSingleLineShape */

class YSingleLineShape : public SingleLineShape
 {
  public:
  
   // methods
  
   explicit YSingleLineShape(const Config &cfg) : SingleLineShape(cfg) {}
  
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
  
   void draw(const DrawBuf &buf) const;
 };

/* class DoubleLineShape */

class DoubleLineShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
   
     RefVal<VColor> top    = Gray ;
     RefVal<VColor> bottom = Snow ;
    
     Config() {}
    };
   
   const Config &cfg;
   Pane pane;
 
   // methods
  
   explicit DoubleLineShape(const Config &cfg_) : cfg(cfg_) {}
 };

/* class XDoubleLineShape */

class XDoubleLineShape : public DoubleLineShape
 {
  public:
  
   // methods
  
   explicit XDoubleLineShape(const Config &cfg) : DoubleLineShape(cfg) {}
  
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
  
   void draw(const DrawBuf &buf) const;
 };

/* class YDoubleLineShape */

class YDoubleLineShape : public DoubleLineShape
 {
  public:
  
   // methods
  
   explicit YDoubleLineShape(const Config &cfg) : DoubleLineShape(cfg) {}
  
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
  
   void draw(const DrawBuf &buf) const;
 };

/* class ContourShape */

class ContourShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
   
     RefVal<VColor> top    = Gray ;
     RefVal<VColor> bottom = Snow ;
    
     Config() {}
    };
   
   const Config &cfg;
   Pane pane;
 
   // methods
  
   explicit ContourShape(const Config &cfg_) : cfg(cfg_) {}
  
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   Pane getInner() const;
  
   void draw(const DrawBuf &buf) const;
 };

/* class TextContourShape */

class TextContourShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
   
     RefVal<VColor> top    =  Gray ;
     RefVal<VColor> bottom =  Snow ;
     RefVal<VColor> text   = Black ;
    
     RefVal<Font> font;
     
     Config() {}
    };
   
   const Config &cfg;
   String title;
   AlignX align_x;
   Pane pane;
 
   // methods
  
   TextContourShape(const Config &cfg_,const String &title_,AlignX align_x_=AlignX_Left) : cfg(cfg_),title(title_),align_x(align_x_) {}
  
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   Pane getInner() const;
  
   void draw(const DrawBuf &buf) const;
 };

/* class SwitchShape */

class SwitchShape
 {
  public:
  
   struct Config
    {
     RefVal<VColor> border =   Blue ;
     RefVal<VColor> focus  = Orange ;
     
     RefVal<VColor> top    =   Snow ;
     RefVal<VColor> bottom =   Gray ;
     RefVal<VColor> faceUp =   Blue ;
     RefVal<VColor> face   =  Black ;
     RefVal<VColor> on     =  Green ;
     RefVal<VColor> off    =    Red ;
     
     Config() {}
    };
   
   const Config &cfg;
   Pane pane;
   
   // state
   
   bool enable =  true ;
   bool focus  = false ;
   bool mover  = false ;
   bool check  = false ;
   
   // methods
   
   explicit SwitchShape(const Config &cfg_,bool check_=false) : cfg(cfg_),check(check_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

/* class LightShape */

class LightShape
 {
  public:
  
   struct Config
    {
     RefVal<VColor> top      =   Gray ; 
     RefVal<VColor> bottom   =  Black ;
     RefVal<VColor> inactive = Silver ;
     
     Config() {}
    };
   
   const Config &cfg;
   VColor face = Green ;
   Pane pane;
   
   // state
   
   bool on = false ;
   
   // methods
   
   explicit LightShape(const Config &cfg_) : cfg(cfg_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

/* enum ScrollType */

enum ScrollType
 {
  ScrollType_None = 0,
  
  ScrollType_Down,
  ScrollType_DownPage,
  ScrollType_Drag,
  ScrollType_UpPage,
  ScrollType_Up
 };

/* class ScrollShape */

class ScrollShape
 {
  protected:
  
   static unsigned Accelerate(unsigned change_count,unsigned period);
  
   static ulen Delta(ulen m,uCoord p,uCoord q);
   
   ulen delta(uCoord delta,uCoord len,uCoord dlen) const;
   
   void dragPos(Coord from,Coord to,uCoord len,uCoord dlen);
  
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
  
     RefVal<VColor> top    =   Snow ;
     RefVal<VColor> back   = Silver ;
     RefVal<VColor> bottom =   Gray ;
     RefVal<VColor> focus  = Orange ;
     RefVal<VColor> face   =  Black ;
     RefVal<VColor> faceUp =   Blue ;
     
     RefVal<unsigned> speedUpPeriod = 12 ;
     
     Config() {}
    };
   
   const Config &cfg;
   Pane pane;
   
   // state
   
   ulen total = 0 ;
   ulen page  = 0 ; // page <= total
   ulen pos   = 0 ; // pos <= total-page
   
   bool enable=true;
   bool focus=false;
   ScrollType mover = ScrollType_None ;
   ScrollType down = ScrollType_None ;
   
   ScrollType press_type = ScrollType_None ;
   bool mouse = false ;
   Point drag_base;
   ulen drag_pos = 0 ;
   unsigned change_count = 0 ;
   
   // methods
   
   explicit ScrollShape(const Config &cfg_) : cfg(cfg_) {}
   
   ulen getMaxPos() const
    {
     if( page<total ) return total-page;
     
     return 0;
    }
   
   void adjustPos()
    {
     Replace_min(pos,getMaxPos());
    }

   void posMin()
    {
     pos=0;
    }
   
   void posMax()
    {
     pos=getMaxPos();
    }
   
   void posDown()
    {
     if( pos ) pos--;
    }
   
   void posDown(ulen d)
    {
     if( !d ) return;
     
     if( pos>d ) 
       pos-=d;
     else
       pos=0;
    }
   
   void posDownPage() { posDown(page); }
   
   void posUp()
    {
     ulen cap=getMaxPos();
     
     if( pos<cap ) pos++;
    }
   
   void posUp(ulen d)
    {
     if( !d ) return;
     
     ulen cap=getMaxPos();
     
     if( d<cap && pos<cap-d )
       pos+=d;
     else
       pos=cap;
    }
   
   void posUpPage() { posUp(page); }
   
   bool posChange()
    {
     ulen old_pos=pos;
     
     switch( press_type )
       {
        case ScrollType_Down :
         {
          posDown(Accelerate(change_count,+cfg.speedUpPeriod));
         }
        break;

        case ScrollType_Up : 
         {
          posUp(Accelerate(change_count,+cfg.speedUpPeriod));
         }
        break;
        
        case ScrollType_DownPage : 
         {
          if( (change_count%+cfg.speedUpPeriod)==0 ) posDownPage();
         }
        break;
         
        case ScrollType_UpPage : 
         {
          if( (change_count%+cfg.speedUpPeriod)==0 ) posUpPage();
         }
        break;
       }
     
     change_count++;
     
     return old_pos!=pos;
    }
 };

/* class XScrollShape */

class XScrollShape : public ScrollShape
 {
  public:
  
   static const VKey DownKey = VKey_Left ;
   
   static const VKey UpKey = VKey_Right ;
  
   // methods
   
   explicit XScrollShape(const Config &cfg) : ScrollShape(cfg) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize() && size.x>=5*size.y ; }
   
   ScrollType getType(MPoint point) const;
   
   void drag(Point point) { dragPos(drag_base.x,point.x,pane.dx,pane.dy); }
   
   void draw(const DrawBuf &buf) const;
 };

/* class YScrollShape */

class YScrollShape : public ScrollShape
 {
  public:
  
   static const VKey DownKey = VKey_Up ;
  
   static const VKey UpKey = VKey_Down ;
   
   // methods
   
   explicit YScrollShape(const Config &cfg) : ScrollShape(cfg) {}
   
   Point getMinSize() const;
   
   ScrollType getType(MPoint point) const;
   
   void drag(Point point) { dragPos(drag_base.y,point.y,pane.dy,pane.dx); }
   
   bool isGoodSize(Point size) const { return size>=getMinSize() && size.y>=5*size.x ; }
   
   void draw(const DrawBuf &buf) const;
 };

/* class ProgressShape */

class ProgressShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> border       =     Black ;
     RefVal<VColor> active       =    Silver ;
     
     RefVal<VColor> top          =      Snow ;
     RefVal<VColor> bottom       =      Gray ;
     
     RefVal<VColor> activeTop    =     Green ;
     RefVal<VColor> activeBottom = DarkGreen ;
     
     RefVal<unsigned> time   = 3*25 ;
     RefVal<unsigned> period =    2 ;
     
     Config() {}
    };
   
   const Config &cfg;
   Pane pane;
   
   // state

   static const unsigned MaxActivePos = 100 ;
   
   unsigned total      =   100 ;
   unsigned pos        =     0 ;
   unsigned active_pos =     0 ;
   bool has_active     = false ;
   
   unsigned time  = 0 ;
   unsigned count = 0 ;
   
   // methods
   
   explicit ProgressShape(const Config &cfg_) : cfg(cfg_) {}
   
   Point getMinSize() const;
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void adjustPos()
    {
     Replace_min(pos,total);
    }
   
   void resetTime() { time=+cfg.time; }
   
   bool tick()
    {
     if( ++count>=cfg.period.get() )
       {
        count=0;
        
        return true; 
       }
     
     return false;
    }
   
   bool startActive()
    {
     if( !has_active )
       {
        has_active=true;
        active_pos=0;
        
        return true;
       }
     
     return false;
    }
     
   void nextActive()
    {
     if( (active_pos+=MaxActivePos/10)>MaxActivePos ) active_pos=0;
    }

   void stopActive() 
    {  
     has_active=false;
    }
   
   void draw(const DrawBuf &buf) const;
 };

/* class InfoShape */

class InfoShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
     
     RefVal<Coord> space_dxy = 5 ;
     
     RefVal<VColor> text  =  Black ;
     RefVal<VColor> focus = Orange ;
     
     RefVal<Font> text_font;
    
     Config()
      {
      }
    };
   
   // parameters
   
   const Config &cfg;
   Info info;
   Pane pane;
   
   // state

   bool has_focus = false ;
   
   ulen yoff  = 0 ;
   Coord xoff = 0 ;
   
   ulen yoffMax  = 0 ;
   Coord xoffMax = 0 ;
   Coord dxoff   = 0 ;
   
   bool drag = false ;
   Point drag_base;
   Coord xoff_base = 0 ;
   
   // methods
   
   explicit InfoShape(const Config &cfg_) : cfg(cfg_) {}
   
   InfoShape(const Config &cfg_,const Info &info_) : cfg(cfg_),info(info_) {}
   
   Point getMinSize() const;
   
   void setMax();
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore
 
#endif
 

