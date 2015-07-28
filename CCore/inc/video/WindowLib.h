/* WindowLib.h */ 
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

#ifndef CCore_inc_video_WindowLib_h
#define CCore_inc_video_WindowLib_h

#include <CCore/inc/video/ShapeLib.h>
#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/Signal.h>
#include <CCore/inc/DeferCall.h>
 
#include <CCore/inc/CharProp.h>
#include <CCore/inc/algon/EuclidRotate.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class ButtonWindowOf;

template <class Shape> class CheckWindowOf;

class RadioItem;

class RadioGroup;

template <class Shape> class RadioWindowOf;

template <class Shape> class TextWindowOf;

template <class Shape> class DecorWindowOf;

template <class Shape> class LightWindowOf;

template <class Shape> class ScrollWindowOf;

template <class Shape> class ProgressWindowOf;

template <class Shape> class InfoWindowOf;

template <class Shape,ulen TextBufLen=1024> class LineEditWindowOf;

/* class ButtonWindowOf<Shape> */

template <class Shape>
class ButtonWindowOf : public SubWindow
 {
   Shape shape;
   
  private:
   
   void inside()
    {
     if( Change(shape.mover,true) ) redraw();
    }
   
   void outside()
    {
     if( shape.down && shape.mouse )
       {
        shape.mover=false;
        shape.down=false;
        
        releaseMouse();
        
        redraw();
       }
     else
       {
        if( Change(shape.mover,false) ) redraw();
       }
    }
   
  public:
  
   template <class ... TT>
   explicit ButtonWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }
  
   virtual ~ButtonWindowOf() {}
   
   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   bool isEnabled() const { return shape.enable; }
   
   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }
   
   void disable() { enable(false); }
   
   using FaceType = typename Shape::FaceType ;
   
   FaceType getFace() const { return shape.face; }
   
   void setFace(const FaceType &face)
    { 
     shape.face=face; 
     
     redraw(); 
    }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }
   
   // base
   
   virtual void open()
    {
     shape.focus=false;
     shape.down=false;
     shape.mover=false;
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     if( Change(shape.focus,true) ) redraw();
    }
   
   virtual void looseFocus()
    {
     if( shape.down && !shape.mouse ) 
       {
        shape.down=false;
        shape.focus=false;
        
        redraw();
       }
     else
       {
        if( Change(shape.focus,false) ) redraw();
       }
    }
   
   // mouse
 
   virtual void looseCapture()
    {
     if( shape.down && shape.mouse )
       {
        shape.down=false;
        
        redraw();
       }
    }
 
   virtual MouseShape getMouseShape(Point,KeyMod)
    {
     if( shape.enable ) return Mouse_Hand;
     
     return Mouse_Arrow;
    }
   
   // user input
   
   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }
   
   void react_Key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_Enter :
        case VKey_Space :
         {
          if( shape.enable && !shape.down ) 
            {
             shape.down=true;
             shape.mouse=false;
             
             redraw();
            }
         }
        break; 
        
        case VKey_Tab :
         {
          tabbed.assert(kmod&KeyMod_Shift);
         }
        break; 
       }
    }
   
   void react_KeyUp(VKey vkey,KeyMod)
    {
     switch( vkey )
       {
        case VKey_Enter :
        case VKey_Space :
         {
          if( shape.down && !shape.mouse ) 
            {
             shape.down=false;
             
             pressed.assert();
             
             redraw();
            }
         }
        break; 
       }
    }
   
   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && !shape.down && shape.pane.contains(point) )
       {
        shape.mouse=true;
        shape.down=true;
        
        captureMouse();
        
        redraw();
       }
    }
   
   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.down && shape.mouse )
       {
        shape.down=false;
        
        releaseMouse();
        
        if( shape.pane.contains(point) ) pressed.assert();
        
        redraw();
       }
    }
   
   void react_LeftDClick(Point point,MouseKey mkey)
    {
     react_LeftClick(point,mkey);
    }
   
   void react_Move(Point point,MouseKey)
    {
     if( shape.pane.contains(point) )
       {
        inside();
       }
     else
       {
        outside();
       } 
    }
   
   void react_Leave()
    {
     outside();
    }
   
   // signals
   
   Signal<> pressed;
   Signal<bool> tabbed; // shift
 };

/* type ButtonWindow */

using ButtonWindow = ButtonWindowOf<ButtonShape> ;

/* type KnobWindow */

using KnobWindow = ButtonWindowOf<KnobShape> ;

/* class CheckWindowOf<Shape> */

