/* test0047.ScanBit.cpp */ 
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

#include <CCore/inc/ScanBit.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_0047 {

/* class Engine<T> */

template <class T>
class Engine : NoCopy
 {
   T obj;
   bool flag[T::IndexLim];
   Random random;
   
  private:
   
   void fail(unsigned num)
    {
     Printf(Exception,"fail #;",num);
    }
   
   void testMin()
    {
     ulen ind=random.select(0,T::IndexLim-1);
     
     ulen i=obj.findMin(ind);
     
     if( i<T::IndexLim )
       {
        if( i<ind ) fail(1);
        
        if( !obj.test(i) ) fail(2);
        
        if( !flag[i] ) fail(3);
       }
     
     while( (i--)>ind ) 
       {
        if( obj.test(i) ) fail(4);
        
        if( flag[i] ) fail(5);
       }
    }
   
   void testMax()
    {
     ulen ind=random.select(0,T::IndexLim-1);
     
     ulen i=obj.findMax(ind);
     
     if( i<T::IndexLim )
       {
        if( i>ind ) fail(6);
        
        if( !obj.test(i) ) fail(7);
        
        if( !flag[i] ) fail(8);
       }
     else
       {
        i=0;
        
        if( obj.test(i) ) fail(9);
        
        if( flag[i] ) fail(10);
       }
     
     while( (i++)<ind )
       {
        if( obj.test(i) ) fail(9);
        
        if( flag[i] ) fail(10);
       }
    }
   
  public:
   
   Engine() 
    : flag()
    {
    }
   
   void run(ulen cnt)
    {
     for(; cnt ;cnt--)
       {
        ulen ind=random.select(0,T::IndexLim-1);
        
        if( flag[ind] )
          {
           flag[ind]=false;
           
           obj.clear(ind);
          }
        else
          {
           flag[ind]=true;
           
           obj.set(ind);
          }
        
        testMin();
        testMax();
       }
    }
 };
 
} // namespace Private_0047
 
using namespace Private_0047; 
 
/* Testit<47> */ 

template<>
const char *const Testit<47>::Name="Test47 ScanBit";

template<>
bool Testit<47>::Main() 
 { 
  Engine<ScanBit<ScanMSBitAlgo,10> >().run(1000000); 
  
  Engine<ScanBit<ScanLSBitAlgo,10> >().run(1000000);
  
  return true;
 }
 
} // namespace App
 
