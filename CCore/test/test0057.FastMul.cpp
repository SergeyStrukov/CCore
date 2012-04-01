/* test0057.FastMul.cpp */ 
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

#include <CCore/test/test.h>
#include <CCore/test/testIntAlgo.h>

#include <CCore/inc/Random.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/String.h>
#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/math/FastMul.h>

namespace App {

namespace Private_0057 {

/* class EngineBase<Unit> */

template <class Unit>
class EngineBase : public TestIntBase 
 {
   DynArray<Unit> array;
  
  public:
   
   EngineBase() {}
   
   ~EngineBase() {}
  
   Unit * provide(ulen len)
    {
     ulen alen=array.getLen();
    
     if( len>alen ) array.extend_default(len-alen);
     
     return array.getPtr();
    }
 };

/* struct DefAlgo<Unit> */

template <class Unit_>
struct DefAlgo
 {
  typedef Unit_ Unit;
  
  // tunning
  
  static const unsigned D1 = 2 ;
  
  static const unsigned D2 = 2 ;
  
  static const ulen TempLen = 64 ;
  
  // operations
  
  static unsigned CountD(ulen n)
   {
    unsigned ret=0;
    
    for(; n>1 ;ret++,n>>=1);
    
    return ret;
   }
  
  typedef Math::IntegerSlowAlgo<Unit> Slow;
  
  static void Null(Unit *a,ulen na)
   {
    Slow::Null(a,na);
   }
  
  static Unit UAddUnit(Unit *a,ulen na,Unit b)
   {
    return Slow::UAddUnit(a,na,b);
   }
  
  static Unit UAdd(Unit *restrict b,const Unit *a,ulen nab)
   {
    return Slow::UAdd(b,a,nab);
   }
  
  static Unit UDouble(Unit *a,ulen na)
   {
    return Slow::ULShift(a,na,1);
   }
  
  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
   {
    Slow::UMul(c,a,na,b,nb);
   }
  
  static Unit UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
   {
    return Slow::UMac(c,a,na,b,nb);
   }
  
  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb)
   {
    Slow::UMulLo(c,nc,a,na,b,nb);
   }
  
  static void USq(Unit *restrict c,const Unit *a,ulen na)
   {
    Slow::USq(c,a,na);
   }
 };

/* class TestEngine<Unit> */

template <class Unit>
class TestEngine : NoCopy
 {
   unsigned d;
   ulen n;
   
   const Unit *a;
   
   DynArray<Unit> buf;
  
   typedef Math::IntegerSlowAlgo<Unit> Slow;
   
  public:
  
   explicit TestEngine(unsigned d_)
    {
     d=d_;
     n=ulen(1)<<(d-1);
     
     buf.extend_raw(2*n);
    }
   
   ~TestEngine() {}
   
   void reset(unsigned d_)
    {
     d=d_;
     n=ulen(1)<<(d-1);
     
     if( buf.getLen()<2*n )
       {
        buf.erase();
        buf.extend_raw(2*n);
        
        Printf(Con,"extension\n");
       }
    }
   
   void downA(const Unit *a_)
    {
     a=a_;
    }
   
   void downB(const Unit *b)
    {
     Slow::UMul(buf.getPtr(),a,n,b,n);
    }
   
   void mul(Unit *c)
    {
     Range(c,2*n).copy(buf.getPtr());
    }
   
   Unit mac(Unit *c)
    {
     return Slow::UAdd(c,buf.getPtr(),2*n);
    }
   
   void mul_lo(Unit *c,ulen nc)
    {
     Range(c,nc).copy(buf.getPtr());
    }
   
   void mac_lo(Unit *c,ulen nc)
    {
     Slow::UAdd(c,buf.getPtr(),nc);
    }
   
   void sq(Unit *c)
    {
     Slow::USq(c,a,n);
    }
 };

/* class Engine1<Unit,Engine> */

template <class Unit,class Engine>
class Engine1 : EngineBase<Unit>
 {
   typedef Math::Pow2Mul<DefAlgo<Unit>,Engine> Fast;
   typedef Math::IntegerSlowAlgo<Unit> Slow;
   
   using EngineBase<Unit>::provide;
   using EngineBase<Unit>::Error;
   using EngineBase<Unit>::select;
   using EngineBase<Unit>::fill;
   
  public:
   
   Engine1() {}
   
   ~Engine1() {}
   