template <class Shape> 
class CheckWindowOf : public SubWindow
 {
   Shape shape;
   
  private: 
  
   void inside()
    {
     if( Change(shape.mover,true) ) redraw();
    }
   
   void outside()
    {
     if( Change(shape.mover,false) ) redraw();
    }
   
   void change()
    {
     shape.check=!shape.check;
    
     changed.assert(shape.check);
     
     redraw();
    }
   
  public:
   
   template <class ... TT>
   explicit CheckWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }
   
   virtual ~CheckWindowOf() {}
   
   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   bool isEnabled() const { return shape.enable; }
   
   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }
   
   void disable() { enable(false); }
   
   bool isChecked() const { return shape.check; }
   
   void check(bool check=true)
    {  
     if( Change(shape.check,check) ) redraw();
    }
   
   void uncheck() { check(false); }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }
   
   // base
   
   virtual void open()
    {
     shape.focus=false;
     shape.mover=false;
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     if( Change(shape.focus,true) ) redraw();
    }
   
   virtual void looseFocus()
    {
     if( Change(shape.focus,false) ) redraw();
    }
   
   // mouse
 
   virtual MouseShape getMouseShape(Point,KeyMod)
    {
     if( shape.enable ) return Mouse_Hand;
     
     return Mouse_Arrow;
    }
   
   // user input
   
   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_Enter :
        case VKey_Space :
         {
          if( shape.enable ) change();  
         }
        break; 
        
        case VKey_Tab :
         {
          tabbed.assert(kmod&KeyMod_Shift);
         }
        break; 
       }
    }
   
   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && shape.pane.contains(point) ) change();
    }
   
   void react_LeftDClick(Point point,MouseKey mkey)
    {
     react_LeftClick(point,mkey);
    }
   
   void react_Move(Point point,MouseKey)
    {
     if( shape.pane.contains(point) )
       {
        inside();
       }
     else
       {
        outside();
       } 
    }
   
   void react_Leave()
    {
     outside();
    }
   
   // signals
   
   Signal<bool> changed; // check
   Signal<bool> tabbed;  // shift
 };

/* type CheckWindow */

using CheckWindow = CheckWindowOf<CheckShape> ;

/* type SwitchWindow */

using SwitchWindow = CheckWindowOf<SwitchShape> ;

/* class RadioItem */

class RadioItem : NoCopy
 {
   int radio_id;
  
   DLink<RadioItem> link;
   RadioGroup *group = 0 ;
  
  protected:
  
   void setCheck();
   
   virtual void check(bool check)=0;
   
   virtual void uncheck()=0;
   
   friend class RadioGroup;
  
  public:
  
   explicit RadioItem(int radio_id_);
   
   ~RadioItem();
 };

/* class RadioGroup */

class RadioGroup : NoCopy
 {
   using Algo = DLink<RadioItem>::LinearAlgo<&RadioItem::link> ;
   
   Algo::FirstLast list;
   RadioItem *cur = 0 ;
   
   friend class RadioItem;
  
  public:
  
   RadioGroup();
   
   ~RadioGroup();
   
   void add(RadioItem *item);
   
   void del(RadioItem *item);
   
   void add(RadioItem &item) { add(&item); }

   template <class ... TT>
   void add(RadioItem *item,TT * ... tt)
    {
     add(item);
     
     add(tt...);
    }

   template <class ... TT>
   void add(RadioItem &item,TT && ... tt)
    {
     add(item);
     
     add(tt...);
    }

   // signals
   
   Signal<int,int> changed; // new_id, prev_id
 };

/* class RadioWindowOf<Shape> */

template <class Shape> 
class RadioWindowOf : public SubWindow , public RadioItem
 {
   Shape shape;
  
  private: 
   
   void inside()
    {
     if( Change(shape.mover,true) ) redraw();
    }
   
   void outside()
    {
     if( Change(shape.mover,false) ) redraw();
    }
   
   void select()
    {
     if( !shape.check )
       {
        shape.check=true;
        
        setCheck();
        
        redraw();
       }
    }
   
   virtual void check(bool check)
    {
     shape.check=check;
    }
   
   virtual void uncheck()
    {
     shape.check=false;
     
     redraw();
    }
   
  public:

   template <class ... TT>
   RadioWindowOf(SubWindowHost &host,int radio_id,TT && ... tt)
    : SubWindow(host),
      RadioItem(radio_id),
      shape( std::forward<TT>(tt)... )
    {
    }
  
   virtual ~RadioWindowOf() {}
   
   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   bool isEnabled() const { return shape.enable; }
   
   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }
   
   void disable() { enable(false); }
   
   bool isChecked() const { return shape.check; }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }
   
   // base
   
   virtual void open()
    {
     shape.focus=false;
     shape.mover=false;
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     if( Change(shape.focus,true) ) redraw();
    }
   
   virtual void looseFocus()
    {
     if( Change(shape.focus,false) ) redraw();
    }
   
   // mouse
 
   virtual MouseShape getMouseShape(Point,KeyMod)
    {
     if( shape.enable ) return Mouse_Hand;
     
     return Mouse_Arrow;
    }
   
   // user input
   
   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_Enter :
        case VKey_Space :
         {
          if( shape.enable ) select();  
         }
        break; 
        
        case VKey_Tab :
         {
          tabbed.assert(kmod&KeyMod_Shift);
         }
        break; 
       }
    }
   
   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && shape.pane.contains(point) ) select();
    }
   
   void react_LeftDClick(Point point,MouseKey mkey)
    {
     react_LeftClick(point,mkey);
    }
   
   void react_Move(Point point,MouseKey)
    {
     if( shape.pane.contains(point) )
       {
        inside();
       }
     else
       {
        outside();
       } 
    }
   
   void react_Leave()
    {
     outside();
    }
   
   // signals
   
   Signal<bool> tabbed; // shift
 };

