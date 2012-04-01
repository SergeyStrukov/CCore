/* FastMul.h */ 
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

#ifndef CCore_inc_math_FastMul_h
#define CCore_inc_math_FastMul_h

#include <CCore/inc/Array.h>
 
namespace CCore {
namespace Math {

/* functions */

void GuardFastMulOverlen(unsigned d);

void GuardFastMulOverbits(unsigned d,unsigned extra);

/* classes */

template <class DefAlgo,class Engine> struct Pow2Mul;

template <class KAlgo> struct KaratsubaMul;

struct FastConvolutionLens;

template <class T,class UnitAlgo> struct ConvolutionAlgoBase;

template <class T> struct ConvolutionUnitAlgoBase;

template <class Algo> struct RotFFT;

template <class Algo> struct FastConvolution;

template <class Algo,class Ext> struct ConvolutionExtAlgoBase;

template <class ExtAlgo> struct ConvolutionMul;

/* struct DefAlgo */

#if 0

struct DefAlgo
 {
  typedef ??? Unit;
  
  // tunning
  
  static const unsigned D1 = ??? ;
  
  static const unsigned D2 = ??? ;
  
  static const ulen TempLen = ??? ;
  
  // operations
  
  static unsigned CountD(ulen n); // n!=0 , return max d , 2^d<=n
  
  static void Null(Unit *a,ulen na);
  
  static Unit UAddUnit(Unit *a,ulen na,Unit b);
  
  static Unit UAdd(Unit *restrict b,const Unit *a,ulen nab);
  
  static Unit UDouble(Unit *a,ulen na);
  
  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // 0<na<=nb , nc==na+nb , na<=2^D1-1
  
  static Unit UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // 0<na<=nb , nc==na+nb , na<=2^D1-1
  
  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb); // 0<na<=nb , nc<=na+nb , na<=2^D1-1
  
  static void USq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na , na<=2^D2-1
 };

class Engine : NoCopy
 {
  public:
  
   explicit Engine(unsigned d); // d>min(D1,D2)
   
   ~Engine();
   
   void reset(unsigned d); // d>min(D1,D2)
   
   void downA(const Unit *a); // na==2^(d-1) , reusable
   
   void downB(const Unit *b); // nb==2^(d-1)
   
   void mul(Unit *c); // nc==2^d
   
   Unit mac(Unit *c); // nc==2^d
   
   void mul_lo(Unit *c,ulen nc); // nc<=2^d
   
   void mac_lo(Unit *c,ulen nc); // nc<=2^d
   
   void sq(Unit *c); // nc==2^d
 };

#endif

/* struct Pow2Mul<DefAlgo,Engine> */

template <class DefAlgo,class Engine> 
struct Pow2Mul
 {
  typedef typename DefAlgo::Unit Unit;
  
  static const ulen MaxMulLen = (ulen(1)<<DefAlgo::D1)-1 ;

  static const ulen MaxSqLen = (ulen(1)<<DefAlgo::D2)-1 ;
  
  // internal
  
  static Unit UMacExtra(Engine &engine,Unit *c,ulen nc,ulen extra)
   {
    Unit carry=engine.mac(c);
    
    return DefAlgo::UAddUnit(c+nc,extra,carry);
   }
  
