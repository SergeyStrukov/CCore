/* test0079.MultiSignal.cpp */ 
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

#include <CCore/inc/MultiSignal.h>

namespace App {

namespace Private_0079 {

/* class Test */

class Test : NoCopy
 {
   DeferMultiSignal msig;
   
  public:
   
   Test() : msig(100) {}
   
   ~Test() {}
   
   // signals
   
   Signal<int> & take_signal1() { return msig.take<10,int>(); }
   
   Signal<int,int> & take_signal2() { return msig.take<20,int,int>(); }
   
   Signal<int,int,int> & take_signal3() { return msig.take<30,int,int,int>(); }
   
   // assert
   
   void assert_signal1(int a) { msig.assert<10,int>(a); }
   
   void assert_signal2(int a,int b) { msig.assert<20,int,int>(a,b); }
   
   void assert_signal3(int a,int b,int c) { msig.assert<30,int,int,int>(a,b,c); }
   
   // post
   
   void post_signal1(int a) { msig.post<10,int>(a); }
   
   void post_signal2(int a,int b) { msig.post<20,int,int>(a,b); }
   
   void post_signal3(int a,int b,int c) { msig.post<30,int,int,int>(a,b,c); }
   
   // post_first
   
   void post_first_signal1(int a) { msig.post_first<10,int>(a); }
   
   void post_first_signal2(int a,int b) { msig.post_first<20,int,int>(a,b); }
   
   void post_first_signal3(int a,int b,int c) { msig.post_first<30,int,int,int>(a,b,c); }
 };

/* class TestConnect */

class TestConnect : NoCopy
 {
   int num;
   
  private:
  
   void method1(int a)
    {
     Printf(Con,"TestConnect(#;).method1(#;)\n",num,a);
    }
   
   void method3(int a,int b,int c)
    {
     Printf(Con,"TestConnect(#;).method3(#;,#;,#;)\n",num,a,b,c);
     
     if( c==666 ) DeferCallQueue::Stop();
    }
  
   SignalConnector<TestConnect,int> connector1;
   SignalConnector<TestConnect,int,int,int> connector3;
  
  public:
  
   TestConnect() 
    : num(3044),
      connector1(this,&TestConnect::method1),
      connector3(this,&TestConnect::method3)
    {
    }
   
   ~TestConnect() 
    {
    }
   
   void connect(Test &test)
    {
     connector1.connect(test.take_signal1());
     connector3.connect(test.take_signal3());
    }
 };

/* class Queue */

class Queue : public DeferCallQueue
 {
   Test *test;
  
  public:
  
   Queue() 
    {
     activate();
    }
   
   ~Queue() 
    {
     deactivate();
    }
   
   void set(Test *test_) { test=test_; }
   
   void forward(TimeScope) override
    {
     test->post_signal1(1);
     test->post_signal2(1,2);
     test->post_signal3(1,2,3);
     
     test->post_first_signal1(-1);
     test->post_first_signal2(-1,2);
     test->post_first_signal3(-1,2,3);
     
     test->post_signal3(1,2,666);
    }
 };

} // namespace Private_0079
 
using namespace Private_0079; 
 
/* Testit<79> */ 

template<>
const char *const Testit<79>::Name="Test79 MultiSignal";

template<>
bool Testit<79>::Main() 
 {
  Queue queue;
  
  Test test;
  TestConnect test_connect;
  
  test_connect.connect(test);
  
  test.assert_signal1(0);
  test.assert_signal2(0,2);
  test.assert_signal3(0,2,3);
  
  queue.set(&test);
  
  Queue::Loop();
  
  return true;
 }
 
} // namespace App
 
