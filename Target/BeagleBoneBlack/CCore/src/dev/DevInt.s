@ DevInt.s
@-----------------------------------------------------------------------------------------
@
@  Project: CCore 1.08
@
@  Tag: Target/BeagleBoneBlack
@
@  License: Boost Software License - Version 1.0 - August 17th, 2003 
@
@            see http://www.boost.org/LICENSE_1_0.txt or the local copy
@
@  Copyright (c) 2014 Sergey Strukov. All rights reserved.
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
        
        bx      lr
        
_ZN5CCore3Dev7IntLock8Internal6EnableEv:         @ CCore::Dev::IntLock::Internal::Enable
        
        cpsie   i
        
        bx      lr
        
_ZN5CCore3Dev7IntLock8Internal7DisableEv:        @ CCore::Dev::IntLock::Internal::Disable

        mrs     r0, CPSR
        tst     r0, #128
        
        movne   r0, #0
        
        bxne    lr

        cpsid   i
                
        mov     r0, #1
        
        bx      lr
        
@-----------------------------------------------------------------------------------------

