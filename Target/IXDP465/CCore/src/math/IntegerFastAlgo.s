@ IntegerFastAlgo.s
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
@  Copyright (c) 2011 Sergey Strukov. All rights reserved.
@
@-----------------------------------------------------------------------------------------

        .text
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo12CountZeroMSBEj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo12CountZeroMSBEj:       @  unsigned CCore::Math::IntegerFastAlgo::CountZeroMSB(Unit a)

        clz     r0, r0
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

@        .global _ZN5CCore4Math15IntegerFastAlgo4NullEPjj
         
        .align 2

@_ZN5CCore4Math15IntegerFastAlgo4NullEPjj:              @  void CCore::Math::IntegerFastAlgo::Null(Unit *a,ulen na)

        tst     r1, r1
        moveq   pc, lr
        
        mov     r2, #0
        mov     r3, #0
        
        tst     r0, #4
        beq     1f
        
        strcs   r2, [r0],#4
        subs    r1, r1, #1
        moveq   pc, lr
1:        
        movs    r1, r1, LSR #1
        adc     ip, r2, #0
        
        movs    r1, r1, LSR #1
        strcsd  r2, [r0],#8
        
        movs    r1, r1, LSR #1
        strcsd  r2, [r0],#8
        strcsd  r2, [r0],#8
        
        tst     r1, r1
        beq     3f
2:        
        strd    r2, [r0],#8
        strd    r2, [r0],#8
        strd    r2, [r0],#8
        strd    r2, [r0],#8
        
        subs    r1, #1
        bne     2b
3:
        tst     ip, ip    
        strne   r2, [r0],#4
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo4NullEPjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo4NullEPjj:              @  void CCore::Math::IntegerFastAlgo::Null(Unit *a,ulen na)

        tst     r1, r1
        moveq   pc, lr
        
        mov     ip, #0

        movs    r1, r1, LSR #1
        strcs   ip, [r0],#4
        
        movs    r1, r1, LSR #1
        strcs   ip, [r0],#4
        strcs   ip, [r0],#4
        
        movs    r1, r1, LSR #1
        strcs   ip, [r0],#4
        strcs   ip, [r0],#4
        strcs   ip, [r0],#4
        strcs   ip, [r0],#4

        tst     r1, r1
        moveq   pc, lr
