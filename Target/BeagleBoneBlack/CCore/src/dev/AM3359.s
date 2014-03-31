@ AM3359.s
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
        
        .global _ZN6AM33594CP157GetCPSREv
        .global _ZN6AM33594CP1515GetSecureConfigEv
        .global _ZN6AM33594CP1515SetSecureConfigENS0_17Type_SecureConfigE

_ZN6AM33594CP157GetCPSREv:                       @ AM3359::CP15::GetCPSR
        
        mrs     r0, CPSR
        
        bx      lr
        
_ZN6AM33594CP1515GetSecureConfigEv:              @ AM3359::CP15::GetSecureConfig

        mrc     p15, 0, r0, c1, c1, 0

        bx      lr
        
_ZN6AM33594CP1515SetSecureConfigENS0_17Type_SecureConfigE:           @ AM3359::CP15::SetSecureConfig

        mcr     p15, 0, r0, c1, c1, 0

        bx      lr

@-----------------------------------------------------------------------------------------
          
        .text
        .align 2
        
        .global _ZN6AM33594CP1511CPUFeaturesC1Ev
        .global _ZN6AM33594CP1511CPUFeaturesC2Ev
        
_ZN6AM33594CP1511CPUFeaturesC1Ev:                @ AM3359::CP15::CPUFeatures::CPUFeatures
_ZN6AM33594CP1511CPUFeaturesC2Ev:

        mov     r2, r0
        
        mrc     p15, 0, r1, c0, c0, 0
        str     r1, [r2], #4
        
        mrc     p15, 0, r1, c0, c0, 1
        str     r1, [r2], #4

        mrc     p15, 0, r1, c0, c0, 2
        str     r1, [r2], #4
        
        mrc     p15, 0, r1, c0, c0, 3        
        str     r1, [r2], #4
        
        mrc     p15, 0, r1, c0, c0, 5        
        str     r1, [r2], #4
        
        mrc     p15, 0, r1, c0, c1, 0        
        str     r1, [r2], #4
        
        mrc     p15, 0, r1, c0, c1, 1        
        str     r1, [r2], #4

        mrc     p15, 0, r1, c0, c1, 2        
        str     r1, [r2], #4

        mrc     p15, 0, r1, c0, c1, 3        
        str     r1, [r2], #4
        
        mrc     p15, 0, r1, c0, c1, 4
        str     r1, [r2], #4
        
        bx      lr
        
@-----------------------------------------------------------------------------------------          
        
