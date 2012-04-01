@ DevInt.s
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
        
        .global _ZN5CCore3Dev12IsIntContextEv
        .global _ZN5CCore3Dev7IntLock8Internal6EnableEv
        .global _ZN5CCore3Dev7IntLock8Internal7DisableEv
        
_ZN5CCore3Dev12IsIntContextEv:                   @ CCore::Dev::IsIntContext
        
        mrs     r0, CPSR
        and     r0, r0, #31
        cmp     r0, #18
        
        movne   r0, #0
        moveq   r0, #1
        
        mov     pc, lr
        
_ZN5CCore3Dev7IntLock8Internal6EnableEv:         @ CCore::Dev::IntLock::Internal::Enable
        
        mrs     r0, CPSR
        bic     r0, r0, #128
        msr     CPSR_c, r0
        
        mov     pc, lr
        
_ZN5CCore3Dev7IntLock8Internal7DisableEv:        @ CCore::Dev::IntLock::Internal::Disable

        mrs     r0, CPSR
        tst     r0, #128
        movne   r0, #0
        
        movne   pc, lr
        
        orr     r0, r0, #128
        msr     CPSR_c, r0
        mov     r0, #1
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