/* type RadioWindow */

using RadioWindow = RadioWindowOf<RadioShape> ;

/* class TextWindowOf<Shape> */

template <class Shape> 
class TextWindowOf : public SubWindow
 {
   Shape shape;
   
  public: 
  
   template <class ... TT>
   TextWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }
   
   virtual ~TextWindowOf() {}
   
   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   bool isEnabled() const { return shape.enable; }
   
   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }
   
   void disable() { enable(false); }
   
   String getText() const { return shape.text; }
   
   void setText(const String &text)
    {
     shape.text=text;
     
     redraw();
    }
   
   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     setText( Stringf(format,tt...) );
    }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }
 };

/* type TextWindow */

using TextWindow = TextWindowOf<TextShape> ;

/* type LabelWindow */

using LabelWindow = TextWindowOf<LabelShape> ;

/* class DecorWindowOf<Shape> */

template <class Shape> 
class DecorWindowOf : public SubWindow
 {
   Shape shape;
   
  public: 
  
   template <class ... TT>
   DecorWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }
   
   virtual ~DecorWindowOf() {}
   
   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   Pane getInner() const { return shape.getInner()+getPlace().getBase(); }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }
 };

/* type XSingleLineWindow */

using XSingleLineWindow = DecorWindowOf<XSingleLineShape> ;

/* type YSingleLineWindow */

using YSingleLineWindow = DecorWindowOf<YSingleLineShape> ;

/* type XDoubleLineWindow */

using XDoubleLineWindow = DecorWindowOf<XDoubleLineShape> ;

/* type YDoubleLineWindow */

using YDoubleLineWindow = DecorWindowOf<YDoubleLineShape> ;

/* type ContourWindow */

using ContourWindow = DecorWindowOf<ContourShape> ;

/* type TextContourWindow */

using TextContourWindow = DecorWindowOf<TextContourShape> ;

/* class LightWindowOf<Shape> */

template <class Shape> 
class LightWindowOf : public SubWindow
 {
   Shape shape;
   
  public: 
  
   template <class ... TT>
   LightWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }
   
   virtual ~LightWindowOf() {}
   
   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   VColor getFace() const { return shape.face; }
   
   void setFace(VColor face)
    { 
     if( Change(shape.face,face) ) redraw();
    }
   
   bool isOn() const { return shape.on; }
   
   void turn(bool on)
    {
     if( Change(shape.on,on) ) redraw();
    }
   
   void turnOn() { turn(true); }
   
   void turnOff() { turn(false); }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }
 };

/* type LightWindow */

using LightWindow = LightWindowOf<LightShape> ;

/* class ScrollWindowOf<Shape> */

