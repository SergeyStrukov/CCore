/* setjmp.h */ 
/*----------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------*/

#ifndef XCore_setjmp_h
#define XCore_setjmp_h

#ifdef __cplusplus
extern "C" {
#endif

struct __std_jmp_buf
 {
  unsigned xxx;
 };
 
typedef struct __std_jmp_buf jmp_buf[1];
  
extern int setjmp(jmp_buf env);

extern void longjmp(jmp_buf env,int val);

#ifdef __cplusplus
} // extern "C"
#endif

#endif



