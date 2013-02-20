/* test0081.ObjectDomain.cpp */ 
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

#include <CCore/inc/ObjectDomain.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_0081 {

/* global Domain */

static ObjectDomain * Domain=0; 

/* class Test */

class Test
 {
   DynArray<IntObjPtr<Test> > subs;
  
  public:
  
   explicit Test(ulen count)
    : subs(count) 
    {
    }
   
   ~Test()
    {
    }
   
   void add(Random &random)
    {
     ulen count=random.select(10);
    
     IntObjPtr<Test> temp(Domain,count);
   
     subs.append_copy(temp);
    
     ulen len=subs.getLen();
    
     for(IntObjPtr<Test> &obj : temp->subs ) obj=subs[random.select(len)];
    }
   
   void del(Random &random)
    {
     if( ulen len=subs.getLen() )
       {
        ulen index=random.select(len);
        
        IntObjPtr<Test> temp=subs[index];
        
        if( +temp )
          {
           temp->subs.shrink_one();
          }
        
        if( index<len-1 )
          {
           Swap(subs[index],subs[len-1]);
          }
        
        subs.shrink_one();
       }
    }
   
   void delAll()
    {
     subs.erase();
    }
   
   template <class Keeper>
   void keepAlive(Keeper keeper)
    {
     subs.apply(keeper);
    }
 };

/* test1() */

void test1()
 {
  ExtObjPtr<Test> ptr1(Domain,10);
  
  ExtObjPtr<Test> ptr2;
  
  ptr2=ptr1;
 }

/* test2() */

void test2()
 {
  ExtObjPtr<Test> ptr(Domain,0);
  Random random;
  
  ulen break_count=0;
  MSecTimer::ValueType max_time=0;
  
  for(ulen cnt=1000000; cnt ;cnt--)
    {
     ulen collect_count=0;
    
     while( Domain->getObjectCount()>=10000 )
       {
        for(ulen cnt=1000; cnt ;cnt--) ptr->del(random);
        
        MSecTimer timer;
       
        Domain->collect();
        
        Replace_max(max_time,timer.get());
        
        collect_count++;
       }
     
     if( collect_count>1 ) Printf(Con,"#;\n",collect_count);
     
     if( collect_count ) break_count++;
     
     ptr->add(random);
    }
  
  Printf(Con,"time = #; msec\n",max_time);
  Printf(Con,"breaks #;\n",break_count);
 }

/* test3() */

void test3()
 {
  ExtObjPtr<Test> ptr(Domain,0);
  Random random;
  
  ulen break_count=0;
  MSecTimer::ValueType max_time=0;
  
  for(ulen cnt=1000000; cnt ;cnt--)
    {
     if( Domain->getObjectCount()>=10000 ) 
       {
        ptr->delAll();      
        
        MSecTimer timer;
       
        Domain->collect();
        
        Replace_max(max_time,timer.get());
        
        break_count++;
       }
     
     ptr->add(random);
    }
  
  Printf(Con,"time = #; msec\n",max_time);
  Printf(Con,"breaks #;\n",break_count);
 }

} // namespace Private_0081
 
using namespace Private_0081; 
 
/* Testit<81> */ 

template<>
const char *const Testit<81>::Name="Test81 ObjectDomain";

template<>
bool Testit<81>::Main() 
 {
  ObjectDomain domain(10_MByte);
  
  Domain=&domain;
  
  //test1();
  test2();
  //test3();
  
  return true;
 }
 
} // namespace App
 
