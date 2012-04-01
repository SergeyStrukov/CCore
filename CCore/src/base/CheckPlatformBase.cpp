/* CheckPlatformBase.cpp */ 
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
 
#include <CCore/inc/base/PlatformBase.h>
 
namespace CCore {

/* internal */ 

namespace Private_PlatformBase {

/* classes */

template <class UInt,UInt Val=UInt(-1),bool is_one=(Val==1)> struct BitOf;

/* struct BitOf<UInt,UInt Val,bool is_one> */

template <class UInt,UInt Val>
struct BitOf<UInt,Val,false>
 {
  enum RetType { Ret = 1+BitOf<UInt,(Val>>1)>::Ret };
 };
 
template <class UInt,UInt Val>
struct BitOf<UInt,Val,true>
 {
  enum RetType { Ret = 1 };
 };
 
} // namespace Private_PlatformBase
 
using namespace Private_PlatformBase; 

/* asserts */
 
static_assert( std::is_same<uint8,unsigned char>::value ,"CCore::uint8 : must be unsigned char");

static_assert( BitOf<uint8 >::Ret== 8 ,"CCore::uint8 : broken definition");
static_assert( BitOf<uint16>::Ret==16 ,"CCore::uint16 : broken definition");
static_assert( BitOf<uint32>::Ret==32 ,"CCore::uint32 : broken definition");
static_assert( BitOf<uint64>::Ret==64 ,"CCore::uint64 : broken definition");

static_assert( BitOf<unsigned char     >::Ret==Bits::unsigned_char      ,"CCore::Bits::unsigned_char : broken definition");
static_assert( BitOf<unsigned short    >::Ret==Bits::unsigned_short     ,"CCore::Bits::unsigned_short : broken definition");
static_assert( BitOf<unsigned int      >::Ret==Bits::unsigned_int       ,"CCore::Bits::unsigned_int : broken definition");
static_assert( BitOf<unsigned long     >::Ret==Bits::unsigned_long      ,"CCore::Bits::unsigned_long : broken definition");
static_assert( BitOf<unsigned long long>::Ret==Bits::unsigned_long_long ,"CCore::Bits::unsigned_long_long : broken definition");

static_assert( BitOf<ulen>::Ret>=BitOf<std::size_t>::Ret ,"CCore::ulen : broken definition");

static_assert( MaxBitLen>=BitOf<unsigned long long>::Ret ,"CCore::MaxBitLen : broken definition");

} // namespace CCore
 

