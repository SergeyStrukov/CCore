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

template <class Shape,ulen TextBufLen=1024> class LineEditWindowOf;

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
   
   void tick()
    {
     if( shape.tick()  )
       {
        shape.cursor=!shape.cursor;
       
        redraw();
       }
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
     shape.len=Min(len,TextBufLen);
     shape.pos=0;
     shape.xoff=0;
     
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
 
   virtual MouseShape getMouseShape(Point)
    {
     if( shape.xoffMax>0 ) return Mouse_SizeLeftRight;
     
     return Mouse_Arrow;
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
          if( kmod&KeyMod_Shift )
            {
             Coord delta_x=Coord(repeat)*shape.dxoff;
            
             setXOff( IntSub(shape.xoff,delta_x) );
            }
          else if( shape.enable )
            {
             if( shape.pos )
               {
                shape.cursor=true;
                shape.pos--;
                
                redraw();
               }
            }
         }
        break;
        
        case VKey_Right :
         {
          if( kmod&KeyMod_Shift )
            {
             Coord delta_x=Coord(repeat)*shape.dxoff;
            
             setXOff( IntAdd(shape.xoff,delta_x) );
            }
          else if( shape.enable )
            {
             if( shape.pos<shape.len )
               {
                shape.cursor=true;
                shape.pos++;
                
                redraw();
               }
            }
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
 };

/* type LineEditWindow */

using LineEditWindow = LineEditWindowOf<LineEditShape> ;

} // namespace Video
} // namespace CCore
 
#endif
 

