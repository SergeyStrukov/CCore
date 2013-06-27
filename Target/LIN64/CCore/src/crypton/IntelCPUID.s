# IntelCPUID.s
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

#-----------------------------------------------------------------------------------------

        .global _ZN5CCore7Crypton11IntelCPUID1C1Ev

        .p2align 4,,15

_ZN5CCore7Crypton11IntelCPUID1C1Ev:

#
# CCore::Crypton::IntelCPUID1::IntelCPUID1()
#

        pushq   %rbx  
        
        movl    $1, %eax
        cpuid
        
        movl    %eax,   (%rdi)
        movl    %ebx,  4(%rdi)
#        orl     $0x42000000, %ecx
        movl    %ecx,  8(%rdi)
        movl    %edx, 12(%rdi)
        
        popq    %rbx
        
        ret
    
#-----------------------------------------------------------------------------------------

