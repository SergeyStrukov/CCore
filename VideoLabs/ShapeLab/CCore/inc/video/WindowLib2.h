/* WindowLib2.h */ 
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

#ifndef CCore_inc_video_WindowLib2_h
#define CCore_inc_video_WindowLib2_h

#include <CCore/inc/video/ShapeLib2.h>
#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/Signal.h>
#include <CCore/inc/DeferCall.h>
 
namespace CCore {
namespace Video {

/* classes */

template <class Shape> class InfoWindowOf;

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
   
   void drag(Point point)
    {
     Coord delta_x=IntSub(point.x,shape.drag_base.x);
     
     setXOff( IntSub(shape.xoff_base,delta_x) );
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
     shape.has_focus=false;
     shape.drag=false;
    }
   
   // keyboard
   
   virtual void gainFocus()
    {
     shape.has_focus=true;
     
     redraw();
    }
   
   virtual void looseFocus()
    {
     shape.has_focus=false;
     
     redraw();
    }
   
   // mouse
 
   virtual void looseCapture()
    {
     shape.drag=false;
    }
 
   virtual MouseShape getMouseShape(Point)
    {
     if( shape.xoffMax>0 || shape.yoffMax>0 ) return Mouse_SizeAll;
     
     return Mouse_Arrow;
    }
   
   // user input
   
   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }
   
   void react_Key(VKey vkey,KeyMod,unsigned repeat) // TODO
    {
     switch( vkey )
       {
        case VKey_Left :
         {
          Coord delta_x=Coord(repeat);
          
          setXOff( IntSub(shape.xoff,delta_x) );
         }
        break;
        
        case VKey_Right :
         {
          Coord delta_x=Coord(repeat);
          
          setXOff( IntAdd(shape.xoff,delta_x) );
         }
        break;
        
        case VKey_Up :
         {
         }
        break;
        
        case VKey_Down :
         {
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
        drag(point);
       
        shape.drag=false;
        
        releaseMouse();
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
 };

/* type InfoWindow */

using InfoWindow = InfoWindowOf<InfoShape> ;

} // namespace Video
} // namespace CCore
 
#endif
 

