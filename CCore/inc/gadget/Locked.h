/* Locked.h */ 
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

#ifndef CCore_inc_gadget_Locked_h
#define CCore_inc_gadget_Locked_h

namespace CCore {

/* classes */

template <class Mutex,class T> class Locked;

/* class Locked<Mutex,T> */

template <class Mutex,class T>
class Locked : Mutex::Lock
 {
   T &obj;
 
  public:
 
   Locked(Mutex &mutex,T &obj_) : Mutex::Lock(mutex),obj(obj_) {}
   
   ~Locked() {}
   
   // object ptr
   
   T * getPtr() const { return &obj; }
   
   T * operator -> () const { return &obj; }
   
   T & operator * () const { return obj; }
 };

} // namespace CCore
 
#endif
 

