@ string_s.s
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

        .set ByteOrder1 , 0x000000FF
        .set ByteOrder2 , 0x0000FF00
        .set ByteOrder3 , 0x00FF0000
        .set ByteOrder4 , 0xFF000000

        .set ByteOrderBE , 0
        .set ByteOrderLE , 1

@-----------------------------------------------------------------------------------------

        .text
        .align 2

        .global strcmp
        .global strcoll

strcmp:
strcoll:

1:
        ldrb    r2, [r0], #1
        ldrb    r3, [r1], #1
        cmp     r2, #1
        cmpcs   r2, r3
        beq     1b

        sub     r0, r2, r3
        mov     pc, lr

@------------------------------------------------------------------------------

        .text
        .align 2

        .global strncmp

strncmp:

        subs    r2, r2, #1

        movcc   r0, #0
        movcc   pc, lr

        adds    ip, r0, r2
        mvncs   ip, #0

1:
        ldrb    r2, [r0], #1
        ldrb    r3, [r1], #1
        cmp     ip, r0
        cmpcs   r2, #1
        cmpcs   r2, r3
        beq     1b

        sub     r0, r2, r3
        mov     pc, lr

@------------------------------------------------------------------------------

        .text
        .align 2

        .global memcmp

memcmp:

        subs    r2, r2, #1

        movcc   r0, #0
        movcc   pc, lr

        add     ip, r0, r2

1:
        ldrb    r2, [r0], #1
        ldrb    r3, [r1], #1
        cmp     ip, r0
        cmpcs   r2, r3
        beq     1b

        sub     r0, r2, r3
        mov     pc, lr

@------------------------------------------------------------------------------

        .text
        .align 2

        .global __std_memset

__std_memset:

        cmp     r2, #12
        bcc     4f

        and     r1, r1, #0xFF
        orr     r1, r1, r1, lsl #8
        orr     r1, r1, r1, lsl #16

1:
        tst     r0, #3
        strneb  r1, [r0], #1
        subne   r2, r2, #1
        bne     1b

        mov     ip, r1
        mov     r3, r1

2:
        subs    r2, r2, #48
        stmcsia r0!, {r1,r3,ip}
        stmcsia r0!, {r1,r3,ip}
        stmcsia r0!, {r1,r3,ip}
        stmcsia r0!, {r1,r3,ip}
        bcs     2b

        add     r2, r2, #48

3:
        subs    r2, r2, #12
        stmcsia r0!, {r1,r3,ip}
        bcs     3b

        add     r2, r2, #12

4:
        cmp     r2, #0
        moveq   pc, lr

        rsb     r2, r2, #11
        add     pc, pc, r2, lsl #2

        mov     ip, ip

        strb    r1, [r0], #1
        strb    r1, [r0], #1
        strb    r1, [r0], #1

        strb    r1, [r0], #1
        strb    r1, [r0], #1
        strb    r1, [r0], #1
        strb    r1, [r0], #1

        strb    r1, [r0], #1
        strb    r1, [r0], #1
        strb    r1, [r0], #1
        strb    r1, [r0], #1

        mov     pc, lr

@------------------------------------------------------------------------------

        .text
        .align 2

        .global __std_strend

__std_strend:

1:
        tst     r0, #3
        beq     2f
        ldrb    r1, [r0], #1
        cmp     r1, #0
        bne     1b

        sub     r0, r0, #1
        mov     pc, lr

2:
        ldr     r1, [r0], #4
        tst     r1, #ByteOrder1
        tstne   r1, #ByteOrder2
        tstne   r1, #ByteOrder3
        tstne   r1, #ByteOrder4
        bne     2b

        tst     r1, #ByteOrder1
        subeq   r0, r0, #4
        moveq   pc, lr

        tst     r1, #ByteOrder2
        subeq   r0, r0, #3
        moveq   pc, lr

        tst     r1, #ByteOrder3
        subeq   r0, r0, #2
        moveq   pc, lr

        tst     r1, #ByteOrder4
        subeq   r0, r0, #1
        moveq   pc, lr

