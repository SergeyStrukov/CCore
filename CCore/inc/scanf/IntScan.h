/* IntScan.h */ 
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

#ifndef CCore_inc_scanf_IntScan_h
#define CCore_inc_scanf_IntScan_h
 
#include <CCore/inc/scanf/ScanTools.h>

namespace CCore {

/* classes */

//enum IntScanBase;

struct IntScanOpt;

template <class UInt> class UIntDigitAcc;

template <class S,ulen Len> class DetectIntFormat;

template <class S,class UInt> struct UIntScanAlgo;

template <class UInt> class UIntScan;

template <class SInt> class SIntScan;

/* enum IntScanBase */

enum IntScanBase
 {
  IntScanNone,
  
  IntScanHex,
  IntScanBin,
  IntScan0X
 };

template <class Dev>
bool Parse_try(Dev &dev,IntScanBase &ret)
 {
  typename Dev::Peek peek(dev);
  
  if( !peek )
    {
     return false;
    }
  else
    {
     switch( *peek )
       {
        case 'h' : case 'H' : ret=IntScanHex; ++dev; return true;
        case 'b' : case 'B' : ret=IntScanBin; ++dev; return true;
        case 'x' : case 'X' : ret=IntScan0X;  ++dev; return true;
       }
     
     return false;
    }
 }

/* struct IntScanOpt */

struct IntScanOpt
 {
  unsigned base; // 2..16, 0 for any
  IntScanBase scan_base; 
  
  void setDefault()
   {
    base=0;
    scan_base=IntScanNone;
   }
  
  IntScanOpt() { setDefault(); }
  
  IntScanOpt(const char *ptr,const char *lim);
  
  //
  // [.base|.x|.b|.h]
  //
 };

/* class UIntDigitAcc<UInt> */

template <class UInt> 
class UIntDigitAcc
 {
   static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntDigitAcc<UInt> : UInt must be an unsigned integral type");
   
   UInt value;
   
   UInt a;
   UInt b;
   
  public: 
   
   UIntDigitAcc(unsigned dig,unsigned base) 
    { 
     value=UInt(dig);
     
     const UInt MaxVal=UInt(-1);
     
     a=MaxVal/base;
     b=MaxVal%base;
    }
   
   bool next_uns(unsigned dig,unsigned base)
    {
     if( value>a || ( value==a && dig>b ) ) return false;
     
     value=UInt(base*value+dig);
     
     return true;
    }
   
   bool next(int dig,unsigned base) { return next_uns((unsigned)dig,base); }
   
   typedef UInt ValueType;
   
   operator UInt() const { return value; }
 };

/* class DetectIntFormat<S,ulen Len> */

template <class S,ulen Len> 
class DetectIntFormat : NoCopy
 {
   char buf[Len];
   IntScanBase scan_base;
   
   PtrLen<const char> cur;
   bool fail_flag = false ;
 
  public:
   
   explicit DetectIntFormat(S &inp);
   
   IntScanBase getFormat() const { return scan_base; }
   
   // cursor
   
   ulen operator + () const { return cur.len; }
   
   bool operator ! () const { return !cur.len; }
   
   char operator * () const { return *cur; }
   
   void operator ++ () { ++cur; }
   
   // error
   
   bool isOk() const { return !fail_flag; }
   
   bool isFailed() const { return fail_flag; }
   
   void fail() { cur=Nothing; fail_flag=true; }
 };

template <class S,ulen Len> 
DetectIntFormat<S,Len>::DetectIntFormat(S &inp)
 {
  // TODO
 }

/* struct UIntScanAlgo<S,UInt> */

template <class S,class UInt> 
struct UIntScanAlgo
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntScanAlgo<S,UInt> : UInt must be an unsigned integral type");
  
  typedef UInt ValueType;
  
  // Hex
  
  static void PlusHex(S &inp,UInt &ret)
   {
    if( +inp )
      {
       int dig=CharHexValue(*inp);
       
       if( dig<0 )
         {
          inp.fail();
         }
       else
         {
          UIntDigitAcc<UInt> acc(dig,16);
          
          char ch;
         
          for(++inp; (dig=CharHexValue(ch=*inp))>=0 ;++inp)
            {
             if( !acc.next(dig,16) )
               {
                inp.fail();
                
                return;
               }
            }
          
          if( ch=='h' || ch=='H' )
            {
             ++inp;
             
             ret=acc;
            }
          else
            {
             inp.fail();
            }
         }
      }
    else
      {
       inp.fail();
      }
   }
  
  static void MinusHex(S &inp,UInt &ret)
   {
    PlusHex(inp,ret);
    
    if( inp.isOk() ) ret=UInt(-ret);
   }
  
  static void ScanHex(S &inp,UInt &ret)
   {
    if( +inp )
      {
       switch( *inp )
         {
          case '+' : ++inp; // falldown;
          
          default: PlusHex(inp,ret); break;
           
          case '-' : ++inp; MinusHex(inp,ret);
         }
      }
    else
      {
       inp.fail();
      }
   }
  
  // Bin
  
