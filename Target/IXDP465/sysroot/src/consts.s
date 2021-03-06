@ consts.s
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
        
        .weak   __std_image_base
        .set    __std_image_base , 0x200000        @  align 16 , >= 2M
        .global __std_image_base
        
        @ .code+.data+.bss   4M
        
        .weak   __std_mem_size
        .set    __std_mem_size , 0x7A00000         @  align 16 , 58M+64M
        .global __std_mem_size
        
@------------------------------------------------------------------------------
        
        .weak   __std_stack_size
        .set    __std_stack_size , 0x100000        @  align 16 , 1M
        .global __std_stack_size
        
        .weak   __std_int_stack_size
        .set    __std_int_stack_size , 0x10000     @  align 16 , 64K
        .global __std_int_stack_size
        
        .weak   __std_heap_size
        .set    __std_heap_size , 0x7600000        @  align 16 , 54M+64M
        .global __std_heap_size
        
        .weak   __std_int_heap_size
        .set    __std_int_heap_size , 0x100000     @  align 16 , 1M
        .global __std_int_heap_size
        
        .weak   __std_syslog_size
        .set    __std_syslog_size , 0x100000       @  align 16 , 1M
        .global __std_syslog_size
        
@------------------------------------------------------------------------------