@------------------------------------------------------------------------------

        .if ByteOrderBE

        .macro CpyShift a, b

        mov     \a, \a, lsl lr
        orr     \a, \b, lsr ip

        .endm

        .endif

@------------------------------------------------------------------------------

        .if ByteOrderLE

        .macro CpyShift a, b

        mov     \a, \a, lsr lr
        orr     \a, \b, lsl ip

        .endm

        .endif

@------------------------------------------------------------------------------

        .text
        .align 2

        .global __std_memcpy

wordcpy:  @@  r0 , r1 aligned

        cmp     r2, #32
        bcs     wordcpy_big

        tst     r2, #16
        ldmneia r1!, {r3,ip}  
        stmneia r0!, {r3,ip}
        ldmneia r1!, {r3,ip}  
        stmneia r0!, {r3,ip}

        tst     r2, #8
        ldmneia r1!, {r3,ip}  
        stmneia r0!, {r3,ip}

        tst     r2, #4
        ldrne   ip, [r1], #4
        strne   ip, [r0], #4

        tst     r2, #2
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        tst     r2, #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        mov     pc, lr

wordcpy_big:  @@  r0 , r1 aligned , r2 >= 32 

        stmfd   sp!, {r4-r10}

        bic     ip, r2, #31
        add     ip, r1, ip

1:
        ldmia   r1!, {r3,r4,r5,r6,r7,r8,r9,r10}  
        stmia   r0!, {r3,r4,r5,r6,r7,r8,r9,r10}
        cmp     r1, ip
        bne     1b

        tst     r2, #16
        ldmneia r1!, {r3,r4,r5,r6}  
        stmneia r0!, {r3,r4,r5,r6}

        tst     r2, #8
        ldmneia r1!, {r3,r4}  
        stmneia r0!, {r3,r4}

        tst     r2, #4
        ldrne   ip, [r1], #4
        strne   ip, [r0], #4

        tst     r2, #2
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        tst     r2, #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        ldmfd   sp!, {r4-r10}

        mov     pc, lr

badcpy:  @@  r1 is aligned, r0 is not aligned , r2 >= 8

        cmp     r2, #36
        bcs     badcpy_big

        stmfd   sp!, {r4,lr}

        ldr     r3, [r1], #4
        and     ip, r0, #3
        mov     ip, ip, lsl #3
        rsb     lr, ip, #32

        .if ByteOrderBE

        mov     r4, r3, ror #24

        tst     lr, #8
        strneb  r4, [r0], #1
        movne   r4, r4, ror #16
        moveq   r4, r4, ror #24

        tst     lr, #16
        strneh  r4, [r0], #2

        .endif

        .if ByteOrderLE

        mov     r4, r3

        tst     lr, #8
        strneb  r4, [r0], #1
        movne   r4, r4, ror #8

        tst     lr, #16
        strneh  r4, [r0], #2

        .endif

        sub    r2, r2, #8

1:
        ldr     r4, [r1], #4

        CpyShift r3, r4

        str     r3, [r0], #4
        mov     r3, r4

        subs    r2, r2, #4
        bcs     1b

        add     r2, r2, #4

        sub     r1, r1, ip, lsr #3
        add     r2, r2, ip, lsr #3

        tst     r2, #2
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        tst     r2, #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        tst     r2, #4
        ldmeqfd sp!, {r4,pc}

        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1

        ldmfd   sp!, {r4,pc}

badcpy_big:  @@  r1 is aligned, r0 is not aligned , r2 >= 36

        stmfd   sp!, {r4-r11,lr}

        ldr     r3, [r1], #4
        and     ip, r0, #3
        mov     ip, ip, lsl #3
        rsb     lr, ip, #32

        .if ByteOrderBE

        mov     r4, r3, ror #24

        tst     lr, #8
        strneb  r4, [r0], #1
        movne   r4, r4, ror #16
        moveq   r4, r4, ror #24

        tst     lr, #16
        strneh  r4, [r0], #2

        .endif

        .if ByteOrderLE

        mov     r4, r3

        tst     lr, #8
        strneb  r4, [r0], #1
        movne   r4, r4, ror #8

        tst     lr, #16
        strneh  r4, [r0], #2

        .endif

        sub     r2, r2, #36

