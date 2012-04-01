@ IXP465.CP15.s
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
        
        .global _ZN6IXP4654CP156Get_IDEv
        .global _ZN6IXP4654CP1513Get_CacheTypeEv
        .global _ZN6IXP4654CP1511Get_ControlEv
        .global _ZN6IXP4654CP1511Set_ControlENS0_12Type_ControlE
        .global _ZN6IXP4654CP1514Get_AuxControlEv
        .global _ZN6IXP4654CP1514Set_AuxControlENS0_15Type_AuxControlE
        .global _ZN6IXP4654CP1510Get_TTBaseEv
        .global _ZN6IXP4654CP1510Set_TTBaseEj
        .global _ZN6IXP4654CP1512Get_DomainACEv
        .global _ZN6IXP4654CP1512Set_DomainACENS0_13Type_DomainACE      
        .global _ZN6IXP4654CP157Get_PIDEv
        .global _ZN6IXP4654CP157Set_PIDEj
        .global _ZN6IXP4654CP154WaitEv
        
_ZN6IXP4654CP156Get_IDEv:                                 @ IXP465::CP15::Get_ID
        
        mrc     p15, 0, r0, C0, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP1513Get_CacheTypeEv:                         @ IXP465::CP15::Get_CacheType
        
        mrc     p15, 0, r0, C0, C0, 1
        
        mov     pc, lr
        
_ZN6IXP4654CP1511Get_ControlEv:                           @ IXP465::CP15::Get_Control
        
        mrc     p15, 0, r0, C1, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP1511Set_ControlENS0_12Type_ControlE:         @ IXP465::CP15::Set_Control
        
        mcr     p15, 0, r0, C1, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP1514Get_AuxControlEv:                        @ IXP465::CP15::Get_AuxControl
        
        mrc     p15, 0, r0, C1, C0, 1
        
        mov     pc, lr
        
_ZN6IXP4654CP1514Set_AuxControlENS0_15Type_AuxControlE:   @ IXP465::CP15::Set_AuxControl
        
        mcr     p15, 0, r0, C1, C0, 1
        
        mov     pc, lr
        
_ZN6IXP4654CP1510Get_TTBaseEv:                            @ IXP465::CP15::Get_TTBase
        
        mrc     p15, 0, r0, C2, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP1510Set_TTBaseEj:                            @ IXP465::CP15::Set_TTBase
        
        mcr     p15, 0, r0, C2, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP1512Get_DomainACEv:                          @ IXP465::CP15::Get_DomainAC
        
        mrc     p15, 0, r0, C3, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP1512Set_DomainACENS0_13Type_DomainACE:       @ IXP465::CP15::Set_DomainAC
        
        mcr     p15, 0, r0, C3, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP157Get_PIDEv:                                @ IXP465::CP15::Get_PID
        
        mrc     p15, 0, r0, C13, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP157Set_PIDEj:                                @ IXP465::CP15::Set_PID
        
        mcr     p15, 0, r0, C13, C0, 0
        
        mov     pc, lr
        
_ZN6IXP4654CP154WaitEv:                                   @ IXP465::CP15::Wait
        
        mrc     p15, 0, r0, C2, C0, 0
        mov     r0, r0
        sub     pc, pc, #4
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

