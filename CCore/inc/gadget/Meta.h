/* Meta.h */ 
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

#ifndef CCore_inc_gadget_Meta_h
#define CCore_inc_gadget_Meta_h

#include <CCore/inc/base/PlatformBase.h>
 
namespace CCore {
namespace Meta {

/* classes */

template <class T,bool enable> struct Warning;

struct Empty;

template <class T> struct DefType;

template <class SUInt,SUInt Val> struct DefConst;

struct True;

struct False;

template <bool Cond> struct If; 
 
template <bool Cond> struct IfNot;

template <bool Cond,class T1,class T2> struct ImpSelect;

template <bool Cond,template <class> class F,class T> struct BuildIf;

template <class T,class ProbeSet> struct Has;

template <class ... TT> struct TypeListLen;

template <class ... TT> struct IndexOf;

template <class R> struct ImpRangeObjType;

template <class T> struct IsSInt;

template <class T> struct IsUInt;

template <class T> struct IsSUInt;

template <class T> struct SIntToUInt_extra;

template <class SInt> struct SIntToUInt;

template <class T> struct PromoteUInt_extra;

template <class UInt> struct PromoteUInt;

template <class T> struct PromoteSInt_extra;

template <class SInt> struct PromoteSInt;

template <class T> struct UIntBits_extra;

template <class UInt> struct UIntBits;

template <class UInt> struct HexWidth;

/* struct Warning<T,bool enable> */

template <class T>
struct Warning<T,true>
 {
  static constexpr bool NotUsed(int notused=0) { return false; }
 };

template <class T>
struct Warning<T,false>
 {
  static constexpr bool NotUsed(int=0) { return false; }
 };

/* struct Empty */ 

struct Empty
 {
 };
 
/* struct DefType<T> */ 

template <class T> 
struct DefType
 {
  typedef T Ret;
 };
 
/* struct DefConst<SUInt,SUInt Val> */ 

template <class SUInt,SUInt Val> 
struct DefConst
 {
  enum RetType : SUInt { Ret = Val };
 };

/* struct True */

struct True 
 {
  enum RetType { Ret = true };
 };

/* struct False */

struct False 
 {
  enum RetType { Ret = false };
 };

/* struct If<bool Cond> */ 

template <> 
struct If<true> : True {}; 
 
template <> 
struct If<false> : False {};

/* struct IfNot<bool Cond> */ 

template <> 
struct IfNot<true> : False {}; 
 
template <> 
struct IfNot<false> : True {};

/* struct ImpSelect<bool Cond,T1,T2> */

template <class T1,class T2> 
struct ImpSelect<true,T1,T2>
 {
  typedef T1 Ret;
 };
 
template <class T1,class T2> 
struct ImpSelect<false,T1,T2>
 {
  typedef T2 Ret;
 };

/* type Select<bool Cond,T1,T2> */

template <bool Cond,class T1,class T2>
using Select = typename ImpSelect<Cond,T1,T2>::Ret ;

/* struct BuildIf<bool Cond,F<T>,T> */

template <template <class> class F,class T> 
struct BuildIf<true,F,T> : F<T> {};

template <template <class> class F,class T>
struct BuildIf<false,F,T> {};

/* struct Has<T,ProbeSet> */

template <class T,class ProbeSet> 
struct Has
 {
  enum RetType { Ret = ProbeSet::template Probe<T>(0) };
 };

/* type EnableIf<bool Cond,RetType> */
 
template <bool Cond,class RetType=int>
using EnableIf = typename Select<Cond, DefType<RetType> , Empty >::Ret ;

/* struct TypeListLen<TT> */ 
 
template <class ... TT> 
struct TypeListLen : DefConst<unsigned,( sizeof...(TT) )> {};

/* struct IndexOf<TT> */

template <class T>
struct IndexOf<T> {};

template <class T,class ... TT>
struct IndexOf<T,T,TT...> : DefConst<unsigned,1> {};

template <class T,class S,class ... TT>
struct IndexOf<T,S,TT...> : DefConst<unsigned,( 1+IndexOf<T,TT...>::Ret )> {};

/* struct ImpRangeObjType<R> */
 
template <class R> 
struct ImpRangeObjType
 {
  static R & GetR();
  
  typedef typename std::remove_reference<decltype( *GetR() )>::type Ret;
 };

/* type RangeObjType<R> */

template <class R>
using RangeObjType = typename ImpRangeObjType<R>::Ret ;
 
/* struct IsSInt<T> */

template <class T> 
struct IsSInt              : If<( ExtraInt::Prop<T>::IsSigned )> {};

template <> 
struct IsSInt<signed char> : True {};

template <> 
struct IsSInt<short>       : True {};

template <> 
struct IsSInt<int>         : True {};

template <> 
struct IsSInt<long>        : True {};

template <> 
struct IsSInt<long long>   : True {};

template <> 
struct IsSInt<char>        : If<( char(-1)<0 )> {};

/* struct IsUInt<T> */

template <class T> 
struct IsUInt                     : If<( ExtraInt::Prop<T>::IsUnsigned )> {};

template <> 
struct IsUInt<unsigned char>      : True {};

template <> 
struct IsUInt<unsigned short>     : True {};

template <> 
struct IsUInt<unsigned>           : True {};

template <> 
struct IsUInt<unsigned long>      : True {};

template <> 
struct IsUInt<unsigned long long> : True {};

template <> 
struct IsUInt<char>               : IfNot<( char(-1)<0 )> {};

/* struct IsSUInt<T> */

template <class T> 
struct IsSUInt : If<( IsSInt<T>::Ret || IsUInt<T>::Ret )> {};

/* struct SIntToUInt_extra<T> */

template <class T>
struct SIntToUInt_extra
 {
  typedef typename ExtraInt::Prop<T>::SType SType;
  typedef typename ExtraInt::Prop<T>::UType UType;
 };

/* struct SIntToUInt<SInt> */ 

template <class T> 
struct SIntToUInt : BuildIf<IsSInt<T>::Ret,SIntToUInt_extra,T> {};

template <> 
struct SIntToUInt<signed char>
 {
  typedef   signed char SType;
  typedef unsigned char UType;
 };

template <> 
struct SIntToUInt<short>
 {
  typedef          short SType;
  typedef unsigned short UType;
 };

template <> 
struct SIntToUInt<int>
 {
  typedef          int SType;
  typedef unsigned int UType;
 };

template <> 
struct SIntToUInt<long>
 {
  typedef          long SType;
  typedef unsigned long UType;
 };

template <> 
struct SIntToUInt<long long>
 {
  typedef          long long SType;
  typedef unsigned long long UType;
 };

template <> 
struct SIntToUInt<char> : Select<( char(-1)<0 ), SIntToUInt<signed char> , Empty > {};

/* struct PromoteUInt_extra<T> */

template <class T> 
struct PromoteUInt_extra
 {
  typedef typename ExtraInt::Prop<T>::PromoteUType Type;
 };

/* struct PromoteUInt<UInt> */

template <class T> 
struct PromoteUInt : BuildIf<IsUInt<T>::Ret,PromoteUInt_extra,T> {};

template <> 
struct PromoteUInt<unsigned char> 
 {
  typedef unsigned int Type;
 };
 
template <> 
struct PromoteUInt<unsigned short> 
 {
  typedef unsigned int Type;
 };                    
 
template <> 
struct PromoteUInt<unsigned int> 
 {
  typedef unsigned int Type;
 };
 
template <> 
struct PromoteUInt<unsigned long> 
 {
  typedef unsigned long Type;
 };
 
template <> 
struct PromoteUInt<unsigned long long> 
 {
  typedef unsigned long long Type;
 };
 
template <> 
struct PromoteUInt<char> : Select<( char(-1)<0 ), Empty , PromoteUInt<unsigned int> > {};

/* struct PromoteSInt_extra<T> */
 
template <class T> 
struct PromoteSInt_extra
 {
  typedef typename ExtraInt::Prop<T>::PromoteSType SType;
  typedef typename ExtraInt::Prop<T>::PromoteUType UType;
 };

/* struct PromoteSInt<SInt> */ 

template <class T>
struct PromoteSInt : BuildIf<IsSInt<T>::Ret,PromoteSInt_extra,T> {};

template <> 
struct PromoteSInt<signed char>
 {
  typedef          int SType;
  typedef unsigned int UType;
 };
 
template <> 
struct PromoteSInt<short>
 {
  typedef          int SType;
  typedef unsigned int UType;
 };
 
template <> 
struct PromoteSInt<int>
 {
  typedef          int SType;
  typedef unsigned int UType;
 };
 
template <> 
struct PromoteSInt<long>
 {
  typedef          long SType;
  typedef unsigned long UType;
 };
 
template <> 
struct PromoteSInt<long long>
 {
  typedef          long long SType;
  typedef unsigned long long UType;
 };
 
template <> 
struct PromoteSInt<char> : Select<( char(-1)<0 ), PromoteSInt<int> , Empty > {};

/* struct UIntBits_extra<T> */
 
template <class T> 
struct UIntBits_extra : DefConst<unsigned,ExtraInt::Prop<T>::Bits> {};

/* struct UIntBits<UInt> */

template <class T> 
struct UIntBits : BuildIf<IsUInt<T>::Ret,UIntBits_extra,T> {};
 
template <>
struct UIntBits<unsigned char> : DefConst<unsigned,Bits::unsigned_char> {};
 
template <>
struct UIntBits<unsigned short> : DefConst<unsigned,Bits::unsigned_short> {};
 
template <>
struct UIntBits<unsigned int> : DefConst<unsigned,Bits::unsigned_int> {};
 
template <>
struct UIntBits<unsigned long> : DefConst<unsigned,Bits::unsigned_long> {};
 
template <>
struct UIntBits<unsigned long long> : DefConst<unsigned,Bits::unsigned_long_long> {};

template <>
struct UIntBits<char> : Select<( char(-1)<0 ), Empty , DefConst<unsigned,Bits::unsigned_char> > {};
 
/* struct HexWidth<UInt> */ 
 
template <class UInt> 
struct HexWidth : DefConst<unsigned,( (UIntBits<UInt>::Ret+3)/4 )> {};
 
} // namespace Meta
} // namespace CCore
 
#endif
 