   void test1(ulen na,ulen nb,unsigned count)
    {
     ulen nc=na+nb;
     
     Unit *a=provide(na+nb+2*nc);
     Unit *b=a+na;
     Unit *c=b+nb;
     Unit *d=c+nc;
     
     for(; count ;count--)
       {
        fill(Range(a,na));
        fill(Range(b,nb));
        
        Slow::UMul(d,a,na,b,nb);
        Fast::UMul(c,a,na,b,nb);
        
        if( Slow::UCmp(c,d,nc) )
          {
           Error("test1");
          }
       }
    }
   
   void test2(ulen na,ulen nb,unsigned count)
    {
     ulen nc=na+nb;
     
     Unit *a=provide(na+nb+2*nc);
     Unit *b=a+na;
     Unit *c=b+nb;
     Unit *d=c+nc;
     
     for(; count ;count--)
       {
        fill(Range(a,na));
        fill(Range(b,nb));
        fill(Range(c,nc));
        
        Range(c,nc).copyTo(d);
        
        Unit u=Slow::UMac(d,a,na,b,nb);
        Unit u1=Fast::UMac(c,a,na,b,nb);
        
        if( u!=u1 || Slow::UCmp(c,d,nc) )
          {
           Error("test2");
          }
       }
    }
   
   void test3(ulen na,ulen nb,unsigned count)
    {
     ulen nc=select(0,na+nb);
     
     Unit *a=provide(na+nb+2*nc);
     Unit *b=a+na;
     Unit *c=b+nb;
     Unit *d=c+nc;
     
     for(; count ;count--)
       {
        fill(Range(a,na));
        fill(Range(b,nb));
        
        Slow::UMulLo(d,nc,a,na,b,nb);
        Fast::UMulLo(c,nc,a,na,b,nb);
        
        if( Slow::UCmp(c,d,nc) )
          {
           Error("test3");
          }
       }
    }
   
   void test4(ulen na,unsigned count)
    {
     ulen nc=2*na;
     
     Unit *a=provide(na+2*nc);
     Unit *c=a+na;
     Unit *d=c+nc;
     
     for(; count ;count--)
       {
        fill(Range(a,na));
        fill(Range(c,nc));
        
        Range(c,nc).copyTo(d);
        
        Slow::USq(d,a,na);
        Fast::USq(c,a,na);
        
        if( Slow::UCmp(c,d,nc) )
          {
           Error("test4");
          }
       }
    }
 };

/* struct KAlgo<Unit> */

template <class Unit_>
struct KAlgo
 {
  typedef Unit_ Unit;
  
  typedef Math::IntegerSlowAlgo<Unit> Slow;
  
  // tunning
  
  static const unsigned D1 = 1 ;
  
  static const unsigned D2 = 1 ;
  
  static const ulen TempLen = 64 ;
  
  // operations
  
  static Unit UAddUnit(Unit *a,ulen na,Unit b)
   {
    return Slow::UAddUnit(a,na,b);
   }
  
  static Unit UAdd(Unit *restrict b,const Unit *a,ulen nab)
   {
    return Slow::UAdd(b,a,nab);
   }
  
  static Unit USub(Unit *restrict b,const Unit *a,ulen nab)
   {
    return Slow::USub(b,a,nab);
   }
  
  static Unit UAdd(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc)
   {
    Range(a,nabc).copyTo(c);
    
    return Slow::UAdd(c,b,nabc);
   }
  
  static Unit USub(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc)
   {
    Range(a,nabc).copyTo(c);
    
    return Slow::USub(c,b,nabc);
   }
  
  static void UMul(unsigned d,Unit *restrict c,const Unit *a,const Unit *b) // d<=D1 , c[2^(d+1)] , a[2^d] , b[2^d]
   {
    ulen n=ulen(1)<<d;
    
    Slow::UMul(c,a,n,b,n);
   }
  
  static void UMulLo(unsigned d,Unit *restrict c,ulen nc,const Unit *a,const Unit *b) // d<=D1 , nc<=2^(d+1) , a[2^d] , b[2^d]
   {
    ulen n=ulen(1)<<d;
    
    Slow::UMulLo(c,nc,a,n,b,n);
   }
  
  static void USq(unsigned d,Unit *restrict c,const Unit *a) // d<=D2 , c[2^(d+1)] , a[2^d]
   {
    ulen n=ulen(1)<<d;

    Slow::USq(c,a,n);
   }
 };

/* class Engine2<Unit> */

template <class Unit>
class Engine2 : EngineBase<Unit> 
 {
   typedef Math::KaratsubaMul<KAlgo<Unit> > KMul;
   typedef Math::IntegerSlowAlgo<Unit> Slow;
  
