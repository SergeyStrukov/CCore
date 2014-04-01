@ crt0.s
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
        
        .extern __std_memset
        .extern __std_memcpy
        
        .extern __std_context_data
        .extern __std_context_data_lim
        
        .extern __std_mem
        .extern __std_mem_lim
        
        .extern __bss_start__
        .extern __bss_end__
        
        .extern __init_array_start
        .extern __init_array_end
        
        .extern __std_debug_init
        .extern __std_debug
        .extern __std_debug2
        .extern __std_debug_trap
        
        .extern __std_init
        .extern __std_main
        .extern __std_exit
        
        .extern __std_stack_size
        .extern __std_int_stack_size
        .extern __std_heap_size
        .extern __std_int_heap_size
        .extern __std_syslog_size
        
        .extern  __std_shared_mem
        .extern  __std_shared_mem_size
        
        .extern  __std_video_mem
        .extern  __std_video_mem_size
        
@------------------------------------------------------------------------------

        .macro   SetReg  reg, val
        
        movw    \reg, #:lower16:\val 
        movt    \reg, #:upper16:\val
        
        .endm

@------------------------------------------------------------------------------
        
        .section ".absstart","ax"
        .align 2
        
        .global __std_start
        
__std_start:  

        b       start
        
        .align  5

ex_base:
        
        ldr     pc, .trap0
        ldr     pc, .trap1
        ldr     pc, .trap2
        ldr     pc, .trap3
        
        ldr     pc, .trap4
        ldr     pc, .trap5
        ldr     pc, .IRQ_entry 
        ldr     pc, .trap7
                
.trap0:                      .word  trap0                   
.trap1:                      .word  trap1                   
.trap2:                      .word  trap2                   
.trap3:                      .word  trap3                   
.trap4:                      .word  trap4                   
.trap5:                      .word  trap5                   
.trap7:                      .word  trap7                   

.IRQ_entry:                  .word  IRQ_entry
                
@------------------------------------------------------------------------------
        
        .section .rodata
        .align 2
        
nomem_msg:                   .ascii  "__std_alloc() : out of memory\000"      
        
the_end_msg:                 .ascii  "--- the end ---\000"

exittrap_msg:                .ascii  "exittrap() is called -- trap\000"
        
@------------------------------------------------------------------------------
        
        .data
        .align 2 
        
        .global __std_context
        
cur_mem:                     .word  0
        
main_stack:                  .word  0
        
__std_context:               .word  0
        
context_data_init:           .word  0

@------------------------------------------------------------------------------

        .set WDSC      , 0x44E35000+0x010 
        .set WSPR      , 0x44E35000+0x048
        .set WWPS      , 0x44E35000+0x034
        .set WStop1    , 0xAAAA
        .set WStop2    , 0x5555
         
        .set GPIO1_OE  , 0x4804C000+0x134
        .set GPIO1_OUT , 0x4804C000+0x13C
        
@------------------------------------------------------------------------------

        .text
        .align 2
        
start:  
        
     @ disable interrupts   
        
        mrs     r0, CPSR
        orr     r0, r0, #128
        msr     CPSR_c, r0
        
     @ reset and stop WD   
        
        SetReg  r0, WDSC
        ldr     r1, [r0]
        orr     r1, #0x02
        str     r1, [r0]
1:        
        ldr     r1, [r0]
        tst     r1, #0x02
        bne     1b
        
        SetReg  r0, WSPR
        SetReg  r2, WWPS
        
        SetReg  r1, WStop1
        str     r1, [r0]
1:        
        ldr     r1, [r2]
        tst     r1, #0x10
        bne     1b
        
        SetReg  r1, WStop2
        str     r1, [r0]
