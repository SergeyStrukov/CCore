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

/* constructors/destructors */ 

extern void __std_init_global(void);  /* crti.o */ 

extern void __std_exit_global(void);  /* crti.o */ 

/* init */ 

extern void __std_init(void);           

/* main */ 

extern void __std_main(void);           

/* exit */ 

extern void __std_exit(void);           

/* abort */ 

extern void __std_abort(const char *msg) __attribute__((noreturn)) ;

extern void __std_abort2(const char *msg,unsigned len) __attribute__((noreturn)) ;

/* mem */ 

 /* all MaxAlign-ed */ 

extern unsigned __std_get_heap_int_len(void);

extern unsigned __std_get_heap_len(void);

extern unsigned __std_get_syslog_len(void);

extern void * __std_alloc(unsigned len);

/* shared mem */ 

 /* all MaxAlign-ed */ 
 
extern void * __std_get_shared_mem(void);

extern unsigned __std_get_shared_mem_len(void);

/* video mem */

 /* all MaxAlign-ed */ 

extern void * __std_get_video_mem(void);

extern unsigned __std_get_video_mem_len(void);

/* int */ 

typedef void (*__std_handler_t)(void);

extern void __std_intsetup(__std_handler_t handler);

extern void __std_intcleanup(void);

/* context */ 

 /* all MaxAlign-ed */ 
 
extern void * __std_context;

extern unsigned __std_context_len(void);

typedef void (*__std_entry_t)(void *arg);

extern void __std_context_init(void *context,
                               void *stack,
                               unsigned stack_len,
                               __std_entry_t entry,
                               void *arg);
                               
extern void __std_switch(void *context); // int disabled

#ifdef __cplusplus
} // extern "C"
#endif

#endif

