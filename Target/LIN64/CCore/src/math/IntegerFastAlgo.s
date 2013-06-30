# IntegerFastAlgo.s
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
        
        .global _ZN5CCore4Math15IntegerFastAlgo12CountZeroMSBEm
        .global _ZN5CCore4Math15IntegerFastAlgo12CountZeroLSBEm
        .global _ZN5CCore4Math15IntegerFastAlgo10DoubleUDivEmmm
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore4Math15IntegerFastAlgo12CountZeroMSBEm:  # CCore::Math::IntegerFastAlgo::CountZeroMSB

        test  %rdi, %rdi
        je    L1
        
        bsrq  %rdi, %rax
        subl  $63, %eax
        negl  %eax
        
        ret
        
L1:
        movl  $64, %eax 

        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore4Math15IntegerFastAlgo12CountZeroLSBEm:  # CCore::Math::IntegerFastAlgo::CountZeroLSB

        test  %rdi, %rdi
        je    L2
        
        bsfq  %rdi, %rax
        
        ret
        
L2:
        movl  $64, %eax 

        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore4Math15IntegerFastAlgo10DoubleUDivEmmm:  # CCore::Math::IntegerFastAlgo::DoubleUDiv

        movq  %rdx, %rcx
        movq  %rdi, %rdx
        movq  %rsi, %rax
        
        divq  %rcx

        ret
        
#-----------------------------------------------------------------------------------------
        
