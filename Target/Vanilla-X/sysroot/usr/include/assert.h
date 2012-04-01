/* assert.h */ 
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

#ifndef XCore_assert_h
#define XCore_assert_h

#ifdef __cplusplus
extern "C" {
#endif

/* __std_assert_failed() */ 

extern int __std_assert_failed(const char *cond,const char *file_name,int line,const char *func_name);

/* assert() */ 

#ifdef NDEBUG

#define assert(ignore) ((void)0)
 
#else

#define assert(cond) ((void)((cond)?0:__std_assert_failed(#cond,__FILE__,__LINE__,__func__)))
 
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif

