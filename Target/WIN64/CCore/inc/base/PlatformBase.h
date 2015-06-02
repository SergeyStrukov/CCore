/* PlatformBase.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_base_PlatformBase_h
#define CCore_inc_base_PlatformBase_h

/* init priority */ 

#define CCORE_INITPRI_0 __attribute__((init_priority(101)))
#define CCORE_INITPRI_1 __attribute__((init_priority(102)))
#define CCORE_INITPRI_2 __attribute__((init_priority(103)))
#define CCORE_INITPRI_3 __attribute__((init_priority(104)))

/* inlining disabler */ 

#define CCORE_NOINLINE __attribute__((noinline))

/* includes */ 

#include <cstddef>
#include <type_traits>
#include <initializer_list>
#include <utility>

/* restrict */ 

#define restrict __restrict

/* namespace CCore */ 

namespace CCore {

/* consts */ 

const bool EnableNoExcept = true ;

const bool IsLEPlatform  = true ;

const unsigned MaxBitLen = 64   ;

const unsigned MaxAlign  = 16   ;

/* types */ 

typedef unsigned long       ulen   ;
typedef unsigned long       uptr   ;
 
typedef unsigned char       uint8  ;
typedef unsigned short      uint16 ;
typedef unsigned int        uint32 ;
typedef unsigned long       uint64 ;

typedef signed char         sint8  ;
typedef signed short        sint16 ;
typedef signed int          sint32 ;
typedef signed long         sint64 ;

/* consts */ 

const ulen DefaultPacketCount = 50000 ;

const unsigned DefaultEventElementCount = 10000 ;

/* namespace Bits */ 

namespace Bits {

const unsigned unsigned_char      =  8 ;
const unsigned unsigned_short     = 16 ;
const unsigned unsigned_int       = 32 ;
const unsigned unsigned_long      = 64 ;
const unsigned unsigned_long_long = 64 ;

} // namespace Bits

/* namespace ExtraInt */

namespace ExtraInt {

/* classes */

template <class T> struct Prop;

/* struct Prop<T> */

template <class T> 
struct Prop 
 {
  enum 
   {
    IsSigned   = false,
    IsUnsigned = false
   };
 };

// 
// template <> 
// struct Prop<???> 
//  {
//   enum 
//    {
//     IsSigned   = true,
//     IsUnsigned = false,
//    };
//   
//   typedef ??? SType;
//   typedef ??? UType;
//   
//   typedef ??? PromoteSType;
//   typedef ??? PromoteUType;
//  };
// 
// template <> 
// struct Prop<???> 
//  {
//   enum 
//    {
//     IsSigned   = false,
//     IsUnsigned = true,
//       
//     Bits = ???  
//    };
//   
//   typedef ??? PromoteUType;
//  };
// 

} // namespace ExtraInt

/* namespace Meta */

namespace Meta {

/* classes */

template <class T> struct HasNoDtor;

template <class T> struct HasNoThrowDefault;

template <class T> struct HasNoThrowCopy;

template <class UInt> struct DoubleUInt;

/* struct HasNoDtor<T> */

template <class T> 
struct HasNoDtor
 {
  enum RetType { Ret = std::is_trivially_destructible<T>::value }; 
 };

/* struct HasNoThrowDefault<T> */

template <class T>
struct HasNoThrowDefault
 {
  enum RetType { Ret = !std::is_default_constructible<T>::value || 
                        std::is_nothrow_default_constructible<T>::value 
               };
 };

/* struct HasNoThrowCopy<T> */

template <class T>
struct HasNoThrowCopy
 {
  enum RetType { Ret = !std::is_copy_constructible<T>::value ||
                        std::is_nothrow_copy_constructible<T>::value 
               };
 };

/* struct DoubleUInt<UInt> */

template <class UInt> 
struct DoubleUInt
 {
  typedef void Ret;
 };
 
template <> 
struct DoubleUInt<uint8>
 {
  typedef uint16 Ret;
 };
 
template <> 
struct DoubleUInt<uint16>
 {
  typedef uint32 Ret;
 };
 
template <> 
struct DoubleUInt<uint32>
 {
  typedef uint64 Ret;
 };

} // namespace Meta

/* Used() */ 

template <class T> void Used(T &) {}

/* OptimizeBarrier() */
 
void OptimizeBarrier(void *ptr,ulen len);

} // namespace CCore
 
#endif
 
