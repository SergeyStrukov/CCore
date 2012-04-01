/* IntegerSlowAlgo.h */ 
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

#ifndef CCore_inc_math_IntegerSlowAlgo_h
#define CCore_inc_math_IntegerSlowAlgo_h
 
#include <CCore/inc/Cmp.h>
#include <CCore/inc/Swap.h>

namespace CCore {
namespace Math {

/* classes */

template <class UInt,unsigned Shift> struct RShiftConst_shift;

template <class UInt> struct RShiftConst_zero;

template <class UInt,class DUInt=typename Meta::DoubleUInt<UInt>::Ret> struct IntegerSlowMulAlgo;

template <class UInt> struct IntegerSlowAlgo;

/* struct RShiftConst_shift<UInt,unsigned Shift> */

template <class UInt,unsigned Shift>
struct RShiftConst_shift
 {
  static UInt Do(UInt val) { return UInt( val>>Shift ); }
 };

/* struct RShiftConst_zero<UInt> */

template <class UInt>
struct RShiftConst_zero
 {
  static UInt Do(UInt) { return 0; }
 };

/* type RShiftConst<UInt,unsigned Shift,unsigned UIntBits> */

template <class UInt,unsigned Shift,unsigned UIntBits=Meta::UIntBits<UInt>::Ret>
using RShiftConst = Meta::Select<( Shift<UIntBits ), RShiftConst_shift<UInt,Shift> , RShiftConst_zero<UInt> > ;

/* struct IntegerSlowMulAlgo<UInt,DUInt> */  
 
template <class UInt,class DUInt> 
struct IntegerSlowMulAlgo
 {
  struct DoubleMul
   {
    UInt lo;
    UInt hi;
    
    DoubleMul(UInt a,UInt b);
   };
  
  static UInt DoubleUDiv(UInt hi,UInt lo,UInt den); // hi<den 
 };

template <class UInt,class DUInt> 
IntegerSlowMulAlgo<UInt,DUInt>::DoubleMul::DoubleMul(UInt a,UInt b)
 {
  const unsigned Bits = Meta::UIntBits<UInt>::Ret ;

  DUInt c=DUInt(a)*b;
  
  lo=UInt(c);
  hi=UInt(c>>Bits);
 }

template <class UInt,class DUInt> 
UInt IntegerSlowMulAlgo<UInt,DUInt>::DoubleUDiv(UInt hi,UInt lo,UInt den)
 {
  const unsigned Bits = Meta::UIntBits<UInt>::Ret ;

  DUInt a=(DUInt(hi)<<Bits)|lo; 
  
  return UInt(a/den);
 }

/* struct IntegerSlowMulAlgo<UInt,void> */

template <class UInt> 
struct IntegerSlowMulAlgo<UInt,void>
 {
  struct DoubleMul
   {
    UInt lo;
    UInt hi;
    
    DoubleMul(UInt a,UInt b);
   };
  
  static UInt Inv(UInt den);
  