1:        
        ldr     r1, [r2]
        tst     r1, #0x10
        bne     1b
        
     @ enable FPU and SIMD
     
        mov     r0, #0xF00000
        mcr     p15, 0, r0, c1, c0, 2
        isb
       
        mov     r0, #0x40000000
        vmsr    FPEXC, r0
        
     @ disable non-aligned memory access
     
        mrc     p15, 0, r0, c1, c0, 0
        orr     r0, #2
        mcr     p15, 0, r0, c1, c0, 0
        
     @ setup exception base address    
        
        SetReg  r0, ex_base
        mcr     p15, 0, r0, c12, c0, 0   
        
     @ enable Lights
     
        SetReg  r0, GPIO1_OE
        ldr     r1, [r0]
        bic     r1, #0x1E00000 
        str     r1, [r0]
     
     @ Lights off
     
        SetReg  r0, GPIO1_OUT
        mov     r1, #0
        str     r1, [r0]      
        
     @ cur_mem <- __std_mem   
        
        SetReg  r0, __std_mem
        SetReg  r1, cur_mem
        str     r0, [r1]
        
     @ alloc and setup stack
        
        SetReg  r0, __std_stack_size
        mov     r4, r0
        bl      __std_alloc
        add     r0, r0, r4
        sub     sp, r0, #16
        
        SetReg  r0, main_stack
        str     sp, [r0]
        
     @ erase .bss  
        
        SetReg  r0, __bss_start__
        SetReg  r2, __bss_end__
        sub     r2, r2, r0
        mov     r1, #0
        bl      __std_memset
        
     @ alloc and fill context_data_init

        SetReg  r4, __std_context_data      
        SetReg  r5, __std_context_data_lim
        sub     r5, r5, r4
        mov     r0, r5
        bl      __std_alloc
        SetReg  r6, context_data_init
        str     r0, [r6]
        mov     r1, r4
        mov     r2, r5
        bl      __std_memcpy
        
     @ alloc and setup context  
        
        bl      __std_context_len
        bl      __std_alloc
        SetReg  r1, __std_context
        str     r0, [r1]
        
     @ main
     
        bl      __std_debug_init
        
        bl      __std_init
        
        bl      __std_main
        
        bl      __std_exit
        
        SetReg  r0, the_end_msg
        
        b       __std_abort

@------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global __std_alloc
        
nomem:  

        SetReg  r0, nomem_msg 
        
        b       __std_abort
        
__std_alloc:
        
        adds    r0, r0, #15
        bcs     nomem
        bic     r0, r0, #15
        
        SetReg  r1, cur_mem
        ldr     r2, [r1]
        SetReg  r3, __std_mem_lim
        sub     r3, r3, r2
        cmp     r3, r0
        bcc     nomem
        add     r3, r2, r0
        str     r3, [r1]
        mov     r0, r2

        bx      lr        
        
@------------------------------------------------------------------------------
        
        .text
        .align 2
        
trap:

     @ svc + disable interrupts   
        
        mov     r4, lr
        mov     r0, #0x93
        msr     CPSR_c, r0
        
     @ stop WD   
        
        SetReg  r0, WSPR
        SetReg  r2, WWPS

        SetReg  r1, WStop1        
        str     r1, [r0]
1:        
        ldr     r1, [r2]
        tst     r1, #0x10
        bne     1b

        SetReg  r1, WStop2       
        str     r1, [r0]
1:        
        ldr     r1, [r2]
        tst     r1, #0x10
        bne     1b
        
     @ Lights on
     
        SetReg  r0, GPIO1_OUT
        
        mov     r1, r3
        orr     r3, r3, #8
        mov     r3, r3, LSL #21
        
        str     r3, [r0]
        
     @ setup stack
     
        SetReg  r0, main_stack
        ldr     sp, [r0]
        
     @ debug LR
        
        mov     r0, r4
        bl      __std_debug_trap
              
     @ dead loop         
        
1:
        b       1b        
        
@------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global __std_abort
        .global __std_abort2
        
__std_abort:

        bl      __std_debug
        b       trap0

__std_abort2:

        bl      __std_debug2
        b       trap0
        
trap0:
        mov     r3, #0
        b       trap        
        
trap1:
        mov     r3, #1
        b       trap
                
trap2:
        mov     r3, #2
        b       trap
        
trap3:
        mov     r3, #3
        b       trap
        
trap4:
        mov     r3, #4
        b       trap
        
trap5:
        mov     r3, #5
        b       trap
        
trap6:
        mov     r3, #6
        b       trap
        
trap7:
        mov     r3, #7
        b       trap
        
@------------------------------------------------------------------------------

        .text
        .align 2
        
        .global __std_get_init_base
        .global __std_get_init_lim

