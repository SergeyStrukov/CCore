@ setjmp.s
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
@  Copyright (c) 2009 Sergey Strukov. All rights reserved.
@
@-----------------------------------------------------------------------------------------
        
        .text
        .align 2
        
        .global setjmp
        .global longjmp
        
setjmp:
        
        stmia   r0, {r1-r14}
        mov     r0, #0
        mov     pc, lr
        
        
longjmp:
        
        mov     r2, r0
        movs    r0, r1
        moveq   r0, #1
        ldmia   r2, {r1-r14}
        mov     pc, lr
        
@------------------------------------------------------------------------------
        