  static UInt DoubleUDiv(UInt hi,UInt lo,UInt den); // hi<den 
 };

template <class UInt> 
IntegerSlowMulAlgo<UInt,void>::DoubleMul::DoubleMul(UInt a,UInt b)
 {
  const unsigned Bits = Meta::UIntBits<UInt>::Ret ;

  static_assert( (Bits%2)==0 ,"CCore::Math::IntegerSlowMulAlgo<UInt,void> : odd bits number");
  
  const unsigned Bits2 = Bits/2 ;
  
  const UInt LoMask=UInt( UInt(-1)>>Bits2 );
  
  UInt a1=UInt( a>>Bits2 );
  UInt a0=UInt( a&LoMask );
  
  UInt b1=UInt( b>>Bits2 );
  UInt b0=UInt( b&LoMask );
  
  UInt p0=a0*b0;
  UInt p1=a0*b1;
  UInt p2=a1*b0;
  UInt p3=a1*b1;
  
  p1+=p2;
  
  p3+=UInt( UInt(p1<p2)<<Bits2 );
  
  UInt p1hi=UInt( p1<<Bits2 );
  
  p0+=p1hi;
  p3+=UInt( p1>>Bits2 );
  
  p3+=UInt( p0<p1hi );
  
  hi=p3;
  lo=p0;
 }

template <class UInt> 
UInt IntegerSlowMulAlgo<UInt,void>::Inv(UInt den)
 {
  const unsigned Bits = Meta::UIntBits<UInt>::Ret ;

  static_assert( (Bits%2)==0 ,"CCore::Math::IntegerSlowMulAlgo<UInt,void> : odd bit number");
  
  const unsigned Bits2 = Bits/2 ;
  
  const UInt MSBit = UInt(1)<<(Bits-1) ;
  
  const UInt M2 = UInt(1)<<Bits2 ;

  if( den<=MSBit ) return 0;
  
  UInt a;
  UInt d;
  
  // 1
  {
   UInt b = (den>>Bits2) + 1 ;

   a = 1 + UInt(-b)/b ;

   DoubleMul p(a,den);
   
   if( p.lo )
     {
      p.lo=-p.lo;
      p.hi=M2-1-p.hi;
     }
   else
     {
      p.hi=M2-p.hi;
     }

   while( p.hi || p.lo>=den )
     {
      a++;
      
      p.hi-=(p.lo<den);
      p.lo-=den;
     }
   
   d=p.lo;
  }
  
  // 2
  {
   UInt e = (a<<Bits2) + DoubleMul(a,d).hi ;
   
   DoubleMul p(e,den);
   
   p.hi+=den;
   
   if( p.lo )
     {
      p.lo=-p.lo;
      p.hi=~p.hi;
     }
   else
     {
      p.hi=-p.hi;
     }
   
   return e + ( p.hi || p.lo>=den ) ;
  }
 }

template <class UInt> 
UInt IntegerSlowMulAlgo<UInt,void>::DoubleUDiv(UInt hi,UInt lo,UInt den)
 {
  // 1
  {
   if( unsigned n=IntegerSlowAlgo<UInt>::CountZeroMSB(den) )
     {
      den<<=n;
      hi=IntegerSlowAlgo<UInt>::LShift(hi,lo,n);
      lo<<=n;
     }
  }
  
  // 2
  {
   if( UInt e=Inv(den) )
     {
      UInt ret=hi+DoubleMul(hi,e).hi;
      
      DoubleMul p(ret,den);
      
      bool c=(lo<p.lo);
      
      lo-=p.lo;
      hi-=p.hi+c;
      
      for(;;)
        {
         bool c=(lo<den);
         
         if( hi<c ) return ret;
         
         lo-=den;
         hi-=c;
         
         ret++;
        }
     }
   else
     {
      return IntegerSlowAlgo<UInt>::LShift(hi,lo,1);
     }
  }
 }

/* struct IntegerSlowAlgo<UInt> */ 

template <class UInt> 
struct IntegerSlowAlgo : IntegerSlowMulAlgo<UInt>
 {
  typedef typename IntegerSlowMulAlgo<UInt>::DoubleMul DoubleMul;
  
  // types and consts
  
  typedef UInt Unit;
  
  static const unsigned UnitBits = Meta::UIntBits<Unit>::Ret ;

  static const Unit MaxUnit = Unit(-1) ;
  
  static const Unit MSBit = Unit( MaxUnit^(MaxUnit>>1) );
  
  // functions
  
  static Unit SignExt(Unit a);
   
  static Unit SignExt(const Unit *a,ulen na);
  
  static CmpResult SignCmp(Unit a,Unit b);
  
  static unsigned CountZeroMSB(Unit a);
  
  static unsigned CountZeroLSB(Unit a);
   
  // private functions
  
  static Unit/* c */ Add(Unit &b,Unit a,Unit carry); // carry = 0,1 
   
  static Unit/* c */ Sub(Unit &b,Unit a,Unit carry); // carry = 0,1 
  
  static Unit/* c */ RevSub(Unit &b,Unit a,Unit carry); // carry = 0,1
   
  static Unit LShift(Unit hi,Unit lo,unsigned shift); // 0<shift<UnitBits
 
  static Unit RShift(Unit hi,Unit lo,unsigned shift); // 0<shift<UnitBits
  
  // private operators
  
  static CmpResult UCmp(Unit a,Unit b);
  
  static CmpResult UCmp_(const Unit *a,ulen na,const Unit *b,ulen nb); // na>=nb
  
