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

inline int IntAdd(int a,int b) { return a+b; } // may overflow

inline int IntSub(int a,int b) { return a-b; } // may overflow

inline int IntMul(int a,int b) { return a*b; } // may overflow

} // namespace Video
} // namespace CCore
 
#endif
 

