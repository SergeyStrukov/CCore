/* AM3359.cpp */
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

#include <CCore/inc/dev/AM3359.h>

namespace AM3359 {
namespace CP15 {

#if 0

 // Fake code

Type_CPSR GetCPSR() { return Type_CPSR(0); }

Type_MainID GetMainID() { return Type_MainID(0); }

Type_CacheType GetCacheType() { return Type_CacheType(0); }

Type_TLBType GetTLBType() { return Type_TLBType(0); }

CPUFeatures::CPUFeatures()
 {
  regs[0]=1;
  regs[1]=2;
  regs[2]=3;
  regs[3]=4;
 }

Type_SecureConfig GetSecureConfig() { return Type_SecureConfig(0); }

void SetSecureConfig(Type_SecureConfig) {}

#endif

} // namespace CP15
} // namespace AM3359
