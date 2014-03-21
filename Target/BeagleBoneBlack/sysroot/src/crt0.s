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
        
        .section .rodata
        .align 2
        
nomem_msg:    .ascii  "__std_alloc() : out of memory\000"      
        
the_end_msg:  .ascii  "--- the end ---\000"
        
@------------------------------------------------------------------------------
        
        .bss
        .align 2 
        
        .global __std_context_data_init
        
cur_mem:                  .space 4
        
__std_context_data_init:  .space 4
        
        .space  64
        
@------------------------------------------------------------------------------
        
        .sect ".init"
        .align 2
        
        .global __std_start
        
__std_start:  

        b       start
                
@------------------------------------------------------------------------------

        .text
        .align 2
        
start:  
        
     @ disable interrupts   
        
        mrs     r0, CPSR
        orr     r0, r0, #128
        msr     CPSR_c, r0
        
     @ cur_mem <- __std_mem   
        
        ldr     r0, .__std_mem
        ldr     r1, .cur_mem
        str     r0, [r1]
        
     @ alloc and setup stack
        
        ldr     r0, .__std_stack_size
        mov     r4, r0
        bl      __std_alloc
        add     r0, r0, r4
        sub     sp, r0, #16
        
     @ erase .bss  
        
        ldr     r0, .__bss_start__
        ldr     r2, .__bss_end__
        sub     r2, r2, r0
        mov     r1, #0
        bl      __std_memset
        
     @ alloc and fill __std_context_data_init
        
        ldr     r4, .__std_context_data
        ldr     r5, .__std_context_data_lim
        sub     r5, r5, r4
        mov     r0, r5
        bl      __std_alloc
        ldr     r6, .__std_context_data_init
        str     r0, [r6]
        mov     r1, r4
        mov     r2, r5
        bl      __std_memcpy
        
     @ alloc and setup context  
        
        bl      __std_context_len
        bl      __std_alloc
        ldr     r1, .__std_context
        str     r0, [r1]
        
     @ main
        
        bl      __std_init
        
        bl      __std_main
        
        bl      __std_exit
        
        ldr     r0, .the_end_msg
        
        b       __std_abort
        
        .align 2
        
.__bss_start__:           .word  __bss_start__
        
.__bss_end__:             .word  __bss_end__
        
.__std_mem:               .word  __std_mem
        
.cur_mem:                 .word  cur_mem
        
.__std_context_data:      .word  __std_context_data
        
.__std_context_data_lim:  .word  __std_context_data_lim
        
.__std_context_data_init: .word  __std_context_data_init
        
.__std_context:           .word  __std_context
        
.__std_stack_size:        .word  __std_stack_size
        
.the_end_msg:             .word  the_end_msg
        
@------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global __std_alloc
        
nomem:  
        
        ldr     r0, .nomem_msg
        
        b       __std_abort
        
__std_alloc:
        
        adds    r0, r0, #15
        bcs     nomem
        bic     r0, r0, #15
        
        ldr     r1, .1.cur_mem
        ldr     r2, [r1]
        ldr     r3, .__std_mem_lim
        sub     r3, r3, r2
        cmp     r3, r0
        bcc     nomem
        add     r3, r2, r0
        str     r3, [r1]
        mov     r0, r2
        
        mov     pc, lr
        
        .align 2
        
.1.cur_mem:        .word   cur_mem
        
.__std_mem_lim:    .word   __std_mem_lim
        
.nomem_msg:        .word   nomem_msg
        
@------------------------------------------------------------------------------
        
        .text
        .align 2
        
printchar:        
        
        ldr     r6, [r3]
        tst     r6, #0x20
        beq     printchar
        str     r2, [r4]
        
        mov     pc, lr
        
printmsg:
        
        mov     r5, lr
        
        ldr     r3, .regEN
        mov     r4, #0x40
        str     r4, [r3]
        
        ldr     r3, .regLS
        ldr     r4, .regTX
        
        mov     r2, #13
        bl      printchar
        
        mov     r2, #10
        bl      printchar
        
1:
        ldrb    r2, [r0], #1
        cmp     r2, #0
        blne    printchar
        bne     1b
        
        mov     r2, #13
        bl      printchar
        
        mov     r2, #10
        bl      printchar
        
        mov     pc, r5
        
printmsg2:
        
        mov     r5, lr
        
        ldr     r3, .regEN
        mov     r4, #0x40
        str     r4, [r3]
        
        ldr     r3, .regLS
        ldr     r4, .regTX
        
        mov     r2, #13
        bl      printchar
        
        mov     r2, #10
        bl      printchar
        
