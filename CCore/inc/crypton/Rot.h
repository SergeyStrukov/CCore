/* Rot.h */ 
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

#ifndef CCore_inc_crypton_Rot_h
#define CCore_inc_crypton_Rot_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Crypton {

/* Ror...() */ 

template <class UInt,unsigned UIntBits>
UInt Ror_gen(UInt a,unsigned n) // 0 < n < UIntBits 
 {
  return UInt( (a>>n)|(a<<(UIntBits-n)) );
 }
 
inline uint8 Ror8(uint8 a,unsigned n) { return Ror_gen<uint8,8>(a,n); }
 
inline uint16 Ror16(uint16 a,unsigned n) { return Ror_gen<uint16,16>(a,n); }
 
inline uint32 Ror32(uint32 a,unsigned n) { return Ror_gen<uint32,32>(a,n); }
 
inline uint64 Ror64(uint64 a,unsigned n) { return Ror_gen<uint64,64>(a,n); }

/* Rol...() */

template <class UInt,unsigned UIntBits>
UInt Rol_gen(UInt a,unsigned n) // 0 < n < UIntBits
 {
  return UInt( (a>>(UIntBits-n))|(a<<n) );
 }
 
inline uint8 Rol8(uint8 a,unsigned n) { return Rol_gen<uint8,8>(a,n); }
 
inline uint16 Rol16(uint16 a,unsigned n) { return Rol_gen<uint16,16>(a,n); }
 
inline uint32 Rol32(uint32 a,unsigned n) { return Rol_gen<uint32,32>(a,n); }

inline uint64 Rol64(uint64 a,unsigned n) { return Rol_gen<uint64,64>(a,n); }

} // namespace Crypton
} // namespace CCore
 
#endif
 

