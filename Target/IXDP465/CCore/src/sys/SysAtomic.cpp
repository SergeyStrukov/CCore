/* SysAtomic.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysAtomic.h>
 
namespace CCore {
namespace Sys {

/* struct Atomic */ 

#if 0

 // Fake code

Atomic::Type Atomic::Set(volatile Type *atomic,Type value) noexcept
 {
  Type ret=*atomic;
  
  *atomic=value;
 
  return ret;
 }
 
Atomic::Type Atomic::Add(volatile Type *atomic,Type value) noexcept
 {
  Type ret=*atomic;
  
  *atomic+=value;
 
  return ret;
 }
 
Atomic::Type Atomic::TrySet(volatile Type *atomic,Type old_val,Type new_val) noexcept
 {
  Type ret=*atomic;
  
  if( ret==old_val ) *atomic=new_val;
  
  return ret;
 }
 
#endif
  
} // namespace Sys
} // namespace CCore
 

