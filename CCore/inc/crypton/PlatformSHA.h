/* PlatformSHA.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: GeneralStub
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_PlatformSHA_h
#define CCore_inc_crypton_PlatformSHA_h
 
#include <CCore/inc/crypton/SHA.h>

namespace CCore {
namespace Crypton {

/* types */

using PlatformSHA1 = SHA1 ;
using PlatformSHA224 = SHA224 ;
using PlatformSHA256 = SHA256 ;
using PlatformSHA384 = SHA384 ;
using PlatformSHA512 = SHA512 ;

using PlatformKeyedSHA1 = KeyedSHA1 ;
using PlatformKeyedSHA224 = KeyedSHA224 ;
using PlatformKeyedSHA256 = KeyedSHA256 ;
using PlatformKeyedSHA384 = KeyedSHA384 ;
using PlatformKeyedSHA512 = KeyedSHA512 ;

} // namespace Crypton
} // namespace CCore
 
#endif
 

