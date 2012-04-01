/* test0013.Fifo.cpp */ 
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

#include <CCore/inc/Fifo.h>
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/MemBase.h>

namespace App {

namespace Private_0013 {

/* class TestFifo */

class TestFifo
 {
   FifoBuf<int,10> fifo;
   
  public: 
  
   TestFifo() {}
   
   ulen getCount() const { return fifo.getCount(); }
   
   bool put(int value);
   
   bool get(int &ret);
 };
 
bool TestFifo::put(int value) 
 {
  return fifo.put(value);
 }
   
bool TestFifo::get(int &ret)
 {
  return fifo.get(ret);
 }

/* struct Int */
 
struct Int : MemBase_nocopy
 {
  int value;
  
  explicit Int(int value_=0) : value(value_) {}
  
  operator int() const { return value; }
 }; 
 
/* class TestFifo2 */

class TestFifo2
 {
   FifoBuf<OwnPtr<Int>,10> fifo;
   
  public: 
  
   TestFifo2() {}
   
   ulen getCount() const { return fifo.getCount(); }
   
   bool put(int value);
   
   bool get(int &ret);
 };
 
bool TestFifo2::put(int value)
 {
  OwnPtr<Int> obj(new Int(value));
 
  return fifo.put_swap(obj);
 }
   
bool TestFifo2::get(int &ret)
 {
  OwnPtr<Int> obj;
  
  if( fifo.get_swap(obj) )
    {
     ret=*obj;
    
     return true;
    }
    
  return false;  
 }

/* functions */
 
template <class T> 
void test1()
 {
  Random random;
  T fifo;
  int next=1;
  
  for(unsigned cnt=100; cnt ;cnt--)
    {
     Printf(Con,"[#;]",fifo.getCount());
     
     switch( random.select(2) )
       {
        case 0 : 
         {
          if( fifo.put(next) ) next++;
         }
        break;
        
        case 1 : 
         {
          int ret;
          
          if( fifo.get(ret) ) Printf(Con," #;",ret);
         }
        break;
       }
       
     Putch(Con,'\n');  
    }
 }
 
template <class T> 
void test2()
 {
  Random random;
  T fifo;
  int put_next=1;
  int get_next=1;
  
  for(unsigned cnt=1000000; cnt ;cnt--)
    {
     switch( random.select(2) )
       {
        case 0 : 
         {
          if( fifo.put(put_next) ) put_next++;
         }
        break;
        
        case 1 : 
         {
          int ret;
          
          if( fifo.get(ret) )
            {
             if( ret!=get_next )
               {
                Printf(Exception,"Broken sequence");
               } 
               
             get_next++;  
            }
         }
        break;
       }
    }
 } 
 
} // namespace Private_0013
 
using namespace Private_0013; 
 
/* Testit<13> */ 

template<>
const char *const Testit<13>::Name="Test13 Fifo";

template<>
bool Testit<13>::Main() 
 { 
  test1<TestFifo>();
  test2<TestFifo>();
  
  test1<TestFifo2>();
  test2<TestFifo2>();
 
  return true;
 }
 
} // namespace App
 
