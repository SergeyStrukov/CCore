@ Boot.s
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
        
        .set    mem_top   , 0x4000000
        .set    mem_base  , 0x200000
        .set    stack_top , 0x100000-0x10
        .set    boot      , mem_top-(__std_boot_end-__std_boot_beg)
        
        .text
        .align 2
        
        .global __std_boot
        .global __std_boot_beg
        .global __std_boot_end
        
__std_boot:
        
     @ disable interrupts   
        
        mrs     r4, CPSR
        orr     r4, r4, #0xC0
        msr     CPSR_c, r4
        
     @ disable UART
        
        ldr     r3, .UART0_INT
        mov     r4, #0
        str     r4, [r3]
        
     @ disable T1
     
        ldr     r3, .T1_RELOAD
        mov     r4, #0
        str     r4, [r3]
        
        ldr     r3, .T_STATUS
        mov     r4, #2
        str     r4, [r3]
        
     @ copy up
        
        mov     r3, #mem_top
        
        subs    r5, r3, r1
        beq     L1
        
        add     r5, r0
        
L2:
        ldr     r4, [r1,#-4]!
        str     r4, [r3,#-4]!
        cmp     r1, r0
        bne     L2
        
        mov     r0, r5
L1:
        
     @ sync cache
        
        mov     r3, #1024
        mov     r2, #mem_top
        
L6:
        mcr     p15, 0, r2, C7, C2, 5     @ allocate D-cache line for address r2
        add     r2, r2, #32
        subs    r3, r3, #1
        bne     L6
        
        mov     r3, #128
        mov     r2, #mem_base
        
L7:
        ldr     r4, [r2],#32              @ read loop to clean mini-data cache
        subs    r3, r3, #1
        bne     L7
        
        mcr     p15, 0, r2, C7, C10, 4    @ drain write buffer
        
        mcr     p15, 0, r2, C7, C6, 0     @ invalidate D-cache
        
        mcr     p15, 0, r2, C7, C5, 0     @ invalidate I-cache and BTB
        
        mrc     p15, 0, r2, C2, C0, 0     @ wait
        mov     r2, r2
        sub     pc, pc, #4
        
     @ boot
        
        ldr      r1, .boot
        bx       r1
        
.boot:  .word    boot
        
.UART0_INT:     .word    0xC8000004
.T1_RELOAD:     .word    0xC8005010
.T_STATUS:      .word    0xC8005020
        
__std_boot_beg:
        
     @ copy sections
        
L4:
        ldr      r1, [r0],#+4
        ldr      r2, [r0],#+4
        
        cmp      r2, #0
        beq      L3
        
L5:
        ldr      r3, [r0],#+4
        str      r3, [r1],#+4
        subs     r2, r2, #1
        bne      L5
        
        b        L4
        
L3:
        
     @ sync cache
        
        mov     r3, #1024
        mov     r2, #mem_top
        
L8:
        mcr     p15, 0, r2, C7, C2, 5     @ allocate D-cache line for address r2
        add     r2, r2, #32
        subs    r3, r3, #1
        bne     L8
        
        mov     r3, #128
        mov     r2, #mem_base
        
L9:
        ldr     r4, [r2],#32              @ read loop to clean mini-data cache
        subs    r3, r3, #1
        bne     L9
        
        mcr     p15, 0, r2, C7, C10, 4    @ drain write buffer
        
        mcr     p15, 0, r2, C7, C6, 0     @ invalidate D-cache
        
        mcr     p15, 0, r2, C7, C5, 0     @ invalidate I-cache and BTB
        
        mrc     p15, 0, r2, C2, C0, 0     @ wait
        mov     r2, r2
        sub     pc, pc, #4
        
     @ disable MMU , D and I caches
        
        ldr     r0, .control
        
        mcr     p15, 0, r0, C1, C0, 0
        
        mrc     p15, 0, r2, C2, C0, 0     @ wait
        mov     r2, r2
        sub     pc, pc, #4
        
     @ setup stack
        
        ldr      sp, .stack_top
        
     @ goto entry point
        
        bx       r1
        
.stack_top:     .word   stack_top
.control:       .word   0x00FA
        
__std_boot_end:



