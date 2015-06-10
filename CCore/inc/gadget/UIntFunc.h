/* UIntFunc.h */ 
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

#ifndef CCore_inc_gadget_UIntFunc_h
#define CCore_inc_gadget_UIntFunc_h

#include <CCore/inc/gadget/Meta.h>

#include <CCore/inc/base/Quick.h>
 
namespace CCore {

/* classes */ 

template <class UInt,class ExtUInt> struct UIntMulFunc_double; 

template <class UInt,class ExtUInt> struct UIntMulFunc_exact;

template <class UInt> struct UIntBitFunc;

template <class UInt> struct UIntBitFunc_quick;

template <class UInt> struct UIntFunc;

/* struct UIntMulFunc_double<UInt,ExtUInt> */

template <class UInt,class ExtUInt> 
struct UIntMulFunc_double
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntMulFunc_double<UInt,ExtUInt> : UInt must be an unsigned integral type");
  static_assert( Meta::IsUInt<ExtUInt>::Ret ,"CCore::UIntMulFunc_double<UInt,ExtUInt> : ExtUInt must be an unsigned integral type");
  
  static const unsigned Bits = Meta::UIntBits<UInt>::Ret ;
  
  static_assert( 2*Bits <= Meta::UIntBits<ExtUInt>::Ret ,"CCore::UIntMulFunc_double<UInt,ExtUInt> : ExtUInt must be double larger than UInt");
  
  
  static ExtUInt Combine(UInt hi,UInt lo)
   {
    return (ExtUInt(hi)<<Bits)|lo;
   }
  
  struct Mul
   {
    UInt hi;
    UInt lo;
    
    Mul(UInt a,UInt b)
     {
      ExtUInt p=(ExtUInt)a*b;
      
      lo=UInt(p);
      hi=UInt(p>>Bits);
     }
   };
  
  static UInt Div(UInt hi,UInt lo,UInt den)
   {
    return UInt(Combine(hi,lo)/den);
   }
  
  static UInt Mod(UInt hi,UInt lo,UInt den)
   {
    return UInt(Combine(hi,lo)%den);
   }
  
  struct DivMod
   {
    UInt div;
    UInt mod;
    
    DivMod(UInt hi,UInt lo,UInt den)
     {
      ExtUInt p=Combine(hi,lo);
      
      div=UInt(p/den);
      mod=UInt(p%den);
     }
   };
  
  static UInt ModMul(UInt a,UInt b,UInt mod)
   {
    ExtUInt p=(ExtUInt)a*b;
    
    return UInt(p%mod);
   }

  static UInt ModMac(UInt s,UInt a,UInt b,UInt mod)
   {
    ExtUInt p=(ExtUInt)a*b+s;
    
    return UInt(p%mod);
   }
 };

/* struct UIntMulFunc_exact<UInt,ExtUInt> */

template <class UInt,class ExtUInt> 
struct UIntMulFunc_exact
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntMulFunc_double<UInt,ExtUInt> : UInt must be an unsigned integral type");
  static_assert( Meta::IsUInt<ExtUInt>::Ret ,"CCore::UIntMulFunc_double<UInt,ExtUInt> : ExtUInt must be an unsigned integral type");
  
  static_assert( Meta::UIntBits<UInt>::Ret == Meta::UIntBits<ExtUInt>::Ret ,"CCore::UIntMulFunc_double<UInt,ExtUInt> : ExtUInt must have the same bitsize as UInt");
  
  
  using Algo = typename Quick::UIntMulFunc<ExtUInt> ;
  
  struct Mul
   {
    UInt hi;
    UInt lo;
    
    Mul(UInt a,UInt b)
     {
      typename Algo::Mul res(a,b);
      
      hi=res.hi;
      lo=res.lo;
     }
   };
  
  static UInt Div(UInt hi,UInt lo,UInt den)
   {
    return Algo::Div(hi,lo,den);
   }
  
  static UInt Mod(UInt hi,UInt lo,UInt den)
   {
    return Algo::Mod(hi,lo,den);
   }
  
  struct DivMod
   {
    UInt div;
    UInt mod;
    
    DivMod(UInt hi,UInt lo,UInt den)
     {
      typename Algo::DivMod res(hi,lo,den);
      
      div=res.div;
      mod=res.mod;
     }
   };
  
  static UInt ModMul(UInt a,UInt b,UInt mod)
   {
    return Algo::ModMul(a,b,mod);
   }

  static UInt ModMac(UInt s,UInt a,UInt b,UInt mod)
   {
    return Algo::ModMac(s,a,b,mod);
   }
 };

/* struct UIntBitFunc<UInt> */

