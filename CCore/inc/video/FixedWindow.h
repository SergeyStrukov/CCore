/* FixedWindow.h */ 
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

#ifndef CCore_inc_video_FixedWindow_h
#define CCore_inc_video_FixedWindow_h
 
#include <CCore/inc/video/ClientWindow.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/FrameGuards.h>
#include <CCore/inc/video/RefVal.h>
#include <CCore/inc/video/Shade.h>

#include <CCore/inc/String.h>
#include <CCore/inc/DeferCall.h>
#include <CCore/inc/Signal.h>

namespace CCore {
namespace Video {

/* consts */

enum HitFrameType
 {
  HitFrame_None = 0,
  
  HitFrame_Move,
  
  HitFrame_Close
 };

/* classes */

class FixedShape;

template <class Shape> class FixedWindowOf;

/* class FixedShape */

class FixedShape
 {
  public:
  
   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;
    
     RefVal<Coord> frame_dxy = 12 ;
     RefVal<Coord> title_dy  = 32 ;
     
     RefVal<Coord> btn_dx    = 26 ;
     RefVal<Coord> btn_dy    = 24 ;
    
     RefVal<VColor> top            =      Gray ;
     RefVal<VColor> bottom         =      Snow ;
     
     RefVal<VColor> frame          =      Snow ;
     RefVal<VColor> frameHilight   = RGBColor(0xC0,0xFF,0xC0) ;
     RefVal<VColor> frameDrag      = RGBColor(0xFF,0xC0,0xC0) ;
     
     RefVal<VColor> active         = RGBColor(0x80,0x80,0xFF) ;
     RefVal<VColor> inactive       =    Silver ;
     RefVal<VColor> title          =     Black ;
    
     RefVal<VColor> btnFace        = SteelBlue ;
     RefVal<VColor> btnFaceHilight =     Green ;
     RefVal<VColor> btnPictClose   =       Red ;
     
     RefVal<VColor> shade_color    =    Violet ;
     RefVal<Clr>    shade_alpha    =        64 ;
     
     RefVal<Font> title_font;
    
     Config() {}
    
     mutable Signal<> update;
    };
   
   const Config &cfg;

  private: 
  
   // layout
   
   Point size;
   
   Pane client;
   Pane titleBar;
   Pane btnClose;
   
  private: 
   
   class DrawArt;
   
   void draw_Frame(DrawArt &art) const;
   
   void draw_Title(DrawArt &art) const;
   
   void draw_Close(DrawArt &art) const;
   
  public: 
  
   // state
   
   bool has_focus = false ;
   
   HitFrameType hilight  = HitFrame_None ;
   HitFrameType hit_type = HitFrame_None ;
   
   String title;
  
   // methods
   
   explicit FixedShape(const Config &cfg_) : cfg(cfg_) {}
   
   Point getDeltaSize() const;
   
   Coord getMinDx(StrLen title) const;
   
   Pane getClient() const { return client; }
   
   void reset(const String &title);
   
   void layout(Point size);
   
   void draw(const DrawBuf &buf) const;
   
   void draw(const DrawBuf &buf,HitFrameType hit_type) const;
   
   Pane getPane(HitFrameType hit_type) const;
   
   HitFrameType hitTest(Point point) const;
 };

/* class FixedWindowOf<Shape> */

template <class Shape> 
class FixedWindowOf : public FrameWindow , public SubWindowHost
 {
  public:

   using ShapeType = Shape ;
   
   using ConfigType = typename Shape::Config ;
  
  private:
   
   Shape shape;
   
   ClientWindow *client = 0 ;
   
   Point size;
   
   Point drag_from;
   bool client_enter = false ;
   bool client_capture = false ;
   bool delay_draw = false ;
   bool enable_react = true ;
   
  private:
   
   void guardClient()
    {
     if( !client ) GuardNoClient();
    }
   
   void guardDead()
    {
     if( isAlive() ) GuardNotDead();
    }
   
   void reset()
    {
     size=Null;
     client_enter=false;
     client_capture=false;
     delay_draw=false;
     enable_react=true;
    }
   
   void replace(Pane place,Point delta)
    {
     place+=delta;
     
     Point new_size(place.dx,place.dy);
     
     if( new_size>Null && new_size<=host->getMaxSize() ) 
       {
        Pane screen=Pane(Null,desktop->getScreenSize());
       
        if( +Inf(place,screen) ) 
          {
           host->move(place);
           
           host->invalidate(1);
          }
       }
    }
   
   void replace(Point delta)
    {
     Pane place=host->getPlace();

     replace(place,delta);
    }

   void startDrag(Point point)
    {
     shape.hit_type=HitFrame_Move;
     
     if( !client_capture ) host->captureMouse();
    
     Pane place=host->getPlace();
     
     drag_from=point+place.getBase();
     
     redrawAll();
    }
   