2:
        cmp     r1, #0
        beq     3f
        sub     r1, r1, #1
        ldrb    r2, [r0], #1
        bl      printchar
        b       2b
3:
        
        mov     r2, #13
        bl      printchar
        
        mov     r2, #10
        bl      printchar
        
        mov     pc, r5
        
        
        .align 2
        
.regLS:    .word    0xC8000014   
        
.regTX:    .word    0xC8000000
        
.regEN:    .word    0xC8000004
        
@------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global __std_abort
        .global __std_abort2
        
reset:
        ldr     r0, .regLS
        
waituart:        
        
        ldr     r1, [r0]
        tst     r1, #0x40
        beq     waituart
        
        ldr     r0, .regWDKey
        ldr     r1, .WDKeyOpen
        str     r1, [r0]
        
        ldr     r0, .regWDCnt
        mov     r1, #0
        str     r1, [r0]
        
        ldr     r0, .regWDCtrl
        mov     r1, #5
        str     r1, [r0]
        
waitreset:        
        
        b       waitreset
        
__std_abort:
        
        mov     r2, #0xD3
        msr     CPSR_cxsf, r2
        
        ldr     r2, .INT_base
        mov     r3, #0
        str     r3, [r2, #4]
        str     r3, [r2, #36]
        
        ldr     r2, .1.old_sp
        ldr     sp, [r2]
        
        bl      printmsg
        
        bl      __std_intcleanup
        
        b       reset
        
__std_abort2:
        
        mov     r2, #0xD3
        msr     CPSR_cxsf, r2
        
        ldr     r2, .INT_base
        mov     r3, #0
        str     r3, [r2, #4]
        str     r3, [r2, #36]
        
        ldr     r2, .1.old_sp
        ldr     sp, [r2]
        
        bl      printmsg2
        
        bl      __std_intcleanup
        
        b       reset
        
        .align 2
        
.1.old_sp:  .word  old_sp
        
.INT_base:  .word  0xC8003000
        
.regWDCnt:  .word  0xC8005014
.regWDCtrl: .word  0xC8005018
.regWDKey:  .word  0xC800501C
        
.WDKeyOpen: .word  0x482E
        
@------------------------------------------------------------------------------
        
        .bss
        .align 2 
        
        .global __std_context
        
old_int_sp:         .space  4
old_vect:           .space  4
old_flag:           .space  4
irq_func:           .space  4
int_context_data:   .space  4
__std_context:      .space  4
        
        .space  64
        
@------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global __std_context_len
        .global __std_intsetup
        .global __std_intcleanup
        
__std_context_len:
        
        ldr     r0, .1.__std_context_data
        ldr     r1, .1.__std_context_data_lim
        sub     r0, r1, r0
        add     r0, #324
        
        mov     pc, lr
        
__std_intsetup:
        
        stmfd   sp!, {r4,r5,lr}
        
     @ store handler 
        
        ldr     r1, .irq_func
        str     r0, [r1]
        
     @ setup IRQ stack
        
        ldr     r0, .__std_int_stack_size
        bl      __std_alloc_stack
        mrs     r1, CPSR
        mov     r2, r1
        bic     r1, r1, #0x1F
        orr     r1, r1, #0x12
        msr     CPSR_c, r1
        mov     r3, sp
        mov     sp, r0
        msr     CPSR_cxsf, r2
        ldr     r0, .old_int_sp
        str     r3, [r0]
        
     @ setup IRQ vector 
        
        ldr     r1, .INT_vect
        ldr     r2, .old_vect
        ldr     r0, [r1]
        str     r0, [r2]
        ldr     r0, .IRQ_entry
        str     r0, [r1]
        
     @ set old_flag  
        
        mov     r0, #1
        ldr     r1, .old_flag
        str     r0, [r1]
        
     @ alloc and fill int_context_data  
        
        ldr     r4, .1.__std_context_data
        ldr     r5, .1.__std_context_data_lim
        sub     r5, r5, r4
        mov     r0, r5
        bl      __std_alloc
        ldr     r1, .int_context_data
        str     r0, [r1]
        ldr     r1, .1.__std_context_data_init
        ldr     r1, [r1]
        mov     r2, r5
        bl      __std_memcpy
        
        ldmfd   sp!, {r4,r5,pc}
        
__std_intcleanup:
        
        ldr     r1, .old_flag
        ldr     r0, [r1]
        cmp     r0, #0
        moveq   pc, lr
        
        ldr     r1, .INT_vect
        ldr     r2, .old_vect
        ldr     r0, [r2]
        str     r0, [r1]
        
        ldr     r1, .old_int_sp
        ldr     r0, [r1]
        mrs     r1, CPSR
        mov     r2, r1
        bic     r1, r1, #0x1F
        orr     r1, r1, #0x12
        msr     CPSR_c, r1
        mov     sp, r0
        msr     CPSR_cxsf, r2
        
        mov     pc, lr
        
IRQ_entry:   
        
     @ save task context
        
        str     r12, [sp,#-4]
        
        ldr     r12, .1.__std_context
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
        
     @ switch context data 
        
        mov     r4, r12
        ldr     r5, .int_context_data
        ldr     r5, [r5]
        
        ldr     r6, .1.__std_context_data
        ldr     r7, .1.__std_context_data_lim
        sub     r7, r7, r6
        
        mov     r0, r4
        mov     r1, r6
        mov     r2, r7
        bl      __std_memcpy
        
        mov     r0, r6
        mov     r1, r5
        mov     r2, r7
        bl      __std_memcpy
        
     @ call dispatcher
        
        ldr     r0, .irq_func
        ldr     r0, [r0]
        blx     r0
        
     @ switch context data 
       
        ldr     r4, .1.__std_context
        ldr     r4, [r4]
       
        mov     r0, r5
        mov     r1, r6
        mov     r2, r7
        bl      __std_memcpy
        
        mov     r0, r6
        add     r1, r4, #68
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
        
        subs    pc, lr, #4
        
        .align 2
        
.1.__std_context_data:        .word  __std_context_data
        
.1.__std_context_data_lim:    .word  __std_context_data_lim
        
.irq_func:                    .word  irq_func
        
.__std_int_stack_size:        .word  __std_int_stack_size
        
.old_int_sp:                  .word  old_int_sp
        
.INT_vect:                    .word  0x00000038
        
.old_vect:                    .word  old_vect
        
.IRQ_entry:                   .word  IRQ_entry
        
.old_flag:                    .word  old_flag
        
.int_context_data:            .word  int_context_data
        
.1.__std_context_data_init:   .word  __std_context_data_init
        
.1.__std_context:             .word  __std_context
        
@------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global __std_switch
        
__std_switch:        
        
        ldr     r1, .2.__std_context
        ldr     r1, [r1]
        stmia   r1, {r0-r14}
        add     r1, r1, #60
        add     r3, lr, #4
        mrs     r4, CPSR
        stmia   r1!, {r3,r4}
        
        @ save Q0-Q15 and advance r1
        
        ldr     r4, .2.__std_context_data
        ldr     r5, .2.__std_context_data_lim
        sub     r5, r5, r4
        mov     r6, r0
        
        mov     r0, r1
        mov     r1, r4
        mov     r2, r5
        bl      __std_memcpy
        
        ldr     r1, .2.__std_context
        str     r6, [r1]
        
        mov     r0, r4
        add     r1, r6, #324
        mov     r2, r5
        bl      __std_memcpy
        
        @ load Q0-Q15 from r6+68
        
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
        
        .align 2
        
.2.__std_context:             .word  __std_context
        
.2.__std_context_data:        .word  __std_context_data
        
.2.__std_context_data_lim:    .word  __std_context_data_lim
        
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
        
        ldr     r0, .shared_mem
        
        mov     pc, lr
        
__std_get_shared_mem_len:        
        
        ldr     r0, .shared_mem_size
        
        mov     pc, lr
        
__std_get_video_mem:        

        ldr     r0, .video_mem
        
        mov     pc, lr
        
__std_get_video_mem_len:
        
        ldr     r0, .video_mem_size
        
        mov     pc, lr
        
__std_get_heap_int_len:        
        
        ldr     r0, .__std_int_heap_size
        
        mov     pc, lr
        
__std_get_heap_len:        
        
        ldr     r0, .__std_heap_size
        
        mov     pc, lr
        
__std_get_syslog_len:        
        
        ldr     r0, .__std_syslog_size
        
        mov     pc, lr
        
        .align 2
        
.shared_mem:                  .word  __std_shared_mem
.shared_mem_size:             .word  __std_shared_mem_size
.video_mem:                   .word  __std_video_mem
.video_mem_size:              .word  __std_video_mem_size
.__std_int_heap_size:         .word  __std_int_heap_size
.__std_heap_size:             .word  __std_heap_size
.__std_syslog_size:           .word  __std_syslog_size
        
@------------------------------------------------------------------------------
        
