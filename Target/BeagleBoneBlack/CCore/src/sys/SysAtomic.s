@ SysAtomic.s
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
        
        .global _ZN5CCore3Sys6Atomic3SetEPVjj
        .global _ZN5CCore3Sys6Atomic3AddEPVjj
        .global _ZN5CCore3Sys6Atomic6TrySetEPVjjj
        
_ZN5CCore3Sys6Atomic3SetEPVjj:                   @ CCore::Sys::Atomic::Set
        
        swp     r2, r1, [r0]
        mov     r0, r2
        
        bx      lr
        
_ZN5CCore3Sys6Atomic3AddEPVjj:                   @ CCore::Sys::Atomic::Add
        
        mrs     r3, CPSR
        orr     r2, r3, #128
        msr     CPSR_c, r2
        
        ldr     r2, [r0]
        add     r1, r1, r2
        str     r1, [r0]
        mov     r0, r2
        
        msr     CPSR_c, r3
        
        bx      lr
        
_ZN5CCore3Sys6Atomic6TrySetEPVjjj:               @ CCore::Sys::Atomic::TrySet
        
        mrs     r3, CPSR
        orr     ip, r3, #128
        msr     CPSR_c, ip
        
        ldr     ip, [r0]
        cmp     ip, r1
        streq   r2, [r0]
        mov     r0, ip
        
        msr     CPSR_c, r3
        
        bx      lr
        
@-----------------------------------------------------------------------------------------