  static CmpResult Cmp_(const Unit *a,ulen na,const Unit *b,ulen nb); // na>=nb
  
  // const operators
  
  static CmpResult USign(const Unit *a,ulen na);
  
  static CmpResult Sign(const Unit *a,ulen na);
  
  static CmpResult UCmp(const Unit *a,const Unit *b,ulen nab);
  
  static CmpResult UCmp(const Unit *a,ulen na,const Unit *b,ulen nb);
  
  static CmpResult Cmp(const Unit *a,const Unit *b,ulen nab);
  
  static CmpResult Cmp(const Unit *a,ulen na,const Unit *b,ulen nb);
  
  static ulen UNormalize(const Unit *a,ulen na);
  
  static ulen Normalize(const Unit *a,ulen na);
  
  // additive operators
  
  static Unit/* c */ UNeg(Unit *a,ulen na);
  
  static Unit/* msu */ Neg(Unit *a,ulen na);
  
  static Unit/* c */ UAddUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* msu */ AddUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* c */ USubUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* msu */ SubUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* c */ UNegAddUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* msu */ NegAddUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* c */ UAdd(Unit *restrict b,const Unit *a,ulen nab);
  
  static Unit/* msu */ Add(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

  static Unit/* c */ USub(Unit *restrict b,const Unit *a,ulen nab);
  
  static Unit/* msu */ Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na
  
  static Unit/* c */ URevSub(Unit *restrict b,const Unit *a,ulen nab);
  
  static Unit/* msu */ RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na
  
  // shift operators
  
  static Unit/* msu */ ULShift(Unit *a,ulen na,unsigned shift); // 0<shift<UnitBits
  
  static Unit/* msu */ LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift); // 0<shift<UnitBits
  
  static Unit/* msu */ UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits
  
  static Unit/* msu */ ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits
  
  static void URShift(Unit *a,ulen na,unsigned shift); // 0<shift<UnitBits
  
  static void RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift); // 0<shift<UnitBits
  
  static void UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits
  
  static void ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits
  
  // multiplicative operators
  
  struct MulAcc;
  
  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb
  
  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb
  
  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb); // nc<=na+nb
  
  static void USq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na
  
  static void Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb
  
  static void Sq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na
  
  // data functions  

  static void Null(Unit *a,ulen na);

  static void MoveUp(Unit *a,ulen na,ulen delta); // a[na+delta]
  
  static void MoveDown(Unit *a,ulen na,ulen delta); // a[na+delta]
 };
 
 // functions

template <class UInt> 
UInt IntegerSlowAlgo<UInt>::SignExt(Unit a)
 {
  return Unit( -(a>>(UnitBits-1)) );
 }
 
template <class UInt> 
UInt IntegerSlowAlgo<UInt>::SignExt(const Unit *a,ulen na)
 {
  return (na>0)?SignExt(a[na-1]):0;
 }

template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::SignCmp(Unit a,Unit b)
 {
  return UCmp(Unit(a-MSBit),Unit(b-MSBit));
 }

template <class UInt> 
unsigned IntegerSlowAlgo<UInt>::CountZeroMSB(Unit a) 
 {
  if( !a ) return UnitBits;
  
  if( a&MSBit ) return 0;
  
  unsigned ret=0;
  unsigned n=UnitBits;
  
  while( n>=2 )
    {
     unsigned m=n/2;
     
     Unit mask=Unit( Unit(-1)<<(UnitBits-m) );
     
     if( a&mask )
       {
        n=m;
       }
     else
       {
        ret+=m;
        a<<=m;
        n-=m;
       }
    }
    
  return ret;
 }

template <class UInt> 
unsigned IntegerSlowAlgo<UInt>::CountZeroLSB(Unit a)
 {
  if( !a ) return UnitBits;
  
  if( a&1 ) return 0;
  
  unsigned ret=0;
  unsigned n=UnitBits;
  
  while( n>=2 )
    {
     unsigned m=n/2;
     
     Unit mask=(Unit(1)<<m)-1;
     
     if( a&mask )
       {
        n=m;
       }
     else
       {
        ret+=m;
        a>>=m;
        n-=m;
       }
    }
    
  return ret;
 }

 // private functions

template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::Add(Unit &b,Unit a,Unit c) 
 {
  a+=c;
  b+=a;
  
  return (b<a)|(a<c);
 }

