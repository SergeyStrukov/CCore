/* DDL2MapTypes.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl2_DDL2MapTypes_h
#define CCore_inc_ddl2_DDL2MapTypes_h

#include <CCore/inc/AnyPtr.h>

#include <CCore/inc/ddl2/DDL2PlatformTypes.h>
 
namespace CCore {
namespace DDL2 {

/* classes */

struct MapText;

template <class T> struct MapPtr;

template <class T> struct MapRange;

template <class ... TT> struct MapPolyPtr;

/* struct MapText */

struct MapText
 {
  // data
  
  char *ptr;
  ulen len;
  
  // methods
  
  StrLen getStr() const { return StrLen(ptr,len); }
  
  // cast
  
  operator StrLen() const { return getStr(); }
 };

/* struct MapPtr<T> */

template <class T> 
struct MapPtr // layout-compatible with MapPtr<char>
 {
  // data
  
  void *ptr;
  
  // object ptr
  
  void * operator + () const { return ptr; }
  
  bool operator ! () const { return !ptr; }
  
  T * getPtr() const { return static_cast<T *>(ptr); }
  
  T & operator * () const { return *getPtr(); }
  
  T * operator -> () const { return getPtr(); }
  
  // cast
  
  operator T * () const { return getPtr(); }
 };

/* struct MapRange<T> */

template <class T> 
struct MapRange // layout-compatible with MapRange<char>
 {
  // data
  
  void *ptr;
  ulen len;
  
  // methods
  
  PtrLen<T> getRange() const { return Range(static_cast<T *>(ptr),len); }
  
  // cast
  
  operator PtrLen<T> () const { return getRange(); }
 };

/* struct MapPolyPtr<TT> */

template <class ... TT> 
struct MapPolyPtr // layout-compatible with MapPolyPtr<>
 {
  // data
  
  void *ptr;
  ulen type;
  
  // methods
  
  using AnyPtrType = AnyPtr<TT...> ;
  
  template <class T>
  static AnyPtrType CastTo(void *ptr)
   {
    return AnyPtrType(static_cast<T *>(ptr));
   }
  
  AnyPtrType getPtr() const
   {
    if( type && type<=Meta::TypeListLen<TT...>::Ret )
      {
       using FuncType = AnyPtrType (*) (void *ptr) ; 
      
       static const FuncType Table[]={ CastTo<TT>... };
       
       return Table[type-1](ptr);
      }
     
    return Null; 
   }

  // cast
  
  operator AnyPtrType() const { return getPtr(); }
 };

} // namespace DDL2
} // namespace CCore
 
#endif
 

