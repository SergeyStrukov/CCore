/* __std_init.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <sysroot/usr/include/__std_init.h>

#include <sysroot/usr/include/string.h>

/* abort */ 

void __std_abort(const char * /*msg*/)
 {
  // TODO
 }

void __std_abort2(const char * /*msg*/,unsigned /*len*/)
 {
  // TODO
 }

/* mem */ 

 /* all MaxAlign-ed */ 

unsigned __std_get_heap_int_len(void)
 {
  // TODO

  return 0;
 }

unsigned __std_get_heap_len(void)
 {
  // TODO

  return 0;
 }

unsigned __std_get_syslog_len(void)
 {
  // TODO

  return 0;
 }

void * __std_alloc(unsigned /*len*/)
 {
  // TODO

  return 0;
 }

void * __std_alloc_stack(unsigned /*len*/)
 {
  // TODO

  return 0;
 }

/* shared mem */ 

 /* all MaxAlign-ed */ 
 
void * __std_get_shared_mem(void)
 {
  // TODO

  return 0;
 }

unsigned __std_get_shared_mem_len(void)
 {
  // TODO

  return 0;
 }

/* int */ 

void __std_intsetup(__std_handler_t /*handler*/)
 {
  // TODO
 }

void __std_intcleanup(void)
 {
  // TODO
 }

/* context */ 

 /* all MaxAlign-ed */ 
 
void * __std_context=0;

unsigned __std_context_len(void)
 {
  // TODO

  return 0;
 }

void __std_context_init(void * /*context*/,
                        void * /*stack*/,
                        unsigned /*stack_len*/,
                        __std_entry_t /*entry*/,
                        void * /*arg*/)
 {
  // TODO
 }
                               
void __std_switch(void * /*context*/)
 {
  // TODO
 }

