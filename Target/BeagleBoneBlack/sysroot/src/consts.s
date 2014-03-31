@ consts.s
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
        
        .weak   __std_video_mem
        .set    __std_video_mem , 0x80000000       @  align 1M
        .global __std_video_mem
        
        .weak   __std_video_mem_size
        .set    __std_video_mem_size , 0x800000    @  align 1M , 8M
        .global __std_video_mem_size
        
        .weak   __std_shared_mem
        .set    __std_shared_mem , 0x80800000      @  align 1M
        .global __std_shared_mem
        
        .weak   __std_shared_mem_size
        .set    __std_shared_mem_size , 0x800000   @  align 1M , 8M
        .global __std_shared_mem_size
        
        .weak   __std_image_base
        .set    __std_image_base , 0x81000000      @  align 16 
        .global __std_image_base
        
        .weak   __std_mem_size
        .set    __std_mem_size , 0xE000000         @  align 16 , 224M
        .global __std_mem_size
        
@------------------------------------------------------------------------------
        
        .weak   __std_stack_size
        .set    __std_stack_size , 0x100000        @  align 16 , 1M
        .global __std_stack_size
        
        .weak   __std_int_stack_size
        .set    __std_int_stack_size , 0x100000    @  align 16 , 1M
        .global __std_int_stack_size
        
        .weak   __std_int_heap_size
        .set    __std_int_heap_size , 0x100000     @  align 16 , 1M
        .global __std_int_heap_size
        
        .weak   __std_syslog_size
        .set    __std_syslog_size , 0x1000000      @  align 16 , 16M
        .global __std_syslog_size
        
        .weak   __std_heap_size
        .set    __std_heap_size , 0xCC00000        @  align 16 , 204M
        .global __std_heap_size
        
@------------------------------------------------------------------------------


