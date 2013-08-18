/* IntegerFastAlgo.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/math/IntegerFastAlgo.h>

#include <CCore/inc/math/IntegerSlowAlgo.h>

#include <CCore/inc/Array.h>

namespace CCore {
namespace Math {

/* struct IntegerFastAlgo */

typedef IntegerFastAlgo::Unit Unit;

typedef IntegerSlowAlgo<Unit> Slow;

 // private functions

Unit/* msu */ IntegerFastAlgo::Inc(Unit *a,ulen na) noexcept // na>0
 {
  Unit aext=SignExt(a[na-1]);  
    
  return aext+UAddUnit(a,na,1);  
 }

Unit/* msu */ IntegerFastAlgo::Dec(Unit *a,ulen na) noexcept // na>0
 {
  Unit aext=SignExt(a[na-1]);  
    
  return aext-USubUnit(a,na,1);  
 }

void IntegerFastAlgo::Not_(Unit *a,ulen na) noexcept
 {
  for(; na ;na--,a++) (*a)=~(*a);
 }

Unit/* msu */ IntegerFastAlgo::Not(Unit *a,ulen na) noexcept // na>0
 {
  Not_(a,na);
  
  return SignExt(a[na-1]);
 }

Unit/* msu */ IntegerFastAlgo::IncNot(Unit *a,ulen na) noexcept // na>0
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

Unit/* msu */ IntegerFastAlgo::DecNot(Unit *a,ulen na) noexcept // na>0
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

CmpResult IntegerFastAlgo::Cmp_(const Unit *a,ulen na,const Unit *b,ulen nb) noexcept // na>=nb
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

#if 0

// Fake code

unsigned IntegerFastAlgo::CountZeroMSB(Unit) noexcept
 {
  return 0;
 }

unsigned IntegerFastAlgo::CountZeroLSB(Unit) noexcept
 {
  return 0;
 }
 
Unit IntegerFastAlgo::DoubleUDiv(Unit,Unit,Unit) noexcept
 {
  return 0;
 }

#endif

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

Unit/* msu */ IntegerFastAlgo::Neg(Unit *a,ulen na) noexcept
 {
  if( na==0 ) return 0;
       
  Unit aext=SignExt(a[na-1]);
  Unit c=UNeg(a,na);
  
  return -Unit(aext+c);
 }

Unit/* msu */ IntegerFastAlgo::AddUnit(Unit *a,ulen na,Unit b) noexcept
 {
  if( na==0 ) return b;
    
  Unit aext=SignExt(a[na-1]);  
    
  return aext+UAddUnit(a,na,b);  
 }

Unit/* msu */ IntegerFastAlgo::SubUnit(Unit *a,ulen na,Unit b) noexcept
 {
  if( na==0 ) return Unit(-b);
    
  Unit aext=SignExt(a[na-1]);  
    
  return aext-USubUnit(a,na,b);  
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

Unit/* msu */ IntegerFastAlgo::Add(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept // nb>=na
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

Unit/* msu */ IntegerFastAlgo::Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept // nb>=na
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

Unit/* msu */ IntegerFastAlgo::RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept // nb>=na
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

// multiplicative operators

void IntegerFastAlgo::Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept // nc==na+nb
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

void IntegerFastAlgo::Sq(Unit *restrict c,const Unit *a,ulen na) noexcept // nc==2*na
 {
  if( na==0 ) return;
    
  USq(c,a,na);
  
  if( a[na-1]&MSBit )
    {
     USub(c+na,a,na);
     USub(c+na,a,na);
    }
 }

Unit/* c */ IntegerFastAlgo::UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // nc==na+nb
 {
  ulen nc=na+nb;
  TempArray<Unit,256> temp(nc);
  
  UMul(temp.getPtr(),a,na,b,nb);
  
  return UAdd(c,temp.getPtr(),nc);
 }

void IntegerFastAlgo::UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) // nc<=na+nb
 {
  Replace_min(na,nc);
  Replace_min(nb,nc);
  
  if( na==0 || nb==0 )
    {
     Null(c,nc);
    
     return;
    }
  
  TempArray<Unit,256> temp(na+nb);
   
  UMul(temp.getPtr(),a,na,b,nb);
  
  Range(c,nc).copy(temp.getPtr());
 }

} // namespace Math
} // namespace CCore
 

