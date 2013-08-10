/* SysCon.h */ 
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

#ifndef CCore_inc_sys_SysCon_h
#define CCore_inc_sys_SysCon_h
 
#include <CCore/inc/sys/SysError.h>

namespace CCore {
namespace Sys {

/* functions */ 

void ConWrite(StrLen str) noexcept;

/* classes */ 

struct ConRead;

/* struct ConRead */ 

struct ConRead
 {
  // public
  
  struct IOResult
   {
    ulen len;
    ErrorType error;
   };
  
  // private data
  
  typedef long Type;
  typedef unsigned ModeType;
  
  Type handle;
  ModeType modes;
  
  // private
  
  struct InitType
   {
    Type handle;
    ModeType modes;
    ErrorType error;
   };
  
  static InitType Init() noexcept;
  
  static ErrorType Exit(Type handle,ModeType modes) noexcept;
  
  static IOResult Read(Type handle,char *buf,ulen len) noexcept;
  
  static IOResult Read(Type handle,char *buf,ulen len,MSec timeout) noexcept;
  
  // public
  
  ErrorType init()
   {
    InitType result=Init();
    
    handle=result.handle;
    modes=result.modes;
    
    return result.error;
   }
  
  ErrorType exit() { return Exit(handle,modes); }
  
  IOResult read(char *buf,ulen len) { return Read(handle,buf,len); }
  
  IOResult read(char *buf,ulen len,MSec timeout) { return Read(handle,buf,len,timeout); }
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

