/* SlowSem.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/SlowSem.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintError.h>
 
namespace CCore {

/* class SlowSem */ 

void SlowSem::init(ulen count)
 {
  if( Sys::ErrorType error=sem.init(count) )
    {
     Printf(Exception,"CCore::SlowSem::init(...) : #;",PrintError(error));
    } 
 }
 
SlowSem::SlowSem(ulen count)
 {
  init(count);
 }
 
SlowSem::SlowSem(TextLabel,ulen count)
 {
  init(count);
 }
 
} // namespace CCore
 

