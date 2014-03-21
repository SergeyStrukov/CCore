/* stdlib.h */ 
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

#ifndef XCore_stdlib_h
#define XCore_stdlib_h

#ifdef __STDBUILD
#include <sysroot/usr/include/stddef.h>
#else
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* consts */ 

#define MB_CUR_MAX 1

/* ato...() */ 

extern double atof(const char *str);
 
extern int atoi(const char *str);
 
extern long atol(const char *str);
 
extern long long atoll(const char *str);

/* strto...() */ 

extern float strtof(const char *__restrict str,char **__restrict endptr);

extern double strtod(const char *__restrict str,char **__restrict endptr);
 
extern long double strtold(const char *__restrict str,char **__restrict endptr);

extern long strtol(const char *__restrict str,char **__restrict endptr,int base);

extern long long strtoll(const char *__restrict str,char **__restrict endptr,int base);

extern unsigned long strtoul(const char *__restrict str,char **__restrict endptr,int base);

extern unsigned long long strtoull(const char *__restrict str,char **__restrict endptr,int base);

/* rand() */ 

#define RAND_MAX ((1<<16)-1)

extern void srand(unsigned seed);

extern int rand(void);

/* malloc() */ 

extern void * malloc(size_t size);

extern void * calloc(size_t elem_count,size_t elem_size);

extern void * realloc(void *mem,size_t size);

extern void free(void *mem);

/* malloc_int() */ 

extern void * malloc_int(size_t size); /* ext function */ 

extern void free_int(void *mem); /* ext function */ 

/* ...env() */ 

extern char * getenv(const char *name);

/* system() */ 

extern int system(const char *cmd);

/* search and sort */ 

extern void * bsearch(const void *key,
                      const void *base,size_t elem_count,size_t elem_size,
                      int (*cmp)(const void *,const void *));
                      
extern void qsort(const void *base,size_t elem_count,size_t elem_size,
                  int (*cmp)(const void *,const void *));                      
                  
/* arithmetic */                   

extern int abs(int);

extern long labs(long);

extern long long llabs(long long);

struct __std_div_t
 {
  int quot;
  int rem;
 };
 
typedef struct __std_div_t div_t;

extern div_t div(int a,int b);
 
struct __std_ldiv_t
 {
  long quot;
  long rem;
 };
 
typedef struct __std_ldiv_t ldiv_t;

extern ldiv_t ldiv(long a,long b);

struct __std_lldiv_t
 {
  long long quot;
  long long rem;
 };
 
typedef struct __std_lldiv_t lldiv_t;

extern lldiv_t lldiv(long long a,long long b);

/* char utils */ 

extern int mblen(const char *mbstr,size_t size);

extern int mbtowc(wchar_t *__restrict dst,const char *__restrict src,size_t size);

extern int wctomb(char *str,wchar_t wc);

extern size_t mbstowcs(wchar_t *__restrict dst,const char *__restrict src,size_t dst_size);

extern size_t wcstombs(char *__restrict dst,const wchar_t *__restrict src,size_t dst_size);

/* termination */ 

#define EXIT_SUCCESS  0
#define EXIT_FAILURE  1

extern void abort(void);

extern void _Exit(int status);

extern void exit(int status);

typedef void (*__std_atexit_t)(void);

extern int atexit(__std_atexit_t func);

typedef void (*__cxa_atexit_t)(void *arg);

extern int __cxa_atexit(__cxa_atexit_t func,void *arg,void *dso);

#ifdef __cplusplus
} // extern "C"
#endif

#endif


