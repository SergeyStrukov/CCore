/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-H
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
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
  //Testit<69>().run();
  //Testit<70>().run();
  //Testit<71>().run();
  //Testit<72>().run();
  //Testit<73>().run();
  //Testit<74>().run();
  //Testit<75>().run();
  //Testit<76>().run();
  //Testit<77>().run();
  //Testit<78>().run();
  //Testit<79>().run();
  //Testit<80>().run();
  //Testit<81>().run();
  //Testit<82>().run();
  //Testit<83>().run();
  //Testit<84>().run();
  //Testit<85>().run();
  //Testit<86>().run();
  //Testit<87>().run();
  //Testit<88>().run();
  //Testit<89>().run();
  
  //Testit<100>().run();
  //Testit<101>().run();
  //Testit<102>().run();
  //Testit<103>().run();
  //Testit<104>().run();
  
  //Testit<200>().run();
  
  //Testit<300>().run();
  
  //Testit<400>().run();
  
  //Testit<1001>().run();
  //Testit<1002>().run();
  //Testit<1003>().run();
  //Testit<1004>().run();
  //Testit<1005>().run();
  //Testit<1006>().run();
  //Testit<1007>().run();
  //Testit<1008>().run();
  //Testit<1009>().run();
  //Testit<1010>().run();
  //Testit<1011>().run();
  //Testit<1012>().run();
  //Testit<1013>().run();
  //Testit<1014>().run();
  //Testit<1015>().run();
  //Testit<1016>().run();
  //Testit<1017>().run();
  //Testit<1018>().run();
  //Testit<1019>().run();
  //Testit<1020>().run();
  //Testit<1021>().run();
  //Testit<1022>().run();
  //Testit<1023>().run();
  //Testit<1024>().run();
  //Testit<1025>().run();
  //Testit<1026>().run();
  //Testit<1027>().run();
  //Testit<1028>().run();
  //Testit<1029>().run();
  
  Printf(Con,"\nPeak memory usage #;\n\n",MemPeak());
  
  DetachPacketBufs();
  
  return 0;
 }

 
