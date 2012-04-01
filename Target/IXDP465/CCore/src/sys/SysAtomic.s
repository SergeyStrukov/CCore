@ SysAtomic.s
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
        
        .global _ZN5CCore3Sys6Atomic3SetEPVjj
        
_ZN5CCore3Sys6Atomic3SetEPVjj:             @ CCore::Sys::Atomic::Set
        
        swp     ip, r1, [r0]
        mov     r0, ip
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global _ZN5CCore3Sys6Atomic3AddEPVjj
        
_ZN5CCore3Sys6Atomic3AddEPVjj:             @ CCore::Sys::Atomic::Add
        
        mrs     r3, CPSR
        orr     ip, r3, #0xC0
        msr     CPSR_c, ip
        
        ldr     ip, [r0]
        add     r1, r1, ip
        str     r1, [r0]
        mov     r0, ip
        
        msr     CPSR_c, r3
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global _ZN5CCore3Sys6Atomic6TrySetEPVjjj
        
_ZN5CCore3Sys6Atomic6TrySetEPVjjj:         @ CCore::Sys::Atomic::TrySet
        
        mrs     r3, CPSR
        orr     ip, r3, #0xC0
        msr     CPSR_c, ip
        
        ldr     ip, [r0]
        cmp     ip, r1
        streq   r2, [r0]
        mov     r0, ip
        
        msr     CPSR_c, r3
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------


