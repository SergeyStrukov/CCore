@ Quick.s
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

        .global _ZN5CCore5Quick9ScanLSBitEj         
        .global _ZN5CCore5Quick9ScanMSBitEj
        .global _ZN5CCore5Quick10ByteSwap16Et
        .global _ZN5CCore5Quick10ByteSwap32Ej
        .global _ZN5CCore5Quick10ByteSwap64Ey
        
_ZN5CCore5Quick9ScanLSBitEj:                     @ CCore::Quick::ScanLSBit

        rbit    r0, r0
        clz     r0, r0
                
        mov     pc, lr
        
_ZN5CCore5Quick9ScanMSBitEj:                     @ CCore::Quick::ScanMSBit
        
        clz     r0, r0
        rsb     r0, r0, #31
        
        mov     pc, lr
        
_ZN5CCore5Quick10ByteSwap16Et:                   @ CCore::Quick::ByteSwap16       
        
        rev16   r0, r0
        uxth    r0, r0
        
        mov     pc, lr
        
_ZN5CCore5Quick10ByteSwap32Ej:                   @ CCore::Quick::ByteSwap32

        rev     r0, r0

        mov     pc, lr
        
_ZN5CCore5Quick10ByteSwap64Ey:                   @ CCore::Quick::ByteSwap64
        
        rev     r3, r0
        rev     r0, r1
        mov     r1, r3
    
        mov     pc, lr
        
@-----------------------------------------------------------------------------------------
