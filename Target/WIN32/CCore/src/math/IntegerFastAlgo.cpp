/* IntegerFastAlgo.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/math/IntegerFastAlgo.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>
 
namespace CCore {
namespace Math {

/* struct IntegerFastAlgo::DefAlgoBase */ 

struct IntegerFastAlgo::DefAlgoBase
 {
  typedef IntegerFastAlgo::Unit Unit;
  
  // tunning
  
  static const ulen TempLen = 64 ;
  
  // operations
  
  static unsigned CountD(ulen n) // n!=0 , return max d , 2^d<=n
   {
    return 31-CountZeroMSB(n);
   }
  
  static void Null(Unit *a,ulen na) 
   {
    IntegerFastAlgo::Null(a,na); 
   }
  
  static Unit UAddUnit(Unit *a,ulen na,Unit b) 
   {
    return IntegerFastAlgo::UAddUnit(a,na,b);
   }
  
  static Unit UAdd(Unit *restrict b,const Unit *a,ulen nab) 
   {
    return IntegerFastAlgo::UAdd(b,a,nab); 
   }
  
  static Unit UDouble(Unit *a,ulen na) 
   {
    return IntegerFastAlgo::ULShift(a,na,1);
   }
 };

/* struct IntegerFastAlgo::DefAlgo1 */

struct IntegerFastAlgo::DefAlgo1 : DefAlgoBase
 {
  // tunning
  
  static const unsigned D1 = 5 ;
  
  static const unsigned D2 = 5 ;
  
  // operations
  
  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // 0<na<=nb , nc==na+nb , na<=2^D1-1
   {
    if( na>=2 )
      IntegerFastAlgo::RawUMul(c,a,na,b,nb);
    else if( nb>=2 )
      IntegerFastAlgo::RawUMul1(c,a[0],b,nb);
    else
      IntegerFastAlgo::RawUMul11(c,a[0],b[0]);
   }
  
  static Unit UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // 0<na<=nb , nc==na+nb , na<=2^D1-1
   {
    if( na>=2 )
      return IntegerFastAlgo::RawUMac(c,a,na,b,nb);
    else if( nb>=2 )
      return IntegerFastAlgo::RawUMac1(c,a[0],b,nb);
    else
      return IntegerFastAlgo::RawUMac11(c,a[0],b[0]);
   }
  
  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) // 0<na<=nb , nc<=na+nb , na<=2^D1-1
   {
    if( !nc ) return;
    
    if( na>=2 )
      IntegerFastAlgo::RawUMulLo(c,nc,a,na,b,nb);
    else if( nb>=2 )
      IntegerFastAlgo::RawUMulLo1(c,nc,a[0],b,nb);
    else
      IntegerFastAlgo::RawUMulLo11(c,nc,a[0],b[0]);
   }
  
  static void USq(Unit *restrict c,const Unit *a,ulen na) // nc==2*na , na<=2^D2-1
   {
    if( na>=2 )
      IntegerFastAlgo::RawUSq(c,a,na);
    else if( na )
      IntegerFastAlgo::RawUSq1(c,a[0]);
   }
 };

/* struct IntegerFastAlgo::KAlgo */

struct IntegerFastAlgo::KAlgo
 {
  typedef IntegerFastAlgo::Unit Unit;
  
  // tunning
  
  static const unsigned D1 = 3 ;
  
  static const unsigned D2 = 3 ;
  
  static const ulen TempLen = 64 ;
  
  // operations
  
  static Unit UAddUnit(Unit *a,ulen na,Unit b)
   {
    return IntegerFastAlgo::UAddUnit(a,na,b);
   }
  
  static Unit UAdd(Unit *restrict b,const Unit *a,ulen nab)
   {
    return IntegerFastAlgo::UAdd(b,a,nab);
   }
  
  static Unit USub(Unit *restrict b,const Unit *a,ulen nab)
   {
    return IntegerFastAlgo::USub(b,a,nab);
   }
  
  static Unit UAdd(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc)
   {
    Range(c,nabc).copy(a);
    
    return IntegerFastAlgo::UAdd(c,b,nabc);
   }
  
  static Unit USub(Unit *restrict c,const Unit *a,const Unit *b,ulen nabc)
   {
    Range(c,nabc).copy(a);
    
    return IntegerFastAlgo::USub(c,b,nabc);
   }
  
  static void UMul(unsigned d,Unit *restrict c,const Unit *a,const Unit *b) // d<=D1 , c[2^(d+1)] , a[2^d] , b[2^d]
   {
    if( d )
      {
       ulen n=ulen(1)<<d;
    
       IntegerFastAlgo::RawUMul(c,a,n,b,n);
      }
    else
      {
       IntegerFastAlgo::RawUMul11(c,a[0],b[0]);
      }
   }
  
  static void UMulLo(unsigned d,Unit *restrict c,ulen nc,const Unit *a,const Unit *b) // d<=D1 , nc<=2^(d+1) , a[2^d] , b[2^d]
   {
    if( !nc ) return;
    
    if( d )
      {
       ulen n=ulen(1)<<d;
    
       IntegerFastAlgo::RawUMulLo(c,nc,a,n,b,n);
      }
    else
      {
       IntegerFastAlgo::RawUMulLo11(c,nc,a[0],b[0]);
      }
   }
  
  static void USq(unsigned d,Unit *restrict c,const Unit *a) // d<=D2 , c[2^(d+1)] , a[2^d]
   {
    if( d )
      {
       ulen n=ulen(1)<<d;
       
       IntegerFastAlgo::RawUSq(c,a,n);
      }
    else
      {
       IntegerFastAlgo::RawUSq1(c,a[0]);
      }
   }
 };

