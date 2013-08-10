/* SysSem.h */ 
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

#ifndef CCore_inc_sys_SysSem_h
#define CCore_inc_sys_SysSem_h
 
#include <CCore/inc/sys/SysError.h>

namespace CCore {
namespace Sys {

/* classes */ 

struct Sem;

/* struct Sem */ 

struct Sem
 {
  // private data
  
  typedef long Type;
  
  Type handle;
  
  // private
  
  struct CreateType
   {
    Type handle;
    ErrorType error;
   };
   
  static CreateType Create(ulen count) noexcept;
  
  static void Destroy(Type handle) noexcept;
  
  static void Give(Type handle) noexcept;
  
  static void GiveMany(Type handle,ulen count) noexcept;
  
  static bool TryTake(Type handle) noexcept;
  
  static void Take(Type handle) noexcept;
  
  static bool Take(Type handle,MSec timeout) noexcept;
  
  // public
  
  ErrorType init(ulen count=0)
   {
    CreateType result=Create(count);
    
    handle=result.handle;
    
    return result.error;
   }
  
  void exit() { Destroy(handle); }
  
  void give() { Give(handle); }
  
  void give_many(ulen count) { GiveMany(handle,count); }
  
  bool try_take() { return TryTake(handle); }
  
  void take() { Take(handle); }
  
  bool take(MSec timeout) { return Take(handle,timeout); }
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

