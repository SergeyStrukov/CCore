/* string.h */ 
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

#ifndef XCore_string_h
#define XCore_string_h

#ifdef __STDBUILD
#include <sysroot/usr/include/stddef.h>
#else
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* mem...() */ 

extern void __std_memcpy(void *__restrict dst,const void *__restrict src,size_t size);

/* extern void * memcpy(void *__restrict dst,const void *__restrict src,size_t size); */ 

extern void * memmove(void *dst,const void *src,size_t size);

extern int memcmp(const void *a,const void *b,size_t size);

extern void __std_memset(void *dst,int c,size_t size);

/* extern void * memset(void *dst,int c,size_t size); */ 

extern void * memchr(const void *a,int c,size_t size);

/* str...() */ 

extern const char * __std_strend(const char *a);

/* extern size_t strlen(const char *a); */ 

extern char * strcpy(char *__restrict dst,const char *__restrict src);

extern char * strcat(char *__restrict dst,const char *__restrict src);

extern int strcmp(const char *a,const char *b);

extern int strcoll(const char *a,const char *b);

extern char * strchr(const char *a,int c);

extern char * strrchr(const char *a,int c);

extern char * strstr(const char *a,const char *b);

extern size_t strspn(const char *a,const char *b);

extern size_t strcspn(const char *a,const char *b);

extern char * strpbrk(const char *a,const char *b);

extern char * strtok(char *__restrict dst,const char *__restrict src);

extern char * strerror(int errnum);

/* strdup() */ 

extern char * strdup(const char *str); /* ext function */ 

/* strn...() */ 

extern char * strncpy(char *__restrict dst,const char *__restrict src,size_t size);

extern char * strncat(char *__restrict dst,const char *__restrict src,size_t size);

extern int strncmp(const char *a,const char *b,size_t size);

extern size_t strxfrm(char *__restrict dst,const char *__restrict src,size_t size);

#ifdef __cplusplus
} // extern "C"
#endif

/* inline */ 

#ifdef __cplusplus

inline void * memcpy(void *__restrict dst,const void *__restrict src,size_t size)
 {
  __std_memcpy(dst,src,size);
  
  return dst;
 }
 
inline void * memset(void *dst,int c,size_t size)
 {
  __std_memset(dst,c,size);
  
  return dst;
 }
 
inline size_t strlen(const char *a)
 {
  return size_t( __std_strend(a) - a );
 }
 
#else

extern void * memcpy(void *__restrict dst,const void *__restrict src,size_t size);

extern void * memset(void *dst,int c,size_t size);

extern size_t strlen(const char *a);
 
#endif

#endif

