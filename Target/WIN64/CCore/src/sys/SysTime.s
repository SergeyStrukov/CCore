# SysTime.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 1.06
#
#  Tag: Target/WIN64
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2013 Sergey Strukov. All rights reserved.
#
#-----------------------------------------------------------------------------------------

        .text
        
        .global _ZN5CCore3Sys12GetClockTimeEv
        
#-----------------------------------------------------------------------------------------

        .p2align 4,,15
        
_ZN5CCore3Sys12GetClockTimeEv:      # CCore::Sys::GetClockTime

        rdtsc
        
        shlq   $32, %rdx 
        orq    %rdx, %rax
        
        ret
        
#-----------------------------------------------------------------------------------------