  static Unit UMac(Engine &engine,Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
   {
    if( na==0 || nb==0 ) return 0;
      
    if( na>nb )  
      {
       Swap(a,b);
       Swap(na,nb);
      }
    
    if( na<=MaxMulLen ) return DefAlgo::UMac(c,a,na,b,nb);
    
    unsigned d=DefAlgo::CountD(na); // d>=D1
    
    ulen n=ulen(1)<<d;
    ulen nc=na+nb;
    
    engine.reset(d+1);
    
    engine.downA(a);
    
    ulen off=0;
    Unit ret=0;
    
    for(; off<=nb-n ;off+=n)
      {
       engine.downB(b+off);
       
       ret+=UMacExtra(engine,c+off,2*n,nc-off-2*n);
      }
    
    if( na-n>=nb-off )
      {
       ret+=UMac(engine,c+n,a+n,na-n,b,nb);
       ret+=UMac(engine,c+off,a,n,b+off,nb-off,na-n);
      }
    else
      {
       ret+=UMac(engine,c+off,a,na,b+off,nb-off);
       ret+=UMac(engine,c+n,a+n,na-n,b,off,nb-off);
      }
    
    return ret;
   }
  
  static Unit UMac(Engine &engine,Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,ulen extra)
   {
    Unit carry=UMac(engine,c,a,na,b,nb);
    
    return DefAlgo::UAddUnit(c+na+nb,extra,carry);
   }
  
  static void UMacLo(Engine &engine,Unit *temp,Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb)
   {
    Replace_min(na,nc);
    Replace_min(nb,nc);
    
    if( na==0 || nb==0 ) return;
      
    if( na>nb )  
      {
       Swap(a,b);
       Swap(na,nb);
      }
    
    if( na<=MaxMulLen )
      {
       DefAlgo::UMulLo(temp,nc,a,na,b,nb);
       
       DefAlgo::UAdd(c,temp,nc);
       
       return;
      }
    
    unsigned d=DefAlgo::CountD(na); // d>=D1
    
    ulen n=ulen(1)<<d;
    
    engine.reset(d+1);
    
    engine.downA(a);
    
    ulen off=0;
    ulen lim=Min(nc,nb-n);
    
    for(; off<=lim ;off+=n)
      {
       engine.downB(b+off);
       
       if( nc<off+2*n )
         {
          engine.mac_lo(c+off,nc-off);
         }
       else
         {
          UMacExtra(engine,c+off,2*n,nc-off-2*n);
         }
      }
    
    if( na-n>=nb-off )
      {
       if( n<nc ) UMacLo(engine,temp,c+n,nc-n,a+n,na-n,b,nb);
      
       if( off<nc )
         {
          if( nc<=n+nb )
            UMacLo(engine,temp,c+off,nc-off,a,n,b+off,nb-off);
          else
            UMac(engine,c+off,a,n,b+off,nb-off,nc-n-nb);
         }
      }
    else
      {
       if( off<nc ) UMacLo(engine,temp,c+off,nc-off,a,na,b+off,nb-off);
       
       if( n<nc )
         {
          if( nc<=na+off )
            UMacLo(engine,temp,c+n,nc-n,a+n,na-n,b,off);
          else
            UMac(engine,c+n,a+n,na-n,b,off,nc-na-off);
         }
      }
   }
  
  static void UMul(Engine &engine,Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
   {
    if( na==0 || nb==0 )
      {
       DefAlgo::Null(c,na+nb);
      
       return;
      }
      
    if( na>nb )  
      {
       Swap(a,b);
       Swap(na,nb);
      }
    
    if( na<=MaxMulLen )
      {
       DefAlgo::UMul(c,a,na,b,nb);
       
       return;
      }
    
    unsigned d=DefAlgo::CountD(na); // d>=D1
    
    ulen n=ulen(1)<<d;
    ulen nc=na+nb;
    
    engine.reset(d+1);
    
    engine.downA(a);
    engine.downB(b);
    engine.mul(c);
    
    DefAlgo::Null(c+2*n,nc-2*n);
    
    ulen off=n;
    
    for(; off<=nb-n ;off+=n)
      {
       engine.downB(b+off);
       
       UMacExtra(engine,c+off,2*n,nc-off-2*n);
      }
    
    if( na-n>=nb-off )
      {
       UMac(engine,c+n,a+n,na-n,b,nb);
       UMac(engine,c+off,a,n,b+off,nb-off,na-n);
      }
    else
      {
       UMac(engine,c+off,a,na,b+off,nb-off);
       UMac(engine,c+n,a+n,na-n,b,off,nb-off);
      }
   }
  
  static Unit UMac2(Engine &engine,Unit *temp,Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
   {
    ulen nc=na+nb;
    
    UMul(engine,temp,a,na,b,nb);
    
    Unit carry=DefAlgo::UDouble(temp,nc);
    
    carry+=DefAlgo::UAdd(c,temp,nc);
    
    return carry;
   }
  
  static Unit UMac2(Engine &engine,Unit *temp,Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,ulen extra)
   {
    Unit carry=UMac2(engine,temp,c,a,na,b,nb);
    
    return DefAlgo::UAddUnit(c+na+nb,extra,carry);
   }
  
  static void USq(Engine &engine,Unit *temp,Unit *restrict c,const Unit *a,ulen na)
   {
    if( na<=MaxSqLen )
      {
       DefAlgo::USq(c,a,na);
       
       return;
      }
    
    unsigned d=DefAlgo::CountD(na); // d>=D2
    
    ulen n=ulen(1)<<d;
    
    engine.reset(d+1);
    
    engine.downA(a);
    engine.sq(c);
    
    USq(engine,temp,c+2*n,a+n,na-n);
    
    UMac2(engine,temp,c+n,a,n,a+n,na-n,na-n);
   }
  
  // multiplicative operators
  
  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // nc==na+nb
   {
    if( na==0 || nb==0 )
      {
       DefAlgo::Null(c,na+nb);
      
       return;
      }
      
    if( na>nb )  
      {
       Swap(a,b);
       Swap(na,nb);
      }
    
    if( na<=MaxMulLen )
      {
       DefAlgo::UMul(c,a,na,b,nb);
       
       return;
      }
    
    unsigned d=DefAlgo::CountD(na); // d>=D1
    
    ulen n=ulen(1)<<d;
    ulen nc=na+nb;
    
    Engine engine(d+1);
    
    engine.downA(a);
    engine.downB(b);
    engine.mul(c);
    
    DefAlgo::Null(c+2*n,nc-2*n);
    
    ulen off=n;
    
    for(; off<=nb-n ;off+=n)
      {
       engine.downB(b+off);
       
       UMacExtra(engine,c+off,2*n,nc-off-2*n);
      }
    
    if( na-n>=nb-off )
      {
       UMac(engine,c+n,a+n,na-n,b,nb);
       UMac(engine,c+off,a,n,b+off,nb-off,na-n);
      }
    else
      {
       UMac(engine,c+off,a,na,b+off,nb-off);
       UMac(engine,c+n,a+n,na-n,b,off,nb-off);
      }
   }
  
  static Unit UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // nc==na+nb
   {
    if( na==0 || nb==0 ) return 0; 
      
    if( na>nb )  
      {
       Swap(a,b);
       Swap(na,nb);
      }
    
    if( na<=MaxMulLen ) return DefAlgo::UMac(c,a,na,b,nb);
    
    unsigned d=DefAlgo::CountD(na); // d>=D1
    
    ulen n=ulen(1)<<d;
    ulen nc=na+nb;
    
    Engine engine(d+1);
    
    engine.downA(a);
    
    ulen off=0;
    Unit ret=0;
    
    for(; off<=nb-n ;off+=n)
      {
       engine.downB(b+off);
       
       ret+=UMacExtra(engine,c+off,2*n,nc-off-2*n);
      }
    
    if( na-n>=nb-off )
      {
       ret+=UMac(engine,c+n,a+n,na-n,b,nb);
       ret+=UMac(engine,c+off,a,n,b+off,nb-off,na-n);
      }
    else
      {
       ret+=UMac(engine,c+off,a,na,b+off,nb-off);
       ret+=UMac(engine,c+n,a+n,na-n,b,off,nb-off);
      }
    
    return ret;
   }

  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) // nc<=na+nb
   {
    Replace_min(na,nc);
    Replace_min(nb,nc);
    
    if( na==0 || nb==0 )
      {
       DefAlgo::Null(c,nc);
      
       return;
      }
      
    if( na>nb )  
      {
       Swap(a,b);
       Swap(na,nb);
      }
    
    if( na<=MaxMulLen )
      {
       DefAlgo::UMulLo(c,nc,a,na,b,nb);
       
       return;
      }
    
    unsigned d=DefAlgo::CountD(na); // d>=D1
    
    ulen n=ulen(1)<<d;
    
    Engine engine(d+1);
    TempArray<Unit,DefAlgo::TempLen> array(nc);
    
    Unit *temp=array.getPtr();
    
    engine.downA(a);
    engine.downB(b);
    
    if( nc<2*n )
      {
       engine.mul_lo(c,nc);
      }
    else
      {
       engine.mul(c);
    
       DefAlgo::Null(c+2*n,nc-2*n);
      }
    
    ulen off=n;
    ulen lim=Min(nc,nb-n);
    
    for(; off<=lim ;off+=n)
      {
       engine.downB(b+off);
       
       if( nc<off+2*n )
         {
          engine.mac_lo(c+off,nc-off);
         }
       else
         {
          UMacExtra(engine,c+off,2*n,nc-off-2*n);
         }
      }
    
    if( na-n>=nb-off )
      {
       if( n<nc ) UMacLo(engine,temp,c+n,nc-n,a+n,na-n,b,nb);
      
       if( off<nc )
         {
          if( nc<=n+nb )
            UMacLo(engine,temp,c+off,nc-off,a,n,b+off,nb-off);
          else
            UMac(engine,c+off,a,n,b+off,nb-off,nc-n-nb);
         }
      }
    else
      {
       if( off<nc ) UMacLo(engine,temp,c+off,nc-off,a,na,b+off,nb-off);
       
       if( n<nc )
         {
          if( nc<=na+off )
            UMacLo(engine,temp,c+n,nc-n,a+n,na-n,b,off);
          else
            UMac(engine,c+n,a+n,na-n,b,off,nc-na-off);
         }
      }
   }
  
  static void USq(Unit *restrict c,const Unit *a,ulen na) // nc==2*na
   {
    if( na<=MaxSqLen )
      {
       DefAlgo::USq(c,a,na);
       
       return;
      }
    
    unsigned d=DefAlgo::CountD(na); // d>=D2
    
    ulen n=ulen(1)<<d;
    
    Engine engine(d+1);
    TempArray<Unit,DefAlgo::TempLen> array(na);
    
    Unit *temp=array.getPtr();
    
    engine.downA(a);
    engine.sq(c);
    
    USq(engine,temp,c+2*n,a+n,na-n);
    
    UMac2(engine,temp,c+n,a,n,a+n,na-n,na-n);
   }
 };

/* struct KAlgo */

#if 0

struct KAlgo
 {
  typedef ??? Unit;
  
  // tunning
  
  static const unsigned D1 = ??? ;
  
  static const unsigned D2 = ??? ;
  
  static const ulen TempLen = ??? ;
  
  // operations
  
  static Unit UAddUnit(Unit *a,ulen na,Unit b);
  
  static Unit UAdd(Unit *restrict b,const Unit *a,ulen nab);
  
  static Unit USub(Unit *restrict b,const Unit *a,ulen nab);
  
  static Unit UAdd(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc);
  
  static Unit USub(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc);
  
  static void UMul(unsigned d,Unit *restrict c,const Unit *a,const Unit *b); // d<=D1 , c[2^(d+1)] , a[2^d] , b[2^d]
  
  static void UMulLo(unsigned d,Unit *restrict c,ulen nc,const Unit *a,const Unit *b); // d<=D1 , nc<=2^(d+1) , a[2^d] , b[2^d]
  
  static void USq(unsigned d,Unit *restrict c,const Unit *a); // d<=D2 , c[2^(d+1)] , a[2^d]
 };

#endif

/* struct KaratsubaMul<KAlgo> */ 

template <class KAlgo>
struct KaratsubaMul
 {
  typedef typename KAlgo::Unit Unit;
  
  static bool ModSub(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc) // return a<b
   {
    for(; nabc>0 ;nabc--)
      {
       if( a[nabc-1]!=b[nabc-1] )
         {
          if( a[nabc-1]<b[nabc-1] )
            {
             KAlgo::USub(c,b,a,nabc);
             
             return true;
            }
          else
            {
             KAlgo::USub(c,a,b,nabc);
             
             return false;
            }
         }
       
       c[nabc-1]=0;
      }
    
    return false;
   }
  
  static void UMul(unsigned d,Unit *restrict c,const Unit *a,const Unit *b,Unit *restrict temp) // c[2^(d+1)] , a[2^d] , b[2^d] , temp[2^(d+2)]
   {
    if( d<=KAlgo::D1 ) 
      {
       KAlgo::UMul(d,c,a,b);
       
       return;
      }
    
    unsigned d1=d-1;
    ulen n=ulen(1)<<d1;
    ulen n2=n<<1;
    const Unit *a1=a+n;
    const Unit *b1=b+n;
    Unit *c1=c+n;
    Unit *c2=c1+n;
    Unit *c3=c2+n;
    Unit *temp1=temp+(n2<<1);
    
    UMul(d1,c,a,b,temp1);
    UMul(d1,c2,a1,b1,temp1);
    
    Unit *da=temp;
    Unit *db=da+n;
    Unit *m=db+n;
    
    bool flag_a=ModSub(da,a,a1,n);
    bool flag_b=ModSub(db,b,b1,n);
    
    UMul(d1,m,da,db,temp1);
    
    Unit carry=KAlgo::UAdd(temp,c,c2,n2);
    
    if( flag_a!=flag_b )
      {
       carry+=KAlgo::UAdd(temp,m,n2);
      }
    else
      {
       carry-=KAlgo::USub(temp,m,n2);
      }

    carry+=KAlgo::UAdd(c1,temp,n2);
    
    KAlgo::UAddUnit(c3,n,carry);
   }

  static void UMulLo(unsigned d,Unit *restrict c,ulen nc,const Unit *a,const Unit *b,Unit *restrict temp) // nc<=2^(d+1) , a[2^d] , b[2^d] , temp[2^(d+2)]
   {
    if( d<=KAlgo::D1 ) 
      {
       KAlgo::UMulLo(d,c,nc,a,b);
       
       return;
      }
    
    unsigned d1=d-1;
    ulen n=ulen(1)<<d1;
    
    if( nc<=n )
      {
       UMulLo(d1,c,nc,a,b,temp);
       
       return;       
      }
    
    const Unit *a1=a+n;
    const Unit *b1=b+n;
    Unit *temp1=temp+(n<<2);
    
    Unit *da=temp;
    Unit *db=da+n;
    
    Unit *c1=c+n;
    
    if( nc<=2*n )
      {
       UMulLo(d1,c,nc,a,b,temp1);
       
       ulen k=nc-n;

       UMulLo(d1,da,k,a,b1,temp1);
       UMulLo(d1,db,k,a1,b,temp1);
       
       KAlgo::UAdd(c1,da,k);
       KAlgo::UAdd(c1,db,k);
       
       return;
      }
    
    ulen n2=n<<1;
    Unit *c2=c1+n;
    Unit *c3=c2+n;
    Unit *m=db+n;
    
    UMul(d1,c,a,b,temp1);
    
    bool flag_a=ModSub(da,a,a1,n);
    bool flag_b=ModSub(db,b,b1,n);
    
    if( nc<=3*n )
      {
       ulen k=nc-n;
       
       UMulLo(d1,m,k,da,db,temp1);
       UMulLo(d1,temp,k,a1,b1,temp1);
       
       Range(temp,k-n).copyTo(c2);
         
       KAlgo::UAdd(temp,c,k);
       
       if( flag_a!=flag_b )
         {
          KAlgo::UAdd(temp,m,k);
         }
       else
         {
          KAlgo::USub(temp,m,k);
         }

       KAlgo::UAdd(c1,temp,k);
       
       return;
      }
    
    UMul(d1,m,da,db,temp1);
    UMul(d1,temp,a1,b1,temp1);
    
    Range(temp,nc-n2).copyTo(c2);
      
    Unit carry=KAlgo::UAdd(temp,c,n2);
    
    if( flag_a!=flag_b )
      {
       carry+=KAlgo::UAdd(temp,m,n2);
      }
    else
      {
       carry-=KAlgo::USub(temp,m,n2);
      }

    carry+=KAlgo::UAdd(c1,temp,n2);
    
    KAlgo::UAddUnit(c3,nc-3*n,carry);
   }

  static void USq(unsigned d,Unit *restrict c,const Unit *a,Unit *restrict temp) // c[2^(d+1)] , a[2^d] , temp[2^(d+2)]
   {
    if( d<=KAlgo::D2 ) 
      {
       KAlgo::USq(d,c,a);
       
       return;
      }
    
    unsigned d1=d-1;
    ulen n=ulen(1)<<d1;
    ulen n2=n<<1;
    const Unit *a1=a+n;
    Unit *c1=c+n;
    Unit *c2=c1+n;
    Unit *c3=c2+n;
    Unit *temp1=temp+(n2<<1);
    
    USq(d1,c,a,temp1);
    USq(d1,c2,a1,temp1);
    
    Unit *da=temp;
    Unit *m=da+n2;
    
    ModSub(da,a,a1,n);
    
    USq(d1,m,da,temp1);
    
    Unit carry=KAlgo::UAdd(temp,c,c2,n2);
    
    carry-=KAlgo::USub(temp,m,n2);

    carry+=KAlgo::UAdd(c1,temp,n2);
    
    KAlgo::UAddUnit(c3,n,carry);
   }

  class Engine : NoCopy
   {
     unsigned d;
     ulen n; 
    
     TempArray<Unit,KAlgo::TempLen> array;
     
     const Unit *a;
     const Unit *b;
     
    public:
    
     explicit Engine(unsigned d_) // d>0
      {
       reset(d_);
      }
     
     ~Engine() {}
     
     void reset(unsigned d_) // d>0
      {
       if( d_>Meta::UIntBits<ulen>::Ret-2 ) GuardFastMulOverlen(d_);
       
       d=d_-1;
       n=ulen(1)<<d;
       
       array.provide(6*n);
      }
     
     void downA(const Unit *a_)
      {
       a=a_;
      }
     
     void downB(const Unit *b_)
      {
       b=b_;
      }
     
     void mul(Unit *c)
      {
       UMul(d,c,a,b,array.getPtr());
      }
     
     Unit mac(Unit *c)
      {
       Unit *temp=array.getPtr()+4*n;
       
       UMul(d,temp,a,b,array.getPtr());
       
       return KAlgo::UAdd(c,temp,2*n);
      }
     
     void mul_lo(Unit *c,ulen nc)
      {
       UMulLo(d,c,nc,a,b,array.getPtr());
      }
     
     void mac_lo(Unit *c,ulen nc)
      {
       Unit *temp=array.getPtr()+4*n;
       
       UMulLo(d,temp,nc,a,b,array.getPtr());
       
       KAlgo::UAdd(c,temp,nc);
      }
     
     void sq(Unit *c)
      {
       USq(d,c,a,array.getPtr());
      }
   };
 };

/* struct FastConvolutionLens */ 

struct FastConvolutionLens
 {
  ulen arg_len;
  ulen temp_len;
  unsigned shift;
  
  FastConvolutionLens() : arg_len(),temp_len(),shift() {}
  
  FastConvolutionLens(unsigned d,unsigned d0) // d>d0>=2 , d<ulen_bits-1 , default d0 = 4
   {
    {
     unsigned n=d/2;
     unsigned m=d-n;
    
     temp_len=ulen(1)<<(n+1);
    
     shift=m;
     arg_len=ulen(1)<<(d+1);
    
     d=n+1;
    } 
    
    while( d>d0 )
      {
       unsigned n=d/2;
       unsigned m=d-n;
       
       shift+=m;
       arg_len+=ulen(1)<<(d+1);
       
       d=n+1;
      }
   }
 };

/* struct Algo */

#if 0

struct Algo
 {
  typedef ??? Unit;
  
  // RotFFT
  
  static void AddSub(Unit *restrict b/* <- b+a */,Unit *restrict a/* <- b-a */,ulen N); // a[N] , b[N]
  
  static void NegRotate(Unit *restrict a,ulen N,ulen C,Unit *restrict temp);    // a[N] , 0<C<N , temp[N]
  
  static void NegRotateRev(Unit *restrict a,ulen N,ulen C,Unit *restrict temp); // a[N] , 0<C<N , temp[N]
  
  // FastConvolution
  
  template <class S> // S includes Unit
  static void Set(Unit *restrict a,const S *s,ulen N); // a[N] , s[N]
  
  static void Null(Unit *a,ulen N); // a[N]
  
  static void Add(Unit *restrict c,const Unit *a,const Unit *b,ulen N); // a[N] , b[N] , c[N]
  
  static void Sub(Unit *restrict c,const Unit *a,const Unit *b,ulen N); // a[N] , b[N] , c[N]
  
  static void Add(Unit *restrict a,const Unit *b,ulen N); // a[N] , b[N]
  
  static void Sub(Unit *restrict a,const Unit *b,ulen N); // a[N] , b[N]
  
  static void Convolution(Unit *restrict a,const Unit *b,unsigned n,Unit *restrict temp); // a[2^n] , b[2^n] , temp[2^n]
  
  static void SqConvolution(Unit *restrict a,const Unit *b,unsigned n,Unit *restrict temp); // a[2^n] , b[2^n] , temp[2^n]
 };

#endif

/* struct UnitAlgo */

#if 0

struct UnitAlgo
 {
  // (&c) != (&a) , (&b) 
  
  static void Null(T &c) { c=0; }
  
  static void Neg(T &c,const T &a) { c=-a; }
  
  static void Add(T &c,const T &b,const T &a) { c=b+a; }
  
  static void Sub(T &c,const T &b,const T &a) { c=b-a; }
  
  static void Mul(T &c,const T &b,const T &a) { c=b*a; }
  
  static void AddMul(T &c,const T &b,const T &a) { c+=b*a; }
  
  static void SubMul(T &c,const T &b,const T &a) { c-=b*a; }
  
  static void AddMul2(T &c,const T &b,const T &a) { c+=2*b*a; }
  
  static void SubMul2(T &c,const T &b,const T &a) { c-=2*b*a; }
  
  static void AddSq(T &c,const T &b) { c+=b*b; }
  
  static void SubSq(T &c,const T &b) { c-=b*b; }
  
  static void Add(T &c,const T &a) { c+=a; }

  static void Sub(T &c,const T &a) { c-=a; }
  
  template <class S>
  static void Set(T &c,const S &a) { c=a; }
 };

#endif

/* struct ConvolutionAlgoBase<T,UnitAlgo> */

template <class T,class UnitAlgo>
struct ConvolutionAlgoBase
 {
  typedef T Unit;
  
  static void AddSub(Unit &b,Unit &a)
   {
    Unit b_=b;
    Unit a_=a;

    UnitAlgo::Add(b,b_,a_);
    UnitAlgo::Sub(a,b_,a_);
   }
  
  static void AddSub(Unit *restrict b,Unit *restrict a,ulen N)
   {
    for(; N ;N--,b++,a++) AddSub(*b,*a);
   }
  
  static void NegRotate(Unit *restrict a,ulen N,ulen C,Unit *restrict temp)
   {
    ulen L=N-C;
    
    for(ulen i=0; i<L ;i++) temp[i]=a[i];
    
    for(ulen i=0; i<C ;i++) UnitAlgo::Neg(a[i],a[i+L]);
    
    for(ulen i=0; i<L ;i++) a[i+C]=temp[i];
   }
  
  static void NegRotateRev(Unit *restrict a,ulen N,ulen C,Unit *restrict temp)
   {
    ulen L=N-C;
    
    for(ulen i=0; i<C ;i++) temp[i]=a[i];
    
    for(ulen i=0; i<L ;i++) a[i]=a[i+C];
    
    for(ulen i=0; i<C ;i++) UnitAlgo::Neg(a[i+L],temp[i]);
   }
  
  template <class S>
  static void Set(Unit *restrict a,const S *s,ulen N)
   {
    for(; N ;N--,a++,s++) UnitAlgo::Set(*a,*s); 
   }
  
  static void Null(Unit *a,ulen N)
   {
    for(; N ;N--,a++) UnitAlgo::Null(*a);
   }
  
  static void Add(Unit *restrict c,const Unit *a,const Unit *b,ulen N)
   {
    for(; N ;N--,c++,a++,b++) UnitAlgo::Add(*c,*a,*b);
   }
  
  static void Sub(Unit *restrict c,const Unit *a,const Unit *b,ulen N)
   {
    for(; N ;N--,c++,a++,b++) UnitAlgo::Sub(*c,*a,*b);
   }
  
  static void Add(Unit *restrict a,const Unit *b,ulen N)
   {
    for(; N ;N--,a++,b++) UnitAlgo::Add(*a,*b);
   }
  
  static void Sub(Unit *restrict a,const Unit *b,ulen N)
   {
    for(; N ;N--,a++,b++) UnitAlgo::Sub(*a,*b);
   }
  
  static void Convolution(Unit *restrict a,const Unit *b,unsigned n,Unit *restrict temp)
   {
    ulen N=ulen(1)<<n;
    
    Set(temp,a,N);
    
    for(ulen k=0; k<N ;k++)
      {
       Unit acc;
       
       UnitAlgo::Null(acc);
       
       for(ulen i=0; i<=k ;i++) UnitAlgo::AddMul(acc,b[i],temp[k-i]);
       
       for(ulen i=k+1; i<N ;i++) UnitAlgo::SubMul(acc,b[i],temp[N+k-i]);
       
       a[k]=acc;
      }
   }
  
  static void SqConvolution(Unit *restrict a,const Unit *b,unsigned n,Unit *restrict)
   {
    ulen N=ulen(1)<<n;
    
    for(ulen k=0; k<N ;k++)
      {
       Unit acc;
       
       UnitAlgo::Null(acc);
       
       ulen k2=((k+1)>>1);
       
       for(ulen i=0; i<k2 ;i++) UnitAlgo::AddMul2(acc,b[i],b[k-i]);
       
       if( (k&1)==0 ) UnitAlgo::AddSq(acc,b[k2]);
       
       k2+=(N>>1);
       
       for(ulen i=k+1; i<k2 ;i++) UnitAlgo::SubMul2(acc,b[i],b[N+k-i]);
       
       if( (k&1)==0 ) UnitAlgo::SubSq(acc,b[k2]);
       
       a[k]=acc;
      }
   }
 };

/* struct ConvolutionUnitAlgoBase<T> */

template <class T> 
struct ConvolutionUnitAlgoBase
 {
  static void Null(T &c) { c=0; }
  
  static void Neg(T &c,const T &a) { c=-a; }
  
  static void Add(T &c,const T &b,const T &a) { c=b+a; }
  
  static void Sub(T &c,const T &b,const T &a) { c=b-a; }
  
  static void Mul(T &c,const T &b,const T &a) { c=b*a; }
  
  static void AddMul(T &c,const T &b,const T &a) { c+=b*a; }
  
  static void SubMul(T &c,const T &b,const T &a) { c-=b*a; }

  static void AddMul2(T &c,const T &b,const T &a) { c+=2*b*a; }
  
  static void SubMul2(T &c,const T &b,const T &a) { c-=2*b*a; }
  
  static void AddSq(T &c,const T &b) { c+=b*b; }
  
  static void SubSq(T &c,const T &b) { c-=b*b; }
  
  static void Add(T &c,const T &a) { c+=a; }

  static void Sub(T &c,const T &a) { c-=a; }
  
  template <class S>
  static void Set(T &c,const S &a) { c=a; }
 };

/* struct RotFFT<Algo> */

template <class Algo> 
struct RotFFT
 {
  typedef typename Algo::Unit Unit;
   
  static void Down(unsigned n,unsigned m,Unit *restrict buf,Unit *restrict temp) // n>=m , buf[2^(n+m)] , temp[2^n]
   {
    unsigned shift=n-m;
    ulen N=ulen(1)<<n;
    ulen M=ulen(1)<<m;
    
    {
     Unit *ptr=buf+N;
    
     for(ulen k=1; k<M ;k++,ptr+=N)
       {
        Algo::NegRotate(ptr,N,k<<shift,temp);
       }
    } 
    
    for(ulen P=1; M>1 ;P<<=1)
      {
       M>>=1;
       shift++;
    
       Unit *ptr=buf;
       ulen L=M<<n;
       
       for(ulen cnt=P; cnt ;cnt--)
         {
          Algo::AddSub(ptr,ptr+L,L);
          
          ptr+=L+N;
          
          for(ulen k=1; k<M ;k++,ptr+=N)
            {
             Algo::NegRotate(ptr,N,k<<shift,temp);
            }
         }
      }
   }
  
  static void Up(unsigned n,unsigned m,Unit *restrict buf,Unit *restrict temp) // n>=m , buf[2^(n+m)] , temp[2^n] 
   {
    unsigned shift=n;
    ulen N=ulen(1)<<n;
    ulen M=1;
    
    for(ulen P=ulen(1)<<m; P>1 ;)
      {
       P>>=1;
       
       Unit *ptr=buf;
       ulen L=M<<n;
       
       for(ulen cnt=P; cnt ;cnt--)
         {
          ptr+=L+N;
          
          for(ulen k=1; k<M ;k++,ptr+=N)
            {
             Algo::NegRotateRev(ptr,N,k<<shift,temp);
            }
          
          Algo::AddSub(ptr-2*L,ptr-L,L);
         }
       
       M<<=1;
       shift--;
      }
    
    {
     Unit *ptr=buf+N;
    
     for(ulen k=1; k<M ;k++,ptr+=N)
       {
        Algo::NegRotateRev(ptr,N,k<<shift,temp);
       }
    }
   }
 };

/* struct FastConvolution<Algo> */

template <class Algo> 
struct FastConvolution
 {
  typedef typename Algo::Unit Unit;
  
  static void Set(const Unit *s,unsigned n,unsigned m,Unit *restrict a) // s[2^(n+m)] , a[2^(n+m+1)]
   {
    ulen M=ulen(1)<<m;
    ulen N=ulen(1)<<n;
    
    for(; M ;M--,s+=N,a+=N)
      {
       Algo::Set(a,s,N);
       
       a+=N;
       
       Algo::Null(a,N);
      }
   }

  template <class S>
  static void Set(const S *s,ulen ns,unsigned n,unsigned m,Unit *restrict a) // ns<=2^(n+m) , a[2^(n+m+1)]
   {
    ulen M=ulen(1)<<m;
    ulen N=ulen(1)<<n;
    
    ulen count1=ns>>n;
    ulen count2=ns&(N-1);
    
    for(ulen cnt=count1; cnt ;cnt--,s+=N,a+=N)
      {
       Algo::Set(a,s,N);
       
       a+=N;
       
       Algo::Null(a,N);
      }
    
    Algo::Set(a,s,count2);
    
    Algo::Null(a+count2,((M-count1)<<(n+1))-count2);
   }
  
  static void Get(Unit *s,unsigned n,unsigned m,const Unit *a) // s[2^(n+m)] , a[2^(n+m+1)]
   {
    ulen M=ulen(1)<<m;
    ulen N=ulen(1)<<n;
    ulen L=ulen(1)<<(n+m+1);
    
    Algo::Sub(s,a,a+(L-N),N);

    a+=N;
    s+=N;
    M--;
    
    for(; M ;M--,s+=N,a+=2*N)
      {
       Algo::Add(s,a,a+N,N);
      }
   }
  
  template <class Func>
  static typename Func::RetType Feed(Func func,ulen K,unsigned d,Unit *a) // K<=2^d , a[2^(d+1)]
   {
    unsigned n=d/2;
    unsigned m=d-n;
    
    ulen N=ulen(1)<<n;
    ulen L=ulen(1)<<(n+m+1);
    
    ulen count1=K>>n;
    ulen count2=K&(N-1);
    
    if( count1 )
      {
       Algo::Sub(a,a+(L-N),N);
       func(a,N);

       a+=N;
       count1--;
       
       for(; count1 ;count1--,a+=2*N)
         {
          Algo::Add(a,a+N,N);
          func(a,N);
         }
       
       if( count2 )
        {
         Algo::Add(a,a+N,count2);
         func(a,count2);
        }
      }
    else if( count2 )
      {
       Algo::Sub(a,a+(L-N),count2);
       func(a,count2);
      }
    
    return func.ret();
   }
  
  template <class S>
  static void SetDown(const S *s,ulen ns,unsigned d,Unit *restrict a,Unit *restrict temp) // ns<=2^d
   {
    unsigned n=d/2;
    unsigned m=d-n;
    
    Set(s,ns,n,m,a);
    
    RotFFT<Algo>::Down(n+1,m,a,temp);
   }
  
  static void Convolution(Unit *restrict sa,const Unit *restrict sb,unsigned d,unsigned d0,Unit *restrict a,Unit *restrict b,Unit *restrict temp)
   {
    unsigned n=d/2;
    unsigned m=d-n;
    
    Set(sa,n,m,a);
    Set(sb,n,m,b);
    
    RotFFT<Algo>::Down(n+1,m,a,temp);
    RotFFT<Algo>::Down(n+1,m,b,temp);
    
    MulDowned(d,d0,a,b,temp);
    
    Get(sa,n,m,a);
   }
  
  static void SqConvolution(Unit *restrict sa,const Unit *restrict sb,unsigned d,unsigned d0,Unit *restrict a,Unit *restrict b,Unit *restrict temp)
   {
    unsigned n=d/2;
    unsigned m=d-n;
    
    Set(sb,n,m,b);
    
    RotFFT<Algo>::Down(n+1,m,b,temp);
    
    SqDowned(d,d0,a,b,temp);
    
    Get(sa,n,m,a);
   }
  
  static void MulDowned(unsigned d,unsigned d0,Unit *restrict a,Unit *restrict b,Unit *restrict temp)
   {
    unsigned n=d/2;
    unsigned m=d-n;
    
    unsigned next_d=n+1;

    ulen M=ulen(1)<<m;
    ulen N=ulen(1)<<next_d;
    
    if( next_d>d0 )
      {
       ulen L=ulen(1)<<(d+1);
       
       Unit *ptr_a=a;
       Unit *ptr_b=b;
       
       Unit *next_a=a+L;
       Unit *next_b=b+L;
       
       for(; M ;M--,ptr_a+=N,ptr_b+=N)
         {
          Convolution(ptr_a,ptr_b,next_d,d0,next_a,next_b,temp); // next_d>d0
         }
      }
    else
      {
       Unit *ptr_a=a;
       Unit *ptr_b=b;
       
       for(; M ;M--,ptr_a+=N,ptr_b+=N)
         {
          Algo::Convolution(ptr_a,ptr_b,next_d,temp); // next_d<=d0
         }
      }
    
    RotFFT<Algo>::Up(n+1,m,a,temp);
   }
  
  static void SqDowned(unsigned d,unsigned d0,Unit *restrict a,Unit *restrict b,Unit *restrict temp)
   {
    unsigned n=d/2;
    unsigned m=d-n;
    
    unsigned next_d=n+1;

    ulen M=ulen(1)<<m;
    ulen N=ulen(1)<<next_d;
    
    if( next_d>d0 )
      {
       ulen L=ulen(1)<<(d+1);
       
       Unit *ptr_a=a;
       Unit *ptr_b=b;
       
       Unit *next_a=a+L;
       Unit *next_b=b+L;
       
       for(; M ;M--,ptr_a+=N,ptr_b+=N)
         {
          SqConvolution(ptr_a,ptr_b,next_d,d0,next_a,next_b,temp); // next_d>d0
         }
      }
    else
      {
       Unit *ptr_a=a;
       Unit *ptr_b=b;
       
       for(; M ;M--,ptr_a+=N,ptr_b+=N)
         {
          Algo::SqConvolution(ptr_a,ptr_b,next_d,temp); // next_d<=d0
         }
      }
    
    RotFFT<Algo>::Up(n+1,m,a,temp);
   }
 };

/* struct ExtAlgo */

#if 0

struct ExtAlgo
 {
  typedef ??? Unit;
  
  static const unsigned UnitBits = ??? ;
  
  // tunning
  
  static const unsigned D0 = 4 ; // >=2
  
  // Ext types
  
  static void Null(Unit *a,ulen na);
  
  static void UNeg(Unit *a,ulen na);
  
  static Unit UAdd(Unit *restrict a,const Unit *b,ulen nab);
  
  static void USub(Unit *restrict a,const Unit *b,ulen nab);
  
  static void UMulLo(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc);
  
  static void USqLo(Unit *restrict c,const Unit *a,ulen nac);
  
  static void URShift(Unit *a,ulen na,unsigned shift);
  
  template <unsigned L> // L>2 , small
  struct Ext
   {
    Unit data[L];
    
    typedef Ext<L> Type;
    
    static const unsigned ExtraBits = (L-2)*UnitBits ;
    
    void null() { Null(data,L); }
    
    void neg() { UNeg(data,L); }
    
    Unit add(const Unit *b) { return UAdd(data,b,L); }
    
    void sub(const Unit *b) { USub(data,b,L); }
    
    void mul(const Unit *a,const Unit *b) { UMulLo(data,a,b,L); }
    
    void sq(const Unit *a) { USqLo(data,a,L); }
    
    void shr(unsigned shift) { URShift(data,L,shift); }
    
    void set(Unit a) { data[0]=a; Null(data+1,L-1); }
    
    Unit push(Unit c)
     {
      Unit ret=data[0];
      
      for(unsigned i=0; i<L-1 ;i++) data[i]=data[i+1];
      
      data[L-1]=c;
      
      return ret;
     }
    
    void addpush(Unit &dst,Unit c)
     {
      bool carry;
      
      {
       Unit lo=data[0];
       Unit d=dst+lo;
      
       dst=d;
       carry=(d<lo);
      }
      
      for(unsigned i=0; i<L-1 ;i++) 
        {
         Unit d=data[i+1]+carry;
         
         data[i]=d;
         carry=(d<carry);
        }
      
      data[L-1]=c+carry;
     }
    
    struct UnitAlgo
     {
      static void Null(Type &c) { c.null(); }
      
      static void Neg(Type &c,const Type &a) 
       {
        c=a;
        
        c.neg();
       }
      
      static void Add(Type &c,const Type &b,const Type &a) 
       { 
        c=b;
        
        c.add(a.data);
       }
      
      static void Sub(Type &c,const Type &b,const Type &a) 
       { 
        c=b;
        
        c.sub(a.data);
       }
      
      static void Mul(Type &c,const Type &b,const Type &a) 
       { 
        c.mul(b.data,a.data); 
       }
      
      static void AddMul(Type &c,const Type &b,const Type &a) 
       {
        Type d;
        
        d.mul(b.data,a.data);
        
        c.add(d.data); 
       }
      
      static void SubMul(Type &c,const Type &b,const Type &a) 
       { 
        Type d;
        
        d.mul(b.data,a.data);
        
        c.sub(d.data); 
       }

      static void AddMul2(Type &c,const Type &b,const Type &a)
       {
        Type d;
        
        d.mul(b.data,a.data);
        
        c.add(d.data); 
        c.add(d.data); 
       }
      
      static void SubMul2(Type &c,const Type &b,const Type &a)
       {
        Type d;
        
        d.mul(b.data,a.data);
        
        c.sub(d.data); 
        c.sub(d.data); 
       }
      
      static void AddSq(Type &c,const Type &b)
       {
        Type d;
        
        d.sq(b.data);
        
        c.add(d.data); 
       }
      
      static void SubSq(Type &c,const Type &b)
       {
        Type d;
        
        d.sq(b.data);
        
        c.sub(d.data); 
       }
      
      static void Add(Type &c,const Type &a) { c.add(a.data); }

      static void Sub(Type &c,const Type &a) { c.sub(a.data); }
      
      static void Set(Type &c,const Type &a) { c=a; }
      
      static void Set(Type &c,Unit a) { c.set(a); }
     };
    
    typedef ConvolutionAlgoBase<Type,UnitAlgo> ConvolutionAlgo;
    
    struct Acc
     {
      Unit *dst;
      unsigned shift;
      
      Type acc;
      
      Acc(Unit *dst_,unsigned shift_)
       : dst(dst_),
         shift(shift_)
       {
        acc.null();
       }
      
      void push(Type e)
       {
        e.shr(shift);
        
        Unit c=acc.add(e.data);
        
        *(dst++)=acc.push(c);
       }
      
      void operator () (const Type *e,ulen n) { for(; n ;n--,e++) push(*e); }
      
      typedef void RetType;
      
      RetType ret() {} 
     };
    
    struct AddAcc
     {
      Unit *dst;
      unsigned shift;
      
      Type acc;
      
      AddAcc(Unit *dst_,unsigned shift_)
       : dst(dst_),
         shift(shift_)
       {
        acc.null();
       }
      
      void push(Type e)
       {
        e.shr(shift);
        
        Unit c=acc.add(e.data);
        
        acc.addpush(*(dst++),c);
       }
      
      void operator () (const Type *e,ulen n) { for(; n ;n--,e++) push(*e); }
      
      typedef Unit RetType;
      
      RetType ret() { return acc.data[0]; } 
     };
   };
  
  typedef Ext<3> Ext3;
  typedef Ext<4> Ext4;
 };

#endif

/* struct ConvolutionExtAlgoBase<Algo,Ext> */ 

template <class Algo,class Ext> 
struct ConvolutionExtAlgoBase
 {
  typedef typename Algo::Unit Unit;
  
  static const unsigned UnitBits = Algo::UnitBits ;
  
  // tunning
  
  static const unsigned D0 = 4 ;
  
  // Ext types
  
  template <class Type>
  struct UnitAlgoBase
   {
    static void Null(Type &c) { c.null(); }
    
    static void Neg(Type &c,const Type &a) 
     {
      c=a;
      
      c.neg();
     }
    
    static void Add(Type &c,const Type &b,const Type &a) 
     { 
      c=b;
      
      c.add(a.data);
     }
    
    static void Sub(Type &c,const Type &b,const Type &a) 
     { 
      c=b;
      
      c.sub(a.data);
     }
    
    static void Mul(Type &c,const Type &b,const Type &a) 
     { 
      c.mul(b.data,a.data); 
     }
    
    static void AddMul(Type &c,const Type &b,const Type &a) 
     {
      Type d;
      
      d.mul(b.data,a.data);
      
      c.add(d.data); 
     }
    
    static void SubMul(Type &c,const Type &b,const Type &a) 
     { 
      Type d;
      
      d.mul(b.data,a.data);
      
      c.sub(d.data); 
     }

    static void AddMul2(Type &c,const Type &b,const Type &a)
     {
      Type d;
      
      d.mul(b.data,a.data);
      
      c.add(d.data); 
      c.add(d.data); 
     }
    
    static void SubMul2(Type &c,const Type &b,const Type &a)
     {
      Type d;
      
      d.mul(b.data,a.data);
      
      c.sub(d.data); 
      c.sub(d.data); 
     }
    
    static void AddSq(Type &c,const Type &b)
     {
      Type d;
      
      d.sq(b.data);
      
      c.add(d.data); 
     }
    
    static void SubSq(Type &c,const Type &b)
     {
      Type d;
      
      d.sq(b.data);
      
      c.sub(d.data); 
     }
    
    static void Add(Type &c,const Type &a) { c.add(a.data); }

    static void Sub(Type &c,const Type &a) { c.sub(a.data); }
    
    static void Set(Type &c,const Type &a) { c=a; }
    
    static void Set(Type &c,Unit a) { c.set(a); }
   };
  
  template <class Type>
  struct AccBase
   {
    Unit *dst;
    unsigned shift;
    
    Type acc;
    
    AccBase(Unit *dst_,unsigned shift_)
     : dst(dst_),
       shift(shift_)
     {
      acc.null();
     }
    
    void push(Type e)
     {
      e.shr(shift);
      
      Unit c=acc.add(e.data);
      
      *(dst++)=acc.push(c);
     }
    
    void operator () (const Type *e,ulen n) { for(; n ;n--,e++) push(*e); }
    
    typedef void RetType;
    
    RetType ret() {} 
   };
  
  template <class Type>
  struct AddAccBase
   {
    Unit *dst;
    unsigned shift;
    
    Type acc;
    
    AddAccBase(Unit *dst_,unsigned shift_)
     : dst(dst_),
       shift(shift_)
     {
      acc.null();
     }
    
    void push(Type e)
     {
      e.shr(shift);
      
      Unit c=acc.add(e.data);
      
      acc.addpush(*(dst++),c);
     }
    
    void operator () (const Type *e,ulen n) { for(; n ;n--,e++) push(*e); }
    
    typedef Unit RetType;
    
    RetType ret() { return acc.data[0]; } 
   };
  
  struct Ext3
   {
    Unit data[3];
    
    static const unsigned ExtraBits = UnitBits ;
    
    void null() 
     { 
      data[0]=0;
      data[1]=0;
      data[2]=0;
     }
    
    void neg() { Ext::UNeg3(data); }
    
    Unit add(const Unit *b) { return Ext::UAdd3(data,b); }
    
    void sub(const Unit *b) { Ext::USub3(data,b); }
    
    void mul(const Unit *a,const Unit *b) { Ext::UMulLo3(data,a,b); }
    
    void sq(const Unit *a) { Ext::USqLo3(data,a); }
    
    void shr(unsigned shift) { Ext::URShift3(data,shift); }
    
    void set(Unit a) 
     { 
      data[0]=a; 
      data[1]=0;
      data[2]=0;
     }
    
    Unit push(Unit c)
     {
      Unit ret=data[0];
      
      data[0]=data[1];
      data[1]=data[2];
      data[2]=c;
      
      return ret;
     }
    
    void addpush(Unit &dst,Unit c)
     {
      bool carry;
      
      {
       Unit lo=data[0];
       Unit d=dst+lo;
      
       dst=d;
       carry=(d<lo);
      }
      
      {
       Unit d=data[1]+carry;
         
       data[0]=d;
       carry=(d<carry);
      }
      
      {
       Unit d=data[2]+carry;
         
       data[1]=d;
       carry=(d<carry);
      }
      
      data[2]=c+carry;
     }
    
    typedef UnitAlgoBase<Ext3> UnitAlgo;
    
    typedef ConvolutionAlgoBase<Ext3,UnitAlgo> ConvolutionAlgo;
    
    typedef AccBase<Ext3> Acc;
    
    typedef AddAccBase<Ext3> AddAcc;
   };
  
  struct Ext4
   {
    Unit data[4];
    
    static const unsigned ExtraBits = 2*UnitBits ;
    
    void null() 
     {
      data[0]=0;
      data[1]=0;
      data[2]=0;
      data[3]=0;
     }
    
    void neg() { Ext::UNeg4(data); }
    
    Unit add(const Unit *b) { return Ext::UAdd4(data,b); }
    
    void sub(const Unit *b) { Ext::USub4(data,b); }
    
    void mul(const Unit *a,const Unit *b) { Ext::UMulLo4(data,a,b); }
    
    void sq(const Unit *a) { Ext::USqLo4(data,a); }
    
    void shr(unsigned shift) { Ext::URShift4(data,shift); }
    
    void set(Unit a)
     {
      data[0]=a;
      data[1]=0;
      data[2]=0;
      data[3]=0;
     }
    
    Unit push(Unit c)
     {
      Unit ret=data[0];
      
      data[0]=data[1];
      data[1]=data[2];
      data[2]=data[3];
      data[3]=c;
      
      return ret;
     }
    
    void addpush(Unit &dst,Unit c)
     {
      bool carry;
      
      {
       Unit lo=data[0];
       Unit d=dst+lo;
      
       dst=d;
       carry=(d<lo);
      }
      
      {
       Unit d=data[1]+carry;
         
       data[0]=d;
       carry=(d<carry);
      }
      
      {
       Unit d=data[2]+carry;
         
       data[1]=d;
       carry=(d<carry);
      }
      
      {
       Unit d=data[3]+carry;
         
       data[2]=d;
       carry=(d<carry);
      }
      
      data[3]=c+carry;
     }
    
    typedef UnitAlgoBase<Ext4> UnitAlgo; 
    
    typedef ConvolutionAlgoBase<Ext4,UnitAlgo> ConvolutionAlgo;
    
    typedef AccBase<Ext4> Acc;
    
    typedef AddAccBase<Ext4> AddAcc;
   };
 };

/* struct ConvolutionMul<ExtAlgo> */

template <class ExtAlgo>
struct ConvolutionMul
 {
  typedef typename ExtAlgo::Unit Unit;
  typedef typename ExtAlgo::Ext3 Ext3;
  typedef typename ExtAlgo::Ext4 Ext4;
  
  template <class Ext>
  static void DownA(unsigned d,const Unit *a,ulen na,Ext *ext,ulen arg_len) // na<=2^d
   {
    typedef FastConvolution<typename Ext::ConvolutionAlgo> Fast;
    
    Ext *aext=ext;
    Ext *bext=aext+arg_len;
    Ext *temp=bext+arg_len;

    Fast::SetDown(a,na,d,aext,temp);
   }
  
  template <class Ext>
  static void DownB(unsigned d,const Unit *b,ulen nb,Ext *ext,ulen arg_len) // nb<=2^d
   {
    typedef FastConvolution<typename Ext::ConvolutionAlgo> Fast;
    
    Ext *aext=ext;
    Ext *bext=aext+arg_len;
    Ext *temp=bext+arg_len;

    Fast::SetDown(b,nb,d,bext,temp);
   }
  
  template <class Ext>
  static void MulDowned(Unit *c,ulen nc,unsigned d,unsigned d0,Ext *ext,ulen arg_len,unsigned shift) // nc<=2^d
   {
    typedef FastConvolution<typename Ext::ConvolutionAlgo> Fast;
    
    Ext *aext=ext;
    Ext *bext=aext+arg_len;
    Ext *temp=bext+arg_len;
    
    Fast::MulDowned(d,d0,bext,aext,temp);
    
    typedef typename Ext::Acc Acc;

    Fast::Feed(Acc(c,shift),nc,d,bext);
   }
  
  template <class Ext>
  static Unit MacDowned(Unit *c,ulen nc,unsigned d,unsigned d0,Ext *ext,ulen arg_len,unsigned shift) // nc<=2^d
   {
    typedef FastConvolution<typename Ext::ConvolutionAlgo> Fast;
    
    Ext *aext=ext;
    Ext *bext=aext+arg_len;
    Ext *temp=bext+arg_len;
    
    Fast::MulDowned(d,d0,bext,aext,temp);
    
    typedef typename Ext::AddAcc AddAcc;

    return Fast::Feed(AddAcc(c,shift),nc,d,bext);
   }
  
  template <class Ext>
  static void SqDowned(Unit *c,ulen nc,unsigned d,unsigned d0,Ext *ext,ulen arg_len,unsigned shift) // nc<=2^d
   {
    typedef FastConvolution<typename Ext::ConvolutionAlgo> Fast;
    
    Ext *aext=ext;
    Ext *bext=aext+arg_len;
    Ext *temp=bext+arg_len;
    
    Fast::SqDowned(d,d0,bext,aext,temp);
    
    typedef typename Ext::Acc Acc;

    Fast::Feed(Acc(c,shift),nc,d,bext);
   }
  
  class Engine : NoCopy
   {
     unsigned d;
     FastConvolutionLens lens;
     
     DynArray<Ext3> array3;
     DynArray<Ext4> array4;
     
     Ext3 *ext3;
     Ext4 *ext4;
     
    private:
     
     ulen setD(unsigned d_) // return total
      {
       if( d_>=Meta::UIntBits<ulen>::Ret-1 ) GuardFastMulOverlen(d_);
       
       d=d_;
       lens=FastConvolutionLens(d,ExtAlgo::D0);
       
       ulen total=2*lens.arg_len;
       
       if( total<lens.arg_len ) GuardFastMulOverlen(d);
       
       total+=lens.temp_len;
       
       if( total<lens.temp_len ) GuardFastMulOverlen(d);
       
       return total;
      }
     
    public:
     
     explicit Engine(unsigned d_) // d_>ExtAlgo::D0
      : ext3(0),ext4(0)
      {
       ulen total=setD(d_);
       
       unsigned extra=d+lens.shift;
       
       if( extra<=Ext3::ExtraBits )
         {
          ext3=array3.extend_raw(total).ptr;
         }
       else if( extra<=Ext4::ExtraBits )
         {
          ext4=array4.extend_raw(total).ptr;
         }
       else
         {
          GuardFastMulOverbits(d,extra);
         }
      }
     
     ~Engine() {}
     
     void reset(unsigned d_) // d_>ExtAlgo::D0
      {
       ulen total=setD(d_);
       
       unsigned extra=d+lens.shift;
       
       if( extra<=Ext3::ExtraBits )
         {
          if( ext3 )
            {
             if( total>array3.getLen() )
               {
                array3.erase();
                ext3=0;
                
                ext3=array3.extend_raw(total).ptr;
               }
            }
          else
            {
             array4.erase();
             ext4=0;
             
             ext3=array3.extend_raw(total).ptr;
            }
         }
       else if( extra<=Ext4::ExtraBits )
         {
          if( ext4 )
            {
             if( total>array4.getLen() )
               {
                array4.erase();
                ext4=0;
                
                ext4=array4.extend_raw(total).ptr;
               }
            }
          else
            {
             array3.erase();
             ext3=0;
             
             ext4=array4.extend_raw(total).ptr;
            }
         }
       else
         {
          GuardFastMulOverbits(d,extra);
         }
      }
     
     void downA(const Unit *a,ulen na) // na<=2^d
      {
       if( ext3 )
         {
          DownA(d,a,na,ext3,lens.arg_len);
         }
       else
         {
          DownA(d,a,na,ext4,lens.arg_len);
         }
      }
     
     void downB(const Unit *b,ulen nb) // nb<=2^d
      {
       if( ext3 )
         {
          DownB(d,b,nb,ext3,lens.arg_len);
         }
       else
         {
          DownB(d,b,nb,ext4,lens.arg_len);
         }
      }
     
     void downA(const Unit *a) // na==2^(d-1)
      {
       downA(a,ulen(1)<<(d-1));
      }
     
     void downB(const Unit *b) // nb==2^(d-1)
      {
       downB(b,ulen(1)<<(d-1));
      }
     
     void mul_lo(Unit *c,ulen nc) // nc<=2^d
      {
       if( ext3 )
         {
          MulDowned(c,nc,d,ExtAlgo::D0,ext3,lens.arg_len,lens.shift);
         }
       else
         {
          MulDowned(c,nc,d,ExtAlgo::D0,ext4,lens.arg_len,lens.shift);
         }
      }
     
     void mul(Unit *c) // nc==2^d
      {
       mul_lo(c,ulen(1)<<d);
      }
     
     Unit mac_lo(Unit *c,ulen nc) // nc<=2^d
      {
       if( ext3 )
         {
          return MacDowned(c,nc,d,ExtAlgo::D0,ext3,lens.arg_len,lens.shift);
         }
       else
         {
          return MacDowned(c,nc,d,ExtAlgo::D0,ext4,lens.arg_len,lens.shift);
         }
      }
     
     Unit mac(Unit *c) // nc==2^d
      {
       return mac_lo(c,ulen(1)<<d);
      }
     
     void sq_lo(Unit *c,ulen nc) // nc<=2^d
      {
       if( ext3 )
         {
          SqDowned(c,nc,d,ExtAlgo::D0,ext3,lens.arg_len,lens.shift);
         }
       else
         {
          SqDowned(c,nc,d,ExtAlgo::D0,ext4,lens.arg_len,lens.shift);
         }
      }
     
     void sq(Unit *c) // nc==2^d
      {
       sq_lo(c,ulen(1)<<d);
      }
   };
 };

} // namespace Math
} // namespace CCore
 
#endif
 

