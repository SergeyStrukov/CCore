/* stddef.h */ 
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

#ifndef XCore_stddef_h
#define XCore_stddef_h

/* size_t */ 

typedef __SIZE_TYPE__ size_t;

/* ptrdiff_t */ 

typedef __PTRDIFF_TYPE__ ptrdiff_t;

/* wchar_t */ 

#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif

/* NULL */ 

#ifdef __cplusplus
#define NULL  0
#else
#define NULL  ((void *)0)
#endif

/* offsetof() */ 

#define offsetof(TYPE,MEMBER) __builtin_offsetof(TYPE,MEMBER)
 
#endif