1:
        ldmia   r1!, {r4,r5,r6,r7,r8,r9,r10,r11}  

        CpyShift r3, r4
        CpyShift r4, r5
        CpyShift r5, r6
        CpyShift r6, r7
        CpyShift r7, r8
        CpyShift r8, r9
        CpyShift r9, r10
        CpyShift r10, r11

        stmia   r0!, {r3,r4,r5,r6,r7,r8,r9,r10}
        mov     r3, r11

        subs    r2, r2, #32
        bcs     1b

        add     r2, r2, #32
        subs    r2, r2, #4
        bcc     3f

2:
        ldr     r4, [r1], #4

        CpyShift r3, r4

        str     r3, [r0], #4
        mov     r3, r4

        subs    r2, r2, #4
        bcs     2b

3:
        add     r2, r2, #4

        sub     r1, r1, ip, lsr #3
        add     r2, r2, ip, lsr #3

        tst     r2, #2
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        tst     r2, #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        tst     r2, #4
        ldmeqfd sp!, {r4-r11,pc}

        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1

        ldmfd   sp!, {r4-r11,pc}

__std_memcpy:
__std_memcpy2:

        tst     r2, r2
        moveq   pc, lr

        tst     r0, #3
        tsteq   r1, #3
        beq     wordcpy

        cmp     r2, #8
        bcc     smallcpy

        tst     r1, #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1
        subne   r2, r2, #1

        tst     r1, #2
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1
        subne   r2, r2, #2

        tst     r0, #3
        beq     wordcpy

        cmp     r2, #8
        bcs     badcpy

smallcpy:  @@  r2 <= 7

        tst     r2, #2
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        tst     r2, #1
        ldrneb  ip, [r1], #1
        strneb  ip, [r0], #1

        tst     r2, #4
        moveq   pc, lr

        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1

        mov     pc, lr

@------------------------------------------------------------------------------

        .text
        .align 2

        .global __std_memcpy2

@__std_memcpy2:

	cmp	r1, r0
	bcc	.Lmemcpy_backwards

	moveq	r0, #0			
	moveq	pc, lr

	stmdb	sp!, {r0, lr}		
	subs	r2, r2, #4
	blt	.Lmemcpy_fl4		
	ands	r12, r0, #3
	bne	.Lmemcpy_fdestul	
	ands	r12, r1, #3
	bne	.Lmemcpy_fsrcul		

.Lmemcpy_ft8:
	subs	r2, r2, #8
	blt	.Lmemcpy_fl12		
	subs	r2, r2, #0x14         
	blt	.Lmemcpy_fl32		
	stmdb	sp!, {r4}		

.Lmemcpy_floop32:	
	ldmia	r1!, {r3, r4, r12, lr}
	stmia	r0!, {r3, r4, r12, lr}
	ldmia	r1!, {r3, r4, r12, lr}
	stmia	r0!, {r3, r4, r12, lr}
	subs	r2, r2, #0x20         
	bge	.Lmemcpy_floop32

	cmn	r2, #0x10
	ldmgeia	r1!, {r3, r4, r12, lr}	
	stmgeia	r0!, {r3, r4, r12, lr}
	subge	r2, r2, #0x10         
	ldmia	sp!, {r4}		

.Lmemcpy_fl32:
	adds	r2, r2, #0x14         

.Lmemcpy_floop12:
	ldmgeia	r1!, {r3, r12, lr}
	stmgeia	r0!, {r3, r12, lr}
	subges	r2, r2, #0x0c         
	bge	.Lmemcpy_floop12

.Lmemcpy_fl12:
	adds	r2, r2, #8
	blt	.Lmemcpy_fl4

	subs	r2, r2, #4
	ldrlt	r3, [r1], #4
	strlt	r3, [r0], #4
	ldmgeia	r1!, {r3, r12}
	stmgeia	r0!, {r3, r12}
	subge	r2, r2, #4

.Lmemcpy_fl4:
	adds	r2, r2, #4
	ldmeqia	sp!, {r0, pc}		

	cmp	r2, #2
	ldrb	r3, [r1], #1
	strb	r3, [r0], #1
	ldrgeb	r3, [r1], #1
	strgeb	r3, [r0], #1
	ldrgtb	r3, [r1], #1
	strgtb	r3, [r0], #1
	ldmia	sp!, {r0, pc}

