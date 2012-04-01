/* TextLabel.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_TextLabel_h
#define CCore_inc_TextLabel_h

#include <CCore/inc/Printf.h>

namespace CCore {

/* types */ 

typedef StrLen (*TextLabelFunc)(Handle ctx,PtrLen<char> buf);

/* functions */ 

inline unsigned GetTextLabelNumber(unsigned &Next)
 {
  unsigned ret=Next+1;
  
  if( ret ) Next=ret;
  
  return ret;
 }
 
StrLen BuildNumTextLabel(const char *text,unsigned num,PtrLen<char> buf); 
 
/* classes */ 

class TextLabel;

template <class T> class NumTextLabel;

/* class TextLabel */ 

class TextLabel
 {
   TextLabelFunc func;
   Handle ctx;
   
  private:
  
   static StrLen EmptyFunc(Handle ctx,PtrLen<char> buf); 
   
   static StrLen StringFunc(Handle ctx,PtrLen<char> buf); 
   
   template <class Enum>
   static StrLen EnumFunc(Handle ctx,PtrLen<char>) { return GetTextDesc( Enum(ctx.sid) ); }
   
  public: 
   
   // constructors
  
   TextLabel() : func(EmptyFunc) {}
   
   TextLabel(const char *persistent_string) : func(StringFunc),ctx( (void *)persistent_string ) {}
   
   TextLabel(TextLabelFunc func_,Handle ctx_) : func(func_),ctx(ctx_) {}
   
   template <class Enum, // assume the Enum value range fits into int
             class=Meta::EnableIf<std::is_enum<Enum>::value> >
   TextLabel(Enum e) : func(EnumFunc<Enum>),ctx( (int)e ) {} 
   
   // methods
   
   StrLen getStr(PtrLen<char> buf) const { return func(ctx,buf); }
   
   // print object
   
   typedef StrPrintOpt PrintOptType;
   
   template <class P> 
   void print(P &out,PrintOptType opt) const
    {
     char buf[TextBufLen];
     StrLen str;
     
     str=getStr(Range(buf));
     
     Putobj(out,BindOpt(opt,str));
    }
 };
 
/* class NumTextLabel<T> */ 

 //
 // class T
 //  {
 //    static Mutex NextMutex;
 //
 //    static unsigned Next;
 //
 //   public:
 //
 //    static const char * GetText() { return "ObjName"; }
 //
 //    static unsigned GetNumber() { return GetTextLabelNumber(Next); }
 //
 //    static unsigned GetNumber() { Mutex::Lock lock(NextMutex); return GetTextLabelNumber(Next); }
 //  };
 //

template <class T> 
class NumTextLabel : public TextLabel
 {
  private:
  
   static StrLen Func(Handle ctx,PtrLen<char> buf)
    {
     return BuildNumTextLabel(T::GetText(),ctx.uid,buf);
    }
   
  public:
  
   NumTextLabel() : TextLabel(Func,T::GetNumber()) {}
 };
 
} // namespace CCore
 
#endif

