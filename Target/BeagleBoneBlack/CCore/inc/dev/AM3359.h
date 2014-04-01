/* AM3359.h */
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

#ifndef CCore_inc_dev_AM3359_h
#define CCore_inc_dev_AM3359_h

#include <CCore/inc/Gadget.h>

namespace AM3359 {

/* using */

using CCore::uint8;
using CCore::uint16;
using CCore::uint32;

namespace CP15 {

/* AM3359.CP15.desc -> AM3359.CP15.gen.h */

#include <CCore/inc/dev/AM3359.CP15.gen.h>

/* functions */

Type_CPSR GetCPSR();

Type_SecureConfig GetSecureConfig();

void SetSecureConfig(Type_SecureConfig);

Type_DataFaultStatus GetDataFaultStatus();

Type_InstructionFaultStatus GetInstructionFaultStatus();

Type_DataFaultAddress GetDataFaultAddress();

Type_InstructionFaultAddress GetInstructionFaultAddress();

Type_Control GetControl();

void SetControl(Type_Control);

Type_CacheSizeID GetCacheSizeID();

void SetCacheSizeSel(Type_CacheSizeSel);

Type_DomainAccessControl GetDomainAccessControl();

void SetDomainAccessControl(Type_DomainAccessControl);

Type_TTBase0 GetTTBase0();

void SetTTBase0(Type_TTBase0);

Type_TTControl GetTTControl();

void SetTTControl(Type_TTControl);

Type_AuxControl GetAuxControl();

void SetAuxControl(Type_AuxControl);

/* classes */

class CPUFeatures;

/* class CPUFeatures */

class CPUFeatures
 {
   uint32 regs[21];
  
  public:
   
   CPUFeatures();
   
   Type_MainID getMainID() const { return Type_MainID(regs[0]); }

   Type_CacheType getCacheType() const { return Type_CacheType(regs[1]); }

   Type_TCMType getTCMType() const { return Type_TCMType(regs[2]); }
   
   Type_TLBType getTLBType() const { return Type_TLBType(regs[3]); }
   
   Type_MultiprocessorID getMultiprocessorID() const { return Type_MultiprocessorID(regs[4]); }
   
   Type_ProcessorFeature0 getProcessorFeature0() const { return Type_ProcessorFeature0(regs[5]); }
   
   Type_ProcessorFeature1 getProcessorFeature1() const { return Type_ProcessorFeature1(regs[6]); }

   Type_DebugFeature getDebugFeature() const { return Type_DebugFeature(regs[7]); }
   
   Type_AuxFeature getAuxFeature() const { return Type_AuxFeature(regs[8]); }
   
   Type_MemoryFeature0 getMemoryFeature0() const { return Type_MemoryFeature0(regs[9]); }
   
   Type_MemoryFeature1 getMemoryFeature1() const { return Type_MemoryFeature1(regs[10]); }
   
   Type_MemoryFeature2 getMemoryFeature2() const { return Type_MemoryFeature2(regs[11]); }
   
   Type_MemoryFeature3 getMemoryFeature3() const { return Type_MemoryFeature3(regs[12]); }
   
   Type_CacheLevelID getCacheLevelID() const { return Type_CacheLevelID(regs[13]); }
 };

} // namespace CP15

} // namespace AM3359

#endif