__std_get_init_base:

        SetReg  r0, __init_array_start

        bx      lr
        
__std_get_init_lim:

        SetReg  r0, __init_array_end
         
        bx      lr

@------------------------------------------------------------------------------

        .text
        .align 2
        
        .global __std_get_shared_mem
        .global __std_get_shared_mem_len
        .global __std_get_video_mem
        .global __std_get_video_mem_len
        .global __std_get_heap_int_len
        .global __std_get_heap_len
        .global __std_get_syslog_len
        
__std_get_shared_mem:
        
        SetReg  r0, __std_shared_mem
        
        bx      lr
        
__std_get_shared_mem_len:        

        SetReg  r0, __std_shared_mem_size        
        
        bx      lr
        
__std_get_video_mem:        

        SetReg  r0, __std_video_mem 
        
        bx      lr
        
__std_get_video_mem_len:
        
        SetReg  r0, __std_video_mem_size
        
        bx      lr
        
__std_get_heap_int_len:        
        
        SetReg  r0, __std_int_heap_size
        
        bx      lr
        
__std_get_heap_len:        
        
        SetReg  r0, __std_heap_size
        
        bx      lr
        
__std_get_syslog_len:        
        
        SetReg  r0, __std_syslog_size
        
        bx      lr
        
@------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global __std_context_len
        .global __std_context_init
        .global __std_switch
        
__std_context_len:
        
        SetReg  r0, __std_context_data
        SetReg  r1, __std_context_data_lim
        sub     r0, r1, r0
        add     r0, #332
        
        bx      lr
        
exittrap:    

        SetReg  r0, exittrap_msg
        
        b       __std_abort      
        
