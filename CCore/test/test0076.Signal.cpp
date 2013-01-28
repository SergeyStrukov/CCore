/* test0076.Signal.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Signal.h>

namespace App {

namespace Private_0076 {

/* struct Test */

struct Test
 {
  int num;
  
  explicit Test(int num_) : num(num_),connector(this,&Test::test) {}
  
  virtual void test(int x)
   {
    Printf(Con,"Test(#;).test(#;)\n",num,x);
    
    if( x==num ) connector.disconnect();
   }
  
  SignalConnector<Test,int> connector;
 };

/* struct Test2 */

struct Test2 : Test
 {
  Test *obj;
  
  explicit Test2(int num,Test *obj_) : Test(num),obj(obj_) {}
  
  void test(int x) override
   {
    Printf(Con,"Test2(#;).test(#;)\n",num,x);
    
    if( x==obj->num ) obj->connector.disconnect();
   }
 };

/* test1() */

void test1()
 {
  Signal<int> signal;
  
  Test test1(1);
  
  {
   Test test2(2);
  
   test1.connector.connect(signal);
  
   signal.assert(100);
  
   test2.connector.connect(signal);
  
   signal.assert(200);
   
   {
    Test2 test3(3,&test2);
    
    test3.connector.connect(signal);
    
    signal.assert(2);
    signal.assert(2);
   }
  } 
  
  signal.assert(300);
 }

/* struct TestIf */

struct TestIf
 {
  virtual void test(int x)=0;
 };

/* struct Test3 */

struct Test3 : TestIf
 {
  int num;
  
  explicit Test3(int num_) : num(num_),connector(this) {}
  
  void test(int x) override
   {
    Printf(Con,"Test3(#;).test(#;)\n",num,x);
   }
  
  SignalInterfaceConnector<TestIf> connector;
 };

/* test2() */

void test2()
 {
  SignalInterface<TestIf> signal;
  
  Test3 test1(1);
  
  {
   Test3 test2(2);
  
   test1.connector.connect(signal);
  
   signal.assert( [] (TestIf &obj) { obj.test(100); } );
  
   test2.connector.connect(signal);
  
   signal.assert( [] (TestIf &obj) { obj.test(200); } );
  } 
  
  signal.assert( [] (TestIf &obj) { obj.test(300); } );
 }

} // namespace Private_0076
 
using namespace Private_0076; 
 
/* Testit<76> */ 

template<>
const char *const Testit<76>::Name="Test76 Signal";

template<>
bool Testit<76>::Main() 
 {
  test1();
  test2();
  
  return true;
 }
 
} // namespace App
 