/* struct IntegerFastAlgo::DefAlgo2 */

struct IntegerFastAlgo::DefAlgo2 : DefAlgoBase
 {
  // tunning
  
  static const unsigned D1 = 15 ;
  
  static const unsigned D2 = 15 ;
  
  // operations
  
  typedef KaratsubaMul<KAlgo> KMul;

  typedef Pow2Mul<DefAlgo1,KMul::Engine> ImpMul;
  
  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // 0<na<=nb , nc==na+nb , na<=2^D1-1
   {
    ImpMul::UMul(c,a,na,b,nb);
   }
  
  static Unit UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // 0<na<=nb , nc==na+nb , na<=2^D1-1
   {
    return ImpMul::UMac(c,a,na,b,nb);
   }
  
  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) // 0<na<=nb , nc<=na+nb , na<=2^D1-1
   {
    ImpMul::UMulLo(c,nc,a,na,b,nb);
   }
  
  static void USq(Unit *restrict c,const Unit *a,ulen na) // nc==2*na , na<=2^D2-1
   {
    ImpMul::USq(c,a,na);
   }
 };

/* struct IntegerFastAlgo */

typedef IntegerFastAlgo::Unit Unit;

typedef IntegerSlowAlgo<Unit> Slow;

 // private functions

Unit/* msu */ IntegerFastAlgo::Inc(Unit *a,ulen na) noexcept
 {
  Unit u=SignExt(a[na-1]);
  
  for(; na ;na--,a++) if( ++(*a) ) return u;
  
  return u+1;
 }

Unit/* msu */ IntegerFastAlgo::Dec(Unit *a,ulen na) noexcept
 {
  Unit u=SignExt(a[na-1]);
  
  for(; na ;na--,a++) if( (*a)-- ) return u;
  
  return u-1;
 }

void IntegerFastAlgo::Not_(Unit *a,ulen na) noexcept
 {
  for(; na ;na--,a++) (*a)=~(*a);
 }

Unit/* msu */ IntegerFastAlgo::Not(Unit *a,ulen na) noexcept
 {
  Not_(a,na);
  
  return SignExt(a[na-1]);
 }

Unit/* msu */ IntegerFastAlgo::IncNot(Unit *a,ulen na) noexcept
 {
  Unit u=SignExtNot(a[na-1]);

  for(; na ;na--,a++)
    if( Unit x=(*a) )
      {
       (*a)=-x;
        
       Not_(a+1,na-1);
       
       return u; 
      }
  
  return u+1;
 }

Unit/* msu */ IntegerFastAlgo::DecNot(Unit *a,ulen na) noexcept
 {
  Unit u=SignExtNot(a[na-1]);
  
  for(; na ;na--,a++)
    if( Unit x=~(*a) )
      {
       (*a)=x-1;
       
       Not_(a+1,na-1);
       
       return u; 
      }
  
  return u-1;
 }

 // private functions

Unit/* c */ IntegerFastAlgo::UInc(Unit *a,ulen na) noexcept
 {
  for(; na ;na--,a++) if( ++(*a) ) return 0;
  
  return 1;
 }

Unit/* c */ IntegerFastAlgo::UDec(Unit *a,ulen na) noexcept
 {
  for(; na ;na--,a++) if( (*a)-- ) return 0;
  
  return 1;
 }

 // private functions

 // private functions

