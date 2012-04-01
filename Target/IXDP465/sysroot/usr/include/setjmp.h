/* setjmp.h */ 
/*----------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------*/

#ifndef XCore_setjmp_h
#define XCore_setjmp_h

#ifdef __cplusplus
extern "C" {
#endif

struct __std_jmp_buf
 {
  unsigned r1;
  unsigned r2;
  unsigned r3;
  unsigned r4;
  unsigned r5;
  unsigned r6;
  unsigned r7;
  unsigned r8;
  unsigned r9;
  unsigned r10;  /* sl */ 
  unsigned r11;  /* fp */ 
  unsigned r12;  /* ip */ 
  unsigned r13;  /* sp */ 
  unsigned r14;  /* lr */ 
 };
 
typedef struct __std_jmp_buf jmp_buf[1];
  
extern int setjmp(jmp_buf env);

extern void longjmp(jmp_buf env,int val);

#ifdef __cplusplus
} // extern "C"
#endif

#endif



