@ Quick.s
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
        
        .global _ZN5CCore5Quick9ScanMSBitEj
        
_ZN5CCore5Quick9ScanMSBitEj:    @  CCore::Quick::ScanMSBit
        
        clz     r0, r0
        rsb     r0, r0, #31
        
        mov     pc, lr
