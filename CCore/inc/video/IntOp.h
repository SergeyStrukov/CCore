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

inline uint16 IntDist(sint16 a,sint16 b) // a <= b
 { 
  return SIntFunc<sint16>::Dist(a,b); 
 }

inline sint16 IntMove(sint16 a,int e,uint16 delta)
 {
  return SIntFunc<sint16>::Move(a,e,delta);
 }

inline uint16 IntAbs(sint16 a,sint16 b) { return (a<=b)?IntDist(a,b):IntDist(b,a); }

inline uint32 IntDist(sint32 a,sint32 b) // a <= b
 { 
  return SIntFunc<sint32>::Dist(a,b); 
 }

inline sint32 IntMove(sint32 a,int e,uint32 delta)
 {
  return SIntFunc<sint32>::Move(a,e,delta);
 }

inline uint32 IntAbs(sint32 a,sint32 b) { return (a<=b)?IntDist(a,b):IntDist(b,a); }

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
inline SInt IntLShift(SInt a,unsigned s) { return a<<s; } // may overflow , UB for some arguments must be removed, operates as ASL

template <class SInt>
inline SInt IntRShift(SInt a,unsigned s) { return a>>s; } // US for some arguments must be removed, operates as ASR

} // namespace Video
} // namespace CCore
 
#endif
 

