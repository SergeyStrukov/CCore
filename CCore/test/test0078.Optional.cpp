/* test0078.Optional.cpp */ 
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

#include <CCore/inc/Optional.h>
#include <CCore/inc/Signal.h>

namespace App {

namespace Private_0078 {

/* class Test */

class Test : NoCopy
 {
   Optional optional;
   
  public:
  
   Test() : optional(100) {}
   
   ~Test() {}
   
   // members
   
   int * try_member0() { return optional.try_take<0,int>(); }
   
   int * member0() { return optional.take<0,int>(); }
   
   int * try_member20() { return optional.try_take<20,int>(); }
   
   int * member20() { return optional.take<20,int>(); }
   
   int * try_member100() { return optional.try_take<100,int>(); }
   
   int * member100() { return optional.take<100,int>(); }
 };

/* class TestSignal */

class TestSignal : NoCopy
 {
   Optional optional;
  
  public:
   
   TestSignal() : optional(100) {}
  
   ~TestSignal() {}
   
   // assert signals 
   
   void assert_signal0(int a) 
    {  
     if( auto *s=optional.try_take<0,Signal<int> >() ) s->assert(a);
    }
   
   void assert_signal20(int a,int b)
    {
     if( auto *s=optional.try_take<20,Signal<int,int> >() ) s->assert(a,b);
    }
   
   void assert_signal100(int a,int b,int c)
    {
     if( auto *s=optional.try_take<100,Signal<int,int,int> >() ) s->assert(a,b,c);
    }
   
   // connect signals
   
   Signal<int> & get_signal0() { return *optional.take<0,Signal<int> >(); }
   
   Signal<int,int> & get_signal20() { return *optional.take<20,Signal<int,int> >(); }
   
   Signal<int,int,int> & get_signal100() { return *optional.take<100,Signal<int,int,int> >(); }
 };

/* class TestSignalConnect */

class TestSignalConnect : NoCopy
 {
   int num;
   
  private:
  
   void method0(int a)
    {
     Printf(Con,"TestSignalConnect(#;).method0(#;)\n",num,a);
    }
   
   void method100(int a,int b,int c)
    {
     Printf(Con,"TestSignalConnect(#;).method100(#;,#;,#;)\n",num,a,b,c);
    }
  
   SignalConnector<TestSignalConnect,int> connector0;
   SignalConnector<TestSignalConnect,int,int,int> connector100;
  
  public:
  
   TestSignalConnect() 
    : num(1055),
      connector0(this,&TestSignalConnect::method0),
      connector100(this,&TestSignalConnect::method100)
    {
    }
   
   ~TestSignalConnect() 
    {
    }
   
   void connect(TestSignal &test)
    {
     connector0.connect(test.get_signal0());
     connector100.connect(test.get_signal100());
    }
 };

/* test1() */

void test1()
 {
  Test test;
 
  Printf(Con,"member0 = #;\n",*test.member0());
  Printf(Con,"member20 = #;\n",*test.member20());
  Printf(Con,"member100 = #;\n",*test.member100());
 
  *test.try_member0()=100;
  *test.try_member20()=200;
  *test.try_member100()=300;
 
  Printf(Con,"member0 = #;\n",*test.member0());
  Printf(Con,"member20 = #;\n",*test.member20());
  Printf(Con,"member100 = #;\n",*test.member100());
 }

/* test2() */

void test2()
 {
  TestSignal test;
  
  test.assert_signal0(1);
  test.assert_signal20(1,2);
  test.assert_signal100(1,2,3);

  {
   TestSignalConnect test_connect;
   
   test_connect.connect(test);
   
   test.assert_signal0(1);
   test.assert_signal20(1,2);
   test.assert_signal100(1,2,3);
  } 
  
  test.assert_signal0(1);
  test.assert_signal20(1,2);
  test.assert_signal100(1,2,3);
 }

} // namespace Private_0078
 
using namespace Private_0078; 
 
/* Testit<78> */ 

template<>
const char *const Testit<78>::Name="Test78 Optional";

template<>
bool Testit<78>::Main() 
 {
  //test1();
  test2();
  
  return true;
 }
 
} // namespace App
 