__std_context_init:

        push    {r0,r1,r2,r3,r4,lr}        
        
        add     r4, r0, #332
        mov     r1, #0
        mov     r2, #332
        bl      __std_memset
        
        mov     r0, r4
        SetReg  r1, context_data_init
        ldr     r1, [r1]
        SetReg  r2, __std_context_data
        SetReg  r3, __std_context_data_lim
        sub     r2, r3, r2 
        bl      __std_memcpy
        
        pop     {r0,r1,r2,r3}
        
        ldr     r4, [sp, #8]
        
     @ R0    
        
        str     r4, [r0, #0]
        
     @ SP   

        add     r1, r1, r2
        sub     r1, r1, #16     
        str     r1, [r0, #52]
        
     @ LR
     
        SetReg  r1, exittrap
        str     r1, [r0, #56]
        
     @ PC
     
        add     r1, r3, #4
        str     r1, [r0, #60]
     
     @ CPSR
     
        mov     r1, #0x13
        orr     r1, r1, #0x100
        str     r1, [r0, #64]
     
     @ FPEXC
        
        mov     r1, #0x40000000 
        str     r1, [r0, #68]
        
        pop     {r4,pc}
        
__std_switch:        
        
        SetReg  r1, __std_context
        ldr     r1, [r1]
        stmia   r1, {r0-r14}
        add     r1, r1, #60
        
        add     r3, lr, #4
        mrs     r4, CPSR
        stmia   r1!, {r3,r4}
        
        vmrs    r3, FPEXC
        vmrs    r4, FPSCR
        stmia   r1!, {r3,r4}  
        vstmia  r1!, {D0-D15}  
        vstmia  r1!, {D16-D31}
        
        SetReg  r4, __std_context_data
        SetReg  r5, __std_context_data_lim
        sub     r5, r5, r4
        mov     r6, r0
        
        mov     r0, r1
        mov     r1, r4
        mov     r2, r5
        bl      __std_memcpy
       
     @ context saved   
        
        SetReg  r1, __std_context
        str     r6, [r1]
        
        mov     r0, r4
        add     r1, r6, #332
        mov     r2, r5
        bl      __std_memcpy
        
        add     r0, r6, #68
        ldmia   r0!, {r1,r2}
        vmsr    FPEXC, r1
        vmsr    FPSCR, r2
        vldmia  r0!, {D0-D15}  
        vldmia  r0!, {D16-D31}
        
        ldr     r13, [r6,#52]
        ldr     r14, [r6,#56]
        
        mov     r1, #0x92
        orr     r1, r1, #0x100
        msr     CPSR_cxsf, r1
        
        ldr     r1, [r6, #64]
        msr     SPSR_cxsf, r1
        
        mov     lr, r6
        ldmia   lr!, {r0-r12}
        ldr     lr, [lr, #8]
        
        subs    pc, lr, #4
        
@------------------------------------------------------------------------------
        
        .data
        .align 2
         
irq_func:                    .word  0
int_context_data:            .word  0

@------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global __std_intsetup
        .global __std_intcleanup
        
__std_intsetup:
        
        push    {r3,r4,r5,lr}
        
     @ store handler 
        
        SetReg  r1, irq_func
        str     r0, [r1]
        
     @ setup IRQ stack
        
        SetReg  r0, __std_int_stack_size
        mov     r4, r0
        bl      __std_alloc
        add     r0, r0, r4
        sub     r0, r0, #16
        
        mrs     r1, CPSR
        mov     r2, r1
        bic     r1, r1, #0x1F
        orr     r1, r1, #0x12
        msr     CPSR_c, r1
        mov     sp, r0
        msr     CPSR_cxsf, r2
        
     @ alloc and fill int_context_data  
        
        SetReg  r4, __std_context_data
        SetReg  r5, __std_context_data_lim
        sub     r5, r5, r4
        mov     r0, r5
        bl      __std_alloc
        SetReg  r1, int_context_data
        str     r0, [r1]
        SetReg  r1, context_data_init
        ldr     r1, [r1]
        mov     r2, r5
        bl      __std_memcpy
        
        pop     {r3,r4,r5,pc}
        
__std_intcleanup:
        
        mov     r0, #0
        SetReg  r1, irq_func
        str     r0, [r1]
        
        bx      lr
        
IRQ_entry:   
        
     @ save task context
        
        str     r12, [sp,#-4]
        
        SetReg  r12, __std_context
        ldr     r12, [r12]
        
        stmia   r12! , {r0-r11}
        
        ldr     r0, [sp,#-4]

        mrs     r5, CPSR
        mov     r6, r5
        bic     r5, r5, #0x1F
        orr     r5, r5, #0x13
        msr     CPSR_c, r5
        mov     r1, r13
        mov     r2, r14
        msr     CPSR_cxsf, r6
        
        mov     r3, lr
        
        mrs     r4, SPSR
        
        stmia   r12! , {r0-r4}
        
        vmrs    r3, FPEXC
        vmrs    r4, FPSCR
        stmia   r12!, {r3,r4}  
        vstmia  r12!, {D0-D15}  
        vstmia  r12!, {D16-D31}
        
     @ switch context data 
        
        mov     r4, r12
        SetReg  r5, int_context_data
        ldr     r5, [r5]
        
        SetReg  r6, __std_context_data
        SetReg  r7, __std_context_data_lim
        sub     r7, r7, r6
        
        mov     r0, r4
        mov     r1, r6
        mov     r2, r7
        bl      __std_memcpy
        
        mov     r0, r6
        mov     r1, r5
        mov     r2, r7
        bl      __std_memcpy
        
        mov     r0, #0x40000000
        vmsr    FPEXC, r0   
        
     @ call dispatcher
        
        SetReg  r0, irq_func
        ldr     r0, [r0]
        blx     r0
        
     @ switch context data 
       
        SetReg  r4, __std_context
        ldr     r4, [r4]
       
        mov     r0, r5
        mov     r1, r6
        mov     r2, r7
        bl      __std_memcpy
        
        mov     r0, r6
        add     r1, r4, #332
        mov     r2, r7
        bl      __std_memcpy
        
     @ restore task context
      
        ldr     r0, [r4,#52]
        ldr     r1, [r4,#56]
       
        mrs     r5, CPSR
        mov     r6, r5
        bic     r5, r5, #0x1F
        orr     r5, r5, #0x13
        msr     CPSR_c, r5
        mov     r13, r0
        mov     r14, r1
        msr     CPSR_cxsf, r6
        
        ldr     r0, [r4, #64]
        msr     SPSR_cxsf, r0
        
        mov     lr, r4
        ldmia   lr!, {r0-r12}
        ldr     lr, [lr, #8]
        
        clrex
        
        subs    pc, lr, #4
        
@------------------------------------------------------------------------------
        
        
