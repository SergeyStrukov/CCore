/* test3001.PCI.cpp */ 
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

#include <CCore/inc/dev/DevPCIHost.h>

namespace App {

namespace Private_3001 {


} // namespace Private_3001
 
using namespace Private_3001; 
 
/* Testit<3001> */ 

template<>
const char *const Testit<3001>::Name="Test3001 PCI";

template<>
bool Testit<3001>::Main() 
 { 
  Dev::PCIBus::HostInitExit pci_host;
  
  Printf(Con,"#;\n",pci_host);
 
  return true;
 }
 
} // namespace App
 
