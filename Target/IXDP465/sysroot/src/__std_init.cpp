/* __std_init.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2009 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <sysroot/usr/include/__std_init.h>

#include <sysroot/usr/include/string.h>

extern char __std_context_data[];
extern char __std_context_data_lim[];

extern const void *const __std_context_data_init;

static void exittrap()
 {
  __std_abort("exittrap() is called -- trap");
 } 
  
void __std_context_init(void *context_,
                        void *stack,
                        unsigned stack_len,
                        __std_entry_t entry,
                        void *arg)
 {
  unsigned stack_off=stack_len-16;
 
  unsigned CPSR=0x53;
  unsigned LR=unsigned(&exittrap);
  unsigned PC=unsigned(entry)+4;
  unsigned SP=unsigned(static_cast<char *>(stack)+stack_off);
  unsigned R0=unsigned(arg);
 
  unsigned *context=static_cast<unsigned *>(context_);
  
  context[0]=R0;
  context[1]=0;
  context[2]=0;
  context[3]=0;
  context[4]=0;
  context[5]=0;
  context[6]=0;
  context[7]=0;
  context[8]=0;
  context[9]=0;
  context[10]=0;
  context[11]=0;
  context[12]=0;
  
  context[13]=SP;
  context[14]=LR;
  context[15]=PC;
  context[16]=CPSR;
  
  memcpy(context+17,__std_context_data_init,(__std_context_data_lim-__std_context_data));
 }                      
 

