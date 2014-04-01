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

Type_DataFaultStatus GetDataFaultStatus() { return Type_DataFaultStatus(0); }

Type_InstructionFaultStatus GetInstructionFaultStatus() { return Type_InstructionFaultStatus(0); }

Type_DataFaultAddress GetDataFaultAddress() { return Type_DataFaultAddress(0); }

Type_InstructionFaultAddress GetInstructionFaultAddress() { return Type_InstructionFaultAddress(0); }

Type_Control GetControl() { return Type_Control(0); }

void SetControl(Type_Control) {}

Type_CacheSizeID GetCacheSizeID() { return Type_CacheSizeID(0); }

void SetCacheSizeSel(Type_CacheSizeSel) {}

Type_DomainAccessControl GetDomainAccessControl() { return Type_DomainAccessControl(0); }

void SetDomainAccessControl(Type_DomainAccessControl) {}

Type_TTBase0 GetTTBase0() { return Type_TTBase0(0); }

void SetTTBase0(Type_TTBase0) {}

Type_TTControl GetTTControl() { return Type_TTControl(0); }

void SetTTControl(Type_TTControl) {}

Type_AuxControl GetAuxControl() { return Type_AuxControl(0); }

void SetAuxControl(Type_AuxControl) {}

#endif

} // namespace CP15
} // namespace AM3359