   using EngineBase<Unit>::provide;
   using EngineBase<Unit>::Error;
   using EngineBase<Unit>::select;
   using EngineBase<Unit>::fill;
   
  public:
   
   Engine2() {}
   
   ~Engine2() {}
   
   void test5(unsigned deg,unsigned count)
    {
     ulen n=ulen(1)<<deg;
     
     Unit *a=provide(n+n+2*n+4*n+2*n);
     Unit *b=a+n;
     Unit *c=b+n;
     Unit *temp=c+2*n;
     Unit *d=temp+4*n;
     
     for(; count ;count--)
       {
        fill(Range(a,n));
        fill(Range(b,n));
        
        Slow::UMul(d,a,n,b,n);
        KMul::UMul(deg,c,a,b,temp);
        
        if( Slow::UCmp(c,d,2*n) )
          {
           Error("test5");
          }
       }
    }
   
   void test6(unsigned deg,unsigned count)
    {
     ulen n=ulen(1)<<deg;
     ulen nc=select(0,2*n);
     
     Unit *a=provide(n+n+nc+4*n+nc);
     Unit *b=a+n;
     Unit *c=b+n;
     Unit *temp=c+nc;
     Unit *d=temp+4*n;
     
     for(; count ;count--)
       {
        fill(Range(a,n));
        fill(Range(b,n));
        
        Slow::UMulLo(d,nc,a,n,b,n);
        KMul::UMulLo(deg,c,nc,a,b,temp);
        
        if( Slow::UCmp(c,d,nc) )
          {
           Error("test6");
          }
       }
    }
   
   void test7(unsigned deg,unsigned count)
    {
     ulen n=ulen(1)<<deg;
     
     Unit *a=provide(n+2*n+4*n+2*n);
     Unit *c=a+n;
     Unit *temp=c+2*n;
     Unit *d=temp+4*n;
     
     for(; count ;count--)
       {
        fill(Range(a,n));
        
        Slow::USq(d,a,n);
        KMul::USq(deg,c,a,temp);
        
        if( Slow::UCmp(c,d,2*n) )
          {
           Error("test7");
          }
       }
    }
 };

/* class Engine3<Unit> */

template <class Unit>
class Engine3 : EngineBase<Unit>
 {
   typedef Math::ConvolutionAlgoBase<Unit,Math::ConvolutionUnitAlgoBase<Unit> > Algo;

   typedef Math::RotFFT<Algo> FFT;
  
   using EngineBase<Unit>::provide;
   using EngineBase<Unit>::Error;
   using EngineBase<Unit>::fill;
   
  public:
   
   Engine3() {}
   
   ~Engine3() {}
   
   void test8(unsigned n,unsigned m,unsigned count)
    {
     ulen N=ulen(1)<<n;
     ulen L=ulen(1)<<(n+m);
     
     Unit *buf=provide(2*L+N);
     Unit *buf2=buf+L;
     Unit *temp=buf2+L;
     
     for(; count ;count--)
       {
        fill(Range(buf,L));
        
        Range(buf,L).copyTo(buf2);
        
        FFT::Down(n,m,buf,temp);
        FFT::Up(n,m,buf,temp);
        
        for(ulen i=0; i<L ;i++)
          if( buf[i]!=Unit(buf2[i]<<m) )
            {
             Error("test8");
            }
       }
    }
 };

/* class Engine4<Unit> */

template <class Unit>
class Engine4 : EngineBase<Unit>
 {
   typedef Math::ConvolutionAlgoBase<Unit,Math::ConvolutionUnitAlgoBase<Unit> > Algo;
   
   typedef Math::FastConvolution<Algo> Fast;
  
   using EngineBase<Unit>::provide;
   using EngineBase<Unit>::Error;
   using EngineBase<Unit>::fill;
   
  public:
   
   Engine4() {}
   
   ~Engine4() {}
   
