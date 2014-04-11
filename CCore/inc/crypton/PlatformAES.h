/* PlatformAES.h */ 
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

#ifndef CCore_inc_crypton_PlatformAES_h
#define CCore_inc_crypton_PlatformAES_h

#include <CCore/inc/crypton/AES.h>
 
namespace CCore {
namespace Crypton {

/* types */

using PlatformAES128 = AES128 ;
using PlatformAES192 = AES192 ;
using PlatformAES256 = AES256 ;

using PlatformAESInverse128 = AESInverse128 ;
using PlatformAESInverse192 = AESInverse192 ;
using PlatformAESInverse256 = AESInverse256 ; 

} // namespace Crypton
} // namespace CCore
 
#endif
 

