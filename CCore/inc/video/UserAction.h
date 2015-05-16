/* UserAction.h */ 
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

#ifndef CCore_inc_video_UserAction_h
#define CCore_inc_video_UserAction_h

#include <CCore/inc/video/Point.h>
#include <CCore/inc/video/Keyboard.h>
#include <CCore/inc/video/Mouse.h>
 
namespace CCore {
namespace Video {

/* classes */

class UserAction;

/* class UserAction */

class UserAction
 {
   // type
   
   enum Type
    {
     Key,
     RepeatKey,
     KeyUp,
     RepeatKeyUp,
     
     Char,
     RepeatChar,
     AltChar,
     RepeatAltChar,
     
     LeftClick,
     LeftUp,
     LeftDClick,
     
     RightClick,
     RightUp,
     RightDClick,
     
     Move,
     Hover,
     Leave,
     Wheel
    };
   
   Type type;
  
   // body
   
   struct Body_Key
    {
     VKey vkey;
     KeyMod kmod;
     
     Body_Key(VKey vkey_,KeyMod kmod_) : vkey(vkey_),kmod(kmod_) {}
    };
   
   struct Body_RepeatKey
    {
     VKey vkey;
     KeyMod kmod;
     unsigned repeat;
     
     Body_RepeatKey(VKey vkey_,KeyMod kmod_,unsigned repeat_) : vkey(vkey_),kmod(kmod_),repeat(repeat_) {}
    };
   
   struct Body_Char
    {
     char ch;
     
     explicit Body_Char(char ch_) : ch(ch_) {}
    };
   
   struct Body_RepeatChar
    {
     char ch;
     unsigned repeat;
     
     Body_RepeatChar(char ch_,unsigned repeat_) : ch(ch_),repeat(repeat_) {}
    };
   
   struct Body_Mouse
    {
     Point point;
     MouseKey mkey;
     
     Body_Mouse(Point point_,MouseKey mkey_) : point(point_),mkey(mkey_) {}
    };
   
   struct Body_Wheel
    {
     Point point;
     MouseKey mkey;
     Coord delta;
     
     Body_Wheel(Point point_,MouseKey mkey_,Coord delta_) : point(point_),mkey(mkey_),delta(delta_) {}
    };
   
   union Body
    {
     Body_Key        of_Key;
     Body_RepeatKey  of_RepeatKey;
     Body_Char       of_Char;
     Body_RepeatChar of_RepeatChar;
     Body_Mouse      of_Mouse;
     Body_Wheel      of_Wheel;
     
     Body() {}
    };
   
   Body body;

   // constructors
   
   explicit UserAction(Type type_)
    {
     type=type_;
    }
   
   UserAction(Type type_,Body_Key body_)
    {
     type=type_;
     body.of_Key=body_;
    }
   
   UserAction(Type type_,Body_RepeatKey body_)
    {
     type=type_;
     body.of_RepeatKey=body_;
    }
   
   UserAction(Type type_,Body_Char body_)
    {
     type=type_;
     body.of_Char=body_;
    }
   
   UserAction(Type type_,Body_RepeatChar body_)
    {
     type=type_;
     body.of_RepeatChar=body_;
    }
   
   UserAction(Type type_,Body_Mouse body_)
    {
     type=type_;
     body.of_Mouse=body_;
    }
   
   UserAction(Type type_,Body_Wheel body_)
    {
     type=type_;
     body.of_Wheel=body_;
    }

  public: 
   
   // create functions
   
   static UserAction Create_Key(VKey vkey,KeyMod kmod) { return UserAction(Key,Body_Key(vkey,kmod)); } 
  
   static UserAction Create_RepeatKey(VKey vkey,KeyMod kmod,unsigned repeat) { return UserAction(RepeatKey,Body_RepeatKey(vkey,kmod,repeat)); }
   
   static UserAction Create_KeyUp(VKey vkey,KeyMod kmod) { return UserAction(KeyUp,Body_Key(vkey,kmod)); }
   
