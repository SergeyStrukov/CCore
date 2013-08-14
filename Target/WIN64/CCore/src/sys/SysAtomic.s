# SysAtomic.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 1.06
#
#  Tag: Target/WIN64
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
        
        movq    %rdx, %rax
        xchgq   %rax, (%rcx)
        
        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore3Sys6Atomic3AddEPVmm:      # CCore::Sys::Atomic::Add
        
        movq    %rdx, %rax
   lock xaddq   %rax, (%rcx)
        
        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore3Sys6Atomic6TrySetEPVmmm:  # CCore::Sys::Atomic::TrySet
        
        movq     %rdx, %rax
   lock cmpxchgq %r8 , (%rcx)  
        
        ret

#-----------------------------------------------------------------------------------------



