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
        .global _ZN6AM33594CP1518GetDataFaultStatusEv
        .global _ZN6AM33594CP1525GetInstructionFaultStatusEv
        .global _ZN6AM33594CP1519GetDataFaultAddressEv
        .global _ZN6AM33594CP1526GetInstructionFaultAddressEv
        .global _ZN6AM33594CP1510GetControlEv
        .global _ZN6AM33594CP1510SetControlENS0_12Type_ControlE
        .global _ZN6AM33594CP1514GetCacheSizeIDEv
        .global _ZN6AM33594CP1515SetCacheSizeSelENS0_17Type_CacheSizeSelE

_ZN6AM33594CP157GetCPSREv:                       @ AM3359::CP15::GetCPSR
        
        mrs     r0, CPSR
        
        bx      lr
        
_ZN6AM33594CP1515GetSecureConfigEv:              @ AM3359::CP15::GetSecureConfig

        mrc     p15, 0, r0, c1, c1, 0

        bx      lr
        
_ZN6AM33594CP1515SetSecureConfigENS0_17Type_SecureConfigE:           @ AM3359::CP15::SetSecureConfig

        mcr     p15, 0, r0, c1, c1, 0

        bx      lr
        
_ZN6AM33594CP1518GetDataFaultStatusEv:           @ AM3359::CP15::GetDataFaultStatus

        mrc     p15, 0, r0, c5, c0, 0
       
        bx      lr
        
_ZN6AM33594CP1525GetInstructionFaultStatusEv:    @ AM3359::CP15::GetInstructionFaultStatus

        mrc     p15, 0, r0, c5, c0, 1

        bx      lr
      
_ZN6AM33594CP1519GetDataFaultAddressEv:          @ AM3359::CP15::GetDataFaultAddress

        mrc     p15, 0, r0, c6, c0, 0

        bx      lr
        
_ZN6AM33594CP1526GetInstructionFaultAddressEv:   @ AM3359::CP15::GetInstructionFaultAddress    
        
        mrc     p15, 0, r0, c6, c0, 2
                
        bx      lr
        
_ZN6AM33594CP1510GetControlEv:                   @ AM3359::CP15::GetControl

        mrc     p15, 0, r0, c1, c0, 0

        bx      lr
        
_ZN6AM33594CP1510SetControlENS0_12Type_ControlE:                     @ AM3359::CP15::SetControl        
        
        mcr     p15, 0, r0, c1, c0, 0
        
        bx      lr
        
_ZN6AM33594CP1514GetCacheSizeIDEv:               @ AM3359::CP15::GetCacheSizeID

        mrc     p15, 1, r0, c0, c0, 0

        bx      lr
        
_ZN6AM33594CP1515SetCacheSizeSelENS0_17Type_CacheSizeSelE:           @ AM3359::CP15::SetCacheSizeSel

        mcr     p15, 2, r0, c0, c0, 0       
        
        bx      lr

@-----------------------------------------------------------------------------------------

        .text
        .align 2
        
        .global _ZN6AM33594CP1522GetDomainAccessControlEv
        .global _ZN6AM33594CP1522SetDomainAccessControlENS0_24Type_DomainAccessControlE
        .global _ZN6AM33594CP1510GetTTBase0Ev
        .global _ZN6AM33594CP1510SetTTBase0ENS0_12Type_TTBase0E
        .global _ZN6AM33594CP1512GetTTControlEv
        .global _ZN6AM33594CP1512SetTTControlENS0_14Type_TTControlE
        .global _ZN6AM33594CP1513GetAuxControlEv
        .global _ZN6AM33594CP1513SetAuxControlENS0_15Type_AuxControlE
        
_ZN6AM33594CP1522GetDomainAccessControlEv:       @ AM3359::CP15::GetDomainAccessControl

        mrc     p15, 0, r0, c3, c0, 0
        
        bx      lr
        
_ZN6AM33594CP1522SetDomainAccessControlENS0_24Type_DomainAccessControlE:       @ AM3359::CP15::SetDomainAccessControl 
        
        mcr     p15, 0, r0, c3, c0, 0
        
        bx      lr
        
_ZN6AM33594CP1510GetTTBase0Ev:                   @ AM3359::CP15::GetTTBase0

        mrc     p15, 0, r0, c2, c0, 0
        
        bx      lr
        
_ZN6AM33594CP1510SetTTBase0ENS0_12Type_TTBase0E:                     @ AM3359::CP15::SetTTBase0
        
        mcr     p15, 0, r0, c2, c0, 0
        
        bx      lr
        
_ZN6AM33594CP1512GetTTControlEv:                 @ AM3359::CP15::GetTTControl

        mrc     p15, 0, r0, c2, c0, 2

        bx      lr
        
_ZN6AM33594CP1512SetTTControlENS0_14Type_TTControlE:                 @ AM3359::CP15::SetTTControl

        mcr     p15, 0, r0, c2, c0, 2
        
        bx      lr

_ZN6AM33594CP1513GetAuxControlEv:                @ AM3359::CP15::GetAuxControl

        mrc     p15, 0, r0, c1, c0, 1
        
        bx      lr

_ZN6AM33594CP1513SetAuxControlENS0_15Type_AuxControlE:               @ AM3359::CP15::SetAuxControl
        
        mcr     p15, 0, r0, c1, c0, 1
        
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
        
        mrc     p15, 0, r1, c0, c1, 5
        str     r1, [r2], #4
        
        mrc     p15, 0, r1, c0, c1, 6
        str     r1, [r2], #4
        
        mrc     p15, 0, r1, c0, c1, 7
        str     r1, [r2], #4
        
        mrc     p15, 1, r1, c0, c0, 1
        str     r1, [r2], #4

        bx      lr
        
@-----------------------------------------------------------------------------------------          
        