.Lmemcpy_fdestul:
	rsb	r12, r12, #4
	cmp	r12, #2

	ldrb	r3, [r1], #1
	strb	r3, [r0], #1
	ldrgeb	r3, [r1], #1
	strgeb	r3, [r0], #1
	ldrgtb	r3, [r1], #1
	strgtb	r3, [r0], #1
	subs	r2, r2, r12
	blt	.Lmemcpy_fl4		

	ands	r12, r1, #3
	beq	.Lmemcpy_ft8		

.Lmemcpy_fsrcul:
	bic	r1, r1, #3
	ldr	lr, [r1], #4
	cmp	r12, #2
	bgt	.Lmemcpy_fsrcul3
	beq	.Lmemcpy_fsrcul2
	cmp	r2, #0x0c            
	blt	.Lmemcpy_fsrcul1loop4
	sub	r2, r2, #0x0c         
	stmdb	sp!, {r4, r5}

.Lmemcpy_fsrcul1loop16:
	mov	r3, lr, lsl #8
	ldmia	r1!, {r4, r5, r12, lr}
	orr	r3, r3, r4, lsr #24
	mov	r4, r4, lsl #8
	orr	r4, r4, r5, lsr #24
	mov	r5, r5, lsl #8
	orr	r5, r5, r12, lsr #24
	mov	r12, r12, lsl #8
	orr	r12, r12, lr, lsr #24
	stmia	r0!, {r3-r5, r12}
	subs	r2, r2, #0x10         
	bge	.Lmemcpy_fsrcul1loop16
	ldmia	sp!, {r4, r5}
	adds	r2, r2, #0x0c         
	blt	.Lmemcpy_fsrcul1l4

.Lmemcpy_fsrcul1loop4:
	mov	r12, lr, lsl #8
	ldr	lr, [r1], #4
	orr	r12, r12, lr, lsr #24
	str	r12, [r0], #4
	subs	r2, r2, #4
	bge	.Lmemcpy_fsrcul1loop4

.Lmemcpy_fsrcul1l4:
	sub	r1, r1, #3
	b	.Lmemcpy_fl4

.Lmemcpy_fsrcul2:
	cmp	r2, #0x0c            
	blt	.Lmemcpy_fsrcul2loop4
	sub	r2, r2, #0x0c         
	stmdb	sp!, {r4, r5}

.Lmemcpy_fsrcul2loop16:
	mov	r3, lr, lsl #16
	ldmia	r1!, {r4, r5, r12, lr}
	orr	r3, r3, r4, lsr #16
	mov	r4, r4, lsl #16
	orr	r4, r4, r5, lsr #16
	mov	r5, r5, lsl #16
	orr	r5, r5, r12, lsr #16
	mov	r12, r12, lsl #16
	orr	r12, r12, lr, lsr #16
	stmia	r0!, {r3-r5, r12}
	subs	r2, r2, #0x10         
	bge	.Lmemcpy_fsrcul2loop16
	ldmia	sp!, {r4, r5}
	adds	r2, r2, #0x0c         
	blt	.Lmemcpy_fsrcul2l4

.Lmemcpy_fsrcul2loop4:
	mov	r12, lr, lsl #16
	ldr	lr, [r1], #4
	orr	r12, r12, lr, lsr #16
	str	r12, [r0], #4
	subs	r2, r2, #4
	bge	.Lmemcpy_fsrcul2loop4

.Lmemcpy_fsrcul2l4:
	sub	r1, r1, #2
	b	.Lmemcpy_fl4

.Lmemcpy_fsrcul3:
	cmp	r2, #0x0c            
	blt	.Lmemcpy_fsrcul3loop4
	sub	r2, r2, #0x0c         
	stmdb	sp!, {r4, r5}

