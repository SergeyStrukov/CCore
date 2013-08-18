# IntegerFastAlgo.s
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
        
        .global _ZN5CCore4Math15IntegerFastAlgo12CountZeroMSBEy
        .global _ZN5CCore4Math15IntegerFastAlgo12CountZeroLSBEy
        .global _ZN5CCore4Math15IntegerFastAlgo10DoubleUDivEyyy 
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore4Math15IntegerFastAlgo12CountZeroMSBEy:  # CCore::Math::IntegerFastAlgo::CountZeroMSB

        test  %rcx, %rcx
        je    L1
        
        bsrq  %rcx, %rax
        subl  $63, %eax
        negl  %eax
        
        ret
        
L1:
        movl  $64, %eax 

        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore4Math15IntegerFastAlgo12CountZeroLSBEy:  # CCore::Math::IntegerFastAlgo::CountZeroLSB

        test  %rcx, %rcx
        je    L2
        
        bsfq  %rcx, %rax
        
        ret
        
L2:
        movl  $64, %eax 

        ret
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore4Math15IntegerFastAlgo10DoubleUDivEyyy:  # CCore::Math::IntegerFastAlgo::DoubleUDiv

        movq  %rdx, %rax
        movq  %rcx, %rdx
        
        divq  %r8

        ret
        
#-----------------------------------------------------------------------------------------
        