template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::Sub(Unit &b,Unit a,Unit c) 
 {
  a+=c;
  
  Unit ret=(b<a)|(a<c);
  
  b-=a;
  
  return ret;
 }

template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::RevSub(Unit &b,Unit a,Unit c) 
 {
  Unit d=b+c;
  Unit ret=(a<d)|(d<c);
  
  b=a-d;
  
  return ret;
 }
 
template <class UInt> 
UInt IntegerSlowAlgo<UInt>::LShift(Unit hi,Unit lo,unsigned shift)
 {
  return Unit( (hi<<shift)|(lo>>(UnitBits-shift)) );
 }

template <class UInt> 
UInt IntegerSlowAlgo<UInt>::RShift(Unit hi,Unit lo,unsigned shift)
 {
  return Unit( (hi<<(UnitBits-shift))|(lo>>shift) );
 }

 // private operators 
  
template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::UCmp(Unit a,Unit b)
 {
  return LessCmp(a,b);
 }

template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::UCmp_(const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  for(; na>nb ;na--)
    if( a[na-1] ) return CmpGreater;
       
  for(; na>0 ;na--)
    if( CmpResult ret=UCmp(a[na-1],b[na-1]) ) return ret;
       
  return CmpEqual; 
 }
 
template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::Cmp_(const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na==nb )
    {
     if( na>0 )
       {
        if( CmpResult ret=SignCmp(a[na-1],b[na-1]) ) return ret;
        
        for(na--; na>0 ;na--)
          if( CmpResult ret=UCmp(a[na-1],b[na-1]) ) return ret;
       }
       
     return CmpEqual; 
    }

  if( nb>0 )
    {
     Unit bext=SignExt(b[nb-1]);
     
     if( CmpResult ret=SignCmp(a[na-1],bext) ) return ret;
     
     for(na--; na>nb ;na--)
       if( CmpResult ret=UCmp(a[na-1],bext) ) return ret;
       
     for(; na>0 ;na--)
       if( CmpResult ret=UCmp(a[na-1],b[na-1]) ) return ret;
       
     return CmpEqual; 
    }
    
  return Sign(a,na);  
 }
  
 // const operators
 
template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::USign(const Unit *a,ulen na)
 {
  for(; na>0 ;na--) if( a[na-1]!=0 ) return CmpGreater;
     
  return CmpEqual;  
 }
 
template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::Sign(const Unit *a,ulen na)
 {
  if( na>0 )
    {
     Unit msa=a[na-1];
     
     if( msa&MSBit ) return CmpLess;
     
     if( msa!=0 ) return CmpGreater;
     
     return USign(a,na-1);
    }
  else
    {  
     return CmpEqual;  
    }
 }
  
template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::UCmp(const Unit *a,const Unit *b,ulen nab)
 {
  return UCmp_(a,nab,b,nab);
 }
  
template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::UCmp(const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na<nb ) return -UCmp_(b,nb,a,na);
  
  return UCmp_(a,na,b,nb);
 }
  
template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::Cmp(const Unit *a,const Unit *b,ulen nab)
 {
  return Cmp_(a,nab,b,nab);
 }
  
template <class UInt> 
CmpResult IntegerSlowAlgo<UInt>::Cmp(const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na<nb ) return -Cmp_(b,nb,a,na);
  
  return Cmp_(a,na,b,nb);
 }
  
template <class UInt> 
ulen IntegerSlowAlgo<UInt>::UNormalize(const Unit *a,ulen na)
 {
  for(; na>0 && a[na-1]==0 ;na--);
  
  return na;
 }
  
template <class UInt> 
ulen IntegerSlowAlgo<UInt>::Normalize(const Unit *a,ulen na)
 {
  while( na>=2 )
    {
     Unit msa=a[na-1];
     Unit msa1=a[na-2];
     
     if( msa==SignExt(msa1) )
       na--;
     else  
       return na;
    }
    
  return ( na && a[0] );  
 }
  
 // additive operators

template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::UNeg(Unit *a,ulen na)
 {
  Unit c=0;
  
  for(; na>0 ;a++,na--)
    {
     c=RevSub(*a,0,c);
    }
    
  return c;  
 }
 
