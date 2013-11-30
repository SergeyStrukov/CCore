/* StrKey.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/StrKey.h>

#include <CCore/inc/Crc.h>
 
namespace CCore {

/* struct StrKey */

StrKey::StrKey(StrLen str_)
 : str(str_)
 {
  Crc32 crc;
   
  crc.addRange(str_);
   
  hash=crc;
 }

} // namespace CCore
 

