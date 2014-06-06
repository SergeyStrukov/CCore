/* test0090.DHExp.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/crypton/DHExp.h>

#include <CCore/inc/math/Integer.h>
#include <CCore/inc/math/IntegerFastAlgo.h>
#include <CCore/inc/math/IntegerOctetBuilder.h>
#include <CCore/inc/math/NoPrimeTest.h>

namespace App {

namespace Private_0090 {

/* types */

using Int = Math::Integer<Math::IntegerFastAlgo> ;

using Builder = Math::IntegerOctetBuilder<Int> ;

/* class DBuilder */

class DBuilder
 {
   ulen n;
   
  public:
  
   explicit DBuilder(ulen n_) : n(n_) {}
   
   ulen getLen() const { return LenAdd(n,1); }
   
   PtrLen<Int::Unit> operator () (Place<void> place) const
    {
     Int::Unit *base=place;
     
     Range(base,n).set_null();
     
     base[n]=1;
     
     return Range(base,n+1);
    }
 };

/* PrintInt() */

template <class P>
void PrintInt(P &out,Int a)
 {
  Printf(out," {\n");
  
  ulen ind=0;
  
  for(Int::Unit d : a.getBody() )
    {
     for(unsigned off=0; off<Int::UnitBits ;off+=8)
       {
        uint8 b=uint8(d>>off);
        
        if( (ind&15)==0 ) 
          {
           if( ind )
             {
              Putobj(out,",\n  ");
             }
           else
             {
              Putobj(out,"  ");
             }
          }
        else
          {
           Putobj(out,", ");
          }
          
        Printf(out,"#4.xi;",b);
        
        ind++;
       }
    }
  
  Printf(out,"\n };\n\n");
 }

/* test1() */

template <class DHMod>
void test1(StrLen title)
 {
  Printf(Con,"#;\n\n",Title(title));
  
  Int P(DoBuild,Builder(Range(DHMod::Mod)));
  Int Q=P>>1;

  {
   Math::NoPrimeTest<Int>::RandomTest test(P); 
   
   if( test(100) ) Printf(Con,"P is probably prime\n"); else Printf(Con,"P is not prime\n");
  }
  
  {
   Math::NoPrimeTest<Int>::RandomTest test(Q);
   
   if( test(100) ) Printf(Con,"Q is probably prime\n"); else Printf(Con,"Q is not prime\n");
  }
  
  Printf(Con,"\n");
 }

/* test2() */

struct XY
 {
  Int x;
  Int y;
  
  XY(Int a,Int b)
   {
    if( a>b )
      {
       auto divmod=a.divmod(b);
       
       if( !divmod.mod )
         {
          x=1;
          y=divmod.div-1;
         }
       else
         {
          XY next(divmod.mod,b);
         
          x=next.x;
          y=next.y+divmod.div*next.x;
         }
      }
    else
      {
       auto divmod=b.divmod(a);
       
       if( !divmod.mod )
         {
          x=divmod.div+1;
          y=1;
         }
       else
         {
          XY next(a,divmod.mod);
         
          x=next.x+divmod.div*next.y;
          y=next.y;
         }
      }
    
   }
  
  XY(Int a,Int b,Int &d)
   : XY(a,b)
   {
    d=a*x-b*y;
   }
 };

template <class DHMod,class P>
void test2(P &out,StrLen title)
 {
  Printf(out,"#;\n\n",Title(title));
  
  Int M(DoBuild,Builder(Range(DHMod::Mod)));
  Int D(DoBuild,DBuilder(M.getBody().len-1));
  
  Int d;
  
  XY xy(M,D,d);
  
  Printf(Con,"d = #;\n",d);
  
  Int K=xy.x%D;
  
  PrintInt(out,M);
  PrintInt(out,D);
  PrintInt(out,K);
  
  Int L=((D-M)*D)/M;
  
  PrintInt(out,L);
 }

/* test3() */

template <class DHMod>
void test3(StrLen title)
 {
  Printf(Con,"#;\n\n",Title(title));
  
  Int M(DoBuild,Builder(Range(DHMod::Mod)));
  Int K(DoBuild,Builder(Range(DHMod::InvMod)));
  Int L(DoBuild,Builder(Range(DHMod::Lift)));
  
  Int D(DoBuild,DBuilder(M.getBody().len-1));
  
  if( ((M*K-1)%D).sign() )
    {
     Printf(Exception,"failed");
    }
  
  if( L!=((D-M)*D)/M )
    {
     Printf(Exception,"failed");
    }
  
  PrintCon out(Con);
  
  PrintInt(out,M*K);
 }

} // namespace Private_0090
 
using namespace Private_0090; 
 
/* Testit<90> */ 

template<>
const char *const Testit<90>::Name="Test90 DHExp";

template<>
bool Testit<90>::Main() 
 {
  //test1<Crypton::DHModI>("DH Group I module");
  //test1<Crypton::DHModII>("DH Group II module");
  
  //PrintFile out("test90.txt");

  //test2<Crypton::DHModI>(out,"DH Group I module");
  //test2<Crypton::DHModII>(out,"DH Group II module");
  
  //test3<Crypton::DHModI>("DH Group I module");
  //test3<Crypton::DHModII>("DH Group II module");
  
  return true;
 }
 
} // namespace App
 
