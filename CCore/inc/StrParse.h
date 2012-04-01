/* StrParse.h */ 
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

#ifndef CCore_inc_StrParse_h
#define CCore_inc_StrParse_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* classes */ 

struct DecValue;

class StrParse;

/* struct DecValue */ 

struct DecValue
 {
  bool nok;
  unsigned value;
  
  explicit DecValue(char ch)
   {
    if( ch>='0' && ch<='9' )
      {
       nok=false;
       value=ch-'0';
      }
    else
      {
       nok=true;
       value=0;
      }  
   }
      
  bool operator ! () const { return nok; }
     
  unsigned operator * () const { return value; }
 };
 
/* class StrParse */ 

class StrParse
 {
   const char *ptr;
   const char *lim;
   bool nok;
   
  private:
  
   void init(const char *ptr_,const char *lim_) 
    {
     ptr=ptr_;
     lim=lim_;
     nok=false;
    }
   
   void init(const char *ptr,ulen len)
    {
     init(ptr,ptr+len);
    }
   
  public: 
  
   StrParse(const char *ptr,const char *lim) { init(ptr,lim); }
   
   explicit StrParse(StrLen str) { init(str.ptr,str.len); }
   
   bool operator ! () const { return nok; }
   
   struct Peek
    {
     bool nok;
     char ch;
    
     explicit Peek(StrParse &dev)
      {
       if( dev.nok || dev.ptr>=dev.lim )
         {
          nok=true;
          ch=0;
         }
       else
         {
          nok=false;
          ch=*dev.ptr;
         }  
      }
      
     bool operator ! () const { return nok; }
     
     char operator * () const { return ch; }
    };
    
   void operator ++ () { ptr++; }
   
   void fail() { nok=true; }
   
   NegBool finish() { if( ptr<lim ) nok=true; return nok; }
 };
 
/* functions */ 

template <class Dev>
void ParseChar(Dev &dev,char ch)
 {
  typename Dev::Peek peek(dev);

  if( !peek || *peek!=ch ) 
    dev.fail(); 
  else
    ++dev;
 }
 
template <class Dev>
bool ParseChar_try(Dev &dev,char ch)
 {
  typename Dev::Peek peek(dev);

  if( !peek || *peek!=ch )  
    {
     return false;
    }
  else
    {
     ++dev;
     
     return true;
    }
 }
 
template <class Dev>
void ParseChar_empty(Dev &dev,char &ret,char defval)
 {
  typename Dev::Peek peek(dev);

  if( !peek )  
    {
     ret=defval;
    }
  else
    {
     ret=*peek;
     
     ++dev;
    }
 }
 
/* functions */ 
 
template <class Dev,class UInt>
bool ParseUIntSetup(Dev &dev,UInt &acc)
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::ParseUIntSetup(Dev &dev,UInt &acc) : UInt must be an unsigned integral type");

  typename Dev::Peek peek(dev);
     
  if( !peek ) return false;
     
  DecValue dec(*peek);
     
  if( !dec ) return false;
     
  acc=*dec;
     
  ++dev;
  
  return true;
 }
 
template <class Dev,class UInt>
UInt ParseUIntDo(Dev &dev,UInt acc,UInt minval,UInt maxval)
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::ParseUIntDo(Dev &dev,UInt acc,...) : UInt must be an unsigned integral type");

  UInt a=maxval/10;
  UInt b=maxval%10;
  
  for(;;++dev)
    {
     typename Dev::Peek peek(dev);
     
     if( !peek ) break;
     
     DecValue dec(*peek);
     
     if( !dec ) break;
     
     if( acc>a || ( acc==a && *dec>b ) )
       {
        dev.fail();
        
        return 0;
       }
     
     acc = 10*acc + *dec ;
    }
    
  if( acc<minval )
    {
     dev.fail();
     
     return 0;
    }
    
  return acc;  
 }
 
template <class Dev,class UInt,class UInt1,class UInt2>
void ParseUInt(Dev &dev,UInt &ret,UInt1 minval_,UInt2 maxval_)
 {
  UInt minval=minval_;
  UInt maxval=maxval_;
 
  UInt acc;
  
  if( ParseUIntSetup(dev,acc) && acc<=maxval )
    {
     ret=ParseUIntDo(dev,acc,minval,maxval);  
    }
  else  
    {
     ret=0;
     
     dev.fail();
    }
 }
 
template <class Dev,class UInt,class UInt1>
void ParseUInt(Dev &dev,UInt &ret,UInt1 maxval)
 {
  ParseUInt(dev,ret,0u,maxval);
 }
 
template <class Dev,class UInt>
void ParseUInt(Dev &dev,UInt &ret)
 {
  ParseUInt(dev,ret,0u,UInt(UIntMax()));
 }
 
template <class Dev,class UInt,class UInt1,class UInt2,class UInt3>
void ParseUInt_empty(Dev &dev,UInt &ret,UInt1 defval_,UInt2 minval_,UInt3 maxval_)
 {
  UInt defval=defval_;
  UInt minval=minval_;
  UInt maxval=maxval_;
 
  UInt acc;
  
  if( ParseUIntSetup(dev,acc) )
    {
     if( acc<=maxval )
       {
        ret=ParseUIntDo(dev,acc,minval,maxval);  
       }
     else
       {
        ret=0;
        
        dev.fail();
       }
    }
  else
    {
     ret=defval;
    }
 }
 
template <class Dev,class UInt,class UInt1,class UInt2>
void ParseUInt_empty(Dev &dev,UInt &ret,UInt1 defval,UInt2 maxval)
 {
  ParseUInt_empty(dev,ret,defval,0u,maxval);
 }
 
template <class Dev,class UInt,class UInt1>
void ParseUInt_empty(Dev &dev,UInt &ret,UInt1 defval)
 {
  ParseUInt_empty(dev,ret,defval,0u,UInt(UIntMax()));
 }
 
} // namespace CCore
 
#endif
 