.Lmemcpy_fsrcul3loop16:
	mov	r3, lr, lsl #24
	ldmia	r1!, {r4, r5, r12, lr}
	orr	r3, r3, r4, lsr #8
	mov	r4, r4, lsl #24
	orr	r4, r4, r5, lsr #8
	mov	r5, r5, lsl #24
	orr	r5, r5, r12, lsr #8
	mov	r12, r12, lsl #24
	orr	r12, r12, lr, lsr #8
	stmia	r0!, {r3-r5, r12}
	subs	r2, r2, #0x10         
	bge	.Lmemcpy_fsrcul3loop16
	ldmia	sp!, {r4, r5}
	adds	r2, r2, #0x0c         
	blt	.Lmemcpy_fsrcul3l4

.Lmemcpy_fsrcul3loop4:
	mov	r12, lr, lsl #24
	ldr	lr, [r1], #4
	orr	r12, r12, lr, lsr #8
	str	r12, [r0], #4
	subs	r2, r2, #4
	bge	.Lmemcpy_fsrcul3loop4

.Lmemcpy_fsrcul3l4:
	sub	r1, r1, #1
	b	.Lmemcpy_fl4

.Lmemcpy_backwards:
	add	r1, r1, r2
	add	r0, r0, r2
	subs	r2, r2, #4
	blt	.Lmemcpy_bl4		
	ands	r12, r0, #3
	bne	.Lmemcpy_bdestul	
	ands	r12, r1, #3
	bne	.Lmemcpy_bsrcul		

.Lmemcpy_bt8:
	subs	r2, r2, #8
	blt	.Lmemcpy_bl12		
	stmdb	sp!, {r4, lr}
	subs	r2, r2, #0x14		
	blt	.Lmemcpy_bl32

.Lmemcpy_bloop32:
	ldmdb	r1!, {r3, r4, r12, lr}
	stmdb	r0!, {r3, r4, r12, lr}
	ldmdb	r1!, {r3, r4, r12, lr}
	stmdb	r0!, {r3, r4, r12, lr}
	subs	r2, r2, #0x20         
	bge	.Lmemcpy_bloop32

.Lmemcpy_bl32:
	cmn	r2, #0x10            
	ldmgedb	r1!, {r3, r4, r12, lr}	
	stmgedb	r0!, {r3, r4, r12, lr}
	subge	r2, r2, #0x10         
	adds	r2, r2, #0x14         
	ldmgedb	r1!, {r3, r12, lr}	
	stmgedb	r0!, {r3, r12, lr}
	subge	r2, r2, #0x0c         
	ldmia	sp!, {r4, lr}

