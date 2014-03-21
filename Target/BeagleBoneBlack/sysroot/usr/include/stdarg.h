/* stdarg.h */ 
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

#ifndef XCore_stdarg_h
#define XCore_stdarg_h

/* va_list */ 

typedef __builtin_va_list  va_list;

#define va_start(arg_list,last_arg)  __builtin_va_start(arg_list,last_arg)

#define va_end(arg_list)             __builtin_va_end(arg_list)

#define va_arg(arg_list,type)        __builtin_va_arg(arg_list,type)

#define va_copy(dst,src)             __builtin_va_copy(dst,src)
 
#endif






