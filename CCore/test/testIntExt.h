/* testIntExt.h */
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_test_testIntExt_h
#define CCore_test_testIntExt_h

#include <CCore/test/testIntBase.h>

namespace App {

/* classes */

template <class Algo,class Ext> class TestExtAlgo;

/* class TestExtAlgo<Algo,Ext> */

template <class Algo,class Ext>
class TestExtAlgo : TestIntBase
 {
   typedef typename Algo::Unit Unit;
   
   static const unsigned UnitBits = Algo::UnitBits ;
   
  private: 
   
   Unit a[10];
   Unit b[10];
   Unit c[10];
   Unit d[10];
   
  private: 
   
   static void URShift(Unit *a,ulen na,unsigned shift_)
    {
     ulen delta=shift_/UnitBits;
     unsigned shift=shift_%UnitBits;
 
     if( shift )
       {
        Algo::UShiftDown(a,na-delta,delta,shift);
        Algo::Null(a+(na-delta),delta);
       }
     else
       {
        Algo::MoveDown(a,na-delta,delta);
        Algo::Null(a+(na-delta),delta);
       }
    }
   
  private: 
   
   void test1()
    {
     fill(Range(a));
     
     Range(a).copyTo(d);
     
     Ext::UNeg3(a);
     Algo::UNeg(d,3);
     
     if( !Range(a).equal(d) ) Error("UNeg3");
    }
   
   void test2()
    {
     fill(Range(a));
     
     Range(a).copyTo(d);
     
     Ext::UNeg4(a);
     Algo::UNeg(d,4);
     
     if( !Range(a).equal(d) ) Error("UNeg4");
    }
   
   void test3()
    {
     fill(Range(a));
     fill(Range(b));
     
     Range(a).copyTo(d);
 
     Ext::UAdd3(a,b);
     Algo::UAdd(d,b,3);
     
     if( !Range(a).equal(d) ) Error("UAdd3");
    }
   
   void test4()
    {
     fill(Range(a));
     fill(Range(b));
     
     Range(a).copyTo(d);
 
     Ext::UAdd4(a,b);
     Algo::UAdd(d,b,4);
     
     if( !Range(a).equal(d) ) Error("UAdd4");
    }
   
   void test5()
    {
     fill(Range(a));
     fill(Range(b));
     
     Range(a).copyTo(d);
 
     Ext::USub3(a,b);
     Algo::USub(d,b,3);
     
     if( !Range(a).equal(d) ) Error("USub3");
    }
   
   void test6()
    {
     fill(Range(a));
     fill(Range(b));
     
     Range(a).copyTo(d);
 
     Ext::USub4(a,b);
     Algo::USub(d,b,4);
     
     if( !Range(a).equal(d) ) Error("USub4");
    }
   
   void test7()
    {
     fill(Range(a));
     
     unsigned shift=select(1,UnitBits-1);
     
     Range(a).copyTo(d);
     
     Ext::URShift3(a,shift);
     URShift(d,3,shift);
     
     if( !Range(a).equal(d) ) Error("URShift3");
    }
   
   void test8()
    {
     fill(Range(a));
     
     unsigned shift=select(1,2*UnitBits-1);
     
     Range(a).copyTo(d);
     
     Ext::URShift4(a,shift);
     URShift(d,4,shift);
     
     if( !Range(a).equal(d) ) Error("URShift4");
    }
   
   void test9()
    {
     fill(Range(a));
     fill(Range(b));
     fill(Range(c));
     
     Range(c).copyTo(d);
     
     Ext::UMulLo3(c,a,b);
     Algo::UMulLo(d,3,a,3,b,3);
     
     if( !Range(c).equal(d) ) Error("UMulLo3");
    }
   
   void test10()
    {
     fill(Range(a));
     fill(Range(b));
     fill(Range(c));
     
     Range(c).copyTo(d);
     
     Ext::UMulLo4(c,a,b);
     Algo::UMulLo(d,4,a,4,b,4);
     
     if( !Range(c).equal(d) ) Error("UMulLo4");
    }
   
   void test11()
    {
     fill(Range(a));
     fill(Range(c));
     
     Range(c).copyTo(d);
     
     Ext::USqLo3(c,a);
     Algo::UMulLo(d,3,a,3,a,3);
     
     if( !Range(c).equal(d) ) Error("USqLo3");
    }
   
   void test12()
    {
     fill(Range(a));
     fill(Range(c));
     
     Range(c).copyTo(d);
     
     Ext::USqLo4(c,a);
     Algo::UMulLo(d,4,a,4,a,4);
     
     if( !Range(c).equal(d) ) Error("USqLo4");
    }
   
  public: 
   
   TestExtAlgo() {}
   
   void run(ulen rep)
    {
     for(; rep ;rep--)
       {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
        test8();
        test9();
        test10();
        test11();
        test12();
       }
    }
 };

} // namespace App

#endif


