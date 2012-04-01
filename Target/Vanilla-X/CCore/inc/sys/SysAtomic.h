/* SysAtomic.h */ 
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

#ifndef CCore_inc_sys_SysAtomic_h
#define CCore_inc_sys_SysAtomic_h
 
namespace CCore {
namespace Sys {

/* classes */ 

struct Atomic;

/* struct Atomic */ 

struct Atomic
 {
  // public
  
  typedef unsigned Type; // unsigned integral type

  // private data
  
  volatile Type atomic;

  // private
  
  static Type Get(const volatile Type *atomic) { return *atomic; }
 
  static Type Set(volatile Type *atomic,Type value) noexcept;

  static Type Add(volatile Type *atomic,Type value) noexcept;

  static Type Sub(volatile Type *atomic,Type value) { return Add(atomic,-value); }
 
  static Type Inc(volatile Type *atomic) { return Add(atomic,1); }
 
  static Type Dec(volatile Type *atomic) { return Sub(atomic,1); }
 
  static Type TrySet(volatile Type *atomic,Type old_value,Type new_value) noexcept;

  // public
  
  typedef Type PrintProxyType;
  
  void set_null() { atomic=0; }
  
  operator Type() const { return Get(&atomic); }
  
  // return previous value, memory fence is used (actually, no memory fence on unicore systems) 

  Type operator  = (Type value) { return Set(&atomic,value); }
  
  Type operator += (Type value) { return Add(&atomic,value); }
  
  Type operator -= (Type value) { return Sub(&atomic,value); }
  
  Type operator ++ (int) { return Inc(&atomic); }
  
  Type operator -- (int) { return Dec(&atomic); }
  
  Type trySet(Type old_value,Type new_value) { return TrySet(&atomic,old_value,new_value); }
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