template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::Neg(Unit *a,ulen na)
 {
  if( na==0 ) return 0;
       
  Unit aext=SignExt(a[na-1]);
  Unit c=UNeg(a,na);
  
  RevSub(aext,0,c);    
  
  return aext;
 }
 
template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::UAddUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return b;
    
  Unit c=Add(*a,b,0);  
  
  for(na--,a++; na>0 ;na--,a++)
    {
     c=Add(*a,0,c);
    }
    
  return c;  
 }
 
template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::AddUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return b;
    
  Unit aext=SignExt(a[na-1]);  
    
  return aext+UAddUnit(a,na,b);  
 }
 
template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::USubUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return b;
    
  Unit c=Sub(*a,b,0);  
  
  for(na--,a++; na>0 ;na--,a++)
    {
     c=Sub(*a,0,c);
    }
    
  return c;  
 }
 
template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::SubUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return Unit(-b);
    
  Unit aext=SignExt(a[na-1]);  
    
  return aext-USubUnit(a,na,b);  
 }
 
template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::UNegAddUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return Unit(-b); 
  
  Unit c=RevSub(*a,b,0);
 
  for(na--,a++; na>0 ;a++,na--)
    {
     c=RevSub(*a,0,c);
    }
    
  return c;  
 }

template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::NegAddUnit(Unit *a,ulen na,Unit b)
 {
  if( na==0 ) return b; 

  Unit aext=SignExt(a[na-1]);
  
  return -aext-UNegAddUnit(a,na,b);
 }
   
template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::UAdd(Unit *restrict b,const Unit *a,ulen nab)
 {
  Unit c=0;
 
  for(; nab>0 ;a++,b++,nab--)
    {
     c=Add(*b,*a,c);
    }
    
  return c;  
 }
  
template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::Add(Unit *restrict b,ulen nb,const Unit *a,ulen na)
 {
  if( na==0 ) return SignExt(b,nb);
 
  Unit aext=SignExt(a[na-1]);
  Unit bext=SignExt(b[nb-1]);
  Unit c=0;
  
  for(nb-=na; na>0 ;a++,b++,na--)
    {
     c=Add(*b,*a,c);
    }
    
  for(; nb>0 ;b++,nb--)
    {
     c=Add(*b,aext,c);
    }

  Add(bext,aext,c);    
  
  return bext;
 }
  
template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::USub(Unit *restrict b,const Unit *a,ulen nab)
 {
  Unit c=0;
 
  for(; nab>0 ;a++,b++,nab--)
    {
     c=Sub(*b,*a,c);
    }
    
  return c;  
 }
  
template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na)
 {
  if( na==0 ) return SignExt(b,nb);
 
  Unit aext=SignExt(a[na-1]);
  Unit bext=SignExt(b[nb-1]);
  Unit c=0;
  
  for(nb-=na; na>0 ;a++,b++,na--)
    {
     c=Sub(*b,*a,c);
    }
    
  for(; nb>0 ;b++,nb--)
    {
     c=Sub(*b,aext,c);
    }

  Sub(bext,aext,c);    
  
  return bext;
 }
  
template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::URevSub(Unit *restrict b,const Unit *a,ulen nab)
 {
  Unit c=0;
 
  for(; nab>0 ;a++,b++,nab--)
    {
     c=RevSub(*b,*a,c);
    }
    
  return c;  
 }
   
template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na)
 {
  if( na==0 ) return Neg(b,nb);
 
  Unit aext=SignExt(a[na-1]);
  Unit bext=SignExt(b[nb-1]);
  Unit c=0;
  
  for(nb-=na; na>0 ;a++,b++,na--)
    {
     c=RevSub(*b,*a,c);
    }
    
  for(; nb>0 ;b++,nb--)
    {
     c=RevSub(*b,aext,c);
    }

  RevSub(bext,aext,c);    
  
  return bext;
 }
 
 // shift operators

template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::ULShift(Unit *a,ulen na,unsigned shift)
 {
  if( na==0 ) return 0;
  
  Unit ret=Unit( a[na-1]>>(UnitBits-shift) );
  
  for(; na>=2 ;na--)
    {
     a[na-1]=LShift(a[na-1],a[na-2],shift);
    }
    
  a[0]<<=shift;  
    
  return ret;  
 }
 
