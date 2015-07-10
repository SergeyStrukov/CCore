/* SIntFunc.h */ 
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

#ifndef CCore_inc_gadget_SIntFunc_h
#define CCore_inc_gadget_SIntFunc_h
 
#include <CCore/inc/gadget/UIntFunc.h>

namespace CCore {

/* classes */

template <class SInt> struct SIntFunc;

/* struct SIntFunc<SInt> */

// TODO : this is valid for 2s complementary arithmetic

template <class SInt> 
struct SIntFunc
 {
  static_assert( Meta::IsSInt<SInt>::Ret ,"CCore::SIntFunc<SInt> : SInt must be a signed integral type");

  // types
  
  using UInt = typename Meta::SIntToUInt<SInt>::UType ;

  // consts
  
  static const UInt MaxPositiveAbs = UIntFunc<UInt>::MaxPositive ;
  
  static const UInt MinNegativeAbs = UIntFunc<UInt>::MinNegative ;
  
  static const SInt MaxPositive = SInt(MaxPositiveAbs) ;
  
  static const SInt MinNegative = SInt(MinNegativeAbs) ;
  
  // abs
  
  static SInt PosAbs(UInt abs) { return SInt(abs); }
  
  static SInt NegAbs(UInt abs) { return SInt(UIntFunc<UInt>::Neg(abs)); }
  
  // dist/move
  
  static UInt Dist(SInt a,SInt b) // a <= b
   { 
    return (UInt)b-(UInt)a; 
   }

  static SInt MovePos(SInt a,UInt delta)
   { 
    return a+delta;
   }
  
  static SInt MoveNeg(SInt a,UInt delta)
   { 
    return a-delta;
   }
  
  static SInt Move(SInt a,SInt e,UInt delta)
   {
    return (e>0)?MovePos(a,delta):MoveNeg(a,delta);
   }
 };

} // namespace CCore
 
#endif
 

