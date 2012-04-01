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
 
namespace CCore {

/* classes */ 

template <class UInt> struct UIntFunc;

/* struct UIntFunc<UInt> */ 

template <class UInt> 
struct UIntFunc
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntFunc<UInt> : UInt must be an unsigned integral type");
  
  // consts
  
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
 
} // namespace CCore
 
#endif
 

