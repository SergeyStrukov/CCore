# IntelCPUID.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 1.05
#
#  Tag: Target/WIN32
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

        .global __ZN5CCore7Crypton11IntelCPUID1C1Ev

        .p2align 4,,15

__ZN5CCore7Crypton11IntelCPUID1C1Ev:

#
# CCore::Crypton::IntelCPUID1::IntelCPUID1()
#
        
        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   %ebx
        pushl   %esi
        
        movl    16(%esp), %esi
        
        movl    $1, %eax
        cpuid
        
        movl    %eax,   (%esi)
        movl    %ebx,  4(%esi)
        movl    %ecx,  8(%esi)
        movl    %edx, 12(%esi)
        
        popl    %esi
        popl    %ebx
        
        popl    %ebp
        ret
    
#-----------------------------------------------------------------------------------------

