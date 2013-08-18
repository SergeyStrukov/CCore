# IntelCPUID.s
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

#-----------------------------------------------------------------------------------------

        .global _ZN5CCore7Crypton11IntelCPUID1C1Ev

        .p2align 4,,15

_ZN5CCore7Crypton11IntelCPUID1C1Ev:

#
# CCore::Crypton::IntelCPUID1::IntelCPUID1()
#

        movq   %rcx, %r8
        movq   %rbx, %r9 
        
        movl    $1, %eax
        cpuid
        
        movl    %eax,   (%r8)
        movl    %ebx,  4(%r8)
        movl    %ecx,  8(%r8)
        movl    %edx, 12(%r8)
        
        movq    %r9, %rbx
        
        ret
    
#-----------------------------------------------------------------------------------------

