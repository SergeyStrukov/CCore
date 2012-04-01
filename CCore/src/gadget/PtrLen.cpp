/* PtrLen.cpp */ 
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
 
#include <CCore/inc/gadget/PtrLen.h>

#include <CCore/inc/Exception.h>
 
#include <cstring>
 
namespace CCore {

/* functions */ 

void GuardIndexOutOfRange(ulen index,ulen len)
 {
  Printf(Exception,"CCore::GuardIndex(index=#;,len=#;) : out of range",index,len);
 }
 
/* struct StrLen */ 

StrLen::StrLen(const char *zstr) : PtrLen<const char>(zstr,std::strlen(zstr)) {}
 
} // namespace CCore
 

