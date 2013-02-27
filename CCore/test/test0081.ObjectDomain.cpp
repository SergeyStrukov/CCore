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
#include <CCore/inc/MemSpaceHeap.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_0081 {

/* class TestDomain */

class TestDomain : public ObjectDomain
 {
   SpaceHeap heap;
   
  private: 
   
   virtual void * try_alloc(ulen len) { return heap.alloc(len); }
  
   virtual void free(void *mem) { heap.free(mem); }
   
  public:
  
   explicit TestDomain(ulen max_total_mem) : ObjectDomain(max_total_mem),heap(2*max_total_mem) {}
   
   ~TestDomain() { cleanup(); }
 };

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
    
     ExtObjPtr<Test> temp(Domain,count);
   
     subs.append_fill(temp);
    
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
   
   static_assert( Has_keepAlive<Test>::Ret ,"Test : keepAlive is missing");
   
   //static_assert( Has_breakWeak<Test>::Ret ,"Test : breakWeak is missing");
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
  
  for(ulen cnt=1000000; cnt ;cnt--)
    {
     ulen collect_count=0;
    
     while( Domain->getObjectCount()>10000 )
       {
        for(ulen cnt=1000; cnt ;cnt--) ptr->del(random);
        
        Domain->collect();
        
        collect_count++;
       }
     
     if( collect_count>1 ) Printf(Con,"#;\n",collect_count);
     
     if( collect_count ) break_count++;
     
     ptr->add(random);
    }
  
  Printf(Con,"breaks #;\n",break_count);
 }

/* test3() */

void test3()
 {
  ExtObjPtr<Test> ptr(Domain,0);
  Random random;
  
  ulen break_count=0;
  
  for(ulen cnt=1000000; cnt ;cnt--)
    {
     if( Domain->getObjectCount()>=10000 ) 
       {
        ptr->delAll();      
        
        Domain->collect();
        
        break_count++;
       }
     
     ptr->add(random);
    }
  
  Printf(Con,"breaks #;\n",break_count);
 }

/* class Test1 */

class Test1 : NoCopy
 {
   int num;
   
  public:
   
   IntObjPtr<Test1> ptr;
   WeakObjPtr<Test1> weak_ptr;
   IntDelObjPtr<Test1> del_ptr;
   
   explicit Test1(int num_) 
    : num(num_)
    {
     Printf(Con,"Test1(#;)\n",num);
    }
   
   ~Test1()
    {
     Printf(Con,"~Test1(#;)\n",num);
    }
   
   template <class Keeper>
   void keepAlive(Keeper keeper)
    {
     keeper(ptr);
     keeper(del_ptr);
    }
   
   template <class Breaker>
   void breakWeak(Breaker breaker)
    {
     breaker(weak_ptr);
    }
 };

/* test4() */

void collect(int num)
 {
  Printf(Con,"\nbegin collect #;\n",num);
  
  Domain->collect();
  
  Printf(Con,"end collect\n");
 }

void test4()
 {
  ExtObjPtr<Test1> obj1(Domain,1);
  
  obj1->ptr=IntObjPtr<Test1>(Domain,2);
  
  collect(1);
  
  obj1->ptr.nullify();
  
  collect(2);
  
  obj1->ptr=obj1->weak_ptr=WeakObjPtr<Test1>(Domain,3);
  
  collect(3);
  
  obj1->ptr.nullify();
  
  collect(4);
  
  Printf(Con,"weak #;\n\n",!obj1->weak_ptr);
  
  ExtDelObjPtr<Test1> obj2(Domain,4);
  
  obj1->del_ptr=obj2;
  
  Printf(Con,"destroy1 #;\n",obj1->del_ptr.destroy());
  
  Printf(Con,"destroy2 #;\n",obj2.destroy());
  
  Printf(Con,"del #;\n",!obj1->del_ptr);
  
  Printf(Con,"objects = #;\n",Domain->getObjectCount());
  
  collect(5);
  
  Printf(Con,"objects = #;\n",Domain->getObjectCount());
  
  Printf(Con,"\nend test\n\n");
 }

} // namespace Private_0081
 
using namespace Private_0081; 
 
/* Testit<81> */ 

template<>
const char *const Testit<81>::Name="Test81 ObjectDomain";

template<>
bool Testit<81>::Main() 
 {
  TestDomain domain(10_MByte);
  
  Domain=&domain;
  
  //test1();
  //test2();
  //test3();
  test4();
  
  return true;
 }
 
} // namespace App
 
