/* Quick.h */ 
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

#ifndef CCore_inc_base_Quick_h
#define CCore_inc_base_Quick_h

#include <CCore/inc/base/PlatformBase.h>
 
namespace CCore {
namespace Quick {

/* consts */

const bool ScanLSBitIsFast = false ;
const bool ScanMSBitIsFast = false ;

/* types */ 

typedef uint32 ScanUInt;

/* functions */ 

unsigned ScanLSBit(ScanUInt value) noexcept;

unsigned ScanMSBit(ScanUInt value) noexcept;

uint16 ByteSwap16(uint16 value) noexcept;
 
uint32 ByteSwap32(uint32 value) noexcept;
 
uint64 ByteSwap64(uint64 value) noexcept;

} // namespace Quick
} // namespace CCore
 
#endif
 