.Lmemcpy_bl12:
	adds	r2, r2, #8
	blt	.Lmemcpy_bl4
	subs	r2, r2, #4
	ldrlt	r3, [r1, #-4]!
	strlt	r3, [r0, #-4]!
	ldmgedb	r1!, {r3, r12}
	stmgedb	r0!, {r3, r12}
	subge	r2, r2, #4

.Lmemcpy_bl4:
	adds	r2, r2, #4
	moveq	pc, lr			

	cmp	r2, #2
	ldrb	r3, [r1, #-1]!
	strb	r3, [r0, #-1]!
	ldrgeb	r3, [r1, #-1]!
	strgeb	r3, [r0, #-1]!
	ldrgtb	r3, [r1, #-1]!
	strgtb	r3, [r0, #-1]!
	mov	pc, lr

.Lmemcpy_bdestul:
	cmp	r12, #2

	ldrb	r3, [r1, #-1]!
	strb	r3, [r0, #-1]!
	ldrgeb	r3, [r1, #-1]!
	strgeb	r3, [r0, #-1]!
	ldrgtb	r3, [r1, #-1]!
	strgtb	r3, [r0, #-1]!
	subs	r2, r2, r12
	blt	.Lmemcpy_bl4		
	ands	r12, r1, #3
	beq	.Lmemcpy_bt8		

.Lmemcpy_bsrcul:
	bic	r1, r1, #3
	ldr	r3, [r1, #0]
	cmp	r12, #2
	blt	.Lmemcpy_bsrcul1
	beq	.Lmemcpy_bsrcul2
	cmp	r2, #0x0c            
	blt	.Lmemcpy_bsrcul3loop4
	sub	r2, r2, #0x0c         
	stmdb	sp!, {r4, r5, lr}

.Lmemcpy_bsrcul3loop16:
	mov	lr, r3, lsr #8
	ldmdb	r1!, {r3-r5, r12}
	orr	lr, lr, r12, lsl #24
	mov	r12, r12, lsr #8
	orr	r12, r12, r5, lsl #24
	mov	r5, r5, lsr #8
	orr	r5, r5, r4, lsl #24
	mov	r4, r4, lsr #8
	orr	r4, r4, r3, lsl #24
	stmdb	r0!, {r4, r5, r12, lr}
	subs	r2, r2, #0x10         
	bge	.Lmemcpy_bsrcul3loop16
	ldmia	sp!, {r4, r5, lr}
	adds	r2, r2, #0x0c         
	blt	.Lmemcpy_bsrcul3l4

.Lmemcpy_bsrcul3loop4:
	mov	r12, r3, lsr #8
	ldr	r3, [r1, #-4]!
	orr	r12, r12, r3, lsl #24
	str	r12, [r0, #-4]!
	subs	r2, r2, #4
	bge	.Lmemcpy_bsrcul3loop4

.Lmemcpy_bsrcul3l4:
	add	r1, r1, #3
	b	.Lmemcpy_bl4

.Lmemcpy_bsrcul2:
	cmp	r2, #0x0c            
	blt	.Lmemcpy_bsrcul2loop4
	sub	r2, r2, #0x0c         
	stmdb	sp!, {r4, r5, lr}

.Lmemcpy_bsrcul2loop16:
	mov	lr, r3, lsr #16
	ldmdb	r1!, {r3-r5, r12}
	orr	lr, lr, r12, lsl #16
	mov	r12, r12, lsr #16
	orr	r12, r12, r5, lsl #16
	mov	r5, r5, lsr #16
	orr	r5, r5, r4, lsl #16
	mov	r4, r4, lsr #16
	orr	r4, r4, r3, lsl #16
	stmdb	r0!, {r4, r5, r12, lr}
	subs	r2, r2, #0x10         
	bge	.Lmemcpy_bsrcul2loop16
	ldmia	sp!, {r4, r5, lr}
	adds	r2, r2, #0x0c         
	blt	.Lmemcpy_bsrcul2l4

.Lmemcpy_bsrcul2loop4:
	mov	r12, r3, lsr #16
	ldr	r3, [r1, #-4]!
	orr	r12, r12, r3, lsl #16
	str	r12, [r0, #-4]!
	subs	r2, r2, #4
	bge	.Lmemcpy_bsrcul2loop4

.Lmemcpy_bsrcul2l4:
	add	r1, r1, #2
	b	.Lmemcpy_bl4

.Lmemcpy_bsrcul1:
	cmp	r2, #0x0c            
	blt	.Lmemcpy_bsrcul1loop4
	sub	r2, r2, #0x0c         
	stmdb	sp!, {r4, r5, lr}

.Lmemcpy_bsrcul1loop32:
	mov	lr, r3, lsr #24
	ldmdb	r1!, {r3-r5, r12}
	orr	lr, lr, r12, lsl #8
	mov	r12, r12, lsr #24
	orr	r12, r12, r5, lsl #8
	mov	r5, r5, lsr #24
	orr	r5, r5, r4, lsl #8
	mov	r4, r4, lsr #24
	orr	r4, r4, r3, lsl #8
	stmdb	r0!, {r4, r5, r12, lr}
	subs	r2, r2, #0x10         
	bge	.Lmemcpy_bsrcul1loop32
	ldmia	sp!, {r4, r5, lr}
	adds	r2, r2, #0x0c         
	blt	.Lmemcpy_bsrcul1l4

.Lmemcpy_bsrcul1loop4:
	mov	r12, r3, lsr #24
	ldr	r3, [r1, #-4]!
	orr	r12, r12, r3, lsl #8
	str	r12, [r0, #-4]!
	subs	r2, r2, #4
	bge	.Lmemcpy_bsrcul1loop4

.Lmemcpy_bsrcul1l4:
	add	r1, r1, #1
	b	.Lmemcpy_bl4

@------------------------------------------------------------------------------
