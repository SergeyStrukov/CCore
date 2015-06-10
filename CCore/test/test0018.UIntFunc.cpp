/* test0018.UIntFunc.cpp */ 
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

#include <CCore/inc/Random.h>

namespace App {

namespace Private_0018 {

/* functions */

template <class UInt>
void show(UInt value)
 {
  typedef UIntFunc<UInt> Func;
  
  Printf(Con,"\nvalue = #.h;\n",value);
  Printf(Con,"Neg(value) = #.h;\n",Func::Neg(value));
  Printf(Con,"IsNegative(value) = #.h;\n",Func::IsNegative(value));
  Printf(Con,"NotNegative(value) = #.h;\n",Func::NotNegative(value));
  Printf(Con,"IsPositive(value) = #.h;\n",Func::IsPositive(value));
  Printf(Con,"NotPositive(value) = #.h;\n",Func::NotPositive(value));
 }
 
template <class UInt>
void test(const char *name)
 {
  typedef UIntFunc<UInt> Func;
  
  Printf(Con,"#;\n\n",Title(name));
 
  Printf(Con,"MSBit = #.h;\n",+Func::MSBit);
  Printf(Con,"MaxPositive = #.h;\n",+Func::MaxPositive);
  Printf(Con,"MinNegative = #.h;\n",+Func::MinNegative);
  
  show<UInt>(Func::MinNegative);
  show<UInt>(Func::MinNegative+Func::MaxPositive/2);
  show<UInt>(0);
  show<UInt>(Func::MaxPositive/2);
  show<UInt>(Func::MaxPositive);
  
  Printf(Con,"\n#;\n\n",TextDivider());
 }

/* testSqRoot() */

template <class UInt>
void testSqRoot()
 {
  Random random;
  
  ulen count1=0;
  ulen count2=0;
  ulen count3=0;
  
  for(ulen rep=1000000; rep ;rep--)
    { 
     UInt S=random.next_uint<UInt>();
     
     if( !S ) continue;
     
     UInt x=UIntFunc<UInt>::SqRoot(S);
     
     UInt y=S/x;
     UInt z=S%x;
     
     if( y!=x )
       {
        if( y==x-1 )
          {
           if( z==0 ) Printf(Exception,"fail 1");
           
           count2++;
          }
        else if( y==x+1 )
          {
           if( z!=0 ) Printf(Exception,"fail 2");
           
           count3++;
          }
        else
          {
           Printf(Exception,"fail 3");
          }
       }
     else
       {
        count1++;
       }
    }

  for(ulen rep=1000000; rep ;rep--)
    { 
     UInt S=random.next_uint<UInt>();
     UInt t=random.next_uint<UInt>();
     
     if( !S || !t ) continue;
     
     UInt x=UIntFunc<UInt>::SqRoot(S,t);
     
     UInt y=S/x;
     UInt z=S%x;
     
     if( y!=x )
       {
        if( y==x-1 )
          {
           if( z==0 ) Printf(Exception,"fail 1");
           
           count2++;
          }
        else if( y==x+1 )
          {
           if( z!=0 ) Printf(Exception,"fail 2");
           
           count3++;
          }
        else
          {
           Printf(Exception,"fail 3");
          }
       }
     else
       {
        count1++;
       }
    }
  
  Printf(Con,"#; #; #;\n",count1,count2,count3);
  
  Printf(Con,"SqRoot ok\n");
 }

} // namespace Private_0018
 
using namespace Private_0018; 
 
/* Testit<18> */ 

template<>
const char *const Testit<18>::Name="Test18 UIntFunc";

template<>
bool Testit<18>::Main() 
 { 
  test<unsigned short>("unsigned short");
  test<unsigned>("unsigned");
  test<unsigned long long>("unsigned long long");
  
  testSqRoot<unsigned>();
  testSqRoot<uint32>();
 
  return true;
 }
 
} // namespace App
 