CmpResult IntegerFastAlgo::Cmp_(const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  if( na==nb )
    {
     if( na>0 )
       {
        if( CmpResult ret=SignCmp(a[na-1],b[na-1]) ) return ret;
        
        for(na--; na>0 ;na--)
          if( CmpResult ret=LessCmp(a[na-1],b[na-1]) ) return ret;
       }
       
     return CmpEqual; 
    }

  if( nb>0 )
    {
     Unit bext=SignExt(b[nb-1]);
     
     if( CmpResult ret=SignCmp(a[na-1],bext) ) return ret;
     
     for(na--; na>nb ;na--)
       if( CmpResult ret=LessCmp(a[na-1],bext) ) return ret;
       
     for(; na>0 ;na--)
       if( CmpResult ret=LessCmp(a[na-1],b[na-1]) ) return ret;
       
     return CmpEqual; 
    }
    
  return Sign(a,na);  
 }

 // functions

 // const operators

CmpResult IntegerFastAlgo::USign(const Unit *a,ulen na) noexcept
 {
  return Slow::USign(a,na);
 }

CmpResult IntegerFastAlgo::Sign(const Unit *a,ulen na) noexcept
 {
  return Slow::Sign(a,na);
 }

CmpResult IntegerFastAlgo::UCmp(const Unit *a,const Unit *b,ulen nab) noexcept
 {
  return Slow::UCmp(a,b,nab);
 }

CmpResult IntegerFastAlgo::UCmp(const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  return Slow::UCmp(a,na,b,nb);
 }

CmpResult IntegerFastAlgo::Cmp(const Unit *a,const Unit *b,ulen nab) noexcept
 {
  return Cmp_(a,nab,b,nab);
 }

CmpResult IntegerFastAlgo::Cmp(const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  if( na<nb ) return -Cmp_(b,nb,a,na);
  
  return Cmp_(a,na,b,nb);
 }

ulen IntegerFastAlgo::UNormalize(const Unit *a,ulen na) noexcept
 {
  return Slow::UNormalize(a,na);
 }

ulen IntegerFastAlgo::Normalize(const Unit *a,ulen na) noexcept
 {
  if( na>=2 )
    {
     Unit msa=a[na-1];
     Unit msa1=a[na-2];
     
     if( msa!=SignExt(msa1) ) return na;
     
     for(na--; na>=2 ;na--)
       {
        msa=msa1;
        msa1=a[na-2];
        
        if( msa!=SignExt(msa1) ) return na;
       }
     
     return msa1!=0;  
    }
    
  return ( na && a[0] );  
 }

 // additive operators

Unit/* c */ IntegerFastAlgo::UNeg(Unit *a,ulen na) noexcept
 {
  for(; na ;na--,a++)
    if( Unit x=(*a) )
      {
       (*a)=-x;
       
       Not_(a+1,na-1);
       
       return 1; 
      }
  
  return 0;
 }

Unit/* msu */ IntegerFastAlgo::Neg(Unit *a,ulen na) noexcept
 {
  if( na==0 ) return 0; 

  Unit u=USignExt(a[na-1]);
  
  for(; na ;na--,a++)
    if( Unit x=(*a) )
      {
       (*a)=-x;
        
       Not_(a+1,na-1);
       
       return u-1; 
      }
  
  return u;
 }

Unit/* c */ IntegerFastAlgo::UAddUnit(Unit *a,ulen na,Unit b) noexcept
 {
  if( !na ) return b;
  
  Unit a0=(*a);
  
  a0+=b;
  
  (*a)=a0;
  
  if( a0>=b ) return 0;
  
  return UInc(a+1,na-1);
 }

Unit/* msu */ IntegerFastAlgo::AddUnit(Unit *a,ulen na,Unit b) noexcept
 {
  if( !na ) return b;
  
  Unit u=SignExt(a[na-1]);
  
  Unit a0=(*a);
  
  a0+=b;
  
  (*a)=a0;
  
  if( a0>=b ) return u;
  
  return u+UInc(a+1,na-1);
 }

Unit/* c */ IntegerFastAlgo::USubUnit(Unit *a,ulen na,Unit b) noexcept
 {
  if( !na ) return b;
  
  Unit a0=(*a);
  
  (*a)=a0-b;
  
  if( a0>=b ) return 0;
  
  return UDec(a+1,na-1);
 }

