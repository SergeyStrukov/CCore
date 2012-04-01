/* DefaultValue.h */ 
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

#ifndef CCore_inc_gadget_DefaultValue_h
#define CCore_inc_gadget_DefaultValue_h
 
namespace CCore {

/* classes */ 

struct DefaultValue;

template <class T> struct DefaultInitObject; 

/* struct DefaultValue */ 

struct DefaultValue
 {
  constexpr DefaultValue() {}
   
  template <class T>
  constexpr operator T() const { return T(); }
 };

/* struct DefaultInitObject<T> */

template <class T> 
struct DefaultInitObject
 {
  T obj;
   
  DefaultInitObject() : obj() {}
 };

} // namespace CCore
 
#endif
 

