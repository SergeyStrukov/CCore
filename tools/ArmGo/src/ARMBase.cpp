/* ARMBase.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ARMGo 0.50
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/ARMBase.h>

namespace ARMCore {

/* enum MemTag */

const char * GetTextDesc(MemTag tag)
 {
  static const char *const Table[]=
   {
    "Ok",              // MemTag_Ok
     
    "Not exist",       // MemTag_Void
    "Not initialized", // MemTag_NoVal
    "Not writable",    // MemTag_NoW
    "Not executable",  // MemTag_NoX
    "Not aligned",     // MemTag_NotAligned
   };
  
  return Table[tag];
 }

} // namespace ARMCore

