/* IntelAES.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/crypton/IntelAES.h>

#include <CCore/inc/crypton/IntelCPUID.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Crypton {

/* functions */

bool DetectIntelAES()
 {
  IntelCPUID1 cpuid;
  
  return cpuid.capableAES();  
 }

void GuardIntelAESNotAvailable()
 {
  Printf(Exception,"CCore::Crypton::IntelAESBase::IntelAESBase() : Intel AES commands are not available");
 }

/* struct IntelAES128Func */

#if 0 

// Fake code

void IntelAES128Func::Intel(const uint8 *round_key,uint8 *block) 
 {
  *block=*round_key;
 }

#endif

/* struct IntelAES192Func */

#if 0 

// Fake code

void IntelAES192Func::Intel(const uint8 *round_key,uint8 *block) 
 {
  *block=*round_key;
 }

#endif

/* struct IntelAES256Func */

#if 0 

// Fake code

void IntelAES256Func::Intel(const uint8 *round_key,uint8 *block) 
 {
  *block=*round_key;
 }

#endif

/* struct IntelAESInverse128Func */

#if 0 

// Fake code

void IntelAESInverse128Func::Intel(const uint8 *round_key,uint8 *block) 
 {
  *block=*round_key;
 }

#endif

/* struct IntelAESInverse192Func */

#if 0 

// Fake code

void IntelAESInverse192Func::Intel(const uint8 *round_key,uint8 *block) 
 {
  *block=*round_key;
 }

#endif

/* struct IntelAESInverse256Func */

#if 0 

// Fake code

void IntelAESInverse256Func::Intel(const uint8 *round_key,uint8 *block) 
 {
  *block=*round_key;
 }

#endif

} // namespace Crypton
} // namespace CCore


