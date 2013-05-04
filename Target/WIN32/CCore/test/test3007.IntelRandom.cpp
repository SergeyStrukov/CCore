/* test3007.IntelRandom.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/WIN32 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/crypton/IntelCPUID.h>
#include <CCore/inc/crypton/IntelRandom.h>

namespace App {

namespace Private_3007 {


} // namespace Private_3007
 
using namespace Private_3007; 
 
/* Testit<3007> */ 

template<>
const char *const Testit<3007>::Name="Test3007 IntelRandom";

template<>
bool Testit<3007>::Main() 
 {
  Crypton::IntelCPUID1 cpuid;
  
  Printf(Con,"EAX=#.h; EBX=#.h; ECX=#.h; EDX=#.h;\n",cpuid.EAX,cpuid.EBX,cpuid.ECX,cpuid.EDX);
  
  Crypton::IntelRandom random;
  
  for(unsigned cnt=10; cnt ;cnt--) Printf(Con,"#.h;\n",random.next());
  
  return true;
 }
 
} // namespace App
 
