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

@-----------------------------------------------------------------------------------------

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

@-----------------------------------------------------------------------------------------

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

@-----------------------------------------------------------------------------------------

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

@-----------------------------------------------------------------------------------------

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

@-----------------------------------------------------------------------------------------

        .if ByteOrderBE

        .macro CpyShift a, b

        mov     \a, \a, lsl lr
        orr     \a, \b, lsr ip

        .endm

        .endif

@-----------------------------------------------------------------------------------------

        .if ByteOrderLE

        .macro CpyShift a, b

        mov     \a, \a, lsr lr
        orr     \a, \b, lsl ip

        .endm

        .endif

@-----------------------------------------------------------------------------------------

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

        push    {r4-r10}

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

        pop     {r4-r10}

        mov     pc, lr

badcpy:  @@  r1 is aligned, r0 is not aligned , r2 >= 8

        cmp     r2, #36
        bcs     badcpy_big

        push    {r4,lr}

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
        popeq   {r4,pc}

        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1

        pop     {r4,pc}

badcpy_big:  @@  r1 is aligned, r0 is not aligned , r2 >= 36

        push    {r4-r11,lr}

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
        popeq   {r4-r11,pc}

        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1
        ldrb    ip, [r1], #1
        strb    ip, [r0], #1

        pop     {r4-r11,pc}

__std_memcpy:

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

@-----------------------------------------------------------------------------------------

