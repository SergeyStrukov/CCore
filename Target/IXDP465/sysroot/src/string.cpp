/* string.cpp */ 
//----------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------

#include <sysroot/usr/include/string.h>

#include <sysroot/usr/include/stdlib.h>

/* mem...() */ 

typedef unsigned char uchar;
 
#if 0

void __std_memcpy(void *__restrict dst,const void *__restrict src_,size_t size)
 {
  uchar *ptr=static_cast<uchar *>(dst);
  uchar *lim=ptr+size;

  const uchar *src=static_cast<const uchar *>(src_);
 
  for(; ptr<lim ;ptr++,src++) (*ptr)=(*src);
 }
 
#endif

void * memmove(void *dst_,const void *src_,size_t size)
 {
  char *dst=static_cast<char *>(dst_);
  const char *src=static_cast<const char *>(src_);

  if( dst<=src )
    {
     char *dstlim=dst+size;

     while( dst<dstlim ) (*dst++)=(*src++);
    }
  else
    {
     char *dstlim=dst;

     src+=size;
     dst+=size;

     while( dst>dstlim )  (*--dst)=(*--src);
    }

  return dst_;
 }
 
#if 0
 
int memcmp(const void *a_,const void *b_,size_t size)
 {
  const uchar *a=static_cast<const uchar *>(a_);
  const uchar *b=static_cast<const uchar *>(b_);
 
  for(; size ;a++,b++,size--) 
    {
     uchar ca=(*a);
     uchar cb=(*b);
     
     if( int ret=(int)ca-(int)cb ) return ret;
    }
  
  return 0;
 }
 
#endif

#if 0
  
void __std_memset(void *dst,int c_,size_t size)
 {
  uchar *ptr=static_cast<uchar *>(dst);
  uchar *lim=ptr+size;

  uchar c=(uchar)c_;
 
  for(; ptr<lim ;ptr++) (*ptr)=c;
 }
 
#endif
 
void * memchr(const void *a,int c,size_t size)
 {
  const char *ptr=static_cast<const char *>(a);
  const char *lim=ptr+size;

  for(; ptr<lim ;ptr++) if( *ptr==char(c) ) return const_cast<char *>(ptr);

  return 0;
 }
 
/* str...() */ 

#if 0

const char * __std_strend(const char *str)
 {
  while( *str ) str++;

  return str;
 }
 
#endif
 
char * strcpy(char *__restrict dst,const char *__restrict src)
 {
  for(char *ptr=dst; ((*ptr)=(*src)) ;ptr++,src++);
 
  return dst;
 }
 
char * strcat(char *__restrict dst,const char *__restrict src)
 {
  char *end=const_cast<char *>(__std_strend(dst));
 
  strcpy(end,src);
  
  return dst;
 }
 
#if 0
 
int strcmp(const char *a,const char *b)
 {
  for(;;a++,b++)
    {
     char ca=(*a);
     char cb=(*b);
     
     if( int ret=(int)ca-(int)cb ) return ret;
     
     if( !ca ) return 0;
    }
 }
 
#endif
 
#if 0
 
int strcoll(const char *a,const char *b)
 {
  for(;;a++,b++)
    {
     char ca=(*a);
     char cb=(*b);
     
     if( int ret=(int)ca-(int)cb ) return ret;
     
     if( !ca ) return 0;
    }
 }
 
#endif
 
/* strdup() */ 

char * strdup(const char *str)
 {
  size_t size=strlen(str)+1;

  void *ret=malloc(size);

  if( !ret ) return 0;

  memcpy(ret,str,size);

  return static_cast<char *>(ret);
 }
 
/* strn...() */ 

#if 0
 
int strncmp(const char *a,const char *b,size_t size)
 {
  for(; size ;a++,b++,size--)
    {
     char ca=(*a);
     char cb=(*b);
     
     if( int ret=(int)ca-(int)cb ) return ret;
     
     if( !ca ) return 0;
    }
    
  return 0;  
 }
  
#endif

size_t strxfrm(char *__restrict dst,const char *__restrict src,size_t dst_size)
 {
  size_t ret=strlen(src);

  if( ret<dst_size )
    {
     memcpy(dst,src,ret+1);
    }

  return ret;
 }
 