  static void PlusBin(S &inp,UInt &ret)
   {
    if( +inp )
      {
       int dig=CharBinValue(*inp);
       
       if( dig<0 )
         {
          inp.fail();
         }
       else
         {
          UIntDigitAcc<UInt> acc(dig,2);
          
          char ch;
         
          for(++inp; (dig=CharBinValue(ch=*inp))>=0 ;++inp)
            {
             if( !acc.next(dig,2) )
               {
                inp.fail();
                
                return;
               }
            }
          
          if( ch=='b' || ch=='B' )
            {
             ++inp;
             
             ret=acc;
            }
          else
            {
             inp.fail();
            }
         }
      }
    else
      {
       inp.fail();
      }
   }
  
  static void MinusBin(S &inp,UInt &ret)
   {
    PlusBin(inp,ret);
    
    if( inp.isOk() ) ret=UInt(-ret);
   }
  
  static void ScanBin(S &inp,UInt &ret)
   {
    if( +inp )
      {
       switch( *inp )
         {
          case '+' : ++inp; // falldown;
          
          default: PlusBin(inp,ret); break;
           
          case '-' : ++inp; MinusBin(inp,ret);
         }
      }
    else
      {
       inp.fail();
      }
   }

  // 0X
  
  static void Plus0X(S &inp,UInt &ret)
   {
    PassChars(inp,'0');
    PassOneOfChar(inp, [] (char ch) { return ch=='x' || ch=='X'; } );
    
    if( +inp )
      {
       int dig=CharHexValue(*inp);
       
       if( dig<0 )
         {
          inp.fail();
         }
       else
         {
          UIntDigitAcc<UInt> acc(dig,16);
          
          for(++inp; (dig=CharHexValue(*inp))>=0 ;++inp)
            {
             if( !acc.next(dig,16) )
               {
                inp.fail();
                
                return;
               }
            }
          
          ret=acc;
         }
      }
    else
      {
       inp.fail();
      }
   }
  
  static void Minus0X(S &inp,UInt &ret)
   {
    Plus0X(inp,ret);
    
    if( inp.isOk() ) ret=UInt(-ret);
   }
  
  static void Scan0X(S &inp,UInt &ret)
   {
    if( +inp )
      {
       switch( *inp )
         {
          case '+' : ++inp; // falldown;
          
          default: Plus0X(inp,ret); break;
           
          case '-' : ++inp; Minus0X(inp,ret);
         }
      }
    else
      {
       inp.fail();
      }
   }
 
  // base
  
  static void PlusBase(S &inp,UInt &ret,unsigned base)
   {
    if( +inp )
      {
       int dig=CharBaseValue(*inp,base);
       
       if( dig<0 )
         {
          inp.fail();
         }
       else
         {
          UIntDigitAcc<UInt> acc(dig,base);
          
          for(++inp; (dig=CharBaseValue(*inp,base))>=0 ;++inp)
            {
             if( !acc.next(dig,base) )
               {
                inp.fail();
                
                return;
               }
            }
          
          ret=acc;
         }
      }
    else
      {
       inp.fail();
      }
   }
  
  static void MinusBase(S &inp,UInt &ret,unsigned base)
   {
    PlusBase(inp,ret,base);
    
    if( inp.isOk() ) ret=UInt(-ret);
   }
  
  static void ScanBase(S &inp,UInt &ret,unsigned base)
   {
    if( +inp )
      {
       switch( *inp )
         {
          case '+' : ++inp; // falldown;
          
          default: PlusBase(inp,ret,base); break;
           
          case '-' : ++inp; MinusBase(inp,ret,base);
         }
      }
    else
      {
       inp.fail();
      }
   }
 
  // any
  
  static void ScanAny(S &inp,UInt &ret) // Hex | Bin | 0X | Base(10)
   {
    DetectIntFormat<S,128> detect(inp);
    
    if( inp.isFailed() ) return;
    
    switch( detect.getFormat() )
      {
       case IntScanHex : ScanHex(detect,ret); break;
      
       case IntScanBin : ScanBin(detect,ret); break;
      
       case IntScan0X : Scan0X(detect,ret); break;
     
       case IntScanNone : ScanBase(detect,ret,10); break;
      }
    
    if( detect.isFailed() ) inp.fail();
   }
  
  // opt
  
  static void Scan(S &inp,IntScanOpt opt,UInt &ret)
   {
    switch( opt.scan_base )
      {
       case IntScanHex : ScanHex(inp,ret); break;
        
       case IntScanBin : ScanBin(inp,ret); break;
        
       case IntScan0X : Scan0X(inp,ret); break;
       
       case IntScanNone :
        {
         if( opt.base )
           {
            ScanBase(inp,ret,opt.base);
           }
         else
           {
            ScanAny(inp,ret);
           }
        }
      }
   }
 };

/* class UIntScan<UInt> */

template <class UInt> 
class UIntScan : NoCopy
 {
   UInt &var;
   
  public:
  
   explicit UIntScan(UInt &var_) : var(var_) {}
   
   template <class S>
   void scan(S &inp,IntScanOpt opt)
    {
     var=0;
     
     UIntScanAlgo<S,UInt>::Scan(inp,opt,var);
    }
 };

/* class SIntScan<SInt> */

template <class SInt> 
class SIntScan : NoCopy
 {
   SInt &var;
   
  public:
  
   explicit SIntScan(SInt &var_) : var(var_) {}
   
   template <class S>
   void scan(S &inp,IntScanOpt opt)
    {
     var=0;
     
     // SIntScanAlgo<S,UInt>::Scan(inp,opt,var);
    }
 };

} // namespace CCore
 
#endif
 

