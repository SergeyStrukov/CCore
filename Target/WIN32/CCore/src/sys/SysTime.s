# SysTime.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 1.02
#
#  Tag: Target/WIN32
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2010 Sergey Strukov. All rights reserved.
#
#-----------------------------------------------------------------------------------------

        .text
        
        .global __ZN5CCore3Sys12GetClockTimeEv
        
        .p2align 4,,15
        
__ZN5CCore3Sys12GetClockTimeEv:     # CCore::Sys::GetClockTime

        pushl   %ebp
        movl    %esp, %ebp
        
        rdtsc
        
        popl    %ebp
        ret
        
