@ BootFlash.s
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
        
        .global __std_bootflash_beg
        .global __std_bootflash_end
        
__std_bootflash_beg:        
        
        ldr     pc, .Boot
        
.Boot:  .word   0x50000008
        
@--- Boot ---------------------------------------------------------------------
        
        bl      SetBigEndian
        bl      ConfigExpBus
        bl      ConfigSDRAM
        bl      InitSDRAM
        bl      ConfigUART
        
        mov     r0, #0
        mov     r1, #0x1000
        bl      TestSDRAM
        
        mov     r1, #0x8000000
        mov     r0, #0x1000
        sub     r0, r1, r0
        bl      TestSDRAM
        
        bl      InitTraps
        
        b       BootApp
        
@--- Set big-endian -----------------------------------------------------------
        
SetBigEndian:
        
        mrc     p15, 0, r0, C1, C0, 0
        orr     r0, r0, #0x80
        mcr     p15, 0, r0, C1, C0, 0
        
        mrc     p15, 0, r0, C2, C0, 0
        mov     r0, r0
        
        mov     pc, lr
        
@--- Config Exp bus -----------------------------------------------------------
        
ConfigExpBus:
        
        ldr     r0, .EXP_BASE
        
        ldr     r1, [r0, #32]
        bic     r1, r1, #0x80000000
        str     r1, [r0, #32]
        
        ldr     r1, .EXP_CNFG1_val
        str     r1, [r0, #36]
        
        ldr     r1, .EXP_TIMING_CS0_val
        str     r1, [r0]
        
        ldr     r1, .EXP_TIMING_CS2_val
        str     r1, [r0, #8]
        
        mov     pc, lr
        
.EXP_BASE:            .word  0xC4000000
        
.EXP_CNFG1_val:       .word  0x00000000
        
.EXP_TIMING_CS0_val:  .word  0xBFFF0242
        
                      @ CS0_EN = 1
                      @ PAR_EN = 0
                      @ T1 = 3 (max)
                      @ T2 = 3 (max)
                      @ T3 = 15 (max)
                      @ T4 = 3 (max)
                      @ T5 = 15 (max)
                      @ CYCLE_TYPE = 0
                      @ CNFG = 00001 (32Mb)
                      @ Sync_Intel = 0
                      @ EXP_CHIP = 0
                      @ BYTE_RD16 = 1
                      @ HDRY_POL = 0
                      @ MUX_EN = 0
                      @ SPLI_EN = 0
                      @ WORD_EN = 0
                      @ WR_EN = 1
                      @ BYTE_EN = 0
        
.EXP_TIMING_CS2_val:  .word  0xBFFF3C03
        
                      @ CS2_EN = 1
                      @ PAR_EN = 0
                      @ T1 = 3 (max)
                      @ T2 = 3 (max)
                      @ T3 = 15 (max)
                      @ T4 = 3 (max)
                      @ T5 = 15 (max)
                      @ CYCLE_TYPE = 0
                      @ CNFG = 11110 (16Mb)
                      @ Sync_Intel = 0
                      @ EXP_CHIP = 0
                      @ BYTE_RD16 = 0
                      @ HDRY_POL = 0
                      @ MUX_EN = 0
                      @ SPLI_EN = 0
                      @ WORD_EN = 0
                      @ WR_EN = 1
                      @ BYTE_EN = 1
                      
@--- Config SDRAM -------------------------------------------------------------
        
ConfigSDRAM:
        
        ldr     r0, .MCU_BASE
        
        ldr     r1, .MCU_SDCR0_val
        str     r1, [r0, #4]
        
        ldr     r1, .MCU_SDCR1_val
        str     r1, [r0, #8]
        
        ldr     r1, .MCU_SDBR_val
        str     r1, [r0, #12]
        ldr     r1, [r0, #12]
        
        ldr     r1, .MCU_SBR0_val
        str     r1, [r0, #16]
        ldr     r1, [r0, #16]
        
        ldr     r1, .MCU_SBR1_val
        str     r1, [r0, #20]
        ldr     r1, [r0, #20]
        
        mov     pc, lr
        
.MCU_SDCR0_val:   .word   0x52220106
        
                  @ RAS = 5
                  @ RP = 2
                  @ RCD = 2
                  @ EDP = 2
                  @ WDL = 0
                  @ CAS = 1
        
.MCU_SDCR1_val:   .word   0x2560f084
        
                  @ RTCMD = 2
                  @ WTCMD = 5
                  @ RTW = 6
                  @ RFC = 15
                  @ RC = 8
                  @ WTRD = 4
        
.MCU_SDBR_val:    .word   0x00000000
.MCU_SBR0_val:    .word   0x80000002
.MCU_SBR1_val:    .word   0x80000004
        
@--- Init SDRAM ---------------------------------------------------------------
        
InitSDRAM:
        
        ldr     r0, .MCU_BASE
        
        mov     r1, #0
        str     r1, [r0, #0x48]
        
        mov     r1, #3
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #2
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #4
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #1
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #2
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #6
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #6
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #0
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #15
        str     r1, [r0]
        mov     r2, #0x10000   @ at least 1 ms delay
        subs    r2, r2, #1
        subne   pc, pc, #12
        
        mov     r1, #0x410
        str     r1, [r0, #0x48]
        
        mov     pc, lr
        
.MCU_BASE:    .word   0xCC00E500
        
@--- Config UART --------------------------------------------------------------
        
ConfigUART:
        
        ldr     r0, .UART0_BASE
        
        mov     r1, #0
        str     r1, [r0, #4]
        
        mov     r1, #0x80
        str     r1, [r0, #12]
        
        mov     r1, #0x08
        str     r1, [r0]
        
        mov     r1, #0x00
        str     r1, [r0, #4]
        
        mov     r1, #3
        str     r1, [r0, #12]
        
        mov     r1, #0
        str     r1, [r0, #8]
        
        mov     r1, #2
        str     r1, [r0, #16]
        
        mov     r1, #0x40
        str     r1, [r0, #4]
        
        mov     pc, lr
        
PrintMsg:
        
        ldr     r2, .UART0_BASE
        
1:
        ldrb    r1, [r0], #1
        cmp     r1, #0
        moveq   pc, lr  
        
2:
        ldr     r3, [r2, #20]
        tst     r3, #0x20
        beq     2b
        
        str     r1, [r2]
        
        b       1b
        
.UART0_BASE:  .word      0xC8000000
        
@--- Test SDRAM ---------------------------------------------------------------
        
TestSDRAM:
        
        mov     r2, r0
        
        ldr     r3, .RandInit
        ldr     r4, .RandMul
        mov     r5, r2
        
1:
        mov     r0, r3, lsr #24
        strb    r0, [r2], #1
        mul     r0, r3, r4
        add     r3, r0, #1
        cmp     r2, r1
        bne     1b
        
        ldr     r3, .RandInit
        ldr     r4, .RandMul
        mov     r2, r5
        
2:
        mov     r0, r3, lsr #24
        ldrb    r5, [r2], #1
        cmp     r0, r5
        bne     3f
        mul     r0, r3, r4
        add     r3, r0, #1
        cmp     r2, r1
        bne     2b
        
        mov     sp, lr
        
        add     r0, pc, #(.SDRAMOkMsgText-.-8)
        bl      PrintMsg
        
        mov     pc, sp
        
3:
        add     r0, pc, #(.SDRAMBadMsgText-.-8)
        bl      PrintMsg
        b       3b
        
.RandInit:  .word   357618
.RandMul:   .word  -1644122275
        
.SDRAMOkMsgText:   .ascii  "SDRAM test ok\x0D\x0A\x00"
.SDRAMBadMsgText:  .ascii  "SDRAM test failed\x0D\x0A\x00"
        
        .align 2
        
@--- Init Traps ---------------------------------------------------------------
        
InitTraps:
        
        mov     r0, #0
        add     r1, pc, #(.TrapCode-.-8)
        add     r2, pc, #(.TrapCodeLim-.-8)
        
1:
        ldr     r3, [r1], #4
        str     r3, [r0], #4
        cmp     r1, r2
        bne     1b
        
        mov     pc, lr
        
.TrapCode:
        
        ldr     pc, .Trap_Reset
        ldr     pc, .Trap_Undefined
        ldr     pc, .Trap_SWI
        ldr     pc, .Trap_PrefetchAbort
        
        ldr     pc, .Trap_DataAbort
        ldr     pc, .Trap_Unknown
        ldr     pc, .Trap_IRQ
        ldr     pc, .Trap_FIQ
        
.Trap_Reset:           .word   Trap_Reset-__std_bootflash_beg+0x50000000
.Trap_Undefined:       .word   Trap_Undefined-__std_bootflash_beg+0x50000000
.Trap_SWI:             .word   Trap_SWI-__std_bootflash_beg+0x50000000
.Trap_PrefetchAbort:   .word   Trap_PrefetchAbort-__std_bootflash_beg+0x50000000
        
.Trap_DataAbort:       .word   Trap_DataAbort-__std_bootflash_beg+0x50000000
.Trap_Unknown:         .word   Trap_Unknown-__std_bootflash_beg+0x50000000
.Trap_IRQ:             .word   Trap_IRQ-__std_bootflash_beg+0x50000000
.Trap_FIQ:             .word   Trap_FIQ-__std_bootflash_beg+0x50000000
        
.TrapCodeLim:
        
@--- Trap ---------------------------------------------------------------------
        
Trap:
        mrs     r0, CPSR
        orr     r0, #0xC0
        msr     CPSR_c, r0
        
        bl      ConfigUART
1:
        mov     r0, sp
        bl      PrintMsg
        b       1b
        
Trap_Reset:
        add     sp, pc, #(.ResetMsgText-.-8)
        b       Trap
        
Trap_Undefined:
        add     sp, pc, #(.UndefinedMsgText-.-8)
        b       Trap
        
Trap_SWI:
        add     sp, pc, #(.SWIMsgText-.-8)
        b       Trap
        
Trap_PrefetchAbort:
        add     sp, pc, #(.PrefetchAbortMsgText-.-8)
        b       Trap
        
        
Trap_DataAbort:
        add     sp, pc, #(.DataAbortMsgText-.-8)
        b       Trap
        
Trap_Unknown:
        add     sp, pc, #(.UnknownMsgText-.-8)
        b       Trap
        
Trap_IRQ:
        add     sp, pc, #(.IRQMsgText-.-8)
        b       Trap
        
Trap_FIQ:
        add     sp, pc, #(.FIQMsgText-.-8)
        b       Trap
        
.ResetMsgText:            .ascii  "Reset trap\x0D\x0A\x00"      
.UndefinedMsgText:        .ascii  "Undefined instruction trap\x0D\x0A\x00"
.SWIMsgText:              .ascii  "SWI trap\x0D\x0A\x00"
.PrefetchAbortMsgText:    .ascii  "Prefetch abort trap\x0D\x0A\x00"
        
.DataAbortMsgText:        .ascii  "Data abort trap\x0D\x0A\x00"
.UnknownMsgText:          .ascii  "Data abort trap\x0D\x0A\x00"
.IRQMsgText:              .ascii  "IRQ trap\x0D\x0A\x00"
.FIQMsgText:              .ascii  "FIQ trap\x0D\x0A\x00"
        
        .align 2
        
@--- BootApp ------------------------------------------------------------------
        
BootApp:
        
        ldr     r0, .BootData 
        
1:        
        ldr     r1, [r0],#+4
        ldr     r2, [r0],#+4
        
        cmp     r2, #0
        beq     3f
        
2:        
        ldr      r3, [r0],#+4
        str      r3, [r1],#+4
        subs     r2, r2, #1
        bne      2b
        
        b        1b
        
3:
        mov      sp, #0x10000
        
        bx       r1
        
.BootData:             .word  0x50010000      
        
__std_bootflash_end:
        
@------------------------------------------------------------------------------

