/* test0026.Packet.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/PacketPool.h>

namespace App {

namespace Private_0026 {

/* struct Ext1 */

struct Ext1
 {
  int a;
  
  explicit Ext1(int a_) : a(a_) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;)",a);
   }
 };
 
/* struct Ext2 */

struct Ext2
 {
  int a;
  int b;
  
  Ext2(int a_,int b_) : a(a_),b(b_) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;)",a,b);
   }
 };

/* struct Ext3 */
 
struct Ext3
 {
  int a;
  int b;
  int c;
  
  Ext3(int a_,int b_,int c_) : a(a_),b(b_),c(c_) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;,#;)",a,b,c);
   }
 };
 
} // namespace Private_0026
 
using namespace Private_0026; 
 
/* Testit<26> */ 

template<>
const char *const Testit<26>::Name="Test26 Packet";

template<>
bool Testit<26>::Main() 
 { 
  Packet<uint8> p1=AllocPacket<uint8>();
  Packet<uint8,Ext1> p2=p1.pushExt<Ext1>(1);
  Packet<uint8,Ext1,Ext2> p3=p2.pushExt<Ext2>(2,3);
  Packet<uint8,Ext1,Ext2,Ext3> p4=p3.pushExt<Ext3>(4,5,6);
  
  Printf(Con,"#;\n",*p4.getExt());
  Printf(Con,"#;\n",*p4.getDeepExt<1>());
  Printf(Con,"#;\n",*p4.getDeepExt<2>());
  Printf(Con,"#;\n",*p4.getDeepExt<3>());
  
  auto p5=p4.popExt();
  
  Printf(Con,"#;\n",*p5.getExt());
  
  auto p6=p5.popExt();
  
  Printf(Con,"#;\n",*p6.getExt());
  
  auto p7=p6.popExt();
  
  p7.complete();
 
  return true;
 }
 
} // namespace App
 