   void dragTo(Point point)
    {
     Pane place=host->getPlace();
     Point delta=Diff(drag_from,point+place.getBase());
     
     replace(place,delta);
    }
   
   void endDrag()
    {
     shape.hit_type=HitFrame_None;
     
     redrawAll();
    }
   
   void endDrag(Point point)
    {
     dragTo(point);
     
     shape.hit_type=HitFrame_None;
     
     if( !client_capture ) host->releaseMouse();
     
     redrawAll();
    }
   
   bool forwardKey(VKey vkey,KeyMod kmod,unsigned repeat=1)
    {
     if( kmod&KeyMod_Alt )
       {
        switch( vkey )
          {
           case VKey_Left  : replace(Point(-(Coord)repeat,0)); return true;
           
           case VKey_Right : replace(Point((Coord)repeat,0)); return true;
           
           case VKey_Up    : replace(Point(0,-(Coord)repeat)); return true;
           
           case VKey_Down  : replace(Point(0,(Coord)repeat)); return true;
           
           case VKey_F4    : destroy(); return true;
           
           default: return false;
          }
       }
     else
       {
        return false;
       }
    }
   
   bool forwardKeyUp(VKey vkey,KeyMod kmod,unsigned =1)
    {
     if( kmod&KeyMod_Alt )
       {
        switch( vkey )
          {
           case VKey_Left  : 
           case VKey_Right : 
           case VKey_Up    : 
           case VKey_Down  : 
           case VKey_F4    : return true;
           
           default: return false;
          }
       }
     else
       {
        return false;
       }
    }
   
   ClientWindow & getClient()
    {
     guardClient();
     
     return *client;
    }
   
   SubWindow & getClientSub()
    { 
     return getClient().getSubWindow(); 
    }
   
   void shade(const FrameBuf<DesktopColor> &buf)
    {
     if( !enable_react ) Shade(buf,+shape.cfg.shade_color,+shape.cfg.shade_alpha);
    }
   
   void redrawFrame()
    {
     if( host->isDead() ) return;
     
     if( host->getToken() ) 
       {
        delay_draw=true;
        
        return;
       }
     
     FrameBuf<DesktopColor> buf(host->getDrawPlane());
     
     if( size<=buf.getSize() ) 
       {
        shape.draw(buf);
       
        shade(buf);
        
        host->invalidate(1);
       }
     else
       {
        buf.erase(Black);
        
        host->invalidate(1);
       }
    }
   
   void redrawFrame(HitFrameType hit_type)
    {
     Pane pane=shape.getPane(hit_type);
     
     if( !pane ) return;
     
     if( host->isDead() ) return;
     
     if( host->getToken() ) 
       {
        delay_draw=true;
        
        return;
       }
     
     FrameBuf<DesktopColor> buf(host->getDrawPlane());
     
     if( size<=buf.getSize() ) 
       {
        shape.draw(buf,hit_type);
       
        shade(buf);
        
        host->invalidate(pane,1);
       }
     else
       {
        buf.erase(Black);
        
        host->invalidate(1);
       }
    }
   
  public:
  
   FixedWindowOf(Desktop *desktop,const ConfigType &cfg)
    : FrameWindow(desktop),
      shape(cfg),
      input(this),
      connector_updateConfig(this,&FixedWindowOf<Shape>::updateConfig,cfg.update)
    {
    }
   
   virtual ~FixedWindowOf()
    {
    }
   
   // methods
   
   Point getDeltaSize() const { return shape.getDeltaSize(); }
   
   Point getMinSize(StrLen title,Point size) const
    {
     size+=shape.getDeltaSize();
     
     return Point(Max(size.x,shape.getMinDx(title)),size.y);
    }
   
   void bindClient(ClientWindow &client_)
    { 
     guardDead(); 
     
     client=&client_;
    }
   
   void createMain(Pane pane,const String &title)
    {
     guardClient();
     
     shape.reset(title);
     
     host->createMain(pane,pane.getSize());
     
     host->display(CmdDisplay_Normal);
     host->update();
    }
   
   void create(Pane pane,const String &title)
    {
     guardClient();
     
     shape.reset(title);
     
     host->create(pane,pane.getSize());
     host->show();
    }
   
   void create(WindowHost *parent,Pane pane,const String &title)
    {
     guardClient();
     
     shape.reset(title);
     
     host->create(parent,pane,pane.getSize());
     host->show();
    }
   
   void destroy()
    { 
     if( client && client->askDestroy() ) 
       {
        host->destroy();
        
        destroyed.assert();
       }
    }
   
