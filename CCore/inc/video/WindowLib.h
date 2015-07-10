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
 
   virtual MouseShape getMouseShape(Point)
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
   Signal<bool> tabbed;
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
 
   virtual MouseShape getMouseShape(Point)
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
   
   Signal<bool> changed;
   Signal<bool> tabbed;
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
   
   Signal<int,int> changed;
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
 
   virtual MouseShape getMouseShape(Point)
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
   
   Signal<bool> tabbed;
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
   
   ColorName getFace() const { return shape.face; }
   
   void setFace(ColorName face)
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
   
   class Input : public DeferInput<ScrollWindowOf<Shape> >
    {
     public:
    
      explicit Input(ScrollWindowOf<Shape> *window) : DeferInput<ScrollWindowOf<Shape> >(window) {}
      
      ~Input() {}
    };
   
   Input input;
   
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
 
   virtual MouseShape getMouseShape(Point)
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
      
        case VKey_PageDown :
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
        
        case VKey_PageUp :
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
        
        case VKey_PageDown :
         {
          if( shape.down && !shape.mouse && shape.press_type==ScrollType_DownPage )
            {
             shape.down=ScrollType_None;
             
             pressOff();
             
             redraw();
            }
         }
        break;
        
        case VKey_PageUp :
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
   
   Signal<ulen> changed;
   Signal<bool> tabbed;
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
  
   class Input : public DeferInput<ProgressWindowOf<Shape> >
    {
     public:
    
      explicit Input(ProgressWindowOf<Shape> *window) : DeferInput<ProgressWindowOf<Shape> >(window) {}
      
      ~Input() {}
    };
   
   Input input;
   
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

} // namespace Video
} // namespace CCore
 
#endif
 

