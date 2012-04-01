@ IXP465.s
@-----------------------------------------------------------------------------------------
@
@  Project: CCore 1.02
@
@  Tag: Target/IXDP465
@
@  License: Boost Software License - Version 1.0 - August 17th, 2003 
@
@            see http://www.boost.org/LICENSE_1_0.txt or the local copy
@
@  Copyright (c) 2010 Sergey Strukov. All rights reserved.
@
@-----------------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global _ZN6IXP4657GetCPSREv
        .global _ZN6IXP4657GetSPSREv
        .global _ZN6IXP4657SetCPSRENS_14Type_CPUStatusE
        .global _ZN6IXP46515SetCPSR_controlENS_14Type_CPUStatusE
        
_ZN6IXP4657GetCPSREv:                                   @ IXP465::GetCPSR
        
        mrs     r0, CPSR
        
        mov     pc, lr
        
_ZN6IXP4657GetSPSREv:                                   @ IXP465::GetSPSR
        
        mrs     r0, SPSR
        
        mov     pc, lr
        
_ZN6IXP4657SetCPSRENS_14Type_CPUStatusE:                @ IXP465::SetCPSR
        
        msr     CPSR_cxsf, r0
        
        mov     pc, lr
        
_ZN6IXP46515SetCPSR_controlENS_14Type_CPUStatusE:       @ IXP465::SetCPSR_control
        
        msr     CPSR_c, r0
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------          

