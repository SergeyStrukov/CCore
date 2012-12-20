/* GCDConst.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.03
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_algon_GCDConst_h
#define CCore_inc_algon_GCDConst_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Algon {

/* classes */

template <class UInt,UInt A,UInt B,bool AisNull=( A==0 )> struct Euclid;

template <class UInt,UInt A,UInt B> struct GCDConst;

template <class UInt,UInt A,UInt B> struct LCMConst;

/* struct Euclid<UInt,UInt A,UInt B,bool AisNull> */

template <class UInt,UInt A,UInt B>
struct Euclid<UInt,A,B,true> 
 {
  static constexpr UInt Result() { return B; }
 };

template <class UInt,UInt A,UInt B>
struct Euclid<UInt,A,B,false> : Euclid<UInt,(B%A),A> {};

/* struct GCDConst<UInt,UInt A,UInt B> */

template <class UInt,UInt A,UInt B>
struct GCDConst
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::Algon::GCDConst<UInt> : UInt must be an unsigned integral type");

  static constexpr UInt Result() { return Euclid<UInt,A,B>::Result(); }
 };
 
/* struct LCMConst<UInt,UInt A,UInt B> */

template <class UInt,UInt A,UInt B>
struct LCMConst
 {
  static constexpr UInt Result() { return (A/GCDConst<UInt,A,B>::Result())*B; }
 };
 
} // namespace Algon
} // namespace CCore
 
#endif
 