1:        
        str     ip, [r0],#4
        str     ip, [r0],#4
        str     ip, [r0],#4
        str     ip, [r0],#4
        str     ip, [r0],#4
        str     ip, [r0],#4
        str     ip, [r0],#4
        str     ip, [r0],#4
        
        subs    r1, #1
        bne     1b

        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo6MoveUpEPjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo6MoveUpEPjjj:            @  void CCore::Math::IntegerFastAlgo::MoveUp(Unit *a,ulen na,ulen delta)

        tst     r1, r1
        moveq   pc, lr
        
        stmfd   sp!, {r4-r9}
        
        add     r0, r0, r1, LSL #2
        add     r2, r0, r2, LSL #2

        movs    r1, r1, LSR #1
        ldrcs   ip, [r0,#-4]!
        strcs   ip, [r2,#-4]!
        
        movs    r1, r1, LSR #1
        ldmcsdb r0!, {r3,r4}
        stmcsdb r2!, {r3,r4}
        
        movs    r1, r1, LSR #1
        ldmcsdb r0!, {r3-r6}
        stmcsdb r2!, {r3-r6}
        
        tst     r1, r1
        beq     2f
1:
        ldmdb   r0!, {r3-r9,ip}
        stmdb   r2!, {r3-r9,ip}

        subs    r1, #1
        bne     1b
2:        
        ldmfd   sp!, {r4-r9}
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo8MoveDownEPjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo8MoveDownEPjjj:          @  void CCore::Math::IntegerFastAlgo::MoveDown(Unit *a,ulen na,ulen delta)  

        tst     r1, r1
        moveq   pc, lr
        
        stmfd   sp!, {r4-r9}
        
        add     r2, r0, r2, LSL #2
        
        movs    r1, r1, LSR #1
        ldrcs   ip, [r2],#4
        strcs   ip, [r0],#4
        
        movs    r1, r1, LSR #1
        ldmcsia r2!, {r3,r4}
        stmcsia r0!, {r3,r4}
        
        movs    r1, r1, LSR #1
        ldmcsia r2!, {r3-r6}
        stmcsia r0!, {r3-r6}

        tst     r1, r1
        beq     2f
1:
        ldmia   r2!, {r3-r9,ip}
        stmia   r0!, {r3-r9,ip}

        subs    r1, #1
        bne     1b
2:        
        ldmfd   sp!, {r4-r9}
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo4UAddEPjPKjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo4UAddEPjPKjj:            @  Unit CCore::Math::IntegerFastAlgo::UAdd(Unit *restrict b,const Unit *a,ulen nab)  

        tst     r2, r2
        moveq   r0, r2
        moveq   pc, lr

        stmfd   sp!, {r4-r11}
        
        mov     r11, #0
        mov     ip, #0
        
        movs    r2, r2, LSR #1
        bcc     1f
        
        ldr     r3, [r0]
        ldr     r7, [r1],#4
        
        cmp     r11, #1        
        adcs    r3, r3, r7
        adc     r11, ip, #0
        
        str     r3, [r0],#4
        
1:        
        movs    r2, r2, LSR #1
        bcc     2f
        
        ldmia   r0, {r3,r4}
        ldmia   r1!, {r7,r8}

        cmp     r11, #1        
        adcs    r3, r3, r7
        adcs    r4, r4, r8
        adc     r11, ip, #0
        
        stmia   r0!, {r3,r4}
        
2:        
        tst     r2, r2
        beq     4f        
3:        
        ldmia   r0, {r3,r4,r5,r6}
        ldmia   r1!, {r7,r8,r9,r10}

        cmp     r11, #1        
        adcs    r3, r3, r7
        adcs    r4, r4, r8
        adcs    r5, r5, r9
        adcs    r6, r6, r10
        adc     r11, ip, #0
        
        stmia   r0!, {r3,r4,r5,r6}
        
        subs    r2, #1
        bne     3b
4:        
        mov     r0, r11
        
        ldmfd   sp!, {r4-r11}

        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo4USubEPjPKjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo4USubEPjPKjj:            @  Unit CCore::Math::IntegerFastAlgo::USub(Unit *restrict b,const Unit *a,ulen nab)  

        tst     r2, r2
        moveq   r0, r2
        moveq   pc, lr

        stmfd   sp!, {r4-r11}
        
        mov     r11, #1
        mov     ip, #0
        
        movs    r2, r2, LSR #1
        bcc     1f
        
        ldr     r3, [r0]
        ldr     r7, [r1],#4
        
        cmp     r11, #1        
        sbcs    r3, r3, r7
        adc     r11, ip, #0
        
        str     r3, [r0],#4
        
1:        
        movs    r2, r2, LSR #1
        bcc     2f
        
        ldmia   r0, {r3,r4}
        ldmia   r1!, {r7,r8}

        cmp     r11, #1        
        sbcs    r3, r3, r7
        sbcs    r4, r4, r8
        adc     r11, ip, #0
        
        stmia   r0!, {r3,r4}
        
2:        
        tst     r2, r2
        beq     4f        
3:        
        ldmia   r0, {r3,r4,r5,r6}
        ldmia   r1!, {r7,r8,r9,r10}

        cmp     r11, #1        
        sbcs    r3, r3, r7
        sbcs    r4, r4, r8
        sbcs    r5, r5, r9
        sbcs    r6, r6, r10
        adc     r11, ip, #0
        
        stmia   r0!, {r3,r4,r5,r6}
        
        subs    r2, #1
        bne     3b
4:        
        rsb     r0, r11, #1
        
        ldmfd   sp!, {r4-r11}

        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo7URevSubEPjPKjj 
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo7URevSubEPjPKjj:         @  Unit CCore::Math::IntegerFastAlgo::URevSub(Unit *restrict b,const Unit *a,ulen nab)  

        tst     r2, r2
        moveq   r0, r2
        moveq   pc, lr

        stmfd   sp!, {r4-r11}
        
        mov     r11, #1
        mov     ip, #0
        
        movs    r2, r2, LSR #1
        bcc     1f
        
        ldr     r3, [r0]
        ldr     r7, [r1],#4
        
        cmp     r11, #1        
        sbcs    r3, r7, r3
        adc     r11, ip, #0
        
        str     r3, [r0],#4
        
1:        
        movs    r2, r2, LSR #1
        bcc     2f
        
        ldmia   r0, {r3,r4}
        ldmia   r1!, {r7,r8}

        cmp     r11, #1        
        sbcs    r3, r7, r3
        sbcs    r4, r8, r4
        adc     r11, ip, #0
        
        stmia   r0!, {r3,r4}
        
2:        
        tst     r2, r2
        beq     4f        
3:        
        ldmia   r0, {r3,r4,r5,r6}
        ldmia   r1!, {r7,r8,r9,r10}

        cmp     r11, #1        
        sbcs    r3, r7, r3
        sbcs    r4, r8, r4
        sbcs    r5, r9, r5
        sbcs    r6, r10, r6
        adc     r11, ip, #0
        
        stmia   r0!, {r3,r4,r5,r6}
        
        subs    r2, #1
        bne     3b
4:        
        rsb     r0, r11, #1
        
        ldmfd   sp!, {r4-r11}

        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

@        .global _ZN5CCore4Math15IntegerFastAlgo7ULShiftEPjjj
         
        .align 2

@_ZN5CCore4Math15IntegerFastAlgo7ULShiftEPjjj:           @  Unit CCore::Math::IntegerFastAlgo::ULShift(Unit *a,ulen na,unsigned shift)  

        tst     r1, r1
        moveq   r0, #0
        moveq   pc, lr
        
        stmfd   sp!, {r4,r5}
        
        add     r0, r0, r1, LSL #2
        rsb     ip, r2, #32
        
        ldr     r3, [r0,#-4]!
        mov     r5, r3, LSR ip
        subs    r1, #1
        beq     2f

1:        
        ldr     r4, [r0,#-4]
        
        mov     r3, r3, LSL r2
        orr     r3, r3, r4, LSR ip      
        
        str     r3, [r0],#-4
        mov     r3, r4        
        
        subs    r1, #1
        bne     1b                    
2:
        mov     r3, r3, LSL r2
        str     r3, [r0]
        
        mov     r0, r5
        
        ldmfd   sp!, {r4,r5}
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo7ULShiftEPjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo7ULShiftEPjjj:           @  Unit CCore::Math::IntegerFastAlgo::ULShift(Unit *a,ulen na,unsigned shift)  

        tst     r1, r1
        moveq   r0, #0
        moveq   pc, lr
        
        stmfd   sp!, {r4-r8}
        
        add     r0, r0, r1, LSL #2
        rsb     ip, r2, #32
        
        ldr     r8, [r0,#-4]!
        mov     r3, r8, LSR ip
        subs    r1, #1
        beq     4f

        movs    r1, r1, LSR #1
        bcc     1f
        
        ldr     r7, [r0,#-4]
        
        mov     r8, r8, LSL r2
        orr     r8, r8, r7, LSR ip
        
        str     r8, [r0],#-4 

        mov     r8, r7        
        
1:        
        movs    r1, r1, LSR #1
        bcc     2f
        
        ldmdb   r0, {r6,r7}
        
        mov     r8, r8, LSL r2
        orr     r8, r8, r7, LSR ip
        
        mov     r7, r7, LSL r2
        orr     r7, r7, r6, LSR ip
        
        stmda   r0!, {r7,r8}
                      
        mov     r8, r6     
                      
2:
        tst     r1, r1
        beq     4f
3:
        ldmdb   r0, {r4-r7}
        
        mov     r8, r8, LSL r2
        orr     r8, r8, r7, LSR ip
        
        mov     r7, r7, LSL r2
        orr     r7, r7, r6, LSR ip              
        
        mov     r6, r6, LSL r2
        orr     r6, r6, r5, LSR ip
                      
        mov     r5, r5, LSL r2
        orr     r5, r5, r4, LSR ip
        
        stmda   r0!, {r5-r8} 
                      
        mov     r8, r4     

        subs    r1, #1
        bne     3b                    
4:        
        mov     r8, r8, LSL r2
        str     r8, [r0]
        
        mov     r0, r3
        
        ldmfd   sp!, {r4-r8}
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo6LShiftEPjPKjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo6LShiftEPjPKjjj:         @  Unit CCore::Math::IntegerFastAlgo::LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)

        tst     r2, r2
        moveq   r0, #0
        moveq   pc, lr
        
        stmfd   sp!, {r4-r9}

        add     r0, r0, r2, LSL #2
        add     r1, r1, r2, LSL #2
        rsb     ip, r3, #32
        
        ldr     r8, [r1,#-4]!
        sub     r0, r0, #4
        mov     r9, r8, ASR #31
        mov     r9, r9, LSL r3
        orr     r9, r9, r8, LSR ip
LShift:        
        subs    r2, #1
        beq     4f
  
        movs    r2, r2, LSR #1
        bcc     1f
        
        ldr     r7, [r1,#-4]!
        
        mov     r8, r8, LSL r3
        orr     r8, r8, r7, LSR ip
        
        str     r8, [r0],#-4 

        mov     r8, r7        
        
1:        
        movs    r2, r2, LSR #1
        bcc     2f
        
        ldmdb   r1!, {r6,r7}
        
        mov     r8, r8, LSL r3
        orr     r8, r8, r7, LSR ip
        
        mov     r7, r7, LSL r3
        orr     r7, r7, r6, LSR ip
        
        stmda   r0!, {r7,r8}
                      
        mov     r8, r6     
                      
2:
        tst     r2, r2
        beq     4f
3:
        ldmdb   r1!, {r4-r7}
        
        mov     r8, r8, LSL r3
        orr     r8, r8, r7, LSR ip
        
        mov     r7, r7, LSL r3
        orr     r7, r7, r6, LSR ip              
        
        mov     r6, r6, LSL r3
        orr     r6, r6, r5, LSR ip
                      
        mov     r5, r5, LSL r3
        orr     r5, r5, r4, LSR ip
        
        stmda   r0!, {r5-r8} 
                      
        mov     r8, r4     

        subs    r2, #1
        bne     3b                    
4:        
        mov     r8, r8, LSL r3
        str     r8, [r0]
        
        mov     r0, r9
        
        ldmfd   sp!, {r4-r9}
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo8UShiftUpEPjjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo8UShiftUpEPjjjj:         @  Unit CCore::Math::IntegerFastAlgo::UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift)  

        tst     r1, r1
        moveq   r0, #0
        moveq   pc, lr
        
        stmfd   sp!, {r4-r9}

        mov     ip, r1
        add     r1, r0, ip, LSL #2
        add     r0, r1, r2, LSL #2
        mov     r2, ip
        rsb     ip, r3, #32
        
        ldr     r8, [r1,#-4]!
        sub     r0, r0, #4
        mov     r9, r8, LSR ip

        b       LShift

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo7ShiftUpEPjjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo7ShiftUpEPjjjj:          @  Unit CCore::Math::IntegerFastAlgo::ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift)  

        tst     r1, r1
        moveq   r0, #0
        moveq   pc, lr
        
        stmfd   sp!, {r4-r9}

        mov     ip, r1
        add     r1, r0, ip, LSL #2
        add     r0, r1, r2, LSL #2
        mov     r2, ip
        rsb     ip, r3, #32
        
        ldr     r8, [r1,#-4]!
        sub     r0, r0, #4
        mov     r9, r8, ASR #31
        mov     r9, r9, LSL r3
        orr     r9, r9, r8, LSR ip

        b       LShift

@-----------------------------------------------------------------------------------------

@        .global _ZN5CCore4Math15IntegerFastAlgo7URShiftEPjjj
         
        .align 2

@_ZN5CCore4Math15IntegerFastAlgo7URShiftEPjjj:           @  void CCore::Math::IntegerFastAlgo::URShift(Unit *a,ulen na,unsigned shift) 

        tst     r1, r1
        moveq   pc, lr
        
        stmfd   sp!, {r4}
        
        ldr     r3, [r0]
        rsb     ip, r2, #32
        subs    r1, #1
        beq     2f
1:
        ldr     r4, [r0,#4]
        
        mov     r3, r3, LSR r2
        orr     r3, r4, LSL ip
        
        str     r3, [r0],#4
        mov     r3, r4

        subs    r1, #1
        bne     1b        
2:
        mov     r3, r3, LSR r2
        str     r3, [r0]
        
        ldmfd   sp!, {r4}
        
        mov     pc, lr       

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo7URShiftEPjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo7URShiftEPjjj:           @  void CCore::Math::IntegerFastAlgo::URShift(Unit *a,ulen na,unsigned shift) 

        tst     r1, r1
        moveq   pc, lr
        
        stmfd   sp!, {r4-r7}
        
        ldr     r3, [r0]
        rsb     ip, r2, #32
        subs    r1, #1
        beq     4f
        
        movs    r1, r1, LSR #1
        bcc     1f
        
        ldr     r4, [r0,#4]
        
        mov     r3, r3, LSR r2
        orr     r3, r4, LSL ip
        
        str     r3, [r0],#4
        mov     r3, r4
        
1:
        movs    r1, r1, LSR #1
        bcc     2f
        
        ldmib   r0, {r4,r5}

        mov     r3, r3, LSR r2
        orr     r3, r4, LSL ip
        
        mov     r4, r4, LSR r2
        orr     r4, r5, LSL ip
        
        stmia   r0!, {r3,r4}
        mov     r3, r5
        
2:
        tst     r1, r1
        beq     4f        
3:        
        ldmib   r0, {r4-r7}    

        mov     r3, r3, LSR r2
        orr     r3, r4, LSL ip
        
        mov     r4, r4, LSR r2
        orr     r4, r5, LSL ip
        
        mov     r5, r5, LSR r2
        orr     r5, r6, LSL ip
        
        mov     r6, r6, LSR r2
        orr     r6, r7, LSL ip
        
        stmia   r0!, {r3-r6}
        mov     r3, r7
        
        subs    r1, #1
        bne     3b        
4:
        mov     r3, r3, LSR r2
        str     r3, [r0]
        
        ldmfd   sp!, {r4-r7}
        
        mov     pc, lr       

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo6RShiftEPjPKjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo6RShiftEPjPKjjj:         @  void CCore::Math::IntegerFastAlgo::RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)  

        tst     r2, r2
        moveq   pc, lr
        
        stmfd   sp!, {r4-r9}
        
        mov     r9, #1
RShift:        
        ldr     r4, [r1],#4
        rsb     ip, r3, #32
        subs    r2, #1
        beq     4f
        
        movs    r2, r2, LSR #1
        bcc     1f
        
        ldr     r5, [r1],#4
        
        mov     r4, r4, LSR r3
        orr     r4, r5, LSL ip
        
        str     r4, [r0],#4
        mov     r4, r5
        
1:        
        movs    r2, r2, LSR #1
        bcc     2f
        
        ldmia   r1!, {r5,r6}    

        mov     r4, r4, LSR r3
        orr     r4, r5, LSL ip
        
        mov     r5, r5, LSR r3
        orr     r5, r6, LSL ip
        
        stmia   r0!, {r4,r5}
        mov     r4, r6
        
2:
        tst     r2, r2
        beq     4f        
3:
        ldmia   r1!, {r5-r8}    

        mov     r4, r4, LSR r3
        orr     r4, r5, LSL ip
        
        mov     r5, r5, LSR r3
        orr     r5, r6, LSL ip
        
        mov     r6, r6, LSR r3
        orr     r6, r7, LSL ip
        
        mov     r7, r7, LSR r3
        orr     r7, r8, LSL ip
        
        stmia   r0!, {r4-r7}
        mov     r4, r8
        
        subs    r2, #1
        bne     3b        
        
4:
        tst     r9, r9
        movne   r4, r4, ASR r3
        moveq   r4, r4, LSR r3
        str     r4, [r0]

        ldmfd   sp!, {r4-r9}
        
        mov     pc, lr       
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo10UShiftDownEPjjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo10UShiftDownEPjjjj:      @  void CCore::Math::IntegerFastAlgo::UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift)  

        tst     r1, r1
        moveq   pc, lr
        
        stmfd   sp!, {r4-r9}

        mov     r9, #0
        mov     ip, r1
        add     r1, r0, r2, LSL #2
        mov     r2, ip
        
        b       RShift

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo9ShiftDownEPjjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo9ShiftDownEPjjjj:        @  void CCore::Math::IntegerFastAlgo::ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift)  

        tst     r1, r1
        moveq   pc, lr
        
        stmfd   sp!, {r4-r9}

        mov     r9, #1
        mov     ip, r1
        add     r1, r0, r2, LSL #2
        mov     r2, ip
        
        b       RShift

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo7RawUMulEPjPKjjS4_j
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo7RawUMulEPjPKjjS4_j:     @  void CCore::Math::IntegerFastAlgo::RawUMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)

        stmfd   sp!, {r4-r11,lr}
        sub     sp, #4
        
        ldr     r10, [r1]
        ldr     r11, [r3]
        umull   r4, r5, r10, r11
        mov     r6, #0
        mov     r7, #0
        
        str     r4, [r0],#4

        mov     r4, #1
        add     r3, #4
1:
        add     r4, #1
        add     r3, #4
        str     r4, [sp]
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        str     r5, [r0],#4
        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        cmp     r4, r2     
        bne     1b

        ldr     r4, [sp,#40]
        subs    r4, r4, r2
        beq     3f
        add     r4, r3, r4, LSL #2
        str     r4, [sp]
1:
        add     r3, #4
        mov     r4, r2
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        str     r5, [r0],#4
        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        cmp     r3, r4
        bne     1b
3:

        cmp     r2, #2
        beq     4f
        sub     r4, r2, #1
        
1:
        str     r4, [sp]
        add     r1, #4
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        str     r5, [r0],#4
        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        sub     r4, #1
        cmp     r4, #1
        bne     1b
4:
        
        ldr     r10, [r1,#4]
        ldr     r11, [r3,#-4]
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adc     r6, r6, r9

        stmia   r0, {r5,r6}

        add     sp, #4
        ldmfd   sp!, {r4-r11,pc}

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo8RawUMul1EPjjPKjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo8RawUMul1EPjjPKjj:       @  void CCore::Math::IntegerFastAlgo::RawUMul1(Unit *restrict c,Unit a,const Unit *b,ulen nb)  

        stmfd   sp!, {r4-r6}

        ldr     ip, [r2],#4
        umull   r5, r4, r1, ip
        str     r5, [r0],#4
        sub     r3, #1
1:
        ldr     ip, [r2],#4
        umull   r5, r6, r1, ip
        adds    r5, r5, r4
        adc     r4, r6, #0
        str     r5, [r0],#4
        
        subs    r3, #1
        bne     1b   

        str     r4, [r0]
        
        ldmfd   sp!, {r4-r6}
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo9RawUMul11EPjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo9RawUMul11EPjjj:         @  void CCore::Math::IntegerFastAlgo::RawUMul11(Unit *c,Unit a,Unit b)  

        umull   r3, ip, r1, r2
        
        str     r3, [r0]
        str     ip, [r0,#4]
        
        mov     pc, lr        

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo7RawUMacEPjPKjjS4_j
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo7RawUMacEPjPKjjS4_j:     @  Unit CCore::Math::IntegerFastAlgo::RawUMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)  

        stmfd   sp!, {r4-r11,lr}
        sub     sp, #8
        
        ldr     r10, [r1]
        ldr     r11, [r3]
        umull   r4, r5, r10, r11
        mov     r6, #0
        mov     r7, #0
        
        ldr     r10, [r0]
        mov     r11, #0
        adds    r4, r4, r10     
        adc     r11, r11, #0
        str     r4, [r0],#4
        str     r11, [sp,#4] 

        mov     r4, #1
        add     r3, #4
1:
        add     r4, #1
        add     r3, #4
        str     r4, [sp]
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        ldr     r10, [r0]
        ldr     r11, [sp,#4]
        cmp     r11, #1
        adcs    r5, r5, r10     
        mov     r11, #0
        adc     r11, r11, #0
        str     r5, [r0],#4
        str     r11, [sp,#4]
         
        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        cmp     r4, r2     
        bne     1b

        ldr     r4, [sp,#44]
        subs    r4, r4, r2
        beq     3f
        add     r4, r3, r4, LSL #2
        str     r4, [sp]
1:
        add     r3, #4
        mov     r4, r2
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        ldr     r10, [r0]
        ldr     r11, [sp,#4]
        cmp     r11, #1
        adcs    r5, r5, r10     
        mov     r11, #0
        adc     r11, r11, #0
        str     r5, [r0],#4
        str     r11, [sp,#4]
        
        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        cmp     r3, r4
        bne     1b
3:

        cmp     r2, #2
        beq     4f
        sub     r4, r2, #1
        
1:
        str     r4, [sp]
        add     r1, #4
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        ldr     r10, [r0]
        ldr     r11, [sp,#4]
        cmp     r11, #1
        adcs    r5, r5, r10     
        mov     r11, #0
        adc     r11, r11, #0
        str     r5, [r0],#4
        str     r11, [sp,#4]

        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        sub     r4, #1
        cmp     r4, #1
        bne     1b
4:
        
        ldr     r10, [r1,#4]
        ldr     r11, [r3,#-4]
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adc     r6, r6, r9

        ldmia   r0, {r8,r9}    
        ldr     r11, [sp,#4]
        cmp     r11, #1
        adcs    r5, r5, r8
        adcs    r6, r6, r9
        stmia   r0, {r5,r6}
        mov     r0, #0
        adc     r0, r0, #0
        
        add     sp, #8
        ldmfd   sp!, {r4-r11,pc}

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo8RawUMac1EPjjPKjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo8RawUMac1EPjjPKjj:       @  Unit CCore::Math::IntegerFastAlgo::RawUMac1(Unit *restrict c,Unit a,const Unit *b,ulen nb)  

        stmfd   sp!, {r4-r7}

        ldr     ip, [r2],#4
        ldr     r7, [r0]
        umull   r5, r4, r1, ip
        adds    r5, r5, r7
        adc     r4, r4, #0
        str     r5, [r0],#4
        sub     r3, #1
1:
        ldr     ip, [r2],#4
        ldr     r7, [r0]
        umull   r5, r6, r1, ip
        adds    r5, r5, r4
        adc     r4, r6, #0
        adds    r5, r5, r7               
        adc     r4, r4, #0
        
        str     r5, [r0],#4
        
        subs    r3, #1
        bne     1b   

        ldr     r7, [r0]
        adds    r4, r4, r7
        str     r4, [r0]
        
        mov     r0, #0
        adc     r0, r0, #0
        
        ldmfd   sp!, {r4-r7}
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo9RawUMac11EPjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo9RawUMac11EPjjj:         @  Unit CCore::Math::IntegerFastAlgo::RawUMac11(Unit *c,Unit a,Unit b)  

        umull   r3, ip, r1, r2

        ldmia   r0, {r1,r2}     

        adds    r1, r1, r3
        adcs    r2, r2, ip        
        
        stmia   r0, {r1,r2}
        
        mov     r0, #0
        adc     r0, r0, #0
        
        mov     pc, lr
                
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo9RawUMulLoEPjjPKjjS4_j
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo9RawUMulLoEPjjPKjjS4_j:  @  void CCore::Math::IntegerFastAlgo::RawUMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb)  

        mov     ip, r1
        mov     r1, r2
        mov     r2, r3
        ldr     r3, [sp]
        str     ip, [sp]

        stmfd   sp!, {r4-r11,lr}
        sub     sp, #4
        
        ldr     r10, [r1]
        ldr     r11, [r3]
        umull   r4, r5, r10, r11
        mov     r6, #0
        mov     r7, #0
        
        str     r4, [r0],#4
        ldr     r10, [sp,#40]
        subs    r10, #1
        beq     9f
        str     r10, [sp,#40]    

        mov     r4, #1
        add     r3, #4
1:
        add     r4, #1
        add     r3, #4
        str     r4, [sp]
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        str     r5, [r0],#4
        ldr     r10, [sp,#40]
        subs    r10, #1
        beq     9f
        str     r10, [sp,#40]    
        
        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        cmp     r4, r2     
        bne     1b

        ldr     r4, [sp,#44]
        subs    r4, r4, r2
        beq     3f
        add     r4, r3, r4, LSL #2
        str     r4, [sp]
1:
        add     r3, #4
        mov     r4, r2
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        str     r5, [r0],#4
        ldr     r10, [sp,#40]
        subs    r10, #1
        beq     9f
        str     r10, [sp,#40]
            
        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        cmp     r3, r4
        bne     1b
3:

        cmp     r2, #2
        beq     4f
        sub     r4, r2, #1
        
1:
        str     r4, [sp]
        add     r1, #4
        mov     r12, r1
        mov     r14, r3
2:
        ldr     r10, [r12],#4
        ldr     r11, [r14,#-4]!
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adcs    r6, r6, r9
        adc     r7, r7, #0
        
        subs    r4, #1
        bne     2b        
        
        str     r5, [r0],#4
        ldr     r10, [sp,#40]
        subs    r10, #1
        beq     9f
        str     r10, [sp,#40]
            
        mov     r5, r6
        mov     r6, r7
        mov     r7, #0

        ldr     r4, [sp]
        sub     r4, #1
        cmp     r4, #1
        bne     1b
4:
        
        ldr     r10, [r1,#4]
        ldr     r11, [r3,#-4]
        umull   r8, r9, r10, r11
        adds    r5, r5, r8
        adc     r6, r6, r9

        str     r5, [r0],#4
        ldr     r10, [sp,#40]
        subs    r10, #1
        strne   r6, [r0]
        
9:
        add     sp, #4
        ldmfd   sp!, {r4-r11,pc}

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo10RawUMulLo1EPjjjPKjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo10RawUMulLo1EPjjjPKjj:   @  void CCore::Math::IntegerFastAlgo::RawUMulLo1(Unit *restrict c,ulen nc,Unit a,const Unit *b,ulen nb)  

        stmfd   sp!, {r4-r6}

        ldr     ip, [r3],#4
        umull   r5, r4, r2, ip
        str     r5, [r0],#4
        subs    r1, #1
        beq     2f
        ldr     ip, [sp,#12]
        cmp     r1, ip
        beq     3f
1:
        ldr     ip, [r3],#4
        umull   r5, r6, r2, ip
        adds    r5, r5, r4
        adc     r4, r6, #0
        str     r5, [r0],#4
        
        subs    r1, #1
        bne     1b   
2:
        ldmfd   sp!, {r4-r6}
        
        mov     pc, lr
3:
        sub     r1, #1        
1:
        ldr     ip, [r3],#4
        umull   r5, r6, r2, ip
        adds    r5, r5, r4
        adc     r4, r6, #0
        str     r5, [r0],#4
        
        subs    r1, #1
        bne     1b   

        str     r4, [r0]
        
        ldmfd   sp!, {r4-r6}

        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo11RawUMulLo11EPjjjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo11RawUMulLo11EPjjjj:     @  void CCore::Math::IntegerFastAlgo::RawUMulLo11(Unit *c,ulen nc,Unit a,Unit b)  

        cmp     r1, #1
        umull   r1, ip, r2, r3
        
        str     r1, [r0]
        strne   ip, [r0,#4]
        
        mov     pc, lr        

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo6RawUSqEPjPKjj
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo6RawUSqEPjPKjj:          @  void CCore::Math::IntegerFastAlgo::RawUSq(Unit *restrict c,const Unit *a,ulen na)

        stmfd   sp!, {r4-r11,lr}
        sub     sp, #4
        
        ldr     r5, [r1]
        umull   r7, r12, r5, r5
        mov     r14, #0
        str     r7, [r0],#4

        add     r4, r1, #4
        add     r2, r1, r2, LSL #2
1:
        mov     r3, r1
        str     r4, [sp]
        
        mov     r9, #0
        mov     r10, #0
        mov     r11, #0        
2:
        ldr     r5, [r3],#4
        ldr     r6, [r4],#-4
        umull   r7, r8, r5, r6
        adds    r9, r9, r7
        adcs    r10, r10, r8 
        adc     r11, r11, #0
        cmp     r3, r4
        bcc     2b
        adds    r9, r9, r9
        adcs    r10, r10, r10
        adc     r11, r11, r11
        adds    r9, r9, r12
        adcs    r10, r10, r14 
        adc     r11, r11, #0
        cmp     r3, r4
        bne     3f
        ldr     r5, [r3]
        umull   r7, r8, r5, r5
        adds    r9, r9, r7
        adcs    r10, r10, r8 
        adc     r11, r11, #0
3:
        str     r9, [r0],#4
        mov     r12, r10
        mov     r14, r11
        
        ldr     r4, [sp]
        add     r4, #4
        cmp     r4, r2 
        bne     1b
        
        add     r3, r1, #4
        sub     r2, #4
        cmp     r3, r2
        beq     4f
1:
        mov     r4, r2
        str     r3, [sp]
        
        mov     r9, #0
        mov     r10, #0
        mov     r11, #0        
2:
        ldr     r5, [r3],#4
        ldr     r6, [r4],#-4
        umull   r7, r8, r5, r6
        adds    r9, r9, r7
        adcs    r10, r10, r8 
        adc     r11, r11, #0
        cmp     r3, r4
        bcc     2b
        adds    r9, r9, r9
        adcs    r10, r10, r10
        adc     r11, r11, r11
        adds    r9, r9, r12
        adcs    r10, r10, r14 
        adc     r11, r11, #0
        cmp     r3, r4
        bne     3f
        ldr     r5, [r3]
        umull   r7, r8, r5, r5
        adds    r9, r9, r7
        adcs    r10, r10, r8 
        adc     r11, r11, #0
3:
        str     r9, [r0],#4
        mov     r12, r10
        mov     r14, r11
        
        ldr     r3, [sp]
        add     r3, #4
        cmp     r3, r2 
        bne     1b
4:                                        
        
        ldr     r5, [r2]
        umull   r7, r8, r5, r5
        adds    r7, r7, r12
        adc     r8, r8, r14
        
        stmia   r0, {r7,r8}
        
        add     sp, #4
        ldmfd   sp!, {r4-r11,pc}

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math15IntegerFastAlgo7RawUSq1EPjj 
         
        .align 2

_ZN5CCore4Math15IntegerFastAlgo7RawUSq1EPjj:            @  void CCore::Math::IntegerFastAlgo::RawUSq1(Unit *c,Unit a)  

        umull   r3, ip, r1, r1
        
        str     r3, [r0]
        str     ip, [r0,#4]
        
        mov     pc, lr        

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo5UNeg3EPj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo5UNeg3EPj:                @  void CCore::Math::IntegerExtAlgo::UNeg3(Unit *a)  

        ldmia   r0, {r1,r2,r3}
        
        rsbs    r1, r1, #0
        rscs    r2, r2, #0
        rsc     r3, r3, #0     

        stmia   r0, {r1,r2,r3}
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo5UAdd3EPjPKj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo5UAdd3EPjPKj:             @  Unit CCore::Math::IntegerExtAlgo::UAdd3(Unit *restrict a,const Unit *b)  

        ldr     r2, [r0]
        ldr     r3, [r1]
        adds    r2, r2, r3
        str     r2, [r0]

        ldr     r2, [r0,#4]
        ldr     r3, [r1,#4]
        adcs    r2, r2, r3
        str     r2, [r0,#4]
        
        ldr     r2, [r0,#8]
        ldr     r3, [r1,#8]
        adcs    r2, r2, r3
        str     r2, [r0,#8]
        
        mov     r0, #0
        adc     r0, r0, #0
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo5USub3EPjPKj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo5USub3EPjPKj:             @  void CCore::Math::IntegerExtAlgo::USub3(Unit *restrict a,const Unit *b)

        ldr     r2, [r0]
        ldr     r3, [r1]
        subs    r2, r2, r3
        str     r2, [r0]

        ldr     r2, [r0,#4]
        ldr     r3, [r1,#4]
        sbcs    r2, r2, r3
        str     r2, [r0,#4]
        
        ldr     r2, [r0,#8]
        ldr     r3, [r1,#8]
        sbc     r2, r2, r3
        str     r2, [r0,#8]
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo7UMulLo3EPjPKjS4_
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo7UMulLo3EPjPKjS4_:        @  void CCore::Math::IntegerExtAlgo::UMulLo3(Unit *restrict c,const Unit *a,const Unit *b)  

        stmfd   sp!, {r4-r7}

        ldr     r3, [r1]
        ldr     r4, [r2]
        umull   r5, r6, r3, r4
        str     r5, [r0]

        mov     r7, #0        
        ldr     r5, [r2,#4]
        umlal   r6, r7, r3, r5
        ldr     r5, [r1,#4]   
        umlal   r6, r7, r4, r5
        str     r6, [r0,#4]
        
        ldr     r5, [r2,#8]
        mla     r7, r3, r5, r7
        ldr     r5, [r1,#8]
        mla     r7, r4, r5, r7
        ldr     r3, [r1,#4]
        ldr     r4, [r2,#4]
        mla     r7, r3, r4, r7
        str     r7, [r0,#8]

        ldmfd   sp!, {r4-r7}
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo6USqLo3EPjPKj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo6USqLo3EPjPKj:            @  void CCore::Math::IntegerExtAlgo::USqLo3(Unit *restrict c,const Unit *a)

        stmfd   sp!, {r4-r6}

        ldmia   r1, {r1,r2,r3}
        umull   r5, r4, r1, r1
        str     r5, [r0]

        umull   r5, r6, r1, r2
        adds    r5, r5, r5
        adc     r6, r6, r6
        adds    r5, r5, r4    
        adc     r6, r6, #0
        str     r5, [r0,#4]
        
        mla     r6, r2, r2, r6
        mul     r5, r1, r3
        add     r6, r6, r5    
        add     r6, r6, r5    
        str     r6, [r0,#8]

        ldmfd   sp!, {r4-r6}
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo8URShift3EPjj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo8URShift3EPjj:            @  void CCore::Math::IntegerExtAlgo::URShift3(Unit *a,unsigned shift)  

        rsb     ip, r1, #32
        
        ldr     r3, [r0,#8]
        mov     r2, r3, LSL ip
        mov     r3, r3, LSR r1
        str     r3, [r0,#8]
        
        ldr     r3, [r0,#4]
        orr     r2, r3, LSR r1
        mov     r3, r3, LSL ip
        str     r2, [r0,#4]

        ldr     r2, [r0]
        orr     r3, r2, LSR r1
        str     r3, [r0]
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo5UNeg4EPj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo5UNeg4EPj:                @  void CCore::Math::IntegerExtAlgo::UNeg4(Unit *a)  

        ldmia   r0, {r1,r2,r3,ip}
        
        rsbs    r1, r1, #0
        rscs    r2, r2, #0
        rscs    r3, r3, #0
        rsc     ip, ip, #0     

        stmia   r0, {r1,r2,r3,ip}
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo5UAdd4EPjPKj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo5UAdd4EPjPKj:             @  Unit CCore::Math::IntegerExtAlgo::UAdd4(Unit *restrict a,const Unit *b)  

        ldr     r2, [r0]
        ldr     r3, [r1]
        adds    r2, r2, r3
        str     r2, [r0]

        ldr     r2, [r0,#4]
        ldr     r3, [r1,#4]
        adcs    r2, r2, r3
        str     r2, [r0,#4]
        
        ldr     r2, [r0,#8]
        ldr     r3, [r1,#8]
        adcs    r2, r2, r3
        str     r2, [r0,#8]
        
        ldr     r2, [r0,#12]
        ldr     r3, [r1,#12]
        adcs    r2, r2, r3
        str     r2, [r0,#12]
        
        mov     r0, #0
        adc     r0, r0, #0
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo5USub4EPjPKj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo5USub4EPjPKj:             @  void CCore::Math::IntegerExtAlgo::USub4(Unit *restrict a,const Unit *b)  

        ldr     r2, [r0]
        ldr     r3, [r1]
        subs    r2, r2, r3
        str     r2, [r0]

        ldr     r2, [r0,#4]
        ldr     r3, [r1,#4]
        sbcs    r2, r2, r3
        str     r2, [r0,#4]
        
        ldr     r2, [r0,#8]
        ldr     r3, [r1,#8]
        sbcs    r2, r2, r3
        str     r2, [r0,#8]
        
        ldr     r2, [r0,#12]
        ldr     r3, [r1,#12]
        sbc     r2, r2, r3
        str     r2, [r0,#12]
        
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo7UMulLo4EPjPKjS4_
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo7UMulLo4EPjPKjS4_:        @  void CCore::Math::IntegerExtAlgo::UMulLo4(Unit *restrict c,const Unit *a,const Unit *b)  

        stmfd   sp!, {r4-r10}
        
        ldr     r3, [r1]
        ldr     r4, [r2]
        umull   r5, r8, r3, r4
        str     r5, [r0]
        
        mov     r9, #0
        mov     r10, #0
        
        ldr     r7, [r2,#4]
        umull   r5, r6, r3, r7
        adds    r8, r8, r5
        adcs    r9, r9, r6
        adc     r10, r10, #0 
        
        ldr     r7, [r1,#4]
        umull   r5, r6, r4, r7
        adds    r8, r8, r5
        adcs    r9, r9, r6
        adc     r10, r10, #0 

        str     r8, [r0,#4]
        
        ldr     r5, [r1,#4]
        ldr     r6, [r2,#4]
        ldr     r7, [r1,#8]
        ldr     r8, [r2,#8]
        
        umlal   r9, r10, r3, r8
        umlal   r9, r10, r4, r7
        umlal   r9, r10, r5, r6
        
        str     r9, [r0,#8]
        
        ldr     r9, [r2,#12]
        mla     r10, r3, r9, r10
        mla     r10, r5, r8, r10
        mla     r10, r6, r7, r10
        ldr     r9, [r1,#12]
        mla     r10, r4, r9, r10
        
        str     r10, [r0,#12]

        ldmfd   sp!, {r4-r10}
         
        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo6USqLo4EPjPKj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo6USqLo4EPjPKj:            @  void CCore::Math::IntegerExtAlgo::USqLo4(Unit *restrict c,const Unit *a)  

        stmfd   sp!, {r4-r8}
        
        ldmia   r1, {r1,r2,r3,r4}
        
        umull   r6, r5, r1, r1                
        str     r6, [r0]
                
        umull   r6, r7, r1, r2
        mov     r8, #0
        adds    r6, r6, r6
        adcs    r7, r7, r7
        adc     r8, r8, #0           
        adds    r6, r6, r5
        adcs    r7, r7, #0
        adc     r8, r8, #0
        str     r6, [r0,#4]
                   
        umlal   r7, r8, r2, r2
        umull   r5, r6, r1, r3
        adds    r7, r5
        adc     r8, r6           
        adds    r7, r5
        adc     r8, r6
        str     r7, [r0,#8]
        
        mul     r5, r1, r4
        mul     r6, r2, r3
        add     r8, r5, LSL #1           
        add     r8, r6, LSL #1
        str     r8, [r0,#12]           

        ldmfd   sp!, {r4-r8}

        mov     pc, lr

@-----------------------------------------------------------------------------------------

        .global _ZN5CCore4Math14IntegerExtAlgo8URShift4EPjj
         
        .align 2

_ZN5CCore4Math14IntegerExtAlgo8URShift4EPjj:            @  void CCore::Math::IntegerExtAlgo::URShift4(Unit *a,unsigned shift)  

        rsbs    ip, r1, #32
        beq     1f
        bcc     2f
        
        ldr     r3, [r0,#12]
        mov     r2, r3, LSL ip
        mov     r3, r3, LSR r1
        str     r3, [r0,#12]
        
        ldr     r3, [r0,#8]
        orr     r2, r3, LSR r1
        mov     r3, r3, LSL ip
        str     r2, [r0,#8]

        ldr     r2, [r0,#4]
        orr     r3, r2, LSR r1
        mov     r2, r2, LSL ip
        str     r3, [r0,#4]
        
        ldr     r3, [r0]
        orr     r2, r3, LSR r1
        str     r2, [r0]
        
        mov     pc, lr

1:
        mov     ip, #0
        ldmib   r0, {r1,r2,r3}
        stmia   r0, {r1,r2,r3}
        str     ip, [r0,#12]
        
        mov     pc, lr

2:
        sub     r1, #32
        add     ip, #32

        ldr     r2, [r0,#4]
        ldr     r3, [r0,#8]
        mov     r2, r2, LSR r1
        orr     r2, r3, LSL ip
        str     r2, [r0]
        ldr     r2, [r0,#12]
        mov     r3, r3, LSR r1
        orr     r3, r2, LSL ip
        str     r3, [r0,#4]
        mov     r2, r2, LSR r1
        mov     r3, #0
        str     r2, [r0,#8]
        str     r3, [r0,#12]

        mov     pc, lr
        
@-----------------------------------------------------------------------------------------

@        .global SXXX
         
        .align 2

SXXX:    @  


@-----------------------------------------------------------------------------------------



        
