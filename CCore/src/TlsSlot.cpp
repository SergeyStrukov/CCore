/* TlsSlot.cpp */ 
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
 
#include <CCore/inc/TlsSlot.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* class TlsSlot */ 
 
void TlsSlot::init() 
 { 
  if( slot.init() ) Abort("Fatal error : TLS is full"); 
 }
   
void TlsSlot::exit() 
 { 
  slot.exit(); 
 }
 
TlsSlot::TlsSlot(const char *tag)
 : PlanInitNode(tag,getReqList())
 {
 }
   
TlsSlot::~TlsSlot()
 {
 }
 
} // namespace CCore
 

