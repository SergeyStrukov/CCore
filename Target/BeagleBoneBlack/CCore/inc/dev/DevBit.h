/* DevBit.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevBit_h
#define CCore_inc_dev_DevBit_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Dev {

/* type RegType */

using RegType = uint32 ;

/* functions */

inline constexpr RegType Bit(unsigned num) { return RegType(1)<<num; }

inline constexpr RegType Mask(unsigned num) { return (RegType(1)<<num)-1; }

} // namespace Dev
} // namespace CCore
 
#endif
 

