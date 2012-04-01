/* String.h */ 
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

#ifndef CCore_inc_String_h
#define CCore_inc_String_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Printf.h>
 
namespace CCore {

/* classes */ 

class String;

class PrintString;

template <unsigned Count> class StringSumBuilder;

/* class String */ 

class String
 {
   AtomicRefArray<char> data; 
   
  public: 
  
   String() {}
   
   String(StrLen str) : data(DoCopy(str.len),str.ptr) {}
   
   template <class Builder>
   String(DoBuildType,Builder builder) : data(DoBuild,builder) {}
   
   ~String() {}
   
   // range access
   
   const char * getPtr() const { return data.getPtr(); }
   
   const char * getPtr_const() const { return data.getPtr(); }
   
   ulen getLen() const { return data.getLen(); }
   
   // print object
   
   typedef StrPrintOpt PrintOptType;
   
   template <class P>
   void print(P &obj,PrintOptType opt) const
    {
     StrPrint proxy(Range(*this));
     
     proxy.print(obj,opt);
    }
   
   // swap/move objects
   
   void objSwap(String &obj)
    {
     Swap(data,obj.data);
    }
    
   explicit String(ToMoveCtor<String> obj) 
    : data(ObjToMove(obj->data)) 
    {
    }
   
   String * objMove(Place<void> place) 
    {
     return CtorMove(this,place);
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
/* class PrintString */  

class PrintString : public PrintBase
 {
   ulen max_len;
   ulen frame_len;
   
   Collector<char> data;
   PtrLen<char> buf;
 
  private:
  
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len); 
   
  public: 
  
   static const ulen DefaultFrameLen = 1_KByte ;
  
   explicit PrintString(ulen max_len=MaxULen,ulen frame_len=DefaultFrameLen);
   
   ~PrintString() { cleanup(); }
   
   String close();
   
   void cleanup();
 };

/* class StringSumBuilder<unsigned Count> */

template <unsigned Count> 
class StringSumBuilder
 {
   StrLen list[Count];
   ulen len;
   
  private: 

   template <class T>
   static StrLen Cast(const T &t) { return Range_const(t); }
  
   static StrLen Cast(StrLen t) { return t; }
  
   static StrLen Cast(const char *t) { return t; }
  
   ulen countLen() const 
    {
     ulen ret=0;
    
     for(StrLen str : list) ret+=str.len;
    
     return ret;
    }
   
  public: 
  
   template <class ... TT>
   explicit StringSumBuilder(const TT & ... tt)
    : list{ Cast(tt) ... }
    {
     len=countLen();
    }
   
   ulen getLen() const { return len; }
   
   PtrLen<char> operator () (Place<void> place)
    {
     PtrLen<char> ret(place,len);
     
     PtrLen<char> out=ret;
     
     for(StrLen str : list) (out+=str.len).copy(str.ptr);
     
     return ret;
    }
 };

template <> 
class StringSumBuilder<0>
 {
  public:
   
   StringSumBuilder() {}
  
   ulen getLen() const { return 0; }
  
   PtrLen<char> operator () (Place<void> place) { return PtrLen<char>(place,0); }
 };

/* functions */  

template <class ... TT>
String Stringf(const char *format,const TT & ... tt)
 {
  PrintString out;
  
  Printf(out,format,tt...);
  
  return out.close();
 }
 
template <class ... TT>
String StringCat(const TT & ... tt)
 {
  PrintString out;
  
  Putobj(out,tt...);
  
  return out.close();
 }
 
template <class ... TT>
String StringSum(const TT & ... tt)
 {
  return String(DoBuild,StringSumBuilder<Meta::TypeListLen<TT...>::Ret>(tt...));
 }

template <class T>
String operator + (const String &a,const T &t) { return StringSum(a,t); }

} // namespace CCore
 
#endif
 

