/* stdint.h */ 
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

#ifndef XCore_stdint_h
#define XCore_stdint_h

#ifdef __STDBUILD
#include <sysroot/usr/include/limits.h>
#else
#include <limits.h>
#endif

/* fixed width types */ 

typedef   signed char       int8_t;
typedef unsigned char       uint8_t;

typedef          short      int16_t;
typedef unsigned short      uint16_t;

typedef          int        int32_t;
typedef unsigned int        uint32_t;

typedef          long long  int64_t;
typedef unsigned long long  uint64_t;

/* least width types */ 

typedef int8_t    int_least8_t;
typedef uint8_t   uint_least8_t;

typedef int16_t   int_least16_t;
typedef uint16_t  uint_least16_t;

typedef int32_t   int_least32_t;
typedef uint32_t  uint_least32_t;

typedef int64_t   int_least64_t;
typedef uint64_t  uint_least64_t;

/* fast width types */ 

typedef int32_t   int_fast8_t;
typedef uint32_t  uint_fast8_t;

typedef int32_t   int_fast16_t;
typedef uint32_t  uint_fast16_t;

typedef int32_t   int_fast32_t;
typedef uint32_t  uint_fast32_t;

typedef int64_t   int_fast64_t;
typedef uint64_t  uint_fast64_t;

/* max types */ 

typedef __INTMAX_TYPE__   intmax_t;
typedef __UINTMAX_TYPE__  uintmax_t;

/* ptr types */ 

typedef int       intptr_t;
typedef unsigned  uintptr_t;

/* limits */ 

#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)

/* fixed width types limits */ 

#define INT8_MAX    SCHAR_MAX
#define INT8_MIN    SCHAR_MIN
#define UINT8_MAX   UCHAR_MAX

#define INT16_MAX   SHRT_MAX
#define INT16_MIN   SHRT_MIN
#define UINT16_MAX  USHRT_MAX

#define INT32_MAX   INT_MAX
#define INT32_MIN   INT_MIN
#define UINT32_MAX  UINT_MAX
 
#define INT64_MAX   LLONG_MAX
#define INT64_MIN   LLONG_MIN
#define UINT64_MAX  ULLONG_MAX

/* least width types limits */ 

#define INT_LEAST8_MAX    INT8_MAX
#define INT_LEAST8_MIN    INT8_MIN
#define UINT_LEAST8_MAX   UINT8_MAX
 
#define INT_LEAST16_MAX   INT16_MAX
#define INT_LEAST16_MIN   INT16_MIN
#define UINT_LEAST16_MAX  UINT16_MAX
 
#define INT_LEAST32_MAX   INT32_MAX
#define INT_LEAST32_MIN   INT32_MIN
#define UINT_LEAST32_MAX  UINT32_MAX
 
#define INT_LEAST64_MAX   INT64_MAX
#define INT_LEAST64_MIN   INT64_MIN
#define UINT_LEAST64_MAX  UINT64_MAX
 
/* fast width types limits */ 

#define INT_FAST8_MAX    INT32_MAX
#define INT_FAST8_MIN    INT32_MIN
#define UINT_FAST8_MAX   UINT32_MAX
 
#define INT_FAST16_MAX   INT32_MAX
#define INT_FAST16_MIN   INT32_MIN
#define UINT_FAST16_MAX  UINT32_MAX
 
#define INT_FAST32_MAX   INT32_MAX
#define INT_FAST32_MIN   INT32_MIN
#define UINT_FAST32_MAX  UINT32_MAX
 
#define INT_FAST64_MAX   INT64_MAX
#define INT_FAST64_MIN   INT64_MIN
#define UINT_FAST64_MAX  UINT64_MAX
 
/* max types limits */ 

#define INTMAX_MAX       __INT_MAX_MAX__
#define INTMAX_MIN       (-INTMAX_MAX-INTMAX_C(1))
#define UINTMAX_MAX      (UINTMAX_C(2)*INTMAX_MAX+UINTMAX_C(1))
 
/* ptr types limits */ 

#define INTPTR_MAX   INT_MAX
#define INTPTR_MIN   INT_MIN
#define UINTPTR_MAX  UINT_MAX
 
/* other limits */ 

#define PTRDIFF_MIN  INT_MIN
#define PTRDIFF_MAX  INT_MAX

#define SIZE_MAX     UINT_MAX

/* const macros */ 

#define INT8_C(V)     V
#define UINT8_C(V)    V ## u

#define INT16_C(V)    V
#define UINT16_C(V)   V ## u

#define INT32_C(V)    V
#define UINT32_C(V)   V ## u

#define INT64_C(V)    V ## ll
#define UINT64_C(V)   V ## ull

#define INTMAX_C(V)   V ## ll
#define UINTMAX_C(V)  V ## ull
 
#endif
 
#endif



