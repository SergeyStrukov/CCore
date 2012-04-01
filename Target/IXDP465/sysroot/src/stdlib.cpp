/* stdlib.cpp */ 
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

#include <sysroot/usr/include/stdlib.h>

#include <sysroot/usr/include/__std_init.h>

/* strto...() */ 

float strtof(const char *__restrict,char **__restrict)
 {
  __std_abort("strtof() is called -- trap");
 }
 
double strtod(const char *__restrict,char **__restrict)
 {
  __std_abort("strtod() is called -- trap");
 }
 
long double strtold(const char *__restrict,char **__restrict)
 {
  __std_abort("strtold() is called -- trap");
 }
 
/* termination */ 

void abort(void)
 {
  __std_abort("abort() is called");
 }
  
void exit(int)
 {
  __std_abort("exit() is called -- trap");
 }  
 
void _Exit(int)
 {
  __std_abort("_Exit() is called -- trap");
 }  
 
