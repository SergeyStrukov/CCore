/* locale.cpp */ 
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

#include <sysroot/usr/include/locale.h>

#include <sysroot/usr/include/string.h>
#include <sysroot/usr/include/limits.h>
#include <sysroot/usr/include/errno.h>
 
char * setlocale(int /*category*/,const char *locale)
 {
  if( !locale || !strcmp(locale,"C") || !strcmp(locale,"") )
    {
     return "C";
    }
    
  errno=EBADARG;  
    
  return 0;  
 }
 
static struct lconv actual_lconv_s=
 {
  ".",
  "",
  "",
  
  "",
  "",
  "",
  
  "",
  "",
  
  "",
  
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  
  "",
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX,
  SCHAR_MAX
 };
 
struct lconv * __std_localeconv_s(void)
 {
  return &actual_lconv_s;
 }
 
static struct lconv actual_lconv_u=
 {
  ".",
  "",
  "",
  
  "",
  "",
  "",
  
  "",
  "",
  
  "",
  
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  
  "",
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX,
  (char)UCHAR_MAX
 };
 
struct lconv * __std_localeconv_u(void)
 {
  return &actual_lconv_u;
 }
 
