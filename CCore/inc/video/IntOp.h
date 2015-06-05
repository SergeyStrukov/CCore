/* IntOp.h */ 
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

#ifndef CCore_inc_video_IntOp_h
#define CCore_inc_video_IntOp_h
 
#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Video {

/* guard functions */

void IntGuardAssert();

inline void IntGuard(bool cond) { if( !cond ) IntGuardAssert(); }

/* functions */

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
UInt IntDist(SInt a,SInt b) // a <= b
 { 
  return SIntFunc<SInt>::Dist(a,b); 
 }

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
SInt IntMovePos(SInt a,UInt delta)
 {
  return SIntFunc<SInt>::MovePos(a,delta);
 }

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
SInt IntMoveNeg(SInt a,UInt delta)
 {
  return SIntFunc<SInt>::MoveNeg(a,delta);
 }

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
SInt IntMove(SInt a,SInt e,UInt delta)
 {
  return SIntFunc<SInt>::Move(a,e,delta);
 }

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
UInt IntAbs(SInt a,SInt b)
 { 
  return (a<=b)?IntDist<SInt,UInt>(a,b):IntDist<SInt,UInt>(b,a); 
 }

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
UInt IntAbs(SInt a)
 { 
  return IntAbs<SInt,UInt>(a,0); 
 }

/* functions */

 //
 // Can be substituted to provide checked operations.
 //

template <class SInt>
SInt IntAdd(SInt a,SInt b) { return a+b; } // may overflow

template <class SInt>
SInt IntSub(SInt a,SInt b) { return a-b; } // may overflow

template <class SInt>
SInt IntMul(SInt a,SInt b) { return a*b; } // may overflow

template <class SInt>
SInt IntDiv(SInt a,SInt b) { return a/b; } // may crush

 //
 // Can be substituted to provide proper semantic.
 //

template <class SInt>
constexpr SInt IntLShift(SInt a,unsigned s) { return a<<s; } // may overflow , UB for some arguments must be removed, operates as ASL

template <class SInt>
constexpr SInt IntRShift(SInt a,unsigned s) { return a>>s; } // US for some arguments must be removed, operates as ASR

template <class SInt>
constexpr SInt IntMask(SInt a,SInt mask) { return a&mask; } 

/* sint16 functions */

inline sint16 From32To16(sint32 x) { IntGuard( x>=-32768 && x<=32767 ); return (sint16)x; }

inline sint16 IntAdd(sint16 a,sint16 b) { return From32To16(sint32(a)+sint32(b)); }

inline sint16 IntSub(sint16 a,sint16 b) { return From32To16(sint32(a)-sint32(b)); }

inline sint16 IntMul(sint16 a,sint16 b) { return From32To16(sint32(a)*sint32(b)); }

inline sint16 IntDiv(sint16 a,sint16 b) { IntGuard( b!=0 ); return From32To16(sint32(a)/sint32(b)); }

} // namespace Video
} // namespace CCore
 
#endif
 

