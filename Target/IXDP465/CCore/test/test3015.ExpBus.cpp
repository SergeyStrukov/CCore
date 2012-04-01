/* test3015.ExpBus.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/dev/DevRW.h>

namespace App {

namespace Private_3015 {


} // namespace Private_3015
 
using namespace Private_3015; 
 
/* Testit<3015> */ 

template<>
const char *const Testit<3015>::Name="Test3015 ExpBus";

template<>
bool Testit<3015>::Main() 
 { 
  Dev::RegRW reg(0xC4000000);
  
  Printf(Con,"CNFG0 = #8.16i;\n",reg.get<uint32>(0x20));
  Printf(Con,"CNFG1 = #8.16i;\n",reg.get<uint32>(0x24));
 
  Printf(Con,"CS0 = #8.16i;\n",reg.get<uint32>(0x00));
  Printf(Con,"CS1 = #8.16i;\n",reg.get<uint32>(0x04));
  Printf(Con,"CS2 = #8.16i;\n",reg.get<uint32>(0x08));
  Printf(Con,"CS3 = #8.16i;\n",reg.get<uint32>(0x0C));
  Printf(Con,"CS4 = #8.16i;\n",reg.get<uint32>(0x10));
  Printf(Con,"CS5 = #8.16i;\n",reg.get<uint32>(0x14));
  Printf(Con,"CS6 = #8.16i;\n",reg.get<uint32>(0x18));
  Printf(Con,"CS7 = #8.16i;\n",reg.get<uint32>(0x1C));
  
  Dev::RegRW fpga_reg(0x54100000);
  
  Printf(Con,"FPGA revision = #8.2i;\n",fpga_reg.get<uint8>(2));
  
  for(unsigned i=0; i<16 ;i++)
    {
     fpga_reg.set<uint8>(0,i);
     
     uint8 a=fpga_reg.get<uint8>(0);
     uint8 d=fpga_reg.get<uint8>(1);
     
     if( d!=127 )
       Printf(Con,"#; #; -> #;\n",a,((d&128)?"output":"input"),(d&127));
    }
    
  return true;
 }
 
} // namespace App
 