   void redrawAll(bool do_layout=false)
    {
     if( do_layout )
       {
        shape.layout(size);
       
        if( client ) client->getSubWindow().setPlace(shape.getClient());
       }
     
     if( host->isDead() ) return;
     
     if( host->getToken() ) 
       {
        delay_draw=true;
        
        return;
       }
     
     FrameBuf<DesktopColor> buf(host->getDrawPlane());
     
     if( size<=buf.getSize() ) 
       {
        shape.draw(buf);
       
        getClientSub().forward_draw(buf,shape.hit_type==HitFrame_Move);
       
        shade(buf);
        
        host->invalidate(1);
       }
     else
       {
        buf.erase(Black);
        
        host->invalidate(1);
       }
    }
   
   void redrawClient()
    {
     if( host->isDead() ) return;
     
     if( host->getToken() ) 
       {
        delay_draw=true;
        
        return;
       }
     
     FrameBuf<DesktopColor> buf(host->getDrawPlane());
     
     if( size<=buf.getSize() ) 
       {
        getClientSub().forward_draw(buf,shape.hit_type==HitFrame_Move);
       
        shade(buf);
        
        host->invalidate(shape.getClient(),1);
       }
     else
       {
        buf.erase(Black);
        
        host->invalidate(1);
       }
    }
   
   void redrawClient(Pane pane)
    {
     if( host->isDead() ) return;
     
     if( host->getToken() ) 
       {
        delay_draw=true;
        
        return;
       }
     
     FrameBuf<DesktopColor> buf(host->getDrawPlane());
     
     if( size<=buf.getSize() ) 
       {
        getClientSub().forward_draw(buf,pane,shape.hit_type==HitFrame_Move);
       
        shade(buf);
        
        host->invalidate(pane,1);
       }
     else
       {
        buf.erase(Black);
        
        host->invalidate(1);
       }
    }
   
   unsigned getToken() { return host->getToken(); }
   
   void setTitle(const String &title)
    {
     shape.title=title;
     
     redrawFrame();
    }
   
   // SubWindowHost
   
   virtual FrameWindow * getFrame()
    {
     return this;
    }
  
   virtual Point getScreenOrigin()
    {
     Pane pane=host->getPlace();
     
     return pane.getBase();
    }
  
   virtual void redraw(Pane pane)
    {
     input.redrawClient(pane);
    }
  
   virtual void setFocus(SubWindow *)
    {
     if( shape.has_focus )
       {
        getClientSub().gainFocus();
       }
    }
  
   virtual void captureMouse(SubWindow *)
    {
     if( !client_capture )
       {
        client_capture=true;
       
        if( shape.hit_type!=HitFrame_Move ) host->captureMouse();
       }
    }
  
   virtual void releaseMouse(SubWindow *)
    {
     if( client_capture )
       {
        client_capture=false;
       
        if( shape.hit_type!=HitFrame_Move ) host->releaseMouse();
       }
    }
   
   // base
   
   virtual void alive()
    {
     reset();
     
     host->trackMouseHover();
     host->trackMouseLeave();
     
     if( client ) client->alive();
     
     getClientSub().open();
    }
   
   virtual void dead()
    {
     getClientSub().close();
     
     if( client ) client->dead();
    }
   
   virtual void setSize(Point size_,bool buf_dirty)
    {
     if( size!=size_ || buf_dirty )
       {
        size=size_;
       
        redrawAll(true);
       }
    }
   
   virtual void paintDone(unsigned)
    {
     if( delay_draw )
       {
        delay_draw=false;
        
        redrawAll();
       }
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     shape.has_focus=true;
     
     redrawFrame();
     
     getClientSub().gainFocus();
    }
   
   virtual void looseFocus()
    {
     shape.has_focus=false;
     
     redrawFrame();
     
     getClientSub().looseFocus();
    }
   
   // mouse
   
   virtual void looseCapture()
    {
     if( shape.hit_type==HitFrame_Move ) endDrag();
     
     if( client_capture )
       {
        client_capture=false;
        
        getClientSub().looseCapture();
       }
    }
   
   virtual void setMouseShape(Point point)
    {
     switch( shape.hitTest(point) )
       {
        case HitFrame_Move : host->setMouseShape(Mouse_SizeAll); break;
         
        case HitFrame_Close : host->setMouseShape(Mouse_Stop); break;
        
        default: host->setMouseShape(getClientSub().forward_getMouseShape(point));
       }
    }

   // user input
   
   virtual void disableReact() { enable_react=false; redrawAll(); }
   
   virtual void enableReact() { enable_react=true; redrawAll(); }
   
   virtual void react(UserAction action)
    {
     if( enable_react ) action.dispatch(*this, [this] (UserAction action) { react_other(action); } );
    }
   
   void react_other(UserAction action)
    {
     if( action.fromKeyboard() )
       {
        getClientSub().react(action);
       }
     else
       {
        if( shape.hit_type==HitFrame_Move ) return;
        
        Point point=action.getPoint();
       
        if( client_capture || shape.getClient().contains(point) )
          {
           getClientSub().forward_react(action);
          }
       }
    }
   
