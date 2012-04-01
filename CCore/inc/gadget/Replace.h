/* Replace.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_Replace_h
#define CCore_inc_gadget_Replace_h

#include <CCore/inc/gadget/UtilFunc.h>
 
namespace CCore {

/* Replace...() */ 

template <class T,class S>
T Replace(T &t,S a) { T ret(t); t=a; return ret; }
 
template <class T> 
T Replace_null(T &t) { T ret(t); t=T(); return ret; }
 
template <class T>
T Replace_min(T &t,T a) { T ret(t); t=Min(ret,a); return ret; }
 
template <class T>
T Replace_max(T &t,T a) { T ret(t); t=Max(ret,a); return ret; }
 
template <class T,class S>
T Replace_add(T &t,S a) { T ret(t); t=ret+a; return ret; }
 
template <class T,class S>
T Replace_sub(T &t,S a) { T ret(t); t=ret-a; return ret; }
 
template <class Func,class T>
T Replace_gen(Func func,T &t) { T ret(t); t=func(ret); return ret; }
 
} // namespace CCore
 
#endif
 