Unit/* msu */ IntegerFastAlgo::SubUnit(Unit *a,ulen na,Unit b) noexcept
 {
  if( na==0 ) return Unit(-b);
  
  Unit u=SignExt(a[na-1]);  
  
  Unit a0=(*a);
  
  (*a)=a0-b;
  
  if( a0>=b ) return u;
  
  return u-UDec(a+1,na-1);
 }

Unit/* c */ IntegerFastAlgo::UNegAddUnit(Unit *a,ulen na,Unit b) noexcept
 {
  if( na==0 ) return Unit(-b); 

  Unit a0=(*a);
  
  (*a)=b-a0;
  
  if( b>=a0 ) return UNeg(a+1,na-1);
  
  Not_(a+1,na-1);
  
  return 1;
 }

Unit/* msu */ IntegerFastAlgo::NegAddUnit(Unit *a,ulen na,Unit b) noexcept
 {
  if( na==0 ) return b; 

  Unit u=USignExt(a[na-1]);
  
  Unit a0=(*a);
  
  (*a)=b-a0;
  
  if( b>=a0 ) return u-UNeg(a+1,na-1);
  
  Not_(a+1,na-1);
  
  return u-1;
 }

Unit/* msu */ IntegerFastAlgo::Add(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept
 {
  if( !na ) return SignExt(b,nb);
  
  if( nb==na )
    {
     Unit u=SignExt(b[nb-1])+SignExt(a[na-1]);
     
     return u+UAdd(b,a,na);     
    }
  
  if( UAdd(b,a,na) )
    {
     if( a[na-1]&MSBit )
       {
        return SignExt(b[nb-1]);
       }
     else
       {
        return Inc(b+na,nb-na);
       }
    }
  else
    {
     if( a[na-1]&MSBit )
       {
        return Dec(b+na,nb-na);
       }
     else
       {
        return SignExt(b[nb-1]);
       }
    }
 }

Unit/* msu */ IntegerFastAlgo::Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept
 {
  if( !na ) return SignExt(b,nb);
  
  if( nb==na )
    {
     Unit u=SignExt(b[nb-1])-SignExt(a[na-1]);
     
     return u-USub(b,a,na);     
    }
  
  if( USub(b,a,na) )
    {
     if( a[na-1]&MSBit )
       {
        return SignExt(b[nb-1]);
       }
     else
       {
        return Dec(b+na,nb-na);
       }
    }
  else
    {
     if( a[na-1]&MSBit )
       {
        return Inc(b+na,nb-na);
       }
     else
       {
        return SignExt(b[nb-1]);
       }
    }
 }

Unit/* msu */ IntegerFastAlgo::RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept
 {
  if( !na ) return Neg(b,nb);
  
  if( nb==na )
    {
     Unit u=SignExt(a[na-1])-SignExt(b[nb-1]);
     
     return u-URevSub(b,a,na);     
    }
  
  if( URevSub(b,a,na) )
    {
     if( a[na-1]&MSBit )
       {
        return DecNot(b+na,nb-na);
       }
     else
       {
        return Not(b+na,nb-na);
       }
    }
  else
    {
     if( a[na-1]&MSBit )
       {
        return Not(b+na,nb-na);
       }
     else
       {
        return IncNot(b+na,nb-na);
       }
    }
 }

 // shift operators

 // multiplicative operators

#if 0

void IntegerFastAlgo::UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  if( na>nb )  
    {
     if( nb==0 ) return Null(c,na);
     
     if( nb==1 ) 
       {
        return RawUMul1(c,b[0],a,na);
       }
     
     return RawUMul(c,b,nb,a,na);
    }
  else
    {
     if( na==0 ) return Null(c,nb);
     
     if( na==1 ) 
       {
        if( nb==1 ) return RawUMul11(c,a[0],b[0]);
         
        return RawUMul1(c,a[0],b,nb);
       }
     
     return RawUMul(c,a,na,b,nb);
    }
 }

Unit/* c */ IntegerFastAlgo::UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  if( na>nb )  
    {
     if( nb==0 ) return 0;
     
     if( nb==1 ) 
       {
        return RawUMac1(c,b[0],a,na);
       }
     
     return RawUMac(c,b,nb,a,na);
    }
  else
    {
     if( na==0 ) return 0;
     
     if( na==1 ) 
       {
        if( nb==1 ) return RawUMac11(c,a[0],b[0]);
         
        return RawUMac1(c,a[0],b,nb);
       }
     
     return RawUMac(c,a,na,b,nb);
    }
 }

