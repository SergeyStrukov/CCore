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
        
#-----------------------------------------------------------------------------------------
        
        .global __ZN5CCore5Quick11UIntMulFuncIjE3MulC1Ejj
        .global __ZN5CCore5Quick11UIntMulFuncIjE3DivEjjj
        .global __ZN5CCore5Quick11UIntMulFuncIjE3ModEjjj
        .global __ZN5CCore5Quick11UIntMulFuncIjE6DivModC1Ejjj
        .global __ZN5CCore5Quick11UIntMulFuncIjE6ModMulEjjj
        .global __ZN5CCore5Quick11UIntMulFuncIjE6ModMacEjjjj

        .p2align 4,,15
        
__ZN5CCore5Quick11UIntMulFuncIjE3MulC1Ejj:       # CCore::Quick::UIntMulFunc<uint32>::Mul       

        movl    12(%esp), %eax
        movl    4(%esp), %ecx
        mull    8(%esp)
        
        movl    %edx, (%ecx)
        movl    %eax, 4(%ecx)
        
        ret


        .p2align 4,,15
        
__ZN5CCore5Quick11UIntMulFuncIjE3DivEjjj:        # CCore::Quick::UIntMulFunc<uint32>::Div       

        movl    4(%esp), %edx
        movl    8(%esp), %eax
        divl    12(%esp)

        ret
        
        
        .p2align 4,,15
        
__ZN5CCore5Quick11UIntMulFuncIjE3ModEjjj:        # CCore::Quick::UIntMulFunc<uint32>::Mod       

        movl    4(%esp), %edx
        movl    8(%esp), %eax
        divl    12(%esp)
        
        movl    %edx, %eax
        
        ret
        
        
        .p2align 4,,15
        
__ZN5CCore5Quick11UIntMulFuncIjE6DivModC1Ejjj:   # CCore::Quick::UIntMulFunc<uint32>::DivMod::DivMod       

        movl    8(%esp), %edx
        movl    4(%esp), %ecx
        movl    12(%esp), %eax
        divl    16(%esp)
        
        movl    %edx, 4(%ecx)
        movl    %eax, (%ecx)
        
        ret
        
        
        .p2align 4,,15
        
__ZN5CCore5Quick11UIntMulFuncIjE6ModMulEjjj:     # CCore::Quick::UIntMulFunc<uint32>::ModMul        
        
        movl    4(%esp), %eax
        mull    8(%esp)
        divl    12(%esp)
        
        movl    %edx, %eax
        
        ret
        
        
        .p2align 4,,15
        
__ZN5CCore5Quick11UIntMulFuncIjE6ModMacEjjjj:    # CCore::Quick::UIntMulFunc<uint32>::ModMac
        
        movl    8(%esp), %eax
        mull    12(%esp)
        
        addl    4(%esp), %eax
        adcl    $0, %edx 
        
        divl    16(%esp)
        
        movl    %edx, %eax
        
        ret
        
#-----------------------------------------------------------------------------------------


        
