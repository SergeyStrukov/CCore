/* test0095.InterfaceHost.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/InterfaceHost.h>

namespace App {

namespace Private_0095 {

struct A
 {
  static const StrLen InterfaceName;
  
  virtual void methodA()=0;
 };

const StrLen A::InterfaceName="A";

struct B
 {
  virtual void methodB()=0;
 };

struct Host : InterfaceHost , A , B
 {
  virtual void methodA() { Printf(Con,"1\n"); }
  
  virtual void methodB() { Printf(Con,"2\n"); }
 };

struct CompositeHost : InterfaceHost , A
 {
  virtual void methodA() { Printf(Con,"3\n"); }
  
  Host inner;
  
  virtual void requestInterface(InterfaceCaster &caster) 
   { 
    auto tn=caster.getTypeNumber();
    
    if( tn.oneOf<A>() ) caster.cast(this);
    
    if( tn.oneOf<B>() ) caster.cast(&inner); 
   }
 };

void test1(InterfaceHost &host)
 {
  if( A *a=host.pickInterface<A>() ) a->methodA();
  
  if( B *b=host.pickInterface<B>() ) b->methodB();
 }

void test2(InterfaceHost &host)
 {
  try
    {
     host.takeInterface<A>("test2()");
    }
  catch(CatchType)
    {
    }
  
  try
    {
     host.takeInterface<B>("test2()");
    }
  catch(CatchType)
    {
    }
  
  ReportException::Clear();
 }

} // namespace Private_0095
 
using namespace Private_0095; 
 
/* Testit<95> */ 

template<>
const char *const Testit<95>::Name="Test95 InterfaceHost";

template<>
bool Testit<95>::Main() 
 {
  Host host1;
  InterfaceHost host2;
  CompositeHost host3;
  
  test1(host1);
  test1(host2);
  test1(host3);
  
  test2(host1);
  test2(host2);
  
  return true;
 }
 
} // namespace App
 