void IntegerFastAlgo::UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  if( !nc ) return;
  
  if( na>nb )  
    {
     if( nb==0 ) return Null(c,nc);
     
     if( nb==1 ) 
       {
        return RawUMulLo1(c,nc,b[0],a,na);
       }
     
     return RawUMulLo(c,nc,b,nb,a,na);
    }
  else
    {
     if( na==0 ) return Null(c,nc);
     
     if( na==1 ) 
       {
        if( nb==1 ) return RawUMulLo11(c,nc,a[0],b[0]);
         
        return RawUMulLo1(c,nc,a[0],b,nb);
       }
     
     return RawUMulLo(c,nc,a,na,b,nb);
    }
 }

void IntegerFastAlgo::USq(Unit *restrict c,const Unit *a,ulen na) noexcept
 {
  if( na==0 ) return;

  if( na==1 ) return RawUSq1(c,a[0]);
  
  return RawUSq(c,a,na); 
 }

#else

typedef ConvolutionMul<IntegerExtAlgo> CMul;

typedef Pow2Mul<IntegerFastAlgo::DefAlgo2,CMul::Engine> ImpMul;

void IntegerFastAlgo::UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  ImpMul::UMul(c,a,na,b,nb);
 }

Unit/* c */ IntegerFastAlgo::UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  return ImpMul::UMac(c,a,na,b,nb);
 }

void IntegerFastAlgo::UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  ImpMul::UMulLo(c,nc,a,na,b,nb);
 }

void IntegerFastAlgo::USq(Unit *restrict c,const Unit *a,ulen na) noexcept
 {
  ImpMul::USq(c,a,na);
 }

#endif

void IntegerFastAlgo::Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
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

void IntegerFastAlgo::Sq(Unit *restrict c,const Unit *a,ulen na) noexcept
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

void IntegerFastAlgo::Null(Unit *a,ulen na) noexcept 
 {
  Slow::Null(a,na);
 }

void IntegerFastAlgo::MoveUp(Unit *a,ulen na,ulen delta) noexcept
 {
  Slow::MoveUp(a,na,delta);
 }

void IntegerFastAlgo::MoveDown(Unit *a,ulen na,ulen delta) noexcept
 {
  Slow::MoveDown(a,na,delta);
 }

/* asm */

#if 0

unsigned IntegerFastAlgo::CountZeroMSB(Unit a) noexcept
 {
  return Slow::CountZeroMSB(a);
 }

unsigned IntegerFastAlgo::CountZeroLSB(Unit a) noexcept
 {
  return Slow::CountZeroLSB(a); 
 }

Unit IntegerFastAlgo::DoubleUDiv(Unit hi,Unit lo,Unit den) noexcept
 {
  return Slow::DoubleUDiv(hi,lo,den);
 }

Unit/* c */ IntegerFastAlgo::UAdd(Unit *restrict b,const Unit *a,ulen nab) noexcept
 {
  return Slow::UAdd(b,a,nab);
 }

Unit/* c */ IntegerFastAlgo::USub(Unit *restrict b,const Unit *a,ulen nab) noexcept
 {
  return Slow::USub(b,a,nab);
 }

Unit/* c */ IntegerFastAlgo::URevSub(Unit *restrict b,const Unit *a,ulen nab) noexcept
 {
  return Slow::URevSub(b,a,nab);
 }

Unit/* msu */ IntegerFastAlgo::ULShift(Unit *a,ulen na,unsigned shift) noexcept
 {
  return Slow::ULShift(a,na,shift);
 }

Unit/* msu */ IntegerFastAlgo::LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift) noexcept
 {
  return Slow::LShift(b,a,nab,shift);
 }

Unit/* msu */ IntegerFastAlgo::UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift) noexcept
 {
  return Slow::UShiftUp(a,na,delta,shift);
 }

Unit/* msu */ IntegerFastAlgo::ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift) noexcept
 {
  return Slow::ShiftUp(a,na,delta,shift);
 }

void IntegerFastAlgo::URShift(Unit *a,ulen na,unsigned shift) noexcept
 {
  Slow::URShift(a,na,shift);
 }

void IntegerFastAlgo::RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift) noexcept
 {
  Slow::RShift(b,a,nab,shift);
 }

void IntegerFastAlgo::UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift) noexcept
 {
  Slow::UShiftDown(a,na,delta,shift);
 }

void IntegerFastAlgo::ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift) noexcept
 {
  Slow::ShiftDown(a,na,delta,shift);
 }

void IntegerFastAlgo::RawUMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept 
 {
  Slow::UMul(c,a,na,b,nb);
 }

