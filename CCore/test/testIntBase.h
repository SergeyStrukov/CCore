/* testIntBase.h */
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

#ifndef CCore_test_testIntBase_h
#define CCore_test_testIntBase_h

#include <CCore/inc/Random.h>

namespace App {

/* using */ 

using namespace CCore;

/* classes */ 

class TestIntBase;

/* class TestIntBase */

class TestIntBase : NoCopy
 {
   Random gen;
  
  public: 
   
   TestIntBase() {}
   
   TestIntBase & getBase() { return *this; }
   
   unsigned select(unsigned a,unsigned b) { return gen.select(a,b); }
   
   template <class Unit>
   void fill_unit(Unit &ret)
    {
     const unsigned UnitBits = Meta::UIntBits<Unit>::Ret ;
     
     Unit a=gen.next_uint<Unit>();
     
     switch( gen.select(5) )
       {
        case 0 :
         {
          Unit mask = Unit(-1) << select(0,UnitBits-1) ;
          
          BitClear(a,mask);
         }
        break;
        
        case 1 :
         {
          Unit mask = Unit(-1) << select(0,UnitBits-1) ;

          BitSet(a,mask);
         }
        break;
        
        case 2 :
         {
          Unit mask = Unit(-1) >> select(0,UnitBits-1) ;
          
          BitClear(a,mask);
         }
        break;
        
        case 3 :
         {
          Unit mask = Unit(-1) >> select(0,UnitBits-1) ;

          BitSet(a,mask);
         }
        break;
       }
     
     ret=a; 
    }
   
   template <class Unit>
   void fill_masked(PtrLen<Unit> r)
    {
     for(; +r ;++r) fill_unit(*r);
    }
   
   template <class Unit>
   void fill(PtrLen<Unit> r)
    {
     if( gen.select(2) )
       fill_masked(r);
     else
       gen.fill(r);
    }
   
   static void Error(const char *msg);
 };

} // namespace App

#endif



