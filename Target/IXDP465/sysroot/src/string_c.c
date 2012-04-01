/* string_c.c */ 
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

#include <sysroot/usr/include/string.h>

void * memcpy(void *__restrict dst,const void *__restrict src,size_t size)
 {
  __std_memcpy(dst,src,size);
  
  return dst;
 }
 
void * memset(void *dst,int c,size_t size)
 {
  __std_memset(dst,c,size);
  
  return dst;
 }
 
size_t strlen(const char *a)
 {
  return (size_t)( __std_strend(a) - a );
 }
 
 