template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)
 {
  if( nab==0 ) return 0;
  
  b[0]=Unit( a[0]<<shift );
  
  for(ulen i=1; i<nab ;i++)
    {
     b[i]=LShift(a[i],a[i-1],shift);
    }
    
  return LShift(SignExt(a[nab-1]),a[nab-1],shift);  
 }
 
template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift)
 {
  if( na==0 ) return 0;
  
  Unit ret=Unit( a[na-1]>>(UnitBits-shift) );
  
  for(; na>=2 ;na--)
    {
     a[delta+na-1]=LShift(a[na-1],a[na-2],shift);
    }
  
  a[delta]=Unit( a[0]<<shift );
  
  return ret;  
 }

template <class UInt> 
UInt/* msu */ IntegerSlowAlgo<UInt>::ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift)
 {
  if( na==0 ) return 0;
  
  Unit ret=LShift(SignExt(a[na-1]),a[na-1],shift);
  
  for(; na>=2 ;na--)
    {
     a[delta+na-1]=LShift(a[na-1],a[na-2],shift);
    }
  
  a[delta]=Unit( a[0]<<shift );
  
  return ret;  
 }

template <class UInt> 
void IntegerSlowAlgo<UInt>::URShift(Unit *a,ulen na,unsigned shift)
 {
  if( na==0 ) return;
  
  for(ulen i=0; i<na-1 ;i++)
    {
     a[i]=RShift(a[i+1],a[i],shift);
    }
  
  a[na-1]>>=shift;
 }

template <class UInt> 
void IntegerSlowAlgo<UInt>::RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift)
 {
  if( nab==0 ) return;
  
  for(ulen i=0; i<nab-1 ;i++)
    {
     b[i]=RShift(a[i+1],a[i],shift);
    }
  
  b[nab-1]=RShift(SignExt(a[nab-1]),a[nab-1],shift);
 }
    
template <class UInt> 
void IntegerSlowAlgo<UInt>::UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift)
 {
  if( na==0 ) return;
  
  na--;
  
  for(ulen i=0; i<na ;i++) a[i]=RShift(a[delta+i+1],a[delta+i],shift);
  
  a[na]=Unit( a[delta+na]>>shift );
 }

template <class UInt> 
void IntegerSlowAlgo<UInt>::ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift)
 {
  if( na==0 ) return;
  
  na--;
  
  for(ulen i=0; i<na ;i++) a[i]=RShift(a[delta+i+1],a[delta+i],shift);
  
  a[na]=RShift(SignExt(a[delta+na]),a[delta+na],shift);
 }

 // multiplicative operators

template <class UInt> 
struct IntegerSlowAlgo<UInt>::MulAcc
 {
  Unit lo;
  Unit hi;
  ulen hi2;
  
  MulAcc(Unit a,Unit b)
   {
    DoubleMul prod(a,b);
    
    lo=prod.lo;
    hi=prod.hi;
    hi2=0;
   }
  
  void mac(Unit a,Unit b)
   {
    DoubleMul prod(a,b);
    
    Unit c=Add(lo,prod.lo,0);
    
    c=Add(hi,prod.hi,c);
    
    hi2+=c;
   }
  
  void mac2(Unit a,Unit b)
   {
    DoubleMul prod(a,b);
    
    Unit c1=prod.hi>>(UnitBits-1);
    
    prod.hi=LShift(prod.hi,prod.lo,1);
    prod.lo<<=1;
    
    Unit c=Add(lo,prod.lo,0);
    
    c=Add(hi,prod.hi,c);
    
    hi2+=c+c1;
   }
  
  Unit shift()
   {
    Unit ret=lo;
    
    lo=hi;
    hi=Unit(hi2);
    
    hi2=RShiftConst<ulen,UnitBits>::Do(hi2);
    
    return ret;
   }
 };
 
