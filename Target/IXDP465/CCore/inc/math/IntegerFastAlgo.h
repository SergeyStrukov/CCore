/* IntegerFastAlgo.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_math_IntegerFastAlgo_h
#define CCore_inc_math_IntegerFastAlgo_h
 
#include <CCore/inc/Cmp.h>
#include <CCore/inc/math/FastMul.h>

namespace CCore {
namespace Math {

/* classes */

struct IntegerFastAlgo;

struct IntegerExtAlgo;

/* struct IntegerFastAlgo */

struct IntegerFastAlgo
 {
  // types and consts
  
  typedef unsigned Unit;
  
  static const unsigned UnitBits = 32 ; 

  static const Unit MaxUnit = 0xFFFFFFFF ;
  
  static const Unit MSBit = 0x80000000 ;
  
  // private functions
  
  static Unit/* msu */ Inc(Unit *a,ulen na) noexcept; // na>0
  
  static Unit/* msu */ Dec(Unit *a,ulen na) noexcept; // na>0
  
  static void Not_(Unit *a,ulen na) noexcept;
  
  static Unit/* msu */ Not(Unit *a,ulen na) noexcept; // na>0
  
  static Unit/* msu */ IncNot(Unit *a,ulen na) noexcept; // na>0
  
  static Unit/* msu */ DecNot(Unit *a,ulen na) noexcept; // na>0
  
  // private functions
  
  static Unit USignExt(Unit a) { return a>>31; }
  
  static Unit SignExtNot(Unit a) { return int(~a)>>31; }
  
  static Unit/* c */ UInc(Unit *a,ulen na) noexcept;
  
  static Unit/* c */ UDec(Unit *a,ulen na) noexcept;
  
  // private functions
  
  static void RawUMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // nb>=na>=2, nc==na+nb
  
  static void RawUMul1(Unit *restrict c,Unit a,const Unit *b,ulen nb) noexcept; // nb>=2, nc==1+nb
  
  static void RawUMul11(Unit *c,Unit a,Unit b) noexcept; // nc==2
  
  static Unit RawUMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // nb>=na>=2, nc==na+nb
  
  static Unit RawUMac1(Unit *restrict c,Unit a,const Unit *b,ulen nb) noexcept; // nb>=2, nc==1+nb
  
  static Unit RawUMac11(Unit *c,Unit a,Unit b) noexcept; // nc==2
  
  static void RawUMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // nb>=na>=2, 0<nc<=na+nb
  
  static void RawUMulLo1(Unit *restrict c,ulen nc,Unit a,const Unit *b,ulen nb) noexcept; // nb>=2, 0<nc<=1+nb
  
  static void RawUMulLo11(Unit *c,ulen nc,Unit a,Unit b) noexcept; // 0<nc<=2
  
  static void RawUSq(Unit *restrict c,const Unit *a,ulen na) noexcept; // na>=2, nc==2*na 
  
  static void RawUSq1(Unit *c,Unit a) noexcept; // nc==2
  
  // private functions
  
  static CmpResult Cmp_(const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // na>=nb
  
  // functions
  
  static Unit SignExt(Unit a) { return int(a)>>31; }
   
  static Unit SignExt(const Unit *a,ulen na) { return na?SignExt(a[na-1]):0; }
  
  static CmpResult SignCmp(Unit a,Unit b) { return LessCmp(int(a),int(b)); }
  
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
  
  static Unit/* c */ UNeg(Unit *a,ulen na) noexcept;
  
  static Unit/* msu */ Neg(Unit *a,ulen na) noexcept;
  
  static Unit/* c */ UAddUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* msu */ AddUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* c */ USubUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* msu */ SubUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* c */ UNegAddUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* msu */ NegAddUnit(Unit *a,ulen na,Unit b) noexcept;
  
  static Unit/* c */ UAdd(Unit *restrict b,const Unit *a,ulen nab) noexcept;
  
  static Unit/* msu */ Add(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept; // nb>=na

  static Unit/* c */ USub(Unit *restrict b,const Unit *a,ulen nab) noexcept;
  
  static Unit/* msu */ Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept; // nb>=na
  
  static Unit/* c */ URevSub(Unit *restrict b,const Unit *a,ulen nab) noexcept;
  
  static Unit/* msu */ RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na) noexcept; // nb>=na
  
  // shift operators
  
  static Unit/* msu */ ULShift(Unit *a,ulen na,unsigned shift) noexcept; // 0<shift<UnitBits
  
  static Unit/* msu */ LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift) noexcept; // 0<shift<UnitBits

  static Unit/* msu */ UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift) noexcept; // a[na+delta] , 0<shift<UnitBits
  
  static Unit/* msu */ ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift) noexcept; // a[na+delta] , 0<shift<UnitBits
  
  static void URShift(Unit *a,ulen na,unsigned shift) noexcept; // 0<shift<UnitBits
  
  static void RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift) noexcept; // 0<shift<UnitBits

  static void UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift) noexcept; // a[na+delta] , 0<shift<UnitBits
  
  static void ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift) noexcept; // a[na+delta] , 0<shift<UnitBits

  // multiplicative operators
  
  struct DefAlgoBase;
  
  struct DefAlgo1;
  
  struct KAlgo;
  
  struct DefAlgo2;
  
  static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // nc==na+nb
  
  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // nc==na+nb
  
  static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // nc<=na+nb
  
  static void USq(Unit *restrict c,const Unit *a,ulen na) noexcept; // nc==2*na
  
  static void Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb) noexcept; // nc==na+nb

  static void Sq(Unit *restrict c,const Unit *a,ulen na) noexcept; // nc==2*na
  
  // data functions  

  static void Null(Unit *a,ulen na) noexcept;

  static void MoveUp(Unit *a,ulen na,ulen delta) noexcept; // a[na+delta]

  static void MoveDown(Unit *a,ulen na,ulen delta) noexcept; // a[na+delta]
 };

/* struct IntegerExtAlgo */ 

struct IntegerExtAlgo : Math::ConvolutionExtAlgoBase<IntegerFastAlgo,IntegerExtAlgo>
 {
  // operations
  
  static void UNeg3(Unit *a) noexcept;
  
  static Unit UAdd3(Unit *restrict a,const Unit *b) noexcept;
  
  static void USub3(Unit *restrict a,const Unit *b) noexcept;
  
  static void UMulLo3(Unit *restrict c,const Unit *a,const Unit *b) noexcept;
  
  static void USqLo3(Unit *restrict c,const Unit *a) noexcept;
  
  static void URShift3(Unit *a,unsigned shift) noexcept; // 0<shift<UnitBits
  
  static void UNeg4(Unit *a) noexcept;
  
  static Unit UAdd4(Unit *restrict a,const Unit *b) noexcept;
  
  static void USub4(Unit *restrict a,const Unit *b) noexcept;
  
  static void UMulLo4(Unit *restrict c,const Unit *a,const Unit *b) noexcept;
  
  static void USqLo4(Unit *restrict c,const Unit *a) noexcept;
  
  static void URShift4(Unit *a,unsigned shift) noexcept; // 0<shift<2*UnitBits
 };

} // namespace Math
} // namespace CCore
 
#endif
 

