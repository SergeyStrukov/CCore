/* RefVal.h */ 
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

#ifndef CCore_inc_video_RefVal_h
#define CCore_inc_video_RefVal_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Video {

/* classes */

template <class T> class RefVal;

/* class RefVal<T> */

template <class T> 
class RefVal
 {
   T *ptr;
   T val;
   
  public:
   
   RefVal() : ptr(0),val() {}

   RefVal(const T &val_) : ptr(0),val(val_) {}
   
   T operator + () const { return ptr?(*ptr):val; }
   
   const T & get() const { if( ptr ) return *ptr; return val; }
   
   T & takeVal() { return val; }
   
   void bind(T &obj) { ptr=&obj; }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

