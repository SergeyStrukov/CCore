@ Boot.s
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

        .macro   SetReg  reg, val
        
        movw    \reg, #:lower16:\val 
        movt    \reg, #:upper16:\val
        
        .endm

@------------------------------------------------------------------------------

        .set    mem_base  , 0x80000000
        .set    mem_top   , 0xA0000000
        .set    stack_top , 0x80100000-0x10
        .set    boot      , mem_top-(__std_boot_end-__std_boot_beg)
        
        .text
        .align 2
        
        .global __std_boot
        .global __std_boot_beg
        .global __std_boot_end
        
__std_boot:

     @ disable interrupts
        
        cpsid   i
        
     @ reset T2
     
        SetReg  r3, 0x48040010
        mov     r4, #1
        str     r4, [r3]
        
L1:        
        ldr     r4, [r3]
        ands    r4, r4, #1
        bne     L1
           
     @ reset T4
     
        SetReg  r3, 0x48044010
        mov     r4, #1
        str     r4, [r3]
        
L2:        
        ldr     r4, [r3]
        ands    r4, r4, #1
        bne     L2

     @ copy up
        
        mov     r3, #mem_top
        
        subs    r5, r3, r1
        beq     L3
        
        add     r5, r0
        
L4:
        ldr     r4, [r1,#-4]!
        str     r4, [r3,#-4]!
        cmp     r1, r0
        bne     L4
        
        mov     r0, r5
L3:
     
     @ flush cache

        mov     r1, #0
L5:        
        mov     r2, #0
L4:        
        mov     r3, r1, LSL #6
        orr     r3, r3, r2, LSL #30
        mcr     p15, 0, r3, c7, c10, 2
        
        add     r2, r2, #1
        cmp     r2, #4
        bcc     L4 
        
        add     r1, r1, #1
        cmp     r1, #128
        bcc     L5 
        
        mov     r1, #0
L7:        
        mov     r2, #0
L6:        
        mov     r3, r1, LSL #6
        orr     r3, r3, r2, LSL #29
        mcr     p15, 0, r3, c7, c10, 2
        
        add     r2, r2, #1
        cmp     r2, #8
        bcc     L6 
        
        add     r1, r1, #1
        cmp     r1, #512
        bcc     L7 
        
     @ disable MMU and cache
     
        mrc     p15, 0, r1, c1, c0, 0
        
        bic     r0, r1, #0x5
        bic     r0, r1, #0x1800
        
        mcr     p15, 0, r1, c1, c0, 0
        
     @ invalidate instruction cache   
        
        mov      r1, #0
        
        mcr      p15, 0, r1, c7, c5, 0
        
        mcr      p15, 0, r1, c7, c10, 4
        
     @ boot
        
        SetReg   r1, boot
        bx       r1
        
        
__std_boot_beg:
        
     @ copy sections
        
L102:
        ldr      r1, [r0],#+4
        ldr      r2, [r0],#+4
        
        cmp      r2, #0
        beq      L100
        
L101:
        ldr      r3, [r0],#+4
        str      r3, [r1],#+4
        subs     r2, r2, #1
        bne      L101
        
        b        L102
        
L100:
     @ setup stack
        
        SetReg   sp, stack_top
        
     @ invalidate instruction cache   
        
        mov      r0, #0
        
        mcr      p15, 0, r0, c7, c5, 0
        
        mcr      p15, 0, r0, c7, c10, 4
        
     @ goto entry point
        
        bx       r1
        
__std_boot_end:
        
