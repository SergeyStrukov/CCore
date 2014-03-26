/* __std_init.h */ 
/*----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//--------------------------------------------------------------------------------------*/

#ifndef XCore___std_init_h
#define XCore___std_init_h

#ifdef __cplusplus
extern "C" {
#endif

/* types */

typedef unsigned __std_len_t;

/* init */ 

extern void __std_init(void);           

/* main */ 

extern void __std_main(void);           

/* exit */ 

extern void __std_exit(void);

/* debug */

extern void __std_debug_init(void);

extern void __std_debug(const char *zstr);

extern void __std_debug2(const char *ptr,__std_len_t len);

extern void __std_debug_console(const char *ptr,__std_len_t len);

extern void __std_debug_trap(unsigned LR,unsigned trap);

/* constructors/destructors */

typedef void (*__std_init_t)(void);

extern __std_init_t * __std_get_init_base(void);

extern __std_init_t * __std_get_init_lim(void);

/* abort */ 

extern void __std_abort(const char *zstr) __attribute__((noreturn)) ;

extern void __std_abort2(const char *ptr,__std_len_t len) __attribute__((noreturn)) ;

/* mem */ 

 /* all MaxAlign-ed */ 

extern __std_len_t __std_get_heap_int_len(void);

extern __std_len_t __std_get_heap_len(void);

extern __std_len_t __std_get_syslog_len(void);

extern void * __std_alloc(__std_len_t len);

/* shared mem */ 

 /* all MaxAlign-ed */ 
 
extern void * __std_get_shared_mem(void);

extern __std_len_t __std_get_shared_mem_len(void);

/* video mem */

 /* all MaxAlign-ed */ 

extern void * __std_get_video_mem(void);

extern __std_len_t __std_get_video_mem_len(void);

/* int */ 

typedef void (*__std_handler_t)(void);

extern void __std_intsetup(__std_handler_t handler);

extern void __std_intcleanup(void);

/* context */ 

 /* all MaxAlign-ed */ 
 
extern void * __std_context;

extern __std_len_t __std_context_len(void);

typedef void (*__std_entry_t)(void *arg);

extern void __std_context_init(void *context,
                               void *stack,
                               __std_len_t stack_len,
                               __std_entry_t entry,
                               void *arg);
                               
extern void __std_switch(void *context); // int disabled

#ifdef __cplusplus
} // extern "C"
#endif

#endif

