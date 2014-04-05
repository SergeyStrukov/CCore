/* AM3359.CP15CNT.s */
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
        
        .global _ZN6AM33597CP15CNT10GetControlEv
        .global _ZN6AM33597CP15CNT10SetControlENS0_12Type_ControlE
        .global _ZN6AM33597CP15CNT18GetUserCountEnableEv
        .global _ZN6AM33597CP15CNT18SetUserCountEnableENS0_20Type_UserCountEnableE
        .global _ZN6AM33597CP15CNT13GetClockCountEv
        .global _ZN6AM33597CP15CNT8GetCountEv
        .global _ZN6AM33597CP15CNT8SetCountEj
        .global _ZN6AM33597CP15CNT16SetCounterSelectENS0_18Type_CounterSelectE
        .global _ZN6AM33597CP15CNT14SetEventSelectENS0_16Type_EventSelectE
        .global _ZN6AM33597CP15CNT17SetCountEnableSetENS0_16Type_CounterBitsE
        .global _ZN6AM33597CP15CNT19SetCountEnableClearENS0_16Type_CounterBitsE
        .global _ZN6AM33597CP15CNT22GetCountOverflowStatusEv
        .global _ZN6AM33597CP15CNT22SetCountOverflowStatusENS0_16Type_CounterBitsE
        .global _ZN6AM33597CP15CNT15SetIntEnableSetENS0_16Type_CounterBitsE
        .global _ZN6AM33597CP15CNT17SetIntEnableClearENS0_16Type_CounterBitsE
        .global _ZN6AM33597CP15CNT11SetCountIncENS0_16Type_CounterBitsE
        
_ZN6AM33597CP15CNT10GetControlEv:                @ AM3359::CP15CNT::GetControl

        mrc     p15, 0, r0, c9, c12, 0

        bx      lr
        
_ZN6AM33597CP15CNT10SetControlENS0_12Type_ControlE:                  @ AM3359::CP15CNT::SetControl

        mcr     p15, 0, r0, c9, c12, 0

        bx      lr

_ZN6AM33597CP15CNT18GetUserCountEnableEv:        @ AM3359::CP15CNT::GetUserCountEnable

        mrc     p15, 0, r0, c9, c14, 0

        bx      lr

_ZN6AM33597CP15CNT18SetUserCountEnableENS0_20Type_UserCountEnableE:  @ AM3359::CP15CNT::SetUserCountEnable

        mcr     p15, 0, r0, c9, c14, 0

        bx      lr

_ZN6AM33597CP15CNT13GetClockCountEv:             @ AM3359::CP15CNT::GetClockCount

        mrc     p15, 0, r0, c9, c13, 0 

        bx      lr

_ZN6AM33597CP15CNT8GetCountEv:                   @ AM3359::CP15CNT::GetCount

        mrc     p15, 0, r0, c9, c13, 2

        bx      lr
        
_ZN6AM33597CP15CNT8SetCountEj:                   @ AM3359::CP15CNT::SetCount

        mcr     p15, 0, r0, c9, c13, 2

        bx      lr
        
_ZN6AM33597CP15CNT16SetCounterSelectENS0_18Type_CounterSelectE:      @ AM3359::CP15CNT::SetCounterSelect

        mcr     p15, 0, r0, c9, c12, 5

        bx      lr

_ZN6AM33597CP15CNT14SetEventSelectENS0_16Type_EventSelectE:          @ AM3359::CP15CNT::SetEventSelect

        mcr     p15, 0, r0, c9, c13, 1

        bx      lr

_ZN6AM33597CP15CNT17SetCountEnableSetENS0_16Type_CounterBitsE:       @ AM3359::CP15CNT::SetCountEnableSet

        mcr     p15, 0, r0, c9, c12, 1

        bx      lr

_ZN6AM33597CP15CNT19SetCountEnableClearENS0_16Type_CounterBitsE:     @ AM3359::CP15CNT::SetCountEnableClear

        mcr     p15, 0, r0, c9, c12, 2

        bx      lr

_ZN6AM33597CP15CNT22GetCountOverflowStatusEv:    @ AM3359::CP15CNT::GetCountOverflowStatus

        mrc     p15, 0, r0, c9, c12, 3

        bx      lr

_ZN6AM33597CP15CNT22SetCountOverflowStatusENS0_16Type_CounterBitsE:  @ AM3359::CP15CNT::SetCountOverflowStatus

        mcr     p15, 0, r0, c9, c12, 3

        bx      lr

_ZN6AM33597CP15CNT15SetIntEnableSetENS0_16Type_CounterBitsE:         @ AM3359::CP15CNT::SetIntEnableSet  

        mcr     p15, 0, r0, c9, c14, 1

        bx      lr

_ZN6AM33597CP15CNT17SetIntEnableClearENS0_16Type_CounterBitsE:       @ AM3359::CP15CNT::SetIntEnableClear

        mcr     p15, 0, r0, c9, c14, 2
        
        bx      lr

_ZN6AM33597CP15CNT11SetCountIncENS0_16Type_CounterBitsE:             @ AM3359::CP15CNT::SetCountInc

        mcr     p15, 0, r0, c9, c12, 4
        
        bx      lr
        
@-----------------------------------------------------------------------------------------
        
