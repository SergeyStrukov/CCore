/* HashMap.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: Regen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "HashMap.h"

#include <CCore/inc/Crc.h>

namespace App {

/* struct HashBase */

ulen HashBase::Key(StrLen str)
 {
  Crc16 crc;
  
  crc.addRange(str);
  
  return crc;
 }

} // namespace App
 
