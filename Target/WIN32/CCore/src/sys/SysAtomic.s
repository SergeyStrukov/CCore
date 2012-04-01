# SysAtomic.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 1.02
#
#  Tag: Target/WIN32
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2010 Sergey Strukov. All rights reserved.
#
#-----------------------------------------------------------------------------------------

        .text
        
        .global __ZN5CCore3Sys6Atomic3SetEPVjj
        .global __ZN5CCore3Sys6Atomic3AddEPVjj
        .global __ZN5CCore3Sys6Atomic6TrySetEPVjjj
        
        .p2align 4,,15
        
__ZN5CCore3Sys6Atomic3SetEPVjj:      # CCore::Sys::Atomic::Set
        
        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %ecx
        movl    12(%ebp), %eax
        
        xchgl   %eax, (%ecx)  
        
        popl    %ebp
        ret
        
        .p2align 4,,15
        
__ZN5CCore3Sys6Atomic3AddEPVjj:      # CCore::Sys::Atomic::Add
        
        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %ecx
        movl    12(%ebp), %eax
        
   lock xaddl   %eax, (%ecx)
        
        popl    %ebp
        ret
        
        .p2align 4,,15
        
__ZN5CCore3Sys6Atomic6TrySetEPVjjj:  # CCore::Sys::Atomic::TrySet
        
        pushl   %ebp
        movl    %esp, %ebp
        
        movl     8(%ebp), %ecx
        movl    12(%ebp), %eax
        movl    16(%ebp), %edx
        
   lock cmpxchgl   %edx, (%ecx)
        
        popl    %ebp
        ret