template <class UInt> 
void IntegerSlowAlgo<UInt>::UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na==0 || nb==0 )
    {
     Null(c,na+nb);
    
     return;
    }
    
  if( na>nb )  
    {
     Swap(a,b);
     Swap(na,nb);
    }
    
  if( na==1 )  
    {
     if( nb==1 )
       {
        MulAcc acc(a[0],b[0]);  
        
        c[0]=acc.lo;
        c[1]=acc.hi;
        
        return;
       }
       
     MulAcc acc(a[0],b[0]);  
  
     c[0]=acc.shift();
    
     for(ulen k=1; k<nb-1 ;k++)  
       {
        acc.mac(a[0],b[k]);
       
        c[k]=acc.shift();  
       }
    
     acc.mac(a[0],b[nb-1]);
       
     c[nb-1]=acc.lo;  
     c[nb]=acc.hi;  
     
     return;
    }
    
  MulAcc acc(a[0],b[0]);  
  
  c[0]=acc.shift();
    
  for(ulen k=1; k<na ;k++)  
    {
     for(ulen i=0; i<=k ;i++) acc.mac(a[i],b[k-i]);
       
     c[k]=acc.shift();  
    }
    
  for(ulen k=na; k<nb ;k++)  
    {
     for(ulen i=0; i<na ;i++) acc.mac(a[i],b[k-i]);
       
     c[k]=acc.shift();  
    }
    
  for(ulen k=nb; k<na+nb-2 ;k++)  
    {
     for(ulen i=k-(nb-1); i<na ;i++) acc.mac(a[i],b[k-i]);
       
     c[k]=acc.shift();  
    }
    
  acc.mac(a[na-1],b[nb-1]);  
    
  c[na+nb-2]=acc.lo;  
  c[na+nb-1]=acc.hi;  
 }
 
template <class UInt> 
UInt/* c */ IntegerSlowAlgo<UInt>::UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na==0 || nb==0 ) return 0; 
    
  if( na>nb )  
    {
     Swap(a,b);
     Swap(na,nb);
    }
    
  if( na==1 )  
    {
     if( nb==1 )
       {
        MulAcc acc(a[0],b[0]);  
        Unit carry=0;
        
        carry=Add(c[0],acc.lo,carry);
        carry=Add(c[1],acc.hi,carry);
        
        return carry;
       }
       
     MulAcc acc(a[0],b[0]);  
     Unit carry=0;
  
     carry=Add(c[0],acc.shift(),carry);
    
     for(ulen k=1; k<nb-1 ;k++)  
       {
        acc.mac(a[0],b[k]);
       
        carry=Add(c[k],acc.shift(),carry);  
       }
    
     acc.mac(a[0],b[nb-1]);

     carry=Add(c[nb-1],acc.lo,carry);
     carry=Add(c[nb],acc.hi,carry);
     
     return carry;
    }
    
  MulAcc acc(a[0],b[0]);
  Unit carry=0;
  
  carry=Add(c[0],acc.shift(),carry);
    
  for(ulen k=1; k<na ;k++)  
    {
     for(ulen i=0; i<=k ;i++) acc.mac(a[i],b[k-i]);
       
     carry=Add(c[k],acc.shift(),carry);  
    }
    
  for(ulen k=na; k<nb ;k++)  
    {
     for(ulen i=0; i<na ;i++) acc.mac(a[i],b[k-i]);
       
     carry=Add(c[k],acc.shift(),carry);  
    }
    
  for(ulen k=nb; k<na+nb-2 ;k++)  
    {
     for(ulen i=k-(nb-1); i<na ;i++) acc.mac(a[i],b[k-i]);
       
     carry=Add(c[k],acc.shift(),carry);  
    }
    
  acc.mac(a[na-1],b[nb-1]);  
    
  carry=Add(c[na+nb-2],acc.lo,carry);  
  carry=Add(c[na+nb-1],acc.hi,carry);

  return carry;
 }