template <class Shape> 
class ScrollWindowOf : public SubWindow
 {
   Shape shape;
   
   DeferInput<ScrollWindowOf<Shape> > input;
   
   DeferTick defer_tick;
   
  private: 
   
   void pressOn(ScrollType type,Point point)
    {
     shape.press_type=type;
     
     if( type==ScrollType_Drag )
       {
        shape.drag_base=point;
        shape.drag_pos=shape.pos;
       }
     else
       {
        pressOn();
       }
    }
   
   void pressOn(ScrollType type)
    {
     shape.press_type=type;

     pressOn();
    }
   
   void pressOn()
    {
     shape.change_count=0;
     
     shape.posChange();
     
     changed.assert(shape.pos);
     
     defer_tick.start();
    }
   
   void pressOff(Point point)
    {
     if( shape.press_type==ScrollType_Drag )
       {
        shape.drag(point);
        
        changed.assert(shape.pos);
       }
     else
       {
        pressOff();
       }
    }
   
   void drag(Point point)
    {
     shape.drag(point);
     
     changed.assert(shape.pos);
     
     redraw();
    }
   
   void pressOff()
    {
     defer_tick.stop();
    }
   
   void inside(ScrollType type)
    {
     if( shape.down && shape.mouse )
       {
        if( Change(shape.mover,type) )
          {
           shape.down=ScrollType_None;
           
           releaseMouse();
           
           pressOff();
          
           redraw();
          }
       }
     else
       {
        if( Change(shape.mover,type) ) redraw();
       }
    }
   
   void outside()
    {
     if( shape.down && shape.mouse )
       {
        shape.down=ScrollType_None;
        shape.mover=ScrollType_None;
       
        releaseMouse();
       
        pressOff();
        
        redraw();
       }
     else
       {
        if( Change(shape.mover,ScrollType_None) ) redraw();
       }
    }
   
   void tick()
    {
     if( shape.posChange() )
       {
        changed.assert(shape.pos);
       
        redraw();
       }
    }
   
  public: 
   
   template <class ... TT>
   ScrollWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&ScrollWindowOf<Shape>::tick);
    }
   
   virtual ~ScrollWindowOf() {}

   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   bool isEnabled() const { return shape.enable; }
   
   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }
   
   void disable() { enable(false); }

   ulen getTotal() const { return shape.total; }
   
   ulen getPage() const { return shape.page; }
   
   ulen getPos() const { return shape.pos; }
   
   void setRange(ulen total,ulen page)
    {
     shape.total=total;
     shape.page=page;
     
     shape.adjustPos();
     
     redraw();
    }
   
   void setRange(ulen total,ulen page,ulen pos)
    {
     shape.total=total;
     shape.page=page;
     shape.pos=pos;
     
     shape.adjustPos();
     
     redraw();
    }
   
   void setPos(ulen pos)
    {
     shape.pos=pos;
     
     shape.adjustPos();
     
     redraw();
    }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }
 
   // base
   
   virtual void open()
    {
     shape.focus=false;
     shape.down=ScrollType_None;
     shape.mover=ScrollType_None;
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     if( Change(shape.focus,true) ) redraw();
    }
   
   virtual void looseFocus()
    {
     if( shape.down && !shape.mouse )
       {
        shape.down=ScrollType_None;
        shape.focus=false;
        
        pressOff();
        
        redraw();
       }
     else
       {
        if( Change(shape.focus,false) ) redraw();
       }
    }
   
   // mouse
 
   virtual void looseCapture()
    {
     if( shape.down && shape.mouse )
       {
        shape.down=ScrollType_None;
        shape.mover=ScrollType_None;
        
        pressOff();
        
        redraw();
       }
    }
 
   virtual MouseShape getMouseShape(Point,KeyMod)
    {
     if( shape.enable && shape.page<shape.total ) return Mouse_Hand;
     
     return Mouse_Arrow;
    }
   
   // user input
   
   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }
   
   void react_Key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_Home :
         {
          if( shape.enable && !shape.down )
            {
             shape.posMin();
             
             changed.assert(shape.pos);
             
             redraw();
            }
         }
        break; 
      
        case VKey_End :
         {
          if( shape.enable && !shape.down )
            {
             shape.posMax();
             
             changed.assert(shape.pos);
             
             redraw();
            }
         }
        break;
        
        case Shape::DownKey :
         {
          if( shape.enable && !shape.down )
            {
             shape.down=ScrollType_Down;
             shape.mouse=false;
             
             pressOn(ScrollType_Down);
             
             redraw();
            }
         }
        break; 
        
        case Shape::UpKey :
         {
          if( shape.enable && !shape.down )
            {
             shape.down=ScrollType_Up;
             shape.mouse=false;
             
             pressOn(ScrollType_Up);
             
             redraw();
            }
         }
        break; 
      
        case VKey_PageUp :
         {
          if( shape.enable && !shape.down )
            {
             shape.down=ScrollType_DownPage;
             shape.mouse=false;
             
             pressOn(ScrollType_DownPage);
             
             redraw();
            }
         }
        break; 
        
        case VKey_PageDown :
         {
          if( shape.enable && !shape.down )
            {
             shape.down=ScrollType_UpPage;
             shape.mouse=false;
             
             pressOn(ScrollType_UpPage);
             
             redraw();
            }
         }
        break; 
        
        case VKey_Tab :
         {
          tabbed.assert(kmod&KeyMod_Shift);
         }
        break; 
       }
    }
   
   void react_KeyUp(VKey vkey,KeyMod)
    {
     switch( vkey )
       {
        case Shape::DownKey :
         {
          if( shape.down && !shape.mouse && shape.press_type==ScrollType_Down )
            {
             shape.down=ScrollType_None;
             
             pressOff();
             
             redraw();
            }
         }
        break;
        
        case Shape::UpKey :
         {
          if( shape.down && !shape.mouse && shape.press_type==ScrollType_Up )
            {
             shape.down=ScrollType_None;
             
             pressOff();
             
             redraw();
            }
         }
        break;
        
        case VKey_PageUp :
         {
          if( shape.down && !shape.mouse && shape.press_type==ScrollType_DownPage )
            {
             shape.down=ScrollType_None;
             
             pressOff();
             
             redraw();
            }
         }
        break;
        
        case VKey_PageDown :
         {
          if( shape.down && !shape.mouse && shape.press_type==ScrollType_UpPage )
            {
             shape.down=ScrollType_None;
             
             pressOff();
             
             redraw();
            }
         }
        break; 
       }
    }
   
   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && !shape.down )
       {
        if( ScrollType type=shape.getType(point) )
          {
           shape.mover=type;
           shape.down=type;
           shape.mouse=true;
           
           captureMouse();
           
           pressOn(type,point);
           
           redraw();
          }
       }
    }
   
   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.down && shape.mouse )
       {
        shape.down=ScrollType_None;
        shape.mover=shape.getType(point);
        
        releaseMouse();
        
        pressOff(point);
        
        redraw();
       }
    }
   
   void react_LeftDClick(Point point,MouseKey mkey)
    {
     react_LeftClick(point,mkey);
    }
   
   void react_Move(Point point,MouseKey)
    {
     if( shape.down && shape.mouse && shape.mover==ScrollType_Drag )
       {
        drag(point);
       }
     else
       {
        if( ScrollType type=shape.getType(point) )
          inside(type);
        else
          outside();
       }
    }
   
   void react_Leave()
    {
     if( shape.down && shape.mouse && shape.mover==ScrollType_Drag )
       {
        // do nothing
       }
     else
       {
        outside();
       }
    }
   
   // signals
   
   Signal<ulen> changed; // pos
   Signal<bool> tabbed;  // shift
 };

