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

/* class UBuilder */

class UBuilder
 {
   PtrLen<const Int::Unit> data;
   
  public: 
   
   explicit UBuilder(PtrLen<const Int::Unit> data_) : data(data_) {}
   
   ulen getLen() const { return LenAdd(data.len,1); }
   
   PtrLen<Int::Unit> operator () (Place<void> place) const
    {
     Int::Unit *base=place;
     
     data.copyTo(base);
     
     base[data.len]=0;
     
     return Range(base,data.len+1);
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

/* test4() */

template <class DHMod>
void test4(StrLen title)
 {
  Printf(Con,"#;\n\n",Title(title));
  
  using Exp = Crypton::DHExp<DHMod> ;
  using Unit = typename Exp::Unit ;
  
  typename Exp::Core core;
  
  PlatformRandom random;
  
  Unit A[Exp::IntLen];
  Unit B[Exp::IntLen];
  Unit C[Exp::IntLen];
  
  Int m(DoBuild,Builder(Range(DHMod::Mod)));
  
  for(ulen cnt=10000; cnt ;cnt--)
    {
     random.fill(Range(A));
     random.fill(Range(B));
    
     core.mul(A,B,C);
     
     core.direct(A,A);
     core.direct(B,B);
     core.direct(C,C);
    
     Int a(DoBuild,UBuilder(Range_const(A)));
     Int b(DoBuild,UBuilder(Range_const(B)));
     Int c(DoBuild,UBuilder(Range_const(C)));
     
     if( ((a*b-c)%m).sign() )
       {
        Printf(Exception,"failed");
       }
    }
 }

/* test5() */

template <class DHMod>
void test5(StrLen title)
 {
  Printf(Con,"#;\n\n",Title(title));
  
  using Exp = Crypton::DHExp<DHMod> ;
  using Unit = typename Exp::Unit ;
  
  typename Exp::Core core;
  
  PlatformRandom random;
  
  Unit A[Exp::IntLen];
  Unit B[Exp::IntLen];
  Unit C[Exp::IntLen];
  
  Int m(DoBuild,Builder(Range(DHMod::Mod)));
  Int d(DoBuild,DBuilder(m.getBody().len-1));
  
  for(ulen cnt=10000; cnt ;cnt--)
    {
     random.fill(Range(A));
    
     core.inverse(A,B);
     core.direct(B,C);
    
     Int a(DoBuild,UBuilder(Range_const(A)));
     Int b(DoBuild,UBuilder(Range_const(B)));
     Int c(DoBuild,UBuilder(Range_const(C)));
     
     if( c != a%m )
       {
        Printf(Exception,"failed");
       }
     
     if( (a*d)%m != b%m )
       {
        Printf(Exception,"failed");
       }
    }
 }

/* test6() */

template <class DHMod>
void test6(StrLen title)
 {
  Printf(Con,"#;\n\n",Title(title));
  
  using Exp = Crypton::DHExp<DHMod> ;
  
  PlatformRandom random;
  
  Exp exp;
  
  uint8 x[DHMod::GLen];
  uint8 y[DHMod::GLen];
  uint8 gx[DHMod::GLen];
  uint8 gy[DHMod::GLen];
  uint8 gxy[DHMod::GLen];
  uint8 gyx[DHMod::GLen];
  
  for(ulen cnt=100; cnt ;cnt--)
    {
     random.fill(Range(x));
     random.fill(Range(y));
     
     exp.pow(x,gx);
     exp.pow(gx,y,gxy);
     
     exp.pow(y,gy);
     exp.pow(gy,x,gyx);
     
     if( !Range(gxy).equal(gyx) )
       {
        Printf(Exception,"failed");
       }
    }
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
  
  //test4<Crypton::DHModI>("DH Group I module");
  //test4<Crypton::DHModII>("DH Group II module");
  
  //test5<Crypton::DHModI>("DH Group I module");
  //test5<Crypton::DHModII>("DH Group II module");
  
  test6<Crypton::DHModI>("DH Group I module");
  test6<Crypton::DHModII>("DH Group II module");
  
  return true;
 }
 
} // namespace App
 
