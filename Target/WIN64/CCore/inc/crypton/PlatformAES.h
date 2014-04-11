/* PlatformAES.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_PlatformAES_h
#define CCore_inc_crypton_PlatformAES_h

#include <CCore/inc/crypton/IntelAES.h>
 
namespace CCore {
namespace Crypton {

/* types */

using PlatformAES128 = IntelAES128 ;
using PlatformAES192 = IntelAES192 ;
using PlatformAES256 = IntelAES256 ;

using PlatformAESInverse128 = IntelAESInverse128 ;
using PlatformAESInverse192 = IntelAESInverse192 ;
using PlatformAESInverse256 = IntelAESInverse256 ; 

} // namespace Crypton
} // namespace CCore
 
#endif
 

