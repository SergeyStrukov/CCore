/* PrintCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
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
  packet=Sys::AllocConPacket(timeout);
  
  if( !packet ) return Nothing;
  
  return packet.getMaxRange();
 }
 
void PrintCon::do_flush(char *,ulen len)
 {
  packet.setDataLen(len);
  
  Sys::ConWrite(Replace_null(packet));
 }
 
void PrintCon::Print(const char *ptr,ulen len)
 {
  PrintCon out(Con);
  
  out.put(ptr,len);
 }
 
} // namespace CCore
 