   void react_Key(VKey vkey,KeyMod kmod)
    {
     if( !forwardKey(vkey,kmod) ) getClientSub().put_Key(vkey,kmod);
    }
   
   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     if( !forwardKey(vkey,kmod,repeat) ) getClientSub().put_Key(vkey,kmod,repeat);
    }
   
   void react_KeyUp(VKey vkey,KeyMod kmod)
    {
     if( !forwardKeyUp(vkey,kmod) ) getClientSub().put_KeyUp(vkey,kmod);
    }
   
   void react_KeyUp(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     if( !forwardKeyUp(vkey,kmod,repeat) ) getClientSub().put_KeyUp(vkey,kmod,repeat);
    }
   
   void react_LeftClick(Point point,MouseKey mkey)
    {
     switch( auto hit_type=shape.hitTest(point) )
       {
        case HitFrame_None :
         {
          if( client_capture || shape.getClient().contains(point) )
            {
             getClientSub().forward().put_LeftClick(point,mkey);
            }
         }
        break;
      
        case HitFrame_Close : 
         {
          if( !shape.hit_type ) 
            {
             shape.hit_type=hit_type; 
             
             redrawFrame(hit_type);
            }
         } 
        break;
        
        case HitFrame_Move : 
         {
          if( !shape.hit_type ) startDrag(point);
         }
       }
    }
   
   void react_LeftUp(Point point,MouseKey mkey)
    {
     switch( shape.hit_type )
       {
        case HitFrame_Move : endDrag(point); break;
        
        case HitFrame_Close :
         {
          auto type=Replace(shape.hit_type,HitFrame_None);
          
          redrawFrame(type);
         
          if( shape.hitTest(point)==type )
            {
             switch( type )
               {
                case HitFrame_Close : destroy(); return;
               }
            }
         }
        break; 
        
        default:
         {
          if( client_capture || shape.getClient().contains(point) )
            {
             getClientSub().forward().put_LeftUp(point,mkey);
            }
         }
       }
    }
   
   void react_Move(Point point,MouseKey mkey)
    {
     switch( shape.hit_type )
       {
        case HitFrame_Move :
         {
          if( mkey&MouseKey_Left )
            dragTo(point);
          else
            endDrag(point);
         }
        break;
        
        case HitFrame_Close :
         {
          if( mkey&MouseKey_Left )
            {
             if( shape.hitTest(point)!=shape.hit_type )
               {
                redrawFrame(Replace(shape.hit_type,HitFrame_None));
               }
            }
          else
            {
             redrawFrame(Replace(shape.hit_type,HitFrame_None));
            }
         }
        break;
        
        default:
         {
          auto hit_type=shape.hitTest(point);
          
          if( hit_type!=shape.hilight )
            {
             Replace(shape.hilight,hit_type);
             
             redrawFrame();
            }
          
          if( shape.getClient().contains(point) )
            {
             client_enter=true;
             
             getClientSub().forward().put_Move(point,mkey);
            }
          else
            {
             if( client_capture ) getClientSub().forward().put_Move(point,mkey);
              
             if( client_enter )
               {
                client_enter=false;
                
                getClientSub().put_Leave();
               }
            }
         }
       }
    }
   
   void react_Leave()
    {
     if( shape.hilight  )
       {
        Replace(shape.hilight,HitFrame_None);
        
        redrawFrame();
       }
     
     if( shape.hit_type )
       {
        if( shape.hit_type!=HitFrame_Move )
          {
           redrawFrame(Replace(shape.hit_type,HitFrame_None));
          }
       }
     
     if( client_enter )
       {
        client_enter=false;
        
        getClientSub().put_Leave();
       }
    }

   // signals
   
   Signal<> destroyed;
   
   // DeferInput
   
   class Input : DeferInput<FixedWindowOf<Shape> >
    {
      friend class FixedWindowOf<Shape>;
      
      explicit Input(FixedWindowOf<Shape> *window) : DeferInput<FixedWindowOf<Shape> >(window) {}
      
      ~Input() {}
      
      using DeferInput<FixedWindowOf<Shape> >::try_post;
      
     public:

      void redrawAll(bool do_layout=false) { try_post(&FixedWindowOf<Shape>::redrawAll,do_layout); }
      
      void redrawClient() { try_post(&FixedWindowOf<Shape>::redrawClient); }
      
      void redrawClient(Pane pane) { try_post(&FixedWindowOf<Shape>::redrawClient,pane); }
    };
   
   Input input;
   
  private:
   
   void updateConfig()
    { 
     input.redrawAll(true); 
    }
   
   SignalConnector<FixedWindowOf<Shape> > connector_updateConfig;
 };

/* type FixedWindow */

using FixedWindow = FixedWindowOf<FixedShape> ; 

} // namespace Video
} // namespace CCore
 
#endif
 

