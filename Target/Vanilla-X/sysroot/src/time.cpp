/* time.cpp */ 
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

#include <sysroot/usr/include/time.h>

#include <sysroot/usr/include/__std_init.h>

/* time utilities */ 

size_t strftime(char *__restrict,size_t,const char *__restrict,const struct tm *__restrict)
 {
  __std_abort("strftime() is called -- trap");
 }
 
