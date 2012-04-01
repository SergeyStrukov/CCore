/* Lock.h */ 
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

#ifndef CCore_inc_gadget_Lock_h
#define CCore_inc_gadget_Lock_h

#include <CCore/inc/gadget/NoCopy.h>
 
namespace CCore {

/* classes */ 

template <class T> class LockObject;

/* class LockObject<T> */ 
 
template <class T> 
class LockObject : NoCopy
 {
   T &obj;
   
  public:
  
   explicit LockObject(T &obj_) : obj(obj_) { obj_.lock(); }
   
   ~LockObject() { obj.unlock(); }
 };
 
} // namespace CCore
 
#endif
 

