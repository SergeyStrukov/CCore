/* test0036.SaveLoad.cpp */ 
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

#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/PrintSet.h>

namespace App {

namespace Private_0036 {

/* struct Fixed */

struct Fixed
 {
  uint8  a;
  uint16 b;
  uint32 c;
  uint64 d;
  
  enum { SaveLoadLen = SaveLenCounter<uint8,uint16,uint32,uint64>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(a,b,c,d);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(a,b,c,d);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"{a=#;,b=#;,c=#;,d=#;}",a,b,c,d);
   }
 };

/* test1() */
 
void test1()
 {
  Fixed f{1,2,3,4};
  
  Printf(Con,"len = #;\n",SaveLen(f).value);
  
  uint8 buf[100];
  
  BufPutDev putdev(buf);
  
  putdev(f,f,f);
  
  Fixed f1;
  
  BufGetDev getdev(buf);
  
  getdev(f1);
  
  Printf(Con,"#;\n",f1);
 
  getdev(f1);
  
  Printf(Con,"#;\n",f1);
  
  getdev(f1);
  
  Printf(Con,"#;\n",f1);
  
  RangeGetDev rget(Range_const(buf));
  
  Fixed f2[3];
  
  rget(f2[0],f2[1],f2[2]);
  
  Printf(Con,"#; #; #;\n",f2[0],f2[1],f2[2]);
 } 

/* struct Variable */
 
struct Variable
 {
  uint16 len;
  uint8 buf[10];
  
  Variable()
   {
    len=0;
   }
   
  Variable(std::initializer_list<int> il)
   {
    len=il.size();
    
    for(ulen i=0; i<len ;i++) buf[i]=il.begin()[i];
   }
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(len);
    
    dev.put(buf,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(len);
    
    dev.get(buf,len);
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#;",PrintSet(Range(buf,len)));
   }
 };
 
/* test2() */

void test2()
 {
  Variable v{1,2,3};
  
  Printf(Con,"len = #;\n",SaveLen(v).value);
  
  uint8 buf[100];
  
  BufPutDev putdev(buf);
  
  putdev(v,v,v);
  
  Variable v1;
  
  BufGetDev getdev(buf);
  
  getdev(v1);
  
  Printf(Con,"#;\n",v1);
 
  getdev(v1);
  
  Printf(Con,"#;\n",v1);
  
  getdev(v1);
  
  Printf(Con,"#;\n",v1);
  
  RangeGetDev rget(Range_const(buf));
  
  Variable v2[3];
  
  LoadRange(v2,3,rget);
  
  Printf(Con,"#; #; #;\n",v2[0],v2[1],v2[2]);
 } 
 
} // namespace Private_0036
 
using namespace Private_0036; 
 
/* Testit<36> */ 

template<>
const char *const Testit<36>::Name="Test36 SaveLoad";

template<>
bool Testit<36>::Main() 
 { 
  test1();
  test2();
  
  return true;
 }
 
} // namespace App
 
