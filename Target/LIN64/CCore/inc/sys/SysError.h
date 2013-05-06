/* SysError.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysError_h
#define CCore_inc_sys_SysError_h
 
#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Sys {

/* enum ErrorType */ 

enum ErrorType : int
 {
  NoError = 0,
    
  Error_SysErrorFault = -1
 };
 
/* private functions */ 

ErrorType NonNullError() noexcept;
 
inline ErrorType ErrorIf(bool nok) { if( nok ) return NonNullError(); return NoError; }  
 
/* classes */ 

struct ErrorDesc;

/* struct ErrorDesc */ 

struct ErrorDesc
 {
  // public data
 
  const char *str;
  ulen len;
  
  // private
  
  bool set(StrLen msg);
  
  bool setnone();
  
  // public

  bool init(ErrorType error,PtrLen<char> buf) noexcept;
  
  const char * getPtr() const { return str; }
  
  ulen getLen() const { return len; }
 };
  
} // namespace Sys
} // namespace CCore
 
#endif
 

