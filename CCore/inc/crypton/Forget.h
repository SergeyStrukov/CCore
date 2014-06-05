/* Forget.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_Forget_h
#define CCore_inc_crypton_Forget_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Crypton {

/* functions */

template <class T>
void PrepareForget(T &obj)
 {
  obj=T();
 }

template <class T,ulen Len>
void PrepareForget(T (&obj)[Len])
 {
  for(ulen i=0; i<Len ;i++) PrepareForget(obj[i]);
 }

template <class T>
void Forget(T &obj)
 {
  PrepareForget(obj);
  
  OptimizeBarrier(&obj,sizeof obj);
 }

} // namespace Crypton
} // namespace CCore
 
#endif
 