   void test9(unsigned d,unsigned d0,unsigned count)
    {
     ulen D=ulen(1)<<d;
     
     Math::FastConvolutionLens lens(d,d0);
     
     Unit *sa=provide(2*D+2*lens.arg_len+lens.temp_len+D);
     Unit *sb=sa+D;
     
     Unit *a=sb+D;
     Unit *b=a+lens.arg_len;
     Unit *temp=b+lens.arg_len;
     Unit *c=temp+lens.temp_len;
     
     for(; count ;count--)
       {
        fill(Range(sa,D));
        fill(Range(sb,D));
        
        Range(sa,D).copyTo(c);
        
        Algo::Convolution(c,sb,d,a);
        
        Fast::Convolution(sa,sb,d,d0,a,b,temp);
        
        for(ulen i=0; i<D ;i++)
          if( sa[i]!=Unit(c[i]<<lens.shift) )
            {
             Error("test9");
            }
       }
    }
 };

/* struct ExtAlgo<Unit> */

template <class Unit>
struct ExtAlgo : Math::ConvolutionExtAlgoBase<Math::IntegerSlowAlgo<Unit>,ExtAlgo<Unit> >
 {
  // operations
  
  typedef Math::IntegerSlowAlgo<Unit> Slow;
  
  static void URShift(Unit *a,ulen na,unsigned shift_)
   {
    ulen delta=shift_/Slow::UnitBits;
    unsigned shift=shift_%Slow::UnitBits;
    
    if( shift )
      {
       Slow::UShiftDown(a,na-delta,delta,shift);
       Slow::Null(a+(na-delta),delta);
      }
    else
      {
       Slow::MoveDown(a,na-delta,delta);
       Slow::Null(a+(na-delta),delta);
      }
   }
  
  static void UNeg3(Unit *a) { Slow::UNeg(a,3); }
  
  static Unit UAdd3(Unit *restrict a,const Unit *b) { return Slow::UAdd(a,b,3); }
  
  static void USub3(Unit *restrict a,const Unit *b) { Slow::USub(a,b,3); }
  
  static void UMulLo3(Unit *restrict c,const Unit *a,const Unit *b) { Slow::UMulLo(c,3,a,3,b,3); }
  
  static void USqLo3(Unit *restrict c,const Unit *a) {  Slow::UMulLo(c,3,a,3,a,3);  }
  
  static void URShift3(Unit *a,unsigned shift) { URShift(a,3,shift); }
  
  static void UNeg4(Unit *a) { Slow::UNeg(a,4); }
  
  static Unit UAdd4(Unit *restrict a,const Unit *b) { return Slow::UAdd(a,b,4); }
  
  static void USub4(Unit *restrict a,const Unit *b) { Slow::USub(a,b,4); }
  
  static void UMulLo4(Unit *restrict c,const Unit *a,const Unit *b) { Slow::UMulLo(c,4,a,4,b,4); }
  
  static void USqLo4(Unit *restrict c,const Unit *a) {  Slow::UMulLo(c,4,a,4,a,4);  }
  
  static void URShift4(Unit *a,unsigned shift) { URShift(a,4,shift); }
 };

/* class Engine5<Unit> */

template <class Unit>
class Engine5 : EngineBase<Unit>
 {
   typedef Math::ConvolutionMul<ExtAlgo<Unit> > Fast;
   typedef Math::IntegerSlowAlgo<Unit> Slow;
   
   using EngineBase<Unit>::provide;
   using EngineBase<Unit>::Error;
   using EngineBase<Unit>::fill;
   
  private: 
   
   static unsigned CountD(ulen n) // n<=2^d , d>ExtAlgo<Unit>::D0 
    {
     unsigned d=ExtAlgo<Unit>::D0+1;
     
     while( n>(ulen(1)<<d) ) d++;
     
     return d;
    }
   
   static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
    {
     ulen nc=na+nb;
     unsigned d=CountD(nc);

     typename Fast::Engine engine(d);
     
     engine.downA(a,na);
     engine.downB(b,nb);
     
     engine.mul_lo(c,nc);
    }
   
   static Unit UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
    {
     ulen nc=na+nb;
     unsigned d=CountD(nc);

     typename Fast::Engine engine(d);
     
     engine.downA(a,na);
     engine.downB(b,nb);
     
     return engine.mac_lo(c,nc);
    }
   
   static void USq(Unit *restrict c,const Unit *a,ulen na)
    {
     ulen nc=2*na;
     unsigned d=CountD(nc);

     typename Fast::Engine engine(d);
     
     engine.downA(a,na);
     
     engine.sq_lo(c,nc);
    }
   
  public:
   
   Engine5() {}
   
   ~Engine5() {}
   
