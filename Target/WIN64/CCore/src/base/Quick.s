# Quick.s
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
        
        .global _ZN5CCore5Quick9ScanLSBitEm
        .global _ZN5CCore5Quick9ScanMSBitEm
        .global _ZN5CCore5Quick10ByteSwap16Et
        .global _ZN5CCore5Quick10ByteSwap32Ej
        .global _ZN5CCore5Quick10ByteSwap64Em
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore5Quick9ScanLSBitEm:     #  CCore::Quick::ScanLSBit

        bsfq    %rcx, %rax
        
        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore5Quick9ScanMSBitEm:     #  CCore::Quick::ScanMSBit
        
        bsrq    %rcx, %rax
        
        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore5Quick10ByteSwap16Et:   #  CCore::Quick::ByteSwap16

        movzwl  %cx, %eax
        xchgb   %al, %ah

        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore5Quick10ByteSwap32Ej:   #  CCore::Quick::ByteSwap32

        movl    %ecx, %eax
        bswap   %eax
        
        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore5Quick10ByteSwap64Em:   #  CCore::Quick::ByteSwap64

        movq    %rcx, %rax
        bswap   %rax
        
        ret
        
#-----------------------------------------------------------------------------------------
        
