/* test3006.CPU.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/dev/AM3359.h>

namespace App {

namespace Private_3006 {


} // namespace Private_3006
 
using namespace Private_3006; 
 
/* Testit<3006> */ 

template<>
const char *const Testit<3006>::Name="Test3006 CPU";

template<>
bool Testit<3006>::Main() 
 {
  // CPSR
  
  Printf(Con,"CPSR = #;\n\n",AM3359::CP15::GetCPSR());
  
  // Features
  
  AM3359::CP15::CPUFeatures features;
  
  Printf(Con,"MainID = #;\n\n",features.getMainID());
  
  Printf(Con,"CacheType = #;\n\n",features.getCacheType());
  
  Printf(Con,"TCMType = #;\n\n",features.getTCMType());
  
  Printf(Con,"TLBType = #;\n\n",features.getTLBType());
  
  Printf(Con,"MultiprocessorID = #;\n\n",features.getMultiprocessorID());
  
  Printf(Con,"ProcessorFeature0 = #;\n\n",features.getProcessorFeature0());
  
  Printf(Con,"ProcessorFeature1 = #;\n\n",features.getProcessorFeature1());
  
  Printf(Con,"DebugFeature = #;\n\n",features.getDebugFeature());
  
  Printf(Con,"AuxFeature = #;\n\n",features.getAuxFeature());
  
  Printf(Con,"MemoryFeature0 = #;\n\n",features.getMemoryFeature0());

  // SecureConfig
  
  Printf(Con,"SecureConfig = #;\n\n",AM3359::CP15::GetSecureConfig());
  
  //Printf(Con," = #;\n\n",features.());
  
  return true;
 }
 
} // namespace App
 
