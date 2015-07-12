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

#include <CCore/inc/CharProp.h>
 
namespace CCore {
namespace Video {

/* classes */

class UserAction;

struct UserInput;

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
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"(#;,#;)",vkey,kmod);
      }
    };
   
   struct Body_RepeatKey
    {
     VKey vkey;
     KeyMod kmod;
     unsigned repeat;
     
     Body_RepeatKey(VKey vkey_,KeyMod kmod_,unsigned repeat_) : vkey(vkey_),kmod(kmod_),repeat(repeat_) {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"(#;,#;,#;)",vkey,kmod,repeat);
      }
    };
   
   struct Body_Char
    {
     char ch;
     
     explicit Body_Char(char ch_) : ch(ch_) {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"(#;)",CharCode(ch));
      }
    };
   
   struct Body_RepeatChar
    {
     char ch;
     unsigned repeat;
     
     Body_RepeatChar(char ch_,unsigned repeat_) : ch(ch_),repeat(repeat_) {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"(#;,#;)",CharCode(ch),repeat);
      }
    };
   
   struct Body_Mouse
    {
     Point point;
     MouseKey mkey;
     
     Body_Mouse(Point point_,MouseKey mkey_) : point(point_),mkey(mkey_) {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"(#;,#;)",point,mkey);
      }
    };
   
   struct Body_Wheel
    {
     Point point;
     MouseKey mkey;
     Coord delta;
     
     Body_Wheel(Point point_,MouseKey mkey_,Coord delta_) : point(point_),mkey(mkey_),delta(delta_) {}
     
     // print object
     
     template <class P>
     void print(P &out) const
      {
       Printf(out,"(#;,#;,#;)",point,mkey,delta);
      }
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
   
   bool fromKeyboard() const { return type<LeftClick; }
   
   Point getPoint() const
    {
     if( type>=LeftClick && type<Leave )
       {
        return body.of_Mouse.point;
       }
     else if( type==Wheel )
       {
        return body.of_Wheel.point;
       }
     else
       {
        return Null;
       }
    }
   
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
   auto dispatch_Key(T &obj,Func,NothingType,int) const -> decltype( obj.react_Key(body.of_Key.vkey,body.of_Key.kmod,1) )
    {
     return obj.react_Key(body.of_Key.vkey,body.of_Key.kmod,1);
    }
   
   template <class T,class Func>
   auto dispatch_Key(T &obj,Func,NothingType,NothingType) const -> decltype( obj.react_Key(body.of_Key.vkey,body.of_Key.kmod) )
    {
     return obj.react_Key(body.of_Key.vkey,body.of_Key.kmod);
    }
   
   template <class T,class Func>
   void dispatch_RepeatKey(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatKey(T &obj,Func,NothingType,int) const -> decltype( obj.react_Key(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod) )
    {
     for(unsigned cnt=body.of_RepeatKey.repeat; cnt ;cnt--) obj.react_Key(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatKey(T &obj,Func,NothingType,NothingType) const -> decltype( obj.react_Key(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod,body.of_RepeatKey.repeat) )
    {
     return obj.react_Key(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod,body.of_RepeatKey.repeat);
    }
  
   
   template <class T,class Func>
   void dispatch_KeyUp(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_KeyUp(T &obj,Func,NothingType,int) const -> decltype( obj.react_KeyUp(body.of_Key.vkey,body.of_Key.kmod,1) )
    {
     return obj.react_KeyUp(body.of_Key.vkey,body.of_Key.kmod,1);
    }
   
   template <class T,class Func>
   auto dispatch_KeyUp(T &obj,Func,NothingType,NothingType) const -> decltype( obj.react_KeyUp(body.of_Key.vkey,body.of_Key.kmod) )
    {
     return obj.react_KeyUp(body.of_Key.vkey,body.of_Key.kmod);
    }
   
   template <class T,class Func>
   void dispatch_RepeatKeyUp(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatKeyUp(T &obj,Func,NothingType,int) const -> decltype( obj.react_KeyUp(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod) )
    {
     for(unsigned cnt=body.of_RepeatKey.repeat; cnt ;cnt--) obj.react_KeyUp(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatKeyUp(T &obj,Func,NothingType,NothingType) const -> decltype( obj.react_KeyUp(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod,body.of_RepeatKey.repeat) )
    {
     return obj.react_KeyUp(body.of_RepeatKey.vkey,body.of_RepeatKey.kmod,body.of_RepeatKey.repeat);
    }
   

   template <class T,class Func>
   void dispatch_Char(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_Char(T &obj,Func,NothingType,int) const -> decltype( obj.react_Char(body.of_Char.ch,1) )
    {
     return obj.react_Char(body.of_Char.ch,1);
    }
   
   template <class T,class Func>
   auto dispatch_Char(T &obj,Func,NothingType,NothingType) const -> decltype( obj.react_Char(body.of_Char.ch) )
    {
     return obj.react_Char(body.of_Char.ch);
    }
   
   template <class T,class Func>
   void dispatch_RepeatChar(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatChar(T &obj,Func,NothingType,int) const -> decltype( obj.react_Char(body.of_RepeatChar.ch) )
    {
     for(unsigned cnt=body.of_RepeatChar.repeat; cnt ;cnt--) obj.react_Char(body.of_RepeatChar.ch);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatChar(T &obj,Func,NothingType,NothingType) const -> decltype( obj.react_Char(body.of_RepeatChar.ch,body.of_RepeatChar.repeat) )
    {
     return obj.react_Char(body.of_RepeatChar.ch,body.of_RepeatChar.repeat);
    }
   

   template <class T,class Func>
   void dispatch_AltChar(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_AltChar(T &obj,Func,NothingType,int) const -> decltype( obj.react_AltChar(body.of_Char.ch,1) )
    {
     return obj.react_AltChar(body.of_Char.ch,1);
    }
   
   template <class T,class Func>
   auto dispatch_AltChar(T &obj,Func,NothingType,NothingType) const -> decltype( obj.react_AltChar(body.of_Char.ch) )
    {
     return obj.react_AltChar(body.of_Char.ch);
    }
   
   template <class T,class Func>
   void dispatch_RepeatAltChar(T &,Func func,int,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatAltChar(T &obj,Func,NothingType,int) const -> decltype( obj.react_AltChar(body.of_RepeatChar.ch) )
    {
     for(unsigned cnt=body.of_RepeatChar.repeat; cnt ;cnt--) obj.react_AltChar(body.of_RepeatChar.ch);
    }
   
   template <class T,class Func>
   auto dispatch_RepeatAltChar(T &obj,Func,NothingType,NothingType) const -> decltype( obj.react_AltChar(body.of_RepeatChar.ch,body.of_RepeatChar.repeat) )
    {
     return obj.react_AltChar(body.of_RepeatChar.ch,body.of_RepeatChar.repeat);
    }
   
   
   template <class T,class Func>
   void dispatch_LeftClick(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_LeftClick(T &obj,Func,NothingType) const -> decltype( obj.react_LeftClick(body.of_Mouse.point,body.of_Mouse.mkey) )
    {
     return obj.react_LeftClick(body.of_Mouse.point,body.of_Mouse.mkey);
    }
   

   template <class T,class Func>
   void dispatch_LeftUp(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_LeftUp(T &obj,Func,NothingType) const -> decltype( obj.react_LeftUp(body.of_Mouse.point,body.of_Mouse.mkey) )
    {
     return obj.react_LeftUp(body.of_Mouse.point,body.of_Mouse.mkey);
    }
   

   template <class T,class Func>
   void dispatch_LeftDClick(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_LeftDClick(T &obj,Func,NothingType) const -> decltype( obj.react_LeftDClick(body.of_Mouse.point,body.of_Mouse.mkey) )
    {
     return obj.react_LeftDClick(body.of_Mouse.point,body.of_Mouse.mkey);
    }
   
   
   template <class T,class Func>
   void dispatch_RightClick(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_RightClick(T &obj,Func,NothingType) const -> decltype( obj.react_RightClick(body.of_Mouse.point,body.of_Mouse.mkey) )
    {
     return obj.react_RightClick(body.of_Mouse.point,body.of_Mouse.mkey);
    }
   

   template <class T,class Func>
   void dispatch_RightUp(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_RightUp(T &obj,Func,NothingType) const -> decltype( obj.react_RightUp(body.of_Mouse.point,body.of_Mouse.mkey) )
    {
     return obj.react_RightUp(body.of_Mouse.point,body.of_Mouse.mkey);
    }


   template <class T,class Func>
   void dispatch_RightDClick(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_RightDClick(T &obj,Func,NothingType) const -> decltype( obj.react_RightDClick(body.of_Mouse.point,body.of_Mouse.mkey) )
    {
     return obj.react_RightDClick(body.of_Mouse.point,body.of_Mouse.mkey);
    }
   

   template <class T,class Func>
   void dispatch_Move(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_Move(T &obj,Func,NothingType) const -> decltype( obj.react_Move(body.of_Mouse.point,body.of_Mouse.mkey) )
    {
     return obj.react_Move(body.of_Mouse.point,body.of_Mouse.mkey);
    }
   

   template <class T,class Func>
   void dispatch_Hover(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_Hover(T &obj,Func,NothingType) const -> decltype( obj.react_Hover(body.of_Mouse.point,body.of_Mouse.mkey) )
    {
     return obj.react_Hover(body.of_Mouse.point,body.of_Mouse.mkey);
    }
   
   
   template <class T,class Func>
   void dispatch_Leave(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_Leave(T &obj,Func,NothingType) const -> decltype( obj.react_Leave() )
    {
     return obj.react_Leave();
    }
   

   template <class T,class Func>
   void dispatch_Wheel(T &,Func func,int) const
    {
     func(*this);
    }
   
   template <class T,class Func>
   auto dispatch_Wheel(T &obj,Func,NothingType) const -> decltype( obj.react_Wheel(body.of_Wheel.point,body.of_Wheel.mkey,body.of_Wheel.delta) )
    {
     return obj.react_Wheel(body.of_Wheel.point,body.of_Wheel.mkey,body.of_Wheel.delta);
    }
   
  public:
  
   // dispatch
   
   template <class T,class Func>
   void dispatch(T &obj,Func func) const
    {
     switch( type )
       {
        case Key           : dispatch_Key(obj,func,Nothing,Nothing); break;
        case RepeatKey     : dispatch_RepeatKey(obj,func,Nothing,Nothing); break;
        case KeyUp         : dispatch_KeyUp(obj,func,Nothing,Nothing); break;
        case RepeatKeyUp   : dispatch_RepeatKeyUp(obj,func,Nothing,Nothing); break;
        
        case Char          : dispatch_Char(obj,func,Nothing,Nothing); break;
        case RepeatChar    : dispatch_RepeatChar(obj,func,Nothing,Nothing); break;
        case AltChar       : dispatch_AltChar(obj,func,Nothing,Nothing); break;
        case RepeatAltChar : dispatch_RepeatAltChar(obj,func,Nothing,Nothing); break;
        
        case LeftClick     : dispatch_LeftClick(obj,func,Nothing); break;
        case LeftUp        : dispatch_LeftUp(obj,func,Nothing); break;
        case LeftDClick    : dispatch_LeftDClick(obj,func,Nothing); break;
        
        case RightClick    : dispatch_RightClick(obj,func,Nothing); break;
        case RightUp       : dispatch_RightUp(obj,func,Nothing); break;
        case RightDClick   : dispatch_RightDClick(obj,func,Nothing); break;
        
        case Move          : dispatch_Move(obj,func,Nothing); break;
        case Hover         : dispatch_Hover(obj,func,Nothing); break;
        case Leave         : dispatch_Leave(obj,func,Nothing); break;
        case Wheel         : dispatch_Wheel(obj,func,Nothing); break;
       }
    }
  
   template <class T>
   void dispatch(T &obj) const
    {
     dispatch(obj, [] (UserAction) {} );
    }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     switch( type )
       {
        case Key           : Printf(out,"Key#;",body.of_Key); break;
        case RepeatKey     : Printf(out,"Key#;",body.of_RepeatKey); break;
        case KeyUp         : Printf(out,"KeyUp#;",body.of_Key); break;
        case RepeatKeyUp   : Printf(out,"KeyUp#;",body.of_RepeatKey); break;
        
        case Char          : Printf(out,"Char#;",body.of_Char); break;
        case RepeatChar    : Printf(out,"Char#;",body.of_RepeatChar); break;
        case AltChar       : Printf(out,"AltChar#;",body.of_Char); break;
        case RepeatAltChar : Printf(out,"AltChar#;",body.of_RepeatChar); break;
        
        case LeftClick     : Printf(out,"LeftClick#;",body.of_Mouse); break;
        case LeftUp        : Printf(out,"LeftUp#;",body.of_Mouse); break;
        case LeftDClick    : Printf(out,"LeftDClick#;",body.of_Mouse); break;
        
        case RightClick    : Printf(out,"RightClick#;",body.of_Mouse); break;
        case RightUp       : Printf(out,"RightUp#;",body.of_Mouse); break;
        case RightDClick   : Printf(out,"RightDClick#;",body.of_Mouse); break;
        
        case Move          : Printf(out,"Move#;",body.of_Mouse); break;
        case Hover         : Printf(out,"Hover#;",body.of_Mouse); break;
        case Leave         : Printf(out,"Leave()"); break;
        case Wheel         : Printf(out,"Wheel#;",body.of_Wheel); break;
       }
    }
 };

/* struct SomeClass */

#if 0

struct SomeClass
 {
  void react(UserAction action) { action.dispatch(*this); }

  
  void react_Key(VKey vkey,KeyMod kmod)
   {
    Used(vkey);
    Used(kmod);
   }
  
  void react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
   {
    Used(vkey);
    Used(kmod);
    Used(repeat);
   }
  
  void react_KeyUp(VKey vkey,KeyMod kmod)
   {
    Used(vkey);
    Used(kmod);
   }
  
  void react_KeyUp(VKey vkey,KeyMod kmod,unsigned repeat)
   {
    Used(vkey);
    Used(kmod);
    Used(repeat);
   }

  
  void react_Char(char ch)
   {
    Used(ch);
   }

  void react_Char(char ch,unsigned repeat)
   {
    Used(ch);
    Used(repeat);
   }

  void react_AltChar(char ch)
   {
    Used(ch);
   }

  void react_AltChar(char ch,unsigned repeat)
   {
    Used(ch);
    Used(repeat);
   }
 
  
  void react_LeftClick(Point point,MouseKey mkey)
   {
    Used(point);
    Used(mkey);
   }
  
  void react_LeftUp(Point point,MouseKey mkey)
   {
    Used(point);
    Used(mkey);
   }
  
  void react_LeftDClick(Point point,MouseKey mkey)
   {
    Used(point);
    Used(mkey);
   }

  
  void react_RightClick(Point point,MouseKey mkey)
   {
    Used(point);
    Used(mkey);
   }
  
  void react_RightUp(Point point,MouseKey mkey)
   {
    Used(point);
    Used(mkey);
   }
  
  void react_RightDClick(Point point,MouseKey mkey)
   {
    Used(point);
    Used(mkey);
   }


  void react_Move(Point point,MouseKey mkey)
   {
    Used(point);
    Used(mkey);
   }

  void react_Hover(Point point,MouseKey mkey)
   {
    Used(point);
    Used(mkey);
   }

  void react_Leave()
   {
   }

  void react_Wheel(Point point,MouseKey mkey,Coord delta)
   {
    Used(point);
    Used(mkey);
    Used(delta);
   }
 };

#endif

/* struct UserInput */

struct UserInput
 {
  virtual void disableReact()
   { 
    // do nothing
   }
  
  virtual void enableReact()
   { 
    // do nothing
   }
  
  virtual void react(UserAction action)
   {
    Used(action);
    
    // do nothing
   }
  
  // put_...(...)
  
  void put_Key(VKey vkey,KeyMod kmod) { react(UserAction::Create_Key(vkey,kmod)); }
  
  void put_Key(VKey vkey,KeyMod kmod,unsigned repeat) { react(UserAction::Create_RepeatKey(vkey,kmod,repeat)); }
  
  void put_KeyUp(VKey vkey,KeyMod kmod) { react(UserAction::Create_KeyUp(vkey,kmod)); }
  
  void put_KeyUp(VKey vkey,KeyMod kmod,unsigned repeat) { react(UserAction::Create_RepeatKeyUp(vkey,kmod,repeat)); }
  
  
  void put_Char(char ch) { react(UserAction::Create_Char(ch)); }
  
  void put_Char(char ch,unsigned repeat) { react(UserAction::Create_RepeatChar(ch,repeat)); }
  
  void put_AltChar(char ch) { react(UserAction::Create_AltChar(ch)); }
  
  void put_AltChar(char ch,unsigned repeat) { react(UserAction::Create_RepeatAltChar(ch,repeat)); } 
 
 
  void put_LeftClick(Point point,MouseKey mkey) { react(UserAction::Create_LeftClick(point,mkey)); }
  
  void put_LeftUp(Point point,MouseKey mkey) { react(UserAction::Create_LeftUp(point,mkey)); }
  
  void put_LeftDClick(Point point,MouseKey mkey) { react(UserAction::Create_LeftDClick(point,mkey)); }
  
  
  void put_RightClick(Point point,MouseKey mkey) { react(UserAction::Create_RightClick(point,mkey)); }
  
  void put_RightUp(Point point,MouseKey mkey) { react(UserAction::Create_RightUp(point,mkey)); }
  
  void put_RightDClick(Point point,MouseKey mkey) { react(UserAction::Create_RightDClick(point,mkey)); }
  
  
  void put_Move(Point point,MouseKey mkey) { react(UserAction::Create_Move(point,mkey)); }
  
  void put_Hover(Point point,MouseKey mkey) { react(UserAction::Create_Hover(point,mkey)); }
  
  void put_Leave() { react(UserAction::Create_Leave()); }
  
  void put_Wheel(Point point,MouseKey mkey,Coord delta) { react(UserAction::Create_Wheel(point,mkey,delta)); }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

