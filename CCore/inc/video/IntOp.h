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

inline unsigned IntDist(int a,int b) // a <= b
 { 
  return SIntFunc<int>::Dist(a,b); 
 }

inline int IntMove(int a,int e,unsigned delta)
 {
  return SIntFunc<int>::Move(a,e,delta);
 }

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
inline SInt IntLShift(SInt a,unsigned s) { return a<<s; } // may overflow , UB for some arguments

template <class SInt>
inline SInt IntRShift(SInt a,unsigned s) { return a>>s; } // USB for some arguments

} // namespace Video
} // namespace CCore
 
#endif
 

