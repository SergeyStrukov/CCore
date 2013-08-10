/* SysTlsSlot.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysTlsSlot_h
#define CCore_inc_sys_SysTlsSlot_h

#include <CCore/inc/sys/SysError.h>
 
namespace CCore {
namespace Sys {

/* classes */ 

struct TlsSlot;

/* struct TlsSlot */ 

struct TlsSlot
 {
  // private data
  
  typedef int Type;
 
  Type index;
  
  // private
  
  struct AllocType
   {
    Type index;
    ErrorType error;
   };
   
  static AllocType Alloc() noexcept;
  
  static void Free(Type index) noexcept;
  
  static void * Get(Type index) noexcept;
  
  static void Set(Type index,void *value) noexcept;
  
  // public
  
  ErrorType init()
   {
    AllocType result=Alloc();
    
    index=result.index;
    
    return result.error;
   }
  
  void exit() { Free(index); }
  
  void * get() { return Get(index); }
  
  void set(void *value) { Set(index,value); }
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

