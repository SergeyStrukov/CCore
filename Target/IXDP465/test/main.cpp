/* main.cpp */ 
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

#include <CCore/inc/MemBase.h>
#include <CCore/inc/PacketPool.h>

namespace App {

/* Testit<0> */ 

template<>
const char *const Testit<0>::Name="Test0 empty";
   
template<>
bool Testit<0>::Main() { return false; }
 
} // namespace App
 
/* main() */ 

using namespace App;

int main()
 {
  MemScope mem_scope;
  
  //Testit<0>().run();
  //Testit<1>().run();
  //Testit<2>().run();
  //Testit<3>().run();
  //Testit<4>().run();
  //Testit<5>().run();
  //Testit<6>().run();
  //Testit<7>().run();
  //Testit<8>().run();
  //Testit<9>().run();
  //Testit<10>().run();
  //Testit<11>().run();
  //Testit<12>().run();
  //Testit<13>().run();
  //Testit<14>().run();
  //Testit<15>().run();
  //Testit<16>().run();
  //Testit<17>().run();
  //Testit<18>().run();
  //Testit<19>().run();
  //Testit<20>().run();
  //Testit<21>().run();
  //Testit<22>().run();
  //Testit<23>().run();
  //Testit<24>().run();
  //Testit<25>().run();
  //Testit<26>().run();
  //Testit<27>().run();
  //Testit<28>().run();
  //Testit<29>().run();
  //Testit<30>().run();
  //Testit<31>().run();
  //Testit<32>().run();
  //Testit<33>().run();
  //Testit<34>().run();
  //Testit<35>().run();
  //Testit<36>().run();
  //Testit<37>().run();
  //Testit<38>().run();
  //Testit<39>().run();
  //Testit<40>().run();
  //Testit<41>().run();
  //Testit<42>().run();
  //Testit<43>().run();
  //Testit<44>().run();
  //Testit<45>().run();
  //Testit<46>().run();
  //Testit<47>().run();
  //Testit<48>().run();
  //Testit<49>().run();
  //Testit<50>().run();
  //Testit<51>().run();
  //Testit<52>().run();
  //Testit<53>().run();
  //Testit<54>().run();
  //Testit<55>().run();
  //Testit<56>().run();
  //Testit<57>().run();
  //Testit<58>().run();
  //Testit<59>().run();
  //Testit<60>().run();
  //Testit<61>().run();
  //Testit<62>().run();
  //Testit<63>().run();
  //Testit<64>().run();
  //Testit<65>().run();
  //Testit<66>().run();
  //Testit<67>().run();
  //Testit<68>().run();
  
  //Testit<100>().run();
  //Testit<101>().run();
  //Testit<102>().run();
  //Testit<103>().run();
  //Testit<104>().run();
  
  //Testit<200>().run();
  
  //Testit<300>().run();
  
  //Testit<2001>().run();
  //Testit<2002>().run();
  //Testit<2003>().run();
  //Testit<2004>().run();
  //Testit<2005>().run();
  //Testit<2006>().run();
  //Testit<2007>().run();
  //Testit<2008>().run();
  //Testit<2009>().run();
  //Testit<2010>().run();
  //Testit<2011>().run();
  //Testit<2012>().run();
  //Testit<2013>().run();
  //Testit<2014>().run();
  //Testit<2015>().run();
  //Testit<2016>().run();
  
  //Testit<3001>().run();
  //Testit<3002>().run();
  //Testit<3003>().run();
  //Testit<3004>().run();
  //Testit<3005>().run();
  //Testit<3006>().run();
  //Testit<3007>().run();
  //Testit<3008>().run();
  //Testit<3009>().run();
  //Testit<3010>().run();
  //Testit<3011>().run();
  //Testit<3012>().run();
  //Testit<3013>().run();
  //Testit<3014>().run();
  //Testit<3015>().run();
  //Testit<3016>().run();
  
  Printf(Con,"\nPeak memory usage #;\n\n",MemPeak());  
    
  DetachPacketBufs();
  
  return 0;
 }

 
