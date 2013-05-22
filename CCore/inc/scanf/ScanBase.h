/* ScanBase.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_scanf_ScanBase_h
#define CCore_inc_scanf_ScanBase_h

#include <CCore/inc/TextTools.h>
 
namespace CCore {

/* classes */

template <class S> struct ScanInpAdapter;

class ScanBase;

class ScanString;

/* struct ScanInpAdapter<S> */

template <class S> 
struct ScanInpAdapter
 {
  typedef typename S::ScanInpType ScanInpType;
 };

/* class ScanBase */

class ScanBase : NoCopy
 {
   PtrLen<const char> buf;
   bool fail_flag = false ;
   TextPos text_pos;
  
  private:
   
   virtual PtrLen<const char> underflow()=0;
  
   void updateTextPos(char ch);
  
  protected:
  
   void pump() { buf=underflow(); } // must be called in constructor of derived class
   
   void reset() 
    { 
     buf=Nothing; 
     fail_flag=false;
     text_pos={};
    }
  
  public:
   
   typedef ScanBase & ScanInpType;
   
   ScanInpType scanRef() { return *this; }
   
   // constructors
  
   ScanBase() {}
   
   ~ScanBase() {}
   
   // cursor
   
   ulen operator + () const { return +buf; }
   
   bool operator ! () const { return !buf; }
   
   char operator * () const { return *buf; }
   
   void operator ++ (); 
   
   // position
   
   TextPos getTextPos() const { return text_pos; }
   
   // error
   
   bool isOk() const { return !fail_flag; }
   
   bool isFailed() const { return fail_flag; }
   
   void fail() { buf=Nothing; fail_flag=true; }
 };

/* class ScanString */

class ScanString : public ScanBase
 {
   PtrLen<const char> str;
   
  private:
  
   virtual PtrLen<const char> underflow() { return Replace_null(str); }
  
  public: 
  
   explicit ScanString(StrLen str_) : str(str_) { pump(); }
   
   ~ScanString() {}
 };

} // namespace CCore
 
#endif
 