template <class UInt> 
struct UIntBitFunc
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntBitFunc<UInt> : UInt must be an unsigned integral type");
  
  static const unsigned Bits = Meta::UIntBits<UInt>::Ret ;
  
  static const UInt MaxUnsigned = UInt(-1) ;
  
  static const UInt MSBit = MaxUnsigned^(MaxUnsigned>>1) ;
  
  static unsigned CountZeroMSB(UInt a)
   {
    if( !a ) return Bits;
    
    if( a&MSBit ) return 0;
    
    unsigned ret=0;
    unsigned n=Bits;
    
    while( n>=2 )
      {
       unsigned m=n/2;
       
       UInt mask=UInt( UInt(-1)<<(Bits-m) );
       
       if( a&mask )
         {
          n=m;
         }
       else
         {
          ret+=m;
          a<<=m;
          n-=m;
         }
      }
      
    return ret;
   }
  
  static unsigned CountZeroLSB(UInt a)
   {
    if( !a ) return Bits;
    
    if( a&UInt(1) ) return 0;
    
    unsigned ret=0;
    unsigned n=Bits;
    
    while( n>=2 )
      {
       unsigned m=n/2;
       
       UInt mask=(UInt(1)<<m)-1;
       
       if( a&mask )
         {
          n=m;
         }
       else
         {
          ret+=m;
          a>>=m;
          n-=m;
         }
      }
      
    return ret;
   }
 };

/* struct UIntBitFunc_quick<UInt> */

template <class UInt> 
struct UIntBitFunc_quick
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntBitFunc_quick<UInt> : UInt must be an unsigned integral type");
  
  static const unsigned Bits = Meta::UIntBits<UInt>::Ret ;
  
  static unsigned CountZeroMSB(UInt a)
   {
    if( !a ) return Bits;
    
    return Bits-1-Quick::ScanMSBit(a);
   }
  
  static unsigned CountZeroLSB(UInt a)
   {
    if( !a ) return Bits;
    
    return Quick::ScanLSBit(a);
   }
 };

/* struct UIntFunc<UInt> */ 

template <class UInt> 
struct UIntFunc : Meta::Select< Quick::UIntMulSelect<Meta::UIntBits<UInt>::Ret>::IsDoubleType ,UIntMulFunc_double<UInt,typename Quick::UIntMulSelect<Meta::UIntBits<UInt>::Ret>::ExtType>,
                                                                                               UIntMulFunc_exact<UInt,typename Quick::UIntMulSelect<Meta::UIntBits<UInt>::Ret>::ExtType> >,
                  Meta::Select<( UInt(-1)<=Quick::ScanUInt(-1) ),UIntBitFunc_quick<UInt>,UIntBitFunc<UInt> >                                                                             
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntFunc<UInt> : UInt must be an unsigned integral type");
  
  // consts
  
  static const unsigned Bits = Meta::UIntBits<UInt>::Ret ;
  
  static const UInt MaxUnsigned = UInt(-1) ;
  
  static const UInt MSBit = MaxUnsigned^(MaxUnsigned>>1) ;
  
  static const UInt MaxPositive = MaxUnsigned>>1 ;
  
  static const UInt MinNegative = MSBit ;
  
  // sign
  
  static UInt Neg(UInt value) { return UInt(-value); }
  
  static bool IsNegative(UInt value) { return value&MSBit; }
    
  static bool NotNegative(UInt value) { return !(value&MSBit); }
  
  static bool IsPositive(UInt value) { return UInt(value-1)<=(MaxPositive-1); }
  
  static bool NotPositive(UInt value) { return UInt(value-1)>(MaxPositive-1); }
  
  // additive
  
  struct Add
   {
    UInt result;
    bool carry;
    
    Add(UInt a,UInt b)
     {
      result=a+b;
      carry=(result<a);
     }
   };
   
  struct Sub
   {
    UInt result;
    bool borrow;
    
    Sub(UInt a,UInt b)
     {
      result=a-b;
      borrow=(a<b);
     }
   };
   
  struct Inc
   {
    UInt result;
    bool carry;
    
    explicit Inc(UInt a)
     {
      result=a+1;
      carry=(result==0);
     }
   };
   
  struct Dec
   {
    UInt result;
    bool borrow;
    
    explicit Dec(UInt a)
     {
      result=a-1;
      borrow=(a==0);
     }
   };
 };
 
/* functions */  

template <class UInt>
bool UIntAdd(UInt &a,UInt b)
 {
  typename UIntFunc<UInt>::Add add(a,b);
  
  a=add.result;
  
  return add.carry;
 }
 
template <class UInt>
bool UIntSub(UInt &a,UInt b)
 {
  typename UIntFunc<UInt>::Sub sub(a,b);
  
  a=sub.result;
  
  return sub.borrow;
 }
 
template <class UInt> 
bool UIntInc(UInt &a)
 {
  typename UIntFunc<UInt>::Inc inc(a);
  
  a=inc.result;
  
  return inc.carry;
 }
 
template <class UInt> 
bool UIntDec(UInt &a)
 {
  typename UIntFunc<UInt>::Dec dec(a);
  
  a=dec.result;
  
  return dec.borrow;
 }
 
template <class UInt>
UInt UIntDiv(UInt hi,UInt lo,UInt den)
 {
  return UIntFunc<UInt>::Div(hi,lo,den);
 }

template <class UInt>
UInt UIntMod(UInt hi,UInt lo,UInt den)
 {
  return UIntFunc<UInt>::Mod(hi,lo,den);
 }

template <class UInt>
UInt UIntModMul(UInt a,UInt b,UInt mod)
 {
  return UIntFunc<UInt>::ModMul(a,b,mod);
 }

template <class UInt>
UInt UIntModMac(UInt s,UInt a,UInt b,UInt mod)
 {
  return UIntFunc<UInt>::ModMac(s,a,b,mod);
 }

} // namespace CCore
 
#endif
 