/* type XScrollWindow */

using XScrollWindow = ScrollWindowOf<XScrollShape> ;

/* type YScrollWindow */

using YScrollWindow = ScrollWindowOf<YScrollShape> ;

/* class ProgressWindowOf<Shape> */

template <class Shape> 
class ProgressWindowOf : public SubWindow
 {
   Shape shape;
  
   DeferInput<ProgressWindowOf<Shape> > input;
   
   DeferTick defer_tick;
   
  private:
   
   void tick()
    {
     if( shape.time )
       {
        shape.time--;
        
        if( shape.tick() )
          {
           shape.nextActive();
          
           redraw();
          }
       }
     else
       {
        defer_tick.stop();
        
        shape.stopActive();
        
        redraw();
       }
    }
   
  public: 
  
   template <class ... TT>
   ProgressWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&ProgressWindowOf<Shape>::tick);
    }
   
   virtual ~ProgressWindowOf() {}
   
   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }

   unsigned getPos() const { return shape.pos; }
   
   unsigned getTotal() const { return shape.total; }
   
   void setTotal(unsigned total)
    {
     shape.total=total;
     shape.pos=0;
     shape.stopActive();
     
     redraw();
    }
   
   void setPos(unsigned pos)
    {
     shape.pos=pos;
     
     shape.adjustPos();
     
     redraw();
    }
   
   void ping()
    {
     shape.resetTime();
     
     defer_tick.start();
     
     if( shape.startActive() ) redraw();
    }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }
 };

/* type ProgressWindow */

using ProgressWindow = ProgressWindowOf<ProgressShape> ;

/* class InfoWindowOf<Shape> */

template <class Shape>
class InfoWindowOf : public SubWindow
 {
   Shape shape;
   
  private: 
   
   void setXOff(Coord xoff)
    {
     if( xoff<0 )
       xoff=0;
     else if( xoff>shape.xoffMax )
       xoff=shape.xoffMax;
     
     if( xoff!=shape.xoff )
       {
        shape.xoff=xoff;
      
        redraw();
       }
    }
   
   void setYOff(ulen yoff)
    {
     if( yoff>shape.yoffMax ) yoff=shape.yoffMax;
     
     if( yoff!=shape.yoff )
       {
        shape.yoff=yoff;
        
        redraw();
       }
    }
   
   void addYOff(ulen delta)
    {
     if( shape.yoff<shape.yoffMax )
       {
        ulen cap=shape.yoffMax-shape.yoff;
       
        setYOff(shape.yoff+Min(delta,cap));
       }
    }
   
   void subYOff(ulen delta)
    {
     ulen yoff=shape.yoff;
     
     if( yoff>delta ) 
       yoff-=delta;
     else
       yoff=0;
     
     setYOff(yoff);
    }
   
   void drag(Point point)
    {
     Coord delta=IntSub(point.x,shape.drag_base.x);
     
     setXOff( IntSub(shape.xoff_base,delta) );
    }
   
  public:

   template <class ... TT>
   InfoWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }
   
   virtual ~InfoWindowOf()
    {
    }

   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   void setInfo(const Info &info)
    {
     shape.info=info;
     shape.yoff=0;
     shape.xoff=0;
     
     redraw();
    }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
     
     shape.setMax();
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }

   // base
   
   virtual void open()
    {
     shape.focus=false;
     shape.drag=false;
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     shape.focus=true;
     
     redraw();
    }
   
   virtual void looseFocus()
    {
     shape.focus=false;
     
     redraw();
    }
   
   // mouse
 
   virtual void looseCapture()
    {
     shape.drag=false;
    }
 
   virtual MouseShape getMouseShape(Point,KeyMod)
    {
     if( shape.xoffMax>0 ) return Mouse_SizeLeftRight;
     
     return Mouse_Arrow;
    }
   
   // user input
   
   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }
   
   void react_Key(VKey vkey,KeyMod,unsigned repeat)
    {
     switch( vkey )
       {
        case VKey_Left :
         {
          Coord delta_x=Coord(repeat)*shape.dxoff;
          
          setXOff( IntSub(shape.xoff,delta_x) );
         }
        break;
        
        case VKey_Right :
         {
          Coord delta_x=Coord(repeat)*shape.dxoff;
          
          setXOff( IntAdd(shape.xoff,delta_x) );
         }
        break;
        
        case VKey_Up :
         {
          subYOff(repeat);
         }
        break;
        
        case VKey_Down :
         {
          addYOff(repeat);
         }
        break; 
       }
    }
   
   void react_LeftClick(Point point,MouseKey)
    {
     if( !shape.drag )
       {
        shape.drag=true;
        
        shape.drag_base=point;
        shape.xoff_base=shape.xoff;
        
        captureMouse();
       }
    }
   
   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.drag )
       {
        shape.drag=false;
       
        releaseMouse();
        
        drag(point);
       }
    }
   
   void react_LeftDClick(Point point,MouseKey mkey)
    {
     react_LeftClick(point,mkey);
    }
   
   void react_Move(Point point,MouseKey mkey)
    {
     if( shape.drag ) 
       {
        if( mkey&MouseKey_Left )
          {
           drag(point);
          } 
        else
          {
           shape.drag=false;
          
           releaseMouse();
          }
       }
    }

   void react_Wheel(Point,MouseKey,Coord delta)
    {
     if( delta>0 )
       {
        addYOff(ulen(delta));
       }
     else
       {
        subYOff(ulen(-delta));
       }
    }
 };

