/* Atomic.h */ 
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

#ifndef CCore_inc_task_Atomic_h
#define CCore_inc_task_Atomic_h

#include <CCore/inc/Gadget.h>

#include <CCore/inc/sys/SysAtomic.h>
 
namespace CCore {

/* classes */ 

class Atomic;

/* class Atomic */ 

class Atomic : NoCopy
 {
   Sys::Atomic atomic;
   
  public: 
  
   typedef Sys::Atomic::Type Type;
   
   Atomic() { atomic.set_null(); }
   
   typedef Type PrintProxyType;
  
   operator Type() const { return atomic; }
  
   // return previous value, memory fence is used

   Type operator  = (Type value) { return atomic=value; }
  
   Type operator += (Type value) { return atomic+=value; }
  
   Type operator -= (Type value) { return atomic-=value; }
  
   Type operator ++ (int) { return atomic++; }
  
   Type operator -- (int) { return atomic--; }
  
   Type trySet(Type old_value,Type new_value) { return atomic.trySet(old_value,new_value); }
 };
 
} // namespace CCore
 
#endif
 