template <class UInt> 
void IntegerSlowAlgo<UInt>::UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( nc==0 ) return;
  
  if( na==0 || nb==0 )
    {
     Null(c,nc);
    
     return;
    }
    
  if( na>nb )  
    {
     Swap(a,b);
     Swap(na,nb);
    }
    
  if( na==1 )  
    {
     if( nb==1 )
       {
        MulAcc acc(a[0],b[0]);  
        
        c[0]=acc.lo;
        
        if( 1>=nc ) return;
        
        c[1]=acc.hi;
        
        return;
       }
       
     MulAcc acc(a[0],b[0]);  
  
     c[0]=acc.shift();
    
     for(ulen k=1; k<nb-1 ;k++)  
       {
        if( k>=nc ) return;
    
        acc.mac(a[0],b[k]);
       
        c[k]=acc.shift();  
       }
    
     if( nb-1>=nc ) return;
     
     acc.mac(a[0],b[nb-1]);
       
     c[nb-1]=acc.lo;  
     
     if( nb>=nc ) return;
     
     c[nb]=acc.hi;  
     
     return;
    }
    
  MulAcc acc(a[0],b[0]);  
  
  c[0]=acc.shift();
    
  for(ulen k=1; k<na ;k++)  
    {
     if( k>=nc ) return;
    
     for(ulen i=0; i<=k ;i++) acc.mac(a[i],b[k-i]);
       
     c[k]=acc.shift();  
    }
    
  for(ulen k=na; k<nb ;k++)  
    {
     if( k>=nc ) return;
    
     for(ulen i=0; i<na ;i++) acc.mac(a[i],b[k-i]);
       
     c[k]=acc.shift();  
    }
    
  for(ulen k=nb; k<na+nb-2 ;k++)  
    {
     if( k>=nc ) return;
    
     for(ulen i=k-(nb-1); i<na ;i++) acc.mac(a[i],b[k-i]);
       
     c[k]=acc.shift();  
    }
    
  if( na+nb-2>=nc ) return;
  
  acc.mac(a[na-1],b[nb-1]);  
    
  c[na+nb-2]=acc.lo;  
  
  if( na+nb-1>=nc ) return;
  
  c[na+nb-1]=acc.hi;  
 }
 
template <class UInt> 
void IntegerSlowAlgo<UInt>::USq(Unit *restrict c,const Unit *a,ulen na)
 {
  if( na==0 ) return;
    
  if( na==1 )  
    {
     MulAcc acc(a[0],a[0]);  
        
     c[0]=acc.lo;
     c[1]=acc.hi;
        
     return;
    }
    
  MulAcc acc(a[0],a[0]);  
  
  c[0]=acc.shift();
    
  for(ulen k=1; k<na ;k++)  
    {
     for(ulen i=0; 2*i<k ;i++) acc.mac2(a[i],a[k-i]);
     
     if( (k%2)==0 ) acc.mac(a[k/2],a[k/2]);
       
     c[k]=acc.shift();  
    }
    
  for(ulen k=na; k<2*na-2 ;k++)  
    {
     for(ulen i=k-(na-1); 2*i<k ;i++) acc.mac2(a[i],a[k-i]);
     
     if( (k%2)==0 ) acc.mac(a[k/2],a[k/2]);
     
     c[k]=acc.shift();  
    }
    
  acc.mac(a[na-1],a[na-1]);  
    
  c[2*na-2]=acc.lo;  
  c[2*na-1]=acc.hi;  
 }

template <class UInt> 
void IntegerSlowAlgo<UInt>::Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb)
 {
  if( na==0 || nb==0 )
    {
     Null(c,na+nb);
    
     return;
    }
    
  UMul(c,a,na,b,nb);
  
  if( a[na-1]&MSBit )
    {
     USub(c+na,b,nb);
    }
    
  if( b[nb-1]&MSBit )
    {
     USub(c+nb,a,na);
    }
 }
  
template <class UInt> 
void IntegerSlowAlgo<UInt>::Sq(Unit *restrict c,const Unit *a,ulen na)
 {
  if( na==0 ) return;
    
  USq(c,a,na);
  
  if( a[na-1]&MSBit )
    {
     USub(c+na,a,na);
     USub(c+na,a,na);
    }
 }

 // data functions  

template <class UInt> 
void IntegerSlowAlgo<UInt>::Null(Unit *a,ulen na)
 {
  Range(a,na).set_null();
 }

template <class UInt> 
void IntegerSlowAlgo<UInt>::MoveUp(Unit *a,ulen na,ulen delta)
 {
  if( na==0 || delta==0 ) return;
  
  for(; na>0 ;na--) a[delta+na-1]=a[na-1];
 }

template <class UInt> 
void IntegerSlowAlgo<UInt>::MoveDown(Unit *a,ulen na,ulen delta)
 {
  if( na==0 || delta==0 ) return;
  
  for(ulen i=0; i<na ;i++) a[i]=a[delta+i]; 
 }

} // namespace Math
} // namespace CCore
 
#endif
 

