/* SysAtomic.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
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

Atomic::Type Atomic::Set(volatile Type *atomic,Type value) noexcept
 {
  asm("movl    8(%ebp), %ecx"); 
  asm("movl   12(%ebp), %eax");
  
  asm("xchgl  %eax, (%ecx)  ");
  
  asm("movl   %eax, 12(%ebp)");
  
  return value;
 }
 
Atomic::Type Atomic::Add(volatile Type *atomic,Type value) noexcept
 {
  asm("movl    8(%ebp), %ecx  "); 
  asm("movl   12(%ebp), %eax  ");
  
  asm("lock xaddl %eax, (%ecx)");
  
  asm("movl   %eax, 12(%ebp)  ");

  return value;
 }
 
Atomic::Type Atomic::TrySet(volatile Type *atomic,Type old_val,Type new_val) noexcept
 {
  asm("movl    8(%ebp), %ecx      "); 
  asm("movl   12(%ebp), %eax      ");
  asm("movl   16(%ebp), %edx      ");
  
  asm("lock cmpxchgl  %edx, (%ecx)");
  
  asm("movl   %eax, 12(%ebp)      ");
  
  return old_val;
 }
 
#endif
 
} // namespace Sys
} // namespace CCore
 

