@ DevRW.s
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
        
        .text
        .align 2
        
        .global _ZN5CCore3Dev6VarGetIhEET_PKv
        .global _ZN5CCore3Dev6VarSetIhEEvPvT_
        .global _ZN5CCore3Dev6VarGetItEET_PKv
        .global _ZN5CCore3Dev6VarSetItEEvPvT_
        .global _ZN5CCore3Dev6VarGetIjEET_PKv
        .global _ZN5CCore3Dev6VarSetIjEEvPvT_
        
_ZN5CCore3Dev6VarGetIhEET_PKv:                   @ CCore::Dev::VarGet<uint8>
        
        ldrb    r0, [r0, #0]
        
        mov     pc, lr
        
_ZN5CCore3Dev6VarSetIhEEvPvT_:                   @ CCore::Dev::VarSet<uint8>
        
        strb    r1, [r0, #0]
        
        mov     pc, lr
        
_ZN5CCore3Dev6VarGetItEET_PKv:                   @ CCore::Dev::VarGet<uint16>
        
        ldrh    r0, [r0, #0]
        
        mov     pc, lr
        
_ZN5CCore3Dev6VarSetItEEvPvT_:                   @ CCore::Dev::VarSet<uint16>
        
        strh    r1, [r0, #0]
        
        mov     pc, lr
        
_ZN5CCore3Dev6VarGetIjEET_PKv:                   @ CCore::Dev::VarGet<uint32>
        
        ldr     r0, [r0, #0]
        
        mov     pc, lr
        
_ZN5CCore3Dev6VarSetIjEEvPvT_:                   @ CCore::Dev::VarSet<uint32>
        
        str     r1, [r0, #0]
        
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------          

