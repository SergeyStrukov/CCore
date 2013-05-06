/* SysCon.cpp */ 
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
 
#include <CCore/inc/sys/SysCon.h>

#include <unistd.h>

namespace CCore {
namespace Sys {

/* functions */ 

void ConWrite(StrLen str) noexcept
 {
  auto ret=write(STDOUT_FILENO,str.ptr,str.len);
  
  Used(ret);
 }
 
/* struct ConRead */ 

ErrorType ConRead::init() noexcept
 {
  // TODO

  return NoError;
 }
  
ErrorType ConRead::exit() noexcept
 {
  // TODO

  return NoError;
 }
  
auto ConRead::read(char * /*buf*/,ulen /*len*/) noexcept -> IOResult
 {
  // TODO

  return IOResult{};
 }
  
auto ConRead::read(char * /*buf*/,ulen /*len*/,MSec /*timeout*/) noexcept -> IOResult
 {
  // TODO

  return IOResult{};
 }

} // namespace Sys
} // namespace CCore
 

