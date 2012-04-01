/* UIntSat.h */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_UIntSat_h
#define CCore_inc_gadget_UIntSat_h

#include <CCore/inc/gadget/Len.h>
#include <CCore/inc/gadget/Meta.h>
 
namespace CCore {

/* classes */

template <class UInt> struct UIntSat;

template <class UInt,UInt A,UInt B> struct UIntConstAdd_ok;

template <class UInt,UInt A,UInt B> struct UIntConstSub_ok;

/* struct UIntSat<UInt> */

template <class UInt> 
struct UIntSat
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntSat<UInt> : UInt must be an unsigned integral type");
  
  UInt value;
  bool overflow;
  
  // constructors
  
  constexpr UIntSat() : value(0),overflow(false) {}
  
  constexpr UIntSat(UIntSat<UInt> a,UIntSat<UInt> b)
   : value( (a.value<=UInt(-1)-b.value)?a.value+b.value:UInt(-1) ),
     overflow( a.overflow || b.overflow || (a.value>UInt(-1)-b.value) )
   {
   }
  
  template <class T,class=Meta::EnableIf<Meta::IsUInt<T>::Ret> >
  constexpr UIntSat(T value_) 
   : value( (value_<=UInt(-1))?value_:UInt(-1) ),
     overflow( value_>UInt(-1) ) 
   {
   }
  
  // methods
  
  bool operator ! () const { return overflow; }
  
  friend constexpr UIntSat<UInt> operator + (UIntSat<UInt> a,UIntSat<UInt> b) { return UIntSat<UInt>(a,b); }
  
  UIntSat<UInt> operator += (UIntSat<UInt> b) { *this=*this+b; return *this; }
  
  bool operator < (UInt lim) const { return !overflow && value<lim ; }
  
  bool operator <= (UInt lim) const { return !overflow && value<=lim ; }
 };

/* struct UIntConstAdd_ok<UInt,UInt A,UInt B> */

template <class UInt,UInt A,UInt B> 
struct UIntConstAdd_ok
 {
  enum RetType : UInt { Ret = A+B };
 };

/* type UIntConstAdd<UInt,UInt A,UInt B> */

template <class UInt,UInt A,UInt B> 
using UIntConstAdd = Meta::Select<( A<=UInt(-1)-B ), UIntConstAdd_ok<UInt,A,B> , Meta::Empty > ;

/* struct UIntConstSub_ok<UInt,UInt A,UInt B> */

template <class UInt,UInt A,UInt B> 
struct UIntConstSub_ok
 {
  enum RetType : UInt { Ret = A-B };
 };

/* type UIntConstSub<UInt,UInt A,UInt B> */

template <class UInt,UInt A,UInt B> 
using UIntConstSub = Meta::Select<( A>=B ), UIntConstSub_ok<UInt,A,B> , Meta::Empty > ;

/* type ULenSat */

typedef UIntSat<ulen> ULenSat;

} // namespace CCore
 
#endif
 

