/* locale.h */ 
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

#ifndef XCore_locale_h
#define XCore_locale_h

#ifdef __STDBUILD
#include <sysroot/usr/include/stddef.h>
#include <sysroot/usr/include/limits.h>
#else
#include <stddef.h>
#include <limits.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define LC_ALL       1
#define LC_COLLATE   2
#define LC_CTYPE     3
#define LC_MONETARY  4
#define LC_NUMERIC   5
#define LC_TIME      6

struct lconv
 {
  char *decimal_point;      /* "." */ 
  char *thousands_sep;      /* "" */ 
  char *grouping;           /* "" */ 
  
  char *mon_decimal_point;  /* "" */ 
  char *mon_thousands_sep;  /* "" */ 
  char *mon_grouping;       /* "" */ 
  
  char *positive_sign;      /* "" */ 
  char *negative_sign;      /* "" */ 
  
  char *currency_symbol;    /* "" */ 
  
  char frac_digits;         /* CHAR_MAX */ 
  char p_cs_precedes;       /* CHAR_MAX */ 
  char n_cs_precedes;       /* CHAR_MAX */ 
  char p_sep_by_space;      /* CHAR_MAX */ 
  char n_sep_by_space;      /* CHAR_MAX */ 
  char p_sign_posn;         /* CHAR_MAX */ 
  char n_sign_posn;         /* CHAR_MAX */ 
  
  char *int_curr_symbol;    /* "" */ 
  char int_frac_digits;     /* CHAR_MAX */ 
  char int_p_cs_precedes;   /* CHAR_MAX */ 
  char int_n_cs_precedes;   /* CHAR_MAX */ 
  char int_p_sep_by_space;  /* CHAR_MAX */ 
  char int_n_sep_by_space;  /* CHAR_MAX */ 
  char int_p_sign_posn;     /* CHAR_MAX */ 
  char int_n_sign_posn;     /* CHAR_MAX */ 
 };
 
extern char * setlocale(int category,const char *locale); 
 
extern struct lconv * __std_localeconv_s(void);
extern struct lconv * __std_localeconv_u(void);

#ifdef __cplusplus

#if (CHAR_MIN==0) 

inline struct lconv * localeconv() { return __std_localeconv_u(); }
 
#else

inline struct lconv * localeconv() { return __std_localeconv_s(); }
 
#endif
 
#else
 
#if (CHAR_MIN==0) 

#define localeconv()  (__std_localeconv_u())
 
#else

#define localeconv()  (__std_localeconv_s())
 
#endif
 
#endif
 
#ifdef __cplusplus
} // extern "C"
#endif

#endif


