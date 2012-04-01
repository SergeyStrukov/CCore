/* PrintCon.cpp */ 
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
 
#include <CCore/inc/print/PrintCon.h>

#include <CCore/inc/sys/SysCon.h>
 
namespace CCore {

/* class PrintCon */ 

PtrLen<char> PrintCon::do_provide(ulen)
 {
  return Range(buf);
 }
   
void PrintCon::do_flush(char *ptr,ulen len)
 {
  Print(ptr,len);
 }
 
void PrintCon::Print(StrLen str)
 {
  Sys::ConWrite(str);
 }
 
} // namespace CCore
 