void IntegerFastAlgo::RawUMul1(Unit *restrict c,Unit a,const Unit *b,ulen nb) noexcept
 {
  Slow::UMul(c,&a,1,b,nb);
 }

void IntegerFastAlgo::RawUMul11(Unit *restrict c,Unit a,Unit b) noexcept
 {
  Slow::UMul(c,&a,1,&b,1);
 }

Unit IntegerFastAlgo::RawUMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb,Unit carry) noexcept
 {
  return Slow::UMac(c,a,na,b,nb); // TODO carry
 }

Unit IntegerFastAlgo::RawUMac1(Unit *restrict c,Unit a,const Unit *b,ulen nb,Unit carry) noexcept
 {
  return Slow::UMac(c,&a,1,b,nb); // TODO carry
 }

Unit IntegerFastAlgo::RawUMac11(Unit *c,Unit a,Unit b,Unit carry) noexcept
 {
  return Slow::UMac(c,&a,1,&b,1); // TODO carry
 }

void IntegerFastAlgo::RawUMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept
 {
  Slow::UMulLo(c,nc,a,na,b,nb);
 }

void IntegerFastAlgo::RawUMulLo1(Unit *restrict c,ulen nc,Unit a,const Unit *b,ulen nb) noexcept
 {
  Slow::UMulLo(c,nc,&a,1,b,nb);
 }

void IntegerFastAlgo::RawUMulLo11(Unit *restrict c,ulen nc,Unit a,Unit b) noexcept
 {
  Slow::UMulLo(c,nc,&a,1,&b,1);
 }

void IntegerFastAlgo::RawUSq(Unit *restrict c,const Unit *a,ulen na) noexcept
 {
  RawUMul(c,a,na,a,na);
 }

void IntegerFastAlgo::RawUSq1(Unit *c,Unit a) noexcept
 {
  RawUMul11(c,a,a);
 }

#endif

/* struct IntegerExtAlgo */

/* asm */

#if 0

static void URShift(Unit *a,ulen na,unsigned shift_)
 {
  ulen delta=shift_/Slow::UnitBits;
  unsigned shift=shift_%Slow::UnitBits;
  
  if( shift )
    {
     IntegerFastAlgo::UShiftDown(a,na-delta,delta,shift);
     IntegerFastAlgo::Null(a+(na-delta),delta);
    }
  else
    {
     IntegerFastAlgo::MoveDown(a,na-delta,delta);
     IntegerFastAlgo::Null(a+(na-delta),delta);
    }
 }

void IntegerExtAlgo::UNeg3(Unit *a) noexcept
 {
  IntegerFastAlgo::UNeg(a,3);
 }

Unit IntegerExtAlgo::UAdd3(Unit *restrict a,const Unit *b) noexcept
 {
  return IntegerFastAlgo::UAdd(a,b,3);
 }

void IntegerExtAlgo::USub3(Unit *restrict a,const Unit *b) noexcept
 {
  IntegerFastAlgo::USub(a,b,3);
 }

void IntegerExtAlgo::UMulLo3(Unit *restrict c,const Unit *a,const Unit *b) noexcept
 {
  IntegerFastAlgo::UMulLo(c,3,a,3,b,3);
 }

void IntegerExtAlgo::USqLo3(Unit *restrict c,const Unit *a) noexcept
 {
  UMulLo3(c,a,a);
 }

void IntegerExtAlgo::URShift3(Unit *a,unsigned shift) noexcept
 {
  URShift(a,3,shift); 
 }

void IntegerExtAlgo::UNeg4(Unit *a) noexcept
 {
  IntegerFastAlgo::UNeg(a,4);
 }

Unit IntegerExtAlgo::UAdd4(Unit *restrict a,const Unit *b) noexcept
 {
  return IntegerFastAlgo::UAdd(a,b,4);
 }

void IntegerExtAlgo::USub4(Unit *restrict a,const Unit *b) noexcept
 {
  IntegerFastAlgo::USub(a,b,4);
 }

void IntegerExtAlgo::UMulLo4(Unit *restrict c,const Unit *a,const Unit *b) noexcept
 {
  IntegerFastAlgo::UMulLo(c,4,a,4,b,4);
 }

void IntegerExtAlgo::USqLo4(Unit *restrict c,const Unit *a) noexcept
 {
  UMulLo4(c,a,a);
 }

void IntegerExtAlgo::URShift4(Unit *a,unsigned shift) noexcept
 {
  URShift(a,4,shift); 
 }

#endif

} // namespace Math
} // namespace CCore
 