/* type InfoWindow */

using InfoWindow = InfoWindowOf<InfoShape> ;

/* class LineEditWindowOf<Shape,ulen TextBufLen> */

template <class Shape,ulen TextBufLen> 
class LineEditWindowOf : public SubWindow
 {
   Shape shape;
   
   char text_buf[TextBufLen];
   
   DeferInput<LineEditWindowOf<Shape,TextBufLen> > input;
   
   DeferTick defer_tick;
   
  private: 
  
   void setXOff(Coord xoff)
    {
     if( xoff<0 )
       xoff=0;
     else if( xoff>shape.xoffMax )
       xoff=shape.xoffMax;
     
     if( xoff!=shape.xoff )
       {
        shape.xoff=xoff;
      
        redraw();
       }
    }
   
   void drag(Point point)
    {
     Coord delta=IntSub(point.x,shape.drag_base.x);
     
     setXOff( IntSub(shape.xoff_base,delta) );
    }
   
   void del()
    {
     for(auto r=Range(text_buf+shape.pos,shape.len-shape.pos); r.len>1 ;++r) r[0]=r[1];
     
     shape.len--;
     
     shape.setMax();
     
     Replace_min(shape.xoff,shape.xoffMax);
     
     shape.showCursor();
     
     changed.assert();
     
     redraw();
    }
   
   void tick()
    {
     if( shape.tick()  )
       {
        shape.cursor=!shape.cursor;
       
        redraw();
       }
    }
   
   void delSelection_()
    {
     ulen off=shape.select_off+shape.select_len;
     ulen len=shape.len-off;
     
     auto src=Range(text_buf+off,len);
     auto dst=text_buf+shape.select_off;
     
     for(; +src ;++src,++dst) *dst=*src;
     
     shape.len-=shape.select_len;
     shape.pos=shape.select_off;
     shape.select_off=0;
     shape.select_len=0;
     
     shape.setMax();
     
     shape.cursor=true;
     
     shape.showCursor();
    }
   
   void delSelection()
    {
     delSelection_();
     
     changed.assert();
     
     redraw();
    }
   
   void cut()
    {
     copy();
     
     delSelection();
    }
   
   void copy()
    {
     getFrame()->getHost()->textToClipboard(Range(text_buf+shape.select_off,shape.select_len));
    }
   
   void past()
    {
     if( shape.select_len ) delSelection_();
     
     ulen len=getFrame()->getHost()->textFromClipboard(Range(text_buf+shape.len,TextBufLen-shape.len));
     
     shape.len+=len;
     
     Algon::EuclidRotate_suffix(Range(text_buf+shape.pos,shape.len-shape.pos),len);
     
     shape.pos+=len;
     
     shape.setMax();
     
     shape.cursor=true;
     
     shape.showCursor();
     
     changed.assert();
     
     redraw();
    }
   
   void select(ulen pos1,ulen pos2)
    {
     if( pos1<pos2 )
       {
        shape.select_off=pos1;
        shape.select_len=pos2-pos1;
       }
     else
       {
        shape.select_off=pos2;
        shape.select_len=pos1-pos2;
       }
    }
   
   void posCursor(Point point)
    {
     ulen new_pos=shape.getPosition(point);
     
     if( shape.mouse_pos )
       {
        if( shape.select_len )
          {
           if( shape.pos==shape.select_off )
             {
              select(shape.select_off+shape.select_len,new_pos);
             }
           else if( shape.pos==shape.select_off+shape.select_len )
             {
              select(shape.select_off,new_pos);
             }
           else
             {
              shape.select_off=0;
              shape.select_len=0;
             }
          }
        else
          {
           select(shape.pos,new_pos);
          }
       
        shape.pos=new_pos;
       }
     else
       {
        shape.mouse_pos=true;
        
        shape.pos=new_pos;
        shape.select_off=0;
        shape.select_len=0;
       }
     
     redraw();
    }
   
   void posCursorEnd()
    {
     shape.mouse_pos=false;
    }
   
  public:
  
   template <class ... TT>
   LineEditWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape(Range(text_buf), std::forward<TT>(tt)... ),
      input(this)
    {
     defer_tick=input.create(&LineEditWindowOf<Shape,TextBufLen>::tick);
    }
   
   virtual ~LineEditWindowOf()
    {
    }

   // methods
   
   Point getMinSize() const { return shape.getMinSize(); }
   
   bool isGoodSize(Point size) const { return shape.isGoodSize(size); }
   
   bool isEnabled() const { return shape.enable; }
   
   void enable(bool enable=true)
    {
     if( enable )
       {
        if( !shape.enable )
          {
           shape.enable=true;
           
           if( shape.focus )
             {
              shape.cursor=true;
             
              defer_tick.start();
             }
           
           redraw();
          }
       }
     else
       {
        if( shape.enable )
          {
           shape.enable=false;
           shape.cursor=false;
          
           defer_tick.stop();
           
           redraw();
          }
       }
    }
   
   void disable() { enable(false); }
   
   StrLen getText() const { return Range(text_buf,shape.len); }
   
   PtrLen<char> getBuf() { return Range(text_buf); }
   
   void setTextLen(ulen len)
    {
     shape.cursor=false;
     shape.drag=false;
     
     shape.len=Min(len,TextBufLen);
     shape.xoff=0;
     shape.pos=0;
     shape.select_off=0;
     shape.select_len=0;
     
     shape.setMax();
     
     redraw();
    }
   
   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     PrintBuf out(getBuf());
     
     Printf(out,format,tt...);
     
     out.guardOverflow();
     
     setTextLen( out.close().len );
    }
   
   // drawing
   
   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
     
     shape.setMax();
    }
   
   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }

   // base
   
   virtual void open()
    {
     shape.focus=false;
     shape.cursor=false;
     shape.drag=false;
     shape.mouse_pos=false;
     
     shape.xoff=0;
     shape.pos=0;
     shape.select_off=0;
     shape.select_len=0;
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     shape.focus=true;
     
     if( shape.enable )
       {
        shape.cursor=true;
       
        defer_tick.start();
       }
     
     redraw();
    }
   
   virtual void looseFocus()
    {
     shape.focus=false;
     shape.cursor=false;
     
     defer_tick.stop();
     
     redraw();
    }
   
   // mouse
 
   virtual void looseCapture()
    {
     shape.drag=false;
    }
 
   virtual MouseShape getMouseShape(Point,KeyMod kmod)
    {
     if( shape.xoffMax>0 && kmod&KeyMod_Ctrl ) return Mouse_SizeLeftRight;
     
     return shape.enable?Mouse_IBeem:Mouse_Arrow;
    }
   
   // user input
   
   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }
   
   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     switch( vkey )
       {
        case VKey_Left :
         {
          if( kmod&KeyMod_Ctrl )
            {
             Coord delta_x=Coord(repeat)*shape.dxoff;
            
             setXOff( IntSub(shape.xoff,delta_x) );
            }
          else if( shape.enable )
            {
             if( shape.pos )
               {
                if( kmod&KeyMod_Shift )   
                  {
                   if( shape.select_len )
                     {
                      if( shape.pos==shape.select_off )
                        {
                         shape.select_off--;
                         shape.select_len++;
                        }
                      else if( shape.pos==shape.select_off+shape.select_len )
                        {
                         shape.select_len--;
                        }
                      else
                        {
                         shape.select_off=0;
                         shape.select_len=0;
                        }
                     }
                   else
                     {
                      shape.select_off=shape.pos-1;
                      shape.select_len=1;
                     }
                  }
                else 
                  {
                   shape.select_off=0;
                   shape.select_len=0;
                  }
                
                shape.cursor=true;
                shape.pos--;
                
                shape.showCursor();
                
                redraw();
               }
            }
         }
        break;
        
        case VKey_Right :
         {
          if( kmod&KeyMod_Ctrl )
            {
             Coord delta_x=Coord(repeat)*shape.dxoff;
            
             setXOff( IntAdd(shape.xoff,delta_x) );
            }
          else if( shape.enable )
            {
             if( shape.pos<shape.len )
               {
                if( kmod&KeyMod_Shift )
                  {
                   if( shape.select_len )
                     {
                      if( shape.pos==shape.select_off )
                        {
                         shape.select_off++;
                         shape.select_len--;
                        }
                      else if( shape.pos==shape.select_off+shape.select_len )
                        {
                         shape.select_len++;
                        }
                      else
                        {
                         shape.select_off=0;
                         shape.select_len=0;
                        }
                     }
                   else
                     {
                      shape.select_off=shape.pos;
                      shape.select_len=1;
                     }
                  }
                else
                  {
                   shape.select_off=0;
                   shape.select_len=0;
                  }
                
                shape.cursor=true;
                shape.pos++;
                
                shape.showCursor();
                
                redraw();
               }
            }
         }
        break;
        
        case VKey_Home :
         {
          if( shape.enable )
            {
             if( shape.pos )
               {
                if( kmod&KeyMod_Shift )
                  {
                   if( shape.select_len )
                     {
                      if( shape.pos==shape.select_off )
                        {
                         shape.select_off-=shape.pos;
                         shape.select_len+=shape.pos;
                        }
                      else if( shape.pos==shape.select_off+shape.select_len )
                        {
                         shape.select_len=shape.select_off;
                         shape.select_off=0;
                        }
                      else
                        {
                         shape.select_off=0;
                         shape.select_len=0;
                        }
                     }
                   else
                     {
                      shape.select_off=0;
                      shape.select_len=shape.pos;
                     }
                  }
                else
                  {
                   shape.select_off=0;
                   shape.select_len=0;
                  }
                
                shape.cursor=true;
                shape.pos=0;
                shape.xoff=0;
                
                redraw();
               }
            }
         }
        break;
        
        case VKey_End :
         {
          if( shape.enable )
            {
             if( shape.pos<shape.len )
               {
                if( kmod&KeyMod_Shift )
                  {
                   if( shape.select_len )
                     {
                      if( shape.pos==shape.select_off )
                        {
                         shape.select_off=shape.select_off+shape.select_len;
                         shape.select_len=shape.len-shape.select_off;
                        }
                      else if( shape.pos==shape.select_off+shape.select_len )
                        {
                         shape.select_len+=shape.len-shape.pos;
                        }
                      else
                        {
                         shape.select_off=0;
                         shape.select_len=0;
                        }
                     }
                   else
                     {
                      shape.select_off=shape.pos;
                      shape.select_len=shape.len-shape.pos;
                     }
                  }
                else
                  {
                   shape.select_off=0;
                   shape.select_len=0;
                  }
               
                shape.cursor=true;
                shape.pos=shape.len;
                shape.xoff=shape.xoffMax;
                
                redraw();
               }
            }
         }
        break;
        
        case VKey_c :
         {
          if( shape.enable && kmod&KeyMod_Ctrl )
            {
             if( shape.select_len ) copy();
            }
         }
        break; 
        
        case VKey_v :
         {
          if( shape.enable && kmod&KeyMod_Ctrl )
            {
             past();
            }
         }
        break; 
        
        case VKey_Insert :
         {
          if( shape.enable )
            {
             if( kmod&KeyMod_Ctrl )
               {
                if( shape.select_len ) copy();
               }
             else if( kmod&KeyMod_Shift )
               {
                past(); 
               }
            }
         }
        break; 
        
        case VKey_Delete :
         {
          if( shape.enable )
            {
             if( shape.select_len )
               {
                if( kmod&KeyMod_Shift ) 
                  {
                   cut();
                  }
                else
                  {
                   delSelection();
                  }
               }
             else
               {
                if( !(kmod&KeyMod_Shift) )  
                  {
                   if( shape.pos<shape.len ) del();
                  }
               }            
            }
         }
        break;
        
        case VKey_BackSpace :
         {
          if( shape.enable )
            {
             if( shape.select_len )
               {
                delSelection();
               }
             else
               {
                if( shape.pos )
                  {
                   shape.cursor=true;
                   shape.pos--;
                   
                   del();
                  }
               }
            }
         }
        break;
        
        case VKey_Enter :
         {
          entered.assert();
         }
        break; 
       }
    }
   
   void react_Char(char ch)
    {
     if( shape.enable && CharIsPrintable(ch) )
       {
        if( shape.select_len ) delSelection_();
        
        if( shape.len<TextBufLen )
          {
           shape.len++;
           
           auto r=RangeReverse(text_buf+shape.pos,shape.len-shape.pos);
           
           for(; r.len>1 ;++r) r[0]=r[1];
           
           r[0]=ch;
           
           shape.pos++;
           
           shape.setMax();
           
           shape.showCursor();
           
           changed.assert();
           
           redraw();
          }
       }
    }
   
   void react_LeftClick(Point point,MouseKey mkey)
    {
     if( mkey&MouseKey_Ctrl )
       {
        if( !shape.drag )
          {
           shape.drag=true;
           
           shape.drag_base=point;
           shape.xoff_base=shape.xoff;
           
           captureMouse();
          }
       }
     else
       {
        posCursor(point);
       }
    }
   
   void react_LeftUp(Point point,MouseKey)
    {
     if( shape.drag )
       {
        shape.drag=false;
       
        releaseMouse();
        
        drag(point);
       }
     else
       {
        posCursor(point);
        
        posCursorEnd();
       }
    }
   
   void react_LeftDClick(Point point,MouseKey mkey)
    {
     react_LeftClick(point,mkey);
    }
   
   void react_Move(Point point,MouseKey mkey)
    {
     if( shape.drag ) 
       {
        if( mkey&MouseKey_Left )
          {
           drag(point);
          } 
        else
          {
           shape.drag=false;
          
           releaseMouse();
          }
       }
     else if( mkey&MouseKey_Left )
       {
        posCursor(point);
       }
    }
   
   void react_Leave()
    {
     posCursorEnd();
    }
 
   // signals
   
   Signal<> entered;
   Signal<> changed;
 };

/* type LineEditWindow */

using LineEditWindow = LineEditWindowOf<LineEditShape> ;

} // namespace Video
} // namespace CCore
 
#endif
 

