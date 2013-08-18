/* IntegerFastAlgo.h */ 
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

#ifndef CCore_inc_math_IntegerFastAlgo_h
#define CCore_inc_math_IntegerFastAlgo_h
 
#include <CCore/inc/Cmp.h>
#include <CCore/inc/Swap.h>

#include <gmp.h>

namespace CCore {
namespace Math {

/* classes */

struct IntegerFastAlgo;

/* struct IntegerFastAlgo */

struct IntegerFastAlgo
 {
  // types and consts
 
  typedef mp_limb_t Unit;
  
  typedef mp_limb_signed_t SUnit;
 
  static const unsigned UnitBits = Meta::UIntBits<Unit>::Ret ;

  static const Unit MaxUnit = Unit(-1) ;
 
  static const Unit MSBit = Unit( MaxUnit^(MaxUnit>>1) );
  
  // private functions
 
  static Unit/* msu */ Inc(Unit *a,ulen na) noexcept; // na>0
 
  static Unit/* msu */ Dec(Unit *a,ulen na) noexcept; // na>0
  
  static void Not_(Unit *a,ulen na) noexcept;
  
  static Unit/* msu */ Not(Unit *a,ulen na) noexcept; // na>0
  
  static Unit/* msu */ IncNot(Unit *a,ulen na) noexcept; // na>0
  
  static Unit/* msu */ DecNot(Unit *a,ulen na) noexcept; // na>0
  
  // private functions
  
  static CmpResult Cmp_(const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // na>=nb
  
  // private functions
  
  static Unit USignExt(Unit a) { return a>>(UnitBits-1); }
  
  static Unit SignExtNot(Unit a) { return SignExt(~a); }
  
  // functions
 
  static Unit SignExt(Unit a) { return SUnit(a)>>(UnitBits-1); }
   
  static Unit SignExt(const Unit *a,ulen na) { return na?SignExt(a[na-1]):0; }
  
  static CmpResult SignCmp(Unit a,Unit b) { return LessCmp(SUnit(a),SUnit(b)); }
  
  static unsigned CountZeroMSB(Unit a) noexcept;
  
  static unsigned CountZeroLSB(Unit a) noexcept;
   
  static Unit DoubleUDiv(Unit hi,Unit lo,Unit den) noexcept; // hi<den
  
  // const operators
 
  static CmpResult USign(const Unit *a,ulen na) noexcept;
  
  static CmpResult Sign(const Unit *a,ulen na) noexcept; 
  
  static CmpResult UCmp(const Unit *a,const Unit *b,ulen nab) noexcept;
  
  static CmpResult UCmp(const Unit *a,ulen na,const Unit *b,ulen nb) noexcept;
  
  static CmpResult Cmp(const Unit *a,const Unit *b,ulen nab) noexcept;
  
  static CmpResult Cmp(const Unit *a,ulen na,const Unit *b,ulen nb) noexcept;
  
  static ulen UNormalize(const Unit *a,ulen na) noexcept;
  
  static ulen Normalize(const Unit *a,ulen na) noexcept;
  
  // additive operators
 
  static Unit/* c */ UNeg(Unit *a,ulen na)
   {
    if( na==0 ) return 0;
    
    return mpn_neg(a,a,na);
   }
 
  static Unit/* c */ UAddUnit(Unit *a,ulen na,Unit b)
   {
    if( na==0 ) return b;
    
    return mpn_add_1(a,a,na,b);
   }
 
  static Unit/* c */ USubUnit(Unit *a,ulen na,Unit b)
   {
    if( na==0 ) return b;
    
    return mpn_sub_1(a,a,na,b);
   }
  
  static Unit/* c */ UAdd(Unit *restrict b,const Unit *a,ulen nab)
   {
    if( nab==0 ) return 0;
     
    return mpn_add_n(b,b,a,nab);
   }
 
  static Unit/* c */ USub(Unit *restrict b,const Unit *a,ulen nab)
   {
    if( nab==0 ) return 0;
     
    return mpn_sub_n(b,b,a,nab);
   }
 
  static Unit/* c */ URevSub(Unit *restrict b,const Unit *a,ulen nab)
   {
    if( nab==0 ) return 0;
     
    return mpn_sub_n(b,a,b,nab);
   }
  
  static Unit/* msu */ Neg(Unit *a,ulen na) noexcept;
  
  static Unit/* msu */ AddUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* msu */ SubUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* c */ UNegAddUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* msu */ NegAddUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* msu */ Add(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept; // nb>=na

  static Unit/* msu */ Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept; // nb>=na
  
  static Unit/* msu */ RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept; // nb>=na
  
  // shift operators
 
  static Unit/* msu */ ULShift(Unit *a,ulen na,unsigned shift) noexcept // 0<shift<UnitBits
   {
    if( na==0 ) return 0;
    
    return mpn_lshift(a,a,na,shift);
   }
  
  static Unit/* msu */ LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift) noexcept // 0<shift<UnitBits
   {
    if( nab==0 ) return 0;
    
    Unit out=mpn_lshift(b,a,nab,shift);
    
    return Unit( out|(SignExt(a[nab-1])<<shift) );
   }

  static Unit/* msu */ UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift) noexcept // a[na+delta] , 0<shift<UnitBits
   {
    if( na==0 ) return 0;
    
    return mpn_lshift(a+delta,a,na,shift);
   }
  
