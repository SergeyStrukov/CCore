/* limits.h */ 
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

#ifndef XCore_limits_h
#define XCore_limits_h

/* char */ 

#define CHAR_BIT      __CHAR_BIT__

#define MB_LEN_MAX    1

#define SCHAR_MAX     __SCHAR_MAX__

#define SCHAR_MIN     (-SCHAR_MAX-1)

#define UCHAR_MAX     (2*SCHAR_MAX+1)

#ifdef __CHAR_UNSIGNED__

#define CHAR_MAX      UCHAR_MAX
 
#define CHAR_MIN      0

#else

#define CHAR_MAX      SCHAR_MAX
 
#define CHAR_MIN      SCHAR_MIN

#endif

/* short */ 

#define SHRT_MAX      __SHRT_MAX__

#define SHRT_MIN      (-SHRT_MAX-1)

#define USHRT_MAX     (2*SHRT_MAX+1)

/* int */ 

#define INT_MAX       __INT_MAX__

#define INT_MIN       (-INT_MAX-1)

#define UINT_MAX      (2u*INT_MAX+1u)

/* long */ 

#define LONG_MAX       __LONG_MAX__

#define LONG_MIN       (-LONG_MAX-1l)

#define ULONG_MAX      (2ul*LONG_MAX+1ul)

/* long long */ 

#define LLONG_MAX       __LONG_LONG_MAX__

#define LLONG_MIN       (-LLONG_MAX-1ll)

#define ULLONG_MAX      (2ull*LLONG_MAX+1ull)
 
#endif

