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

struct AbstractInfo;

class InfoBase;

class Info;

class InfoFromString;

class InfoShape;

/* struct AbstractInfo */

struct AbstractInfo
 {
  virtual ulen getLineCount() const =0;
  
  virtual StrLen getLine(ulen index) const =0;
 };

/* class InfoBase */

class InfoBase : public MemBase_nocopy , public AbstractInfo
 {
   Atomic refs;
 
  public:
 
   InfoBase() { refs=1; }
 
   virtual ~InfoBase() {}
  
   void incRef() { refs++; }
  
   bool decRef() { return (refs--)==1; }
  
   void destroy() { delete this; }
 };

/* class Info */

class Info
 {
   RefPtr<InfoBase> ptr;
  
  protected:
  
   explicit Info(InfoBase *info) : ptr(info) {}
  
  public:
  
   ~Info() {}
  
   AbstractInfo * operator -> () const { return ptr.getPtr(); }
 };

/* class InfoFromString */

class InfoFromString : public Info
 {
   class Impl : public InfoBase
    {
      DynArray<String> buf;
      
     private:
      
      static StrLen CutLine(StrLen &str); 
      
     public:
     
      explicit Impl(StrLen str);
      
      virtual ~Impl();
      
      // AbstractInfo
      
      virtual ulen getLineCount() const;
      
      virtual StrLen getLine(ulen index) const;
    };
  
  public:
  
   explicit InfoFromString(StrLen str);
   
   ~InfoFromString();
 };

/* class InfoShape */

class InfoShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
     
     RefVal<Coord> border_dxy = 5 ;
     
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
   
   ulen yoffMax = 0 ;
   Coord xoffMax = 0 ;
   
   bool drag = false ;
   Point drag_base;
   Coord xoff_base = 0 ;
   
   // methods
   
   InfoShape(const Config &cfg_,const Info &info_) : cfg(cfg_),info(info_) {}
   
   Point getMinSize() const;
   
   void setMax();
   
   bool isGoodSize(Point size) const { return size>=getMinSize(); }
   
   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore
 
#endif
 

