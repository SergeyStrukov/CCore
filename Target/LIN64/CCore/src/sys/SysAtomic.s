# SysAtomic.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 1.05
#
#  Tag: Target/LIN64
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2013 Sergey Strukov. All rights reserved.
#
#-----------------------------------------------------------------------------------------

        .text
        
        .global _ZN5CCore3Sys6Atomic3SetEPVmm
        .global _ZN5CCore3Sys6Atomic3AddEPVmm
        .global _ZN5CCore3Sys6Atomic6TrySetEPVmmm
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore3Sys6Atomic3SetEPVmm:      # CCore::Sys::Atomic::Set
        
        movq    %rsi, %rax
        xchgq   %rax, (%rdi)
        
        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore3Sys6Atomic3AddEPVmm:      # CCore::Sys::Atomic::Add
        
        movq    %rsi, %rax
   lock xaddq   %rax, (%rdi)
        
        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore3Sys6Atomic6TrySetEPVmmm:  # CCore::Sys::Atomic::TrySet
        
        movq     %rsi, %rax
   lock cmpxchgq %rdx, (%rdi)  
        
        ret

#-----------------------------------------------------------------------------------------



