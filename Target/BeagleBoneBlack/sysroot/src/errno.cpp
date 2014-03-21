/* errno.cpp */ 
//----------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------

#include <sysroot/usr/include/errno.h>

#include <sysroot/usr/include/string.h>

/* __std_errno() */ 

static int Actual_errno __attribute__((section(".context_data"))) = 0 ;
 
int * __std_errno(void)
 {
  return &Actual_errno;
 }
 
/* strerror() */  
 
char * strerror(int errnum)
 {
  static char *const table[]=
   {
    "no error",
    
    "out of domain",
    "char encoding error",
    "out of valid range",
    
    "no such file",
    "no such path",
    "access denied",
    
    "no memory",
    "bad argument",
    "not supported",
    
    "io fault",
    "fault",
    "unknown"
   };
   
  if( errnum<0 || errnum>EUNKNOWN ) errnum=EUNKNOWN;
   
  return table[errnum]; 
 }
 
