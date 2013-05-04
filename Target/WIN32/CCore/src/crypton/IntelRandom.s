# IntelRandom.s
#-----------------------------------------------------------------------------------------
#
#  Project: CCore 1.05
#
#  Tag: Target/WIN32
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2013 Sergey Strukov. All rights reserved.
#
#-----------------------------------------------------------------------------------------

        .text

#-----------------------------------------------------------------------------------------

        .global __ZN5CCore7Crypton11IntelRandom4nextEv

        .p2align 4,,15
        
__ZN5CCore7Crypton11IntelRandom4nextEv:

#
# uint32 CCore::Crypton::IntelRandom::next()
#

        pushl   %ebp
        movl    %esp, %ebp

L1:        
        rdrand  %eax
        jnc     L1 

        popl    %ebp
        ret

#-----------------------------------------------------------------------------------------
