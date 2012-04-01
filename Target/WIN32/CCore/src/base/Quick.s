# Quick.s
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
        
        .global __ZN5CCore5Quick9ScanLSBitEj
        .global __ZN5CCore5Quick9ScanMSBitEj
        .global __ZN5CCore5Quick10ByteSwap16Et
        .global __ZN5CCore5Quick10ByteSwap32Ej
        .global __ZN5CCore5Quick10ByteSwap64Ey
        
        .p2align 4,,15
        
__ZN5CCore5Quick9ScanLSBitEj:    #  CCore::Quick::ScanLSBit
        
        pushl   %ebp
        movl    %esp, %ebp
        
        bsfl    8(%esp), %eax
        
        popl    %ebp
        ret
        
        .p2align 4,,15
        
__ZN5CCore5Quick9ScanMSBitEj:    #  CCore::Quick::ScanMSBit
        
        pushl   %ebp
        movl    %esp, %ebp
        
        bsrl    8(%esp), %eax
        
        popl    %ebp
        ret
        
        .p2align 4,,15
        
__ZN5CCore5Quick10ByteSwap16Et:  #  CCore::Quick::ByteSwap16
        
        pushl   %ebp
        movl    %esp, %ebp
        
        movl    8(%esp), %eax
        xchgb   %al, %ah
        
        popl    %ebp
        ret
        
        .p2align 4,,15
        
__ZN5CCore5Quick10ByteSwap32Ej:  #  CCore::Quick::ByteSwap32
        
        pushl   %ebp
        movl    %esp, %ebp
        
        movl    8(%esp), %eax
        bswapl  %eax
        
        popl    %ebp
        ret
        
        .p2align 4,,15
        
__ZN5CCore5Quick10ByteSwap64Ey:  #  CCore::Quick::ByteSwap64
        
        pushl   %ebp
        movl    %esp, %ebp
        
        movl    8(%esp), %edx
        bswapl  %edx
        movl    12(%esp), %eax
        bswapl  %eax
        
        popl    %ebp
        ret
        
