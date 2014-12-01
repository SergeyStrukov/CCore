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
     
     
        
     @ disable MMU and cache
     
        
        
     @ boot
        
        SetReg   r1, boot
        bx       r1
        
        
__std_boot_beg:
        
     @ copy sections
        
L7:
        ldr      r1, [r0],#+4
        ldr      r2, [r0],#+4
        
        cmp      r2, #0
        beq      L5
        
L6:
        ldr      r3, [r0],#+4
        str      r3, [r1],#+4
        subs     r2, r2, #1
        bne      L6
        
        b        L7
        
L5:
     @ setup stack
        
        SetReg   sp, stack_top
        
     @ goto entry point
        
        bx       r1
        
__std_boot_end:
        
