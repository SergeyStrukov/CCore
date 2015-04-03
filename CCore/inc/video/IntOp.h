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

/* functions */

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
inline UInt IntDist(SInt a,SInt b) // a <= b
 { 
  return SIntFunc<SInt>::Dist(a,b); 
 }

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
inline SInt IntMove(SInt a,SInt e,UInt delta)
 {
  return SIntFunc<SInt>::Move(a,e,delta);
 }

template <class SInt,class UInt=typename Meta::SIntToUInt<SInt>::UType>
inline UInt IntAbs(SInt a,SInt b) { return (a<=b)?IntDist<SInt,UInt>(a,b):IntDist<SInt,UInt>(b,a); }

/* functions */

 //
 // Can be substituted to provide checked operations.
 //

inline void IntGuard(bool /* cond */) { /* do nothing */ }

template <class SInt>
inline SInt IntAdd(SInt a,SInt b) { return a+b; } // may overflow

template <class SInt>
inline SInt IntSub(SInt a,SInt b) { return a-b; } // may overflow

template <class SInt>
inline SInt IntMul(SInt a,SInt b) { return a*b; } // may overflow

template <class SInt>
inline SInt IntDiv(SInt a,SInt b) { return a/b; } // may crush

template <class SInt>
inline SInt IntLShift(SInt a,unsigned s) { return a<<s; } // may overflow , UB for some arguments must be removed, operates as ASL

template <class SInt>
inline SInt IntRShift(SInt a,unsigned s) { return a>>s; } // US for some arguments must be removed, operates as ASR

} // namespace Video
} // namespace CCore
 
#endif
 