  static Unit/* msu */ ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift) noexcept // a[na+delta] , 0<shift<UnitBits
   {
    if( na==0 ) return 0;
    
    Unit aext=SignExt(a[na-1]);
    Unit out=mpn_lshift(a+delta,a,na,shift);
    
    return Unit( out|(aext<<shift) );
   }
  
  static void URShift(Unit *a,ulen na,unsigned shift) noexcept // 0<shift<UnitBits
   {
    if( na!=0 ) mpn_rshift(a,a,na,shift);
   }
  
  static void RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift) noexcept // 0<shift<UnitBits
   {
    if( nab!=0 )
      {
       mpn_rshift(b,a,nab,shift);
       
       b[nab-1]|=Unit(SignExt(a[nab-1])<<(UnitBits-shift));
      }
   }

  static void UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift) noexcept // a[na+delta] , 0<shift<UnitBits
   {
    if( na!=0 ) mpn_rshift(a,a+delta,na,shift);
   }
  
  static void ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift) noexcept // a[na+delta] , 0<shift<UnitBits
   {
    if( na!=0 )
      {
       Unit aext=SignExt(a[na+delta-1]);
       
       mpn_rshift(a,a+delta,na,shift);
       
       a[na-1]|=Unit(aext<<(UnitBits-shift));
      }
   }

  // multiplicative operators
 
  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) // nc==na+nb
   {
    if( na<nb )
      {
       Swap(a,b);
       Swap(na,nb);
      }
   
    if( nb==0 )
      {
       Null(c,na);
     
       return;
      }
    
    mpn_mul(c,a,na,b,nb);
   }
 
  static void USq(Unit *restrict c,const Unit *a,ulen na) // nc==2*na
   {
    if( na==0 ) return;
    
    mpn_sqr(c,a,na);
   }
  
  static void Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // nc==na+nb

  static void Sq(Unit *restrict c,const Unit *a,ulen na) noexcept; // nc==2*na
  
  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb
  
  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb); // nc<=na+nb
  
  // data functions  

  static void Null(Unit *a,ulen na) noexcept
   {
    if( na!=0 ) mpn_zero(a,na);
   }

  static void MoveUp(Unit *a,ulen na,ulen delta) noexcept // a[na+delta]
   {
    if( na!=0 ) mpn_copyd(a+delta,a,na);
   }

  static void MoveDown(Unit *a,ulen na,ulen delta) noexcept // a[na+delta]
   {
    if( na!=0 ) mpn_copyi(a,a+delta,na);
   }
 };

} // namespace Math
} // namespace CCore
 
#endif
 