   void test10(ulen na,ulen nb,unsigned count)
    {
     ulen nc=na+nb;
     
     Unit *a=provide(na+nb+2*nc);
     Unit *b=a+na;
     Unit *c=b+nb;
     Unit *d=c+nc;
     
     for(; count ;count--)
       {
        fill(Range(a,na));
        fill(Range(b,nb));
        
        Slow::UMul(d,a,na,b,nb);
        UMul(c,a,na,b,nb);
        
        if( Slow::UCmp(c,d,nc) )
          {
           Error("test10");
          }
       }
    }
   
   void test11(ulen na,ulen nb,unsigned count)
    {
     ulen nc=na+nb;
     
     Unit *a=provide(na+nb+2*nc);
     Unit *b=a+na;
     Unit *c=b+nb;
     Unit *d=c+nc;
     
     for(; count ;count--)
       {
        fill(Range(a,na));
        fill(Range(b,nb));
        fill(Range(c,nc));
        
        Range(c,nc).copyTo(d);
        
        Unit u=Slow::UMac(d,a,na,b,nb);
        Unit u1=UMac(c,a,na,b,nb);
        
        if( u!=u1 || Slow::UCmp(c,d,nc) )
          {
           Error("test11");
          }
       }
    }
   
   void test12(ulen na,unsigned count)
    {
     ulen nc=2*na;
     
     Unit *a=provide(na+2*nc);
     Unit *c=a+na;
     Unit *d=c+nc;
     
     for(; count ;count--)
       {
        fill(Range(a,na));
        
        Slow::USq(d,a,na);
        USq(c,a,na);
        
        if( Slow::UCmp(c,d,nc) )
          {
           Error("test12");
          }
       }
    }
 };

} // namespace Private_0057
 
using namespace Private_0057; 
 
/* Testit<57> */ 

template<>
const char *const Testit<57>::Name="Test57 FastMul";

template<>
bool Testit<57>::Main() 
 {
#if 1

  // lens
  {
   for(unsigned d=5; d<=64 ;d++)
     {
      Math::FastConvolutionLens lens(d,4);

      if( d>lens.shift )
        Printf(Con,"d = #; shift = d - #;\n",d,d-lens.shift);
      else
        Printf(Con,"d = #; shift = d + #;\n",d,lens.shift-d);
     }
  }
  
  // Engine1
  {
   Engine1<uint8,TestEngine<uint8> > engine;
   
   for(ulen na=0; na<=100 ;na++)
     {
      for(ulen nb=0; nb<=100 ;nb++)
        {
         engine.test1(na,nb,100);
         engine.test2(na,nb,100);
         engine.test3(na,nb,100);
        }
      
      engine.test4(na,100);
     }
  }
  
  // Engine2
  {
   Engine2<uint8> engine;
   
   for(unsigned deg=1; deg<=10 ;deg++) 
     {
      engine.test5(deg,1000);
      engine.test6(deg,1000);
      engine.test7(deg,1000);
     }
  }
  
  // Engine1
  {
   Engine1<uint8,Math::KaratsubaMul<KAlgo<uint8> >::Engine> engine;
   
   for(ulen na=0; na<=100 ;na++)
     {
      for(ulen nb=0; nb<=100 ;nb++)
        {
         engine.test1(na,nb,100);
         engine.test2(na,nb,100);
         engine.test3(na,nb,100);
        }
      
      engine.test4(na,100);
     }
  }
  
  // Engine3
  {
   Engine3<uint8> engine;

   for(ulen m=1; m<=7 ;m++)
     for(ulen n=m; n<=m+3 ;n++)
       engine.test8(n,m,1000);
  }
  
  // Engine4
  {
   Engine4<uint8> engine;
   
   engine.test9(10,4,1000);
   engine.test9(17,4,10);
  }
  
  // Engine5
  {
   Engine5<uint32> engine;
   
   engine.test10(1000,2000,100);
   
   engine.test10(4000,4000,1);
   
   for(ulen na=0; na<=100 ;na++)
     {
      for(ulen nb=0; nb<=100 ;nb++)
        {
         engine.test10(na,nb,100);
         engine.test11(na,nb,100);
        }
      
      engine.test12(na,100);
     }
  }
  
#endif  

  // Engine1
  {
   Engine1<uint32,Math::ConvolutionMul<ExtAlgo<uint32> >::Engine> engine;
   
   for(ulen na=1000; na<=5000 ;na+=1000)
     {
      for(ulen nb=1000; nb<=5000 ;nb+=1000)
        {
         engine.test1(na,nb,100);
         engine.test2(na,nb,100);
         engine.test3(na,nb,100);
        }
      
      engine.test4(na,100);
     }
  }
  
  return true;
 }
 
} // namespace App
 
