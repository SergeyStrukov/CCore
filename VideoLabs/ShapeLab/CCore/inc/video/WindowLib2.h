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

#include <CCore/inc/CharProp.h>
#include <CCore/inc/algon/EuclidRotate.h>
 
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
   
   void del()
    {
     for(auto r=Range(text_buf+shape.pos,shape.len-shape.pos); r.len>1 ;++r) r[0]=r[1];
     
     shape.len--;
     
     shape.setMax();
     
     Replace_min(shape.xoff,shape.xoffMax);
     
     shape.showCursor();
     
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
     
     redraw();
    }
   
   void posCursor(Point point)
    {
     ulen new_pos=shape.getPosition(point);
     
     if( shape.mouse_pos )
       {
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
        if( shape.select_len )
          {
           // TODO selection
          }
        else
          {
           if( shape.len<TextBufLen )
             {
              shape.len++;
              
              auto r=RangeReverse(text_buf+shape.pos,shape.len-shape.pos);
              
              for(; r.len>1 ;++r) r[0]=r[1];
              
              r[0]=ch;
              
              shape.pos++;
              
              shape.setMax();
              
              shape.showCursor();
              
              redraw();
             }
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
 };

/* type LineEditWindow */

using LineEditWindow = LineEditWindowOf<LineEditShape> ;

} // namespace Video
} // namespace CCore
 
#endif
 

