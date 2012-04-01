/* time.h */ 
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

#ifndef XCore_time_h
#define XCore_time_h

#ifdef __STDBUILD
#include <sysroot/usr/include/stddef.h>
#else
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* clock() */  
 
#define CLOCKS_PER_SEC     66660000

typedef unsigned clock_t;

extern clock_t clock(void); 

/* time() */ 

typedef unsigned time_t;

extern time_t time(time_t *time_ptr);

/* time utilities */ 

struct tm
 {
  int tm_sec;
  int tm_min;
  int tm_hour;
  
  int tm_mday;
  int tm_mon;
  int tm_year;
  
  int tm_wday;
  int tm_yday;
  int tm_isdst;
 };
 
extern double difftime(time_t time1,time_t time2);

extern time_t mktime(struct tm *tm_ptr);

extern char * asctime(const struct tm *tm_ptr);
 
extern char * ctime(const time_t *time_ptr);

extern struct tm * gmtime(const time_t *time_ptr);

extern struct tm * localtime(const time_t *time_ptr);

extern size_t strftime(char *__restrict dst,size_t dst_size,
                       const char *__restrict format,
                       const struct tm *__restrict tm_ptr);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

