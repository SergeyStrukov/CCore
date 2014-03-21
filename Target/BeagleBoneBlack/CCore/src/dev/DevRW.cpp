/* DevRW.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/dev/DevRW.h>
 
namespace CCore {
namespace Dev {

/* functions */ 

#if 0

template <>
uint8 VarGet<uint8>(const void *ptr) noexcept { return *static_cast<const uint8 *>(ptr); }
 
template <>
void VarSet<uint8>(void *ptr,uint8 value) noexcept { *static_cast<uint8 *>(ptr)=value; }
 
template <>
uint16 VarGet<uint16>(const void *ptr) noexcept { return *static_cast<const uint16 *>(ptr); }
 
template <>
void VarSet<uint16>(void *ptr,uint16 value) noexcept { *static_cast<uint16 *>(ptr)=value; }
 
template <>
uint32 VarGet<uint32>(const void *ptr) noexcept { return *static_cast<const uint32 *>(ptr); }
 
template <>
void VarSet<uint32>(void *ptr,uint32 value) noexcept { *static_cast<uint32 *>(ptr)=value; }

#endif
 
} // namespace Dev
} // namespace CCore
 