   static UserAction Create_RepeatKeyUp(VKey vkey,KeyMod kmod,unsigned repeat) { return UserAction(RepeatKeyUp,Body_RepeatKey(vkey,kmod,repeat)); }
   
   
   static UserAction Create_Char(char ch) { return UserAction(Char,Body_Char(ch)); }
   
   static UserAction Create_RepeatChar(char ch,unsigned repeat) { return UserAction(RepeatChar,Body_RepeatChar(ch,repeat)); }
   
   static UserAction Create_AltChar(char ch) { return UserAction(AltChar,Body_Char(ch)); }
   
   static UserAction Create_RepeatAltChar(char ch,unsigned repeat) { return UserAction(RepeatAltChar,Body_RepeatChar(ch,repeat)); }
   
   
   static UserAction Create_LeftClick(Point point,MouseKey mkey) { return UserAction(LeftClick,Body_Mouse(point,mkey)); }
   
   static UserAction Create_LeftUp(Point point,MouseKey mkey) { return UserAction(LeftUp,Body_Mouse(point,mkey)); }
   
   static UserAction Create_LeftDClick(Point point,MouseKey mkey) { return UserAction(LeftDClick,Body_Mouse(point,mkey)); }
   
   static UserAction Create_RightClick(Point point,MouseKey mkey) { return UserAction(RightClick,Body_Mouse(point,mkey)); }
   
   static UserAction Create_RightUp(Point point,MouseKey mkey) { return UserAction(RightUp,Body_Mouse(point,mkey)); }
   
   static UserAction Create_RightDClick(Point point,MouseKey mkey) { return UserAction(RightDClick,Body_Mouse(point,mkey)); }
   
   static UserAction Create_Move(Point point,MouseKey mkey) { return UserAction(Move,Body_Mouse(point,mkey)); }
   
   static UserAction Create_Hover(Point point,MouseKey mkey) { return UserAction(Hover,Body_Mouse(point,mkey)); }
   
   static UserAction Create_Leave() { return UserAction(Leave); }
   
   static UserAction Create_Wheel(Point point,MouseKey mkey,Coord delta) { return UserAction(Wheel,Body_Wheel(point,mkey,delta)); }
  
   // methods
   
   void rebase(Point origin)
    {
     if( type>=LeftClick && type<Leave )
       {
        body.of_Mouse.point-=origin;
       }
     else if( type==Wheel )
       {
        body.of_Wheel.point-=origin;
       }
    }
  
  private:
  
   template <class T,class Func>
   void dispatch_Key(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_Key(T &obj,Func,NothingType,int) const -> decltype( obj.key(body.of_Key.vkey,body.of_Key.kmod,1) )
    {
     return obj.key(body.of_Key.vkey,body.of_Key.kmod,1);
    }
   
   template <class T,class Func>
   auto dispatch_Key(T &obj,Func,NothingType,NothingType) const -> decltype( obj.key(body.of_Key.vkey,body.of_Key.kmod) )
    {
     return obj.key(body.of_Key.vkey,body.of_Key.kmod);
    }
   
   template <class T,class Func>
   void dispatch_RepeatKey(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatKey(T &obj,Func,NothingType,int) const -> decltype( obj.key(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod) )
    {
     for(unsigned cnt=body.of_RepeatKey.repeat; cnt ;cnt--) obj.key(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatKey(T &obj,Func,NothingType,NothingType) const -> decltype( obj.key(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod,body.of_RepeatKey.repeat) )
    {
     return obj.key(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod,body.of_RepeatKey.repeat);
    }
  
  public:
  
   // dispatch
   
   template <class T,class Func>
   void dispatch(T &obj,Func func) const
    {
     switch( type )
       {
        case Key : dispatch_Key(obj,func,Nothing,Nothing); break;
        
        case RepeatKey : dispatch_RepeatKey(obj,func,Nothing,Nothing); break;
        
        // TODO
       }
    }
  
   // print object
   
   template <class P>
   void print(P &out) const
    {
     // TODO
    }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

