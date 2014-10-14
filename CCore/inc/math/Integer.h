/* Integer.h */ 
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

#ifndef CCore_inc_math_Integer_h
#define CCore_inc_math_Integer_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>

namespace CCore {
namespace Math {

/* functions */

void GuardBitsOfOverflow();

void GuardIntegerInverseNotNormalized();

void GuardIntegerInverseOverflow();

void GuardIntegerZeroDivide();

void GuardIntegerBadString();

void GuardAddLenOverflow_ulen(ulen a,ulen b);

void GuardAddLenOverflow_ulen();

template <class UInt>
void GuardAddLenOverflow(UInt a,ulen b)
 {
  if( a<=MaxULen ) 
    GuardAddLenOverflow_ulen(ulen(a),b);
  else
    GuardAddLenOverflow_ulen();
 }

void GuardQSymEven();

void GuardQSymNotCoprime();

/* functions */

template <class UInt>
ulen AddLen(UInt a,ulen b)
 {
  if( a>MaxULen-b ) GuardAddLenOverflow(a,b);
  
  return ulen(a+b); 
 }

template <class UInt>
ulen AddLen(UInt a,ulen b,ulen c) { return AddLen(a,AddLen(b,c)); }

template <class UInt>
char DecDigit(UInt dig)
 {
  return char('0'+dig);
 }
    
unsigned CountBits(unsigned n);

/* classes */

template <class Algo, template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType = ArrayAlgo > class IntegerInverse;

template <class Unit,class UInt,unsigned UnitBits,unsigned UIntBits> struct IntegerFillUInt_ext;

template <class Unit,class UInt,unsigned UnitBits,unsigned UIntBits> struct IntegerFillUInt_same;

template <class Unit,class UInt,unsigned UnitBits,unsigned UIntBits> struct IntegerFillUInt_split;

template <class Unit,class UInt,unsigned UnitBits,unsigned UIntBits> struct IntegerFillUInt_split_exact;

template <class Algo,class SInt> class SCastInteger;

template <class Algo,class UInt> class UCastInteger;

template <class Algo,class SUInt> class CastInteger;

template <class Algo,class SInt> class IntegerSIntBuilder;

template <class Algo,class UInt> class IntegerUIntBuilder;

template <class Algo> class IntegerNegBuilder;

template <class Algo> class IntegerAddBuilder;

template <class Algo> class IntegerSubBuilder;

template <class Algo> class IntegerMulBuilder;

template <class Algo> class IntegerSqBuilder;

template <class Algo> class IntegerLShiftBuilder;

template <class Algo> class IntegerRShiftBuilder;

template <class Algo, template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType = ArrayAlgo > class IntegerDivider;

template <class Integer> class IntegerFromString;

struct IntegerPrintOpt;

template <class Integer> class PrintInteger;

template <class Algo, template <class T,class A> class ArrayType = RefArray , 
                      template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType = ArrayAlgo > class Integer;

template <class Integer> class RandomInteger;

template <class Algo,class TempArrayType> struct GCDAlgo;

template <class Algo,class TempArrayType> class GCDivBuilder;

template <class Integer> class GCDivType;

/* struct Algo */

#if 0

struct Algo
 {
  // types and consts
  
! typedef ??? Unit; // unsigned integral type
  
! static const unsigned UnitBits = ??? ; 

/ static const Unit MaxUnit = ??? ;
  
/ static const Unit MSBit = ??? ;
  
  // functions
  
  static Unit SignExt(Unit a);
   
! static Unit SignExt(const Unit *a,ulen na);
  
  static CmpResult SignCmp(Unit a,Unit b);
  
! static unsigned CountZeroMSB(Unit a);

  static unsigned CountZeroLSB(Unit a);
   
/ static Unit DoubleUDiv(Unit hi,Unit lo,Unit den); // hi<den
  
  // const operators 
 
/ static CmpResult USign(const Unit *a,ulen na);
  
! static CmpResult Sign(const Unit *a,ulen na); 
  
/ static CmpResult UCmp(const Unit *a,const Unit *b,ulen nab);
  
/ static CmpResult UCmp(const Unit *a,ulen na,const Unit *b,ulen nb);
  
  static CmpResult Cmp(const Unit *a,const Unit *b,ulen nab);
  
! static CmpResult Cmp(const Unit *a,ulen na,const Unit *b,ulen nb);

/ static ulen UNormalize(const Unit *a,ulen na);
  
! static ulen Normalize(const Unit *a,ulen na);
  
  // additive operators 

/ static Unit/* c */ UNeg(Unit *a,ulen na);
  
! static Unit/* msu */ Neg(Unit *a,ulen na);
  
/ static Unit/* c */ UAddUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* msu */ AddUnit(Unit *a,ulen na,Unit b);
  
/ static Unit/* c */ USubUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* msu */ SubUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* c */ UNegAddUnit(Unit *a,ulen na,Unit b);
  
  static Unit/* msu */ NegAddUnit(Unit *a,ulen na,Unit b);
  
/ static Unit/* c */ UAdd(Unit *restrict b,const Unit *a,ulen nab);
  
! static Unit/* msu */ Add(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

/ static Unit/* c */ USub(Unit *restrict b,const Unit *a,ulen nab);
  
! static Unit/* msu */ Sub(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na
  
  static Unit/* c */ URevSub(Unit *restrict b,const Unit *a,ulen nab);
  
! static Unit/* msu */ RevSub(Unit *restrict b,ulen nb,const Unit *a,ulen na); // nb>=na

  // shift operators
  
/ static Unit/* msu */ ULShift(Unit *a,ulen na,unsigned shift); // 0<shift<UnitBits
  
! static Unit/* msu */ LShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift); // 0<shift<UnitBits 

  static Unit/* msu */ UShiftUp(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits
  
! static Unit/* msu */ ShiftUp(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits
  
  static void URShift(Unit *a,ulen na,unsigned shift); // 0<shift<UnitBits

! static void RShift(Unit *restrict b,const Unit *a,ulen nab,unsigned shift); // 0<shift<UnitBits

  static void UShiftDown(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits
  
! static void ShiftDown(Unit *a,ulen na,ulen delta,unsigned shift); // a[na+delta] , 0<shift<UnitBits

  // multiplicative operators

/ static void UMul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb
  
  static Unit/* c */ UMac(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb

/ static void UMulLo(Unit *restrict c,ulen nc,const Unit *a,ulen na,const Unit *b,ulen nb); // nc<=na+nb
  
  static void USq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na

! static void Mul(Unit *restrict c,const Unit *a,ulen na,const Unit *b,ulen nb); // nc==na+nb

! static void Sq(Unit *restrict c,const Unit *a,ulen na); // nc==2*na

  // data functions  

! static void Null(Unit *a,ulen na);

! static void MoveUp(Unit *a,ulen na,ulen delta); // a[na+delta]

! static void MoveDown(Unit *a,ulen na,ulen delta); // a[na+delta]
 };

#endif

/* class IntegerInverse<Algo,ArrayAlgoType> */

template <class Algo, template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType > 
class IntegerInverse : NoCopy
 {
   typedef typename Algo::Unit Unit;
   
   DynArray<Unit,ArrayAlgoType<Unit> > buf; 
   
  private:
  
   static Unit Start(Unit a)
    {
     if( a==Algo::MaxUnit ) return 0;
     
     return Algo::DoubleUDiv(Algo::MaxUnit-a,0,a+1);
    }
   
  public:
  
   IntegerInverse(const Unit *a,ulen na,ulen K);
   
   // range access
   
   const Unit * getPtr() const { return buf.getPtr(); }
   
   const Unit * getPtr_const() const { return buf.getPtr(); }
   
   ulen getLen() const { return buf.getLen(); }
 };
 
template <class Algo, template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType > 
IntegerInverse<Algo,ArrayAlgoType>::IntegerInverse(const Unit *a,ulen na,ulen K)
 {
  if( na==0 ) GuardIntegerInverseNotNormalized();
  
  Unit msa=a[na-1];
  
  if( (msa&Algo::MSBit)==0 ) GuardIntegerInverseNotNormalized();
  
  if( msa==Algo::MSBit && Algo::USign(a,na-1)==0 )
    {
     buf.extend_default(K);
     buf.append_copy(2);
     
     return;
    }
       
  if( K==0 )
    {
     buf.append_copy(1);
     
     return;
    }
    
  if( na>=MaxULen/2 || K>=MaxULen/2-na ) GuardIntegerInverseOverflow(); 
  
  ulen buf_len = 2*(K+na+1) ; // (K+1)+na+(na+K+1);

  Unit *X=buf.extend_raw(buf_len).ptr;    
  ulen k=1;

  Unit *x=X+(K-k);
  Unit *d=X+K+1;
  Unit *P=d+na;

  // 1 x<- d<-
  
  {
   x[1]=1;
   
   x[0]=Start(msa);
   
   Algo::UMul(d,x,2,a,na);
   
   Algo::UNeg(d,na+1);
   
   while( Algo::UCmp(d,na+1,a,na)>=0 )
     {
      x[0]++;
      
      d[na]-=Algo::USub(d,a,na);
     }
  }
  
  // 2
  
  while( 2*k<=K )
    {
     Unit *y=x-k;
     
     Algo::UMul(P,x,k+1,d,na);
     
     Range(y,k).copy(P+na);
     
     Algo::UMulLo(P,na+1,a,na,y,k);
     
     Algo::UNeg(P,na+1);
     
     if( k<=na )
       {
        Algo::UAdd(P+k,d,na+1-k);
       }
       
     if( P[na] || Algo::UCmp(P,a,na)>=0 )  
       {
        Algo::UAddUnit(y,2*k+1,1);
        Algo::USub(P,a,na);
       }

     Range(d,na).copy(P);
    
     k*=2;
     x=y;
    }
  
  // 3
  
  if( k<K )
    {
     ulen l=K-k; // l<k
     
     Algo::UMul(P,x,k+1,d,na);
   
     Range(X,l).copy(P+na+(k-l));
   
     Algo::UMulLo(P,na+1,a,na,X,l);
   
     Algo::UNeg(P,na+1);
   
     if( l<=na )
       {
        Algo::UAdd(P+l,d,na+1-l);
       }
        
     if( P[na] || Algo::UCmp(P,a,na)>=0 )  
       {
        Algo::UAddUnit(X,K+1,1);
       }
    }
    
  // 4  
    
  buf.shrink(buf_len-K-1);  
 }

/* struct IntegerFillUInt_ext<Unit,UInt,unsigned UnitBits,unsigned UIntBits> */ 

template <class Unit,class UInt,unsigned UnitBits,unsigned UIntBits> 
struct IntegerFillUInt_ext
 {
  static const ulen Len = 1 ;
  
  static void FillPos(Unit a[Len],UInt val)
   {
    a[0]=val;
   }
   
  static void FillNeg(Unit a[Len],UInt val)
   {
    a[0]=Unit( val|(Unit(-1)^UInt(-1)) );
   }
 };

/* struct IntegerFillUInt_same<Unit,UInt,unsigned UnitBits,unsigned UIntBits> */

template <class Unit,class UInt,unsigned UnitBits,unsigned UIntBits> 
struct IntegerFillUInt_same
 {
  static const ulen Len = 2 ;
  
  static void FillPos(Unit a[Len],UInt val)
   {
    a[0]=val;
    a[1]=0;
   }
   
  static void FillNeg(Unit a[Len],UInt val)
   {
    a[0]=val;
    a[1]=Unit(-1);
   }
 };
 
/* struct IntegerFillUInt_split<Unit,UInt,unsigned UnitBits,unsigned UIntBits> */

template <class Unit,class UInt,unsigned UnitBits,unsigned UIntBits> 
struct IntegerFillUInt_split
 {
  static const ulen Len = 1+UIntBits/UnitBits ;
  
  static void FillPos(Unit a[Len],UInt val)
   {
    for(ulen i=0; i<Len ;i++)
      {
       a[i]=Unit(val);
        
       val>>=UnitBits;
      }
   }
   
  static void FillNeg(Unit a[Len],UInt val)
   {
    for(ulen i=0; i<Len ;i++)
      {
       a[i]=Unit(val);
        
       val>>=UnitBits;
      }
      
    a[Len-1]|=Unit( Unit(-1)<<(UIntBits%UnitBits) );  
   }
 };

/* struct IntegerFillUInt_split_exact<Unit,UInt,unsigned UnitBits,unsigned UIntBits> */

template <class Unit,class UInt,unsigned UnitBits,unsigned UIntBits> 
struct IntegerFillUInt_split_exact
 {
  static const ulen Len = 1+UIntBits/UnitBits ;
  
  static void FillPos(Unit a[Len],UInt val)
   {
    for(ulen i=0; i<Len-1 ;i++)
      {
       a[i]=Unit(val);
        
       val>>=UnitBits;
      }
    
    a[Len-1]=0;
   }
   
  static void FillNeg(Unit a[Len],UInt val)
   {
    for(ulen i=0; i<Len-1 ;i++)
      {
       a[i]=Unit(val);
        
       val>>=UnitBits;
      }
      
    a[Len-1]=Unit(-1);  
   }
 };

/* type IntegerFillUInt<Unit,UInt,unsigned UnitBits,unsigned UIntBits> */

template <class Unit,class UInt,unsigned UnitBits=Meta::UIntBits<Unit>::Ret,unsigned UIntBits=Meta::UIntBits<UInt>::Ret>
using IntegerFillUInt = Meta::Select<( UIntBits>UnitBits ),
                                       Meta::Select<( UIntBits%UnitBits ),
                                                      IntegerFillUInt_split<Unit,UInt,UnitBits,UIntBits>,
                                                      IntegerFillUInt_split_exact<Unit,UInt,UnitBits,UIntBits> >,
                                       Meta::Select<( UIntBits<UnitBits ),
                                                      IntegerFillUInt_ext<Unit,UInt,UnitBits,UIntBits>,
                                                      IntegerFillUInt_same<Unit,UInt,UnitBits,UIntBits> > > ;

/* class SCastInteger<Algo,SInt> */

template <class Algo,class SInt>
class SCastInteger
 {
   typedef typename Algo::Unit Unit;
  
   static_assert( Meta::IsUInt<Unit>::Ret ,"CCore::Math::SCastInteger<Algo,SInt> : Unit must be an unsigned integral type");
   static_assert( Meta::IsSInt<SInt>::Ret ,"CCore::Math::SCastInteger<Algo,SInt> : SInt must be a signed integral type");

   typedef typename Meta::SIntToUInt<SInt>::UType UInt;
   
   static const ulen Len = IntegerFillUInt<Unit,UInt>::Len ;
   
   Unit buf[Len];
   ulen len;
   
  public: 
   
   explicit SCastInteger(SInt val_)
    {
     UInt val=UInt(val_);
     
     if( val_<0 )
       IntegerFillUInt<Unit,UInt>::FillNeg(buf,val);
     else
       IntegerFillUInt<Unit,UInt>::FillPos(buf,val);
     
     len=Algo::Normalize(buf,Len);
    }
   
   // range access
   
   const Unit * getPtr() const { return buf; }
   
   const Unit * getPtr_const() const { return buf; }
   
   ulen getLen() const { return len; }
 };

/* class UCastInteger<Algo,UInt> */

template <class Algo,class UInt> 
class UCastInteger
 {
   typedef typename Algo::Unit Unit;
 
   static_assert( Meta::IsUInt<Unit>::Ret ,"CCore::Math::UCastInteger<Algo,UInt> : Unit must be an unsigned integral type");
   static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::Math::UCastInteger<Algo,UInt> : UInt must be an unsigned integral type");

   static const ulen Len = IntegerFillUInt<Unit,UInt>::Len ;
  
   Unit buf[Len];
   ulen len;
   
  public: 
  
   explicit UCastInteger(UInt val)
    {
     IntegerFillUInt<Unit,UInt>::FillPos(buf,val);
    
     len=Algo::Normalize(buf,Len);
    }
  
   // range access
  
   const Unit * getPtr() const { return buf; }
  
   const Unit * getPtr_const() const { return buf; }
  
   ulen getLen() const { return len; }
 };

/* class CastInteger<Algo,SUInt> */

template <class Algo,class SUInt> 
class CastInteger
 {
   typedef typename Algo::Unit Unit;
  
   typedef Meta::Select<( SUInt(-1)<0 ), SCastInteger<Algo,SUInt> ,
                                         UCastInteger<Algo,SUInt> > CastType;

   CastType cast;
   
  public: 
  
   explicit CastInteger(SUInt val) : cast(val) {}
  
   // range access
  
   const Unit * getPtr() const { return cast.getPtr(); }
  
   const Unit * getPtr_const() const { return cast.getPtr_const(); }
  
   ulen getLen() const { return cast.getLen(); }
 };

/* class IntegerSIntBuilder<Algo,SInt> */

template <class Algo,class SInt>
class IntegerSIntBuilder
 {
   typedef typename Algo::Unit Unit;
  
   typedef typename Meta::SIntToUInt<SInt>::UType UInt;
   
   //
   // SInt::MaxVal < UInt::Mod
   // SInt::MinVal >= -UInt::Mod 
   //
   
   UInt val;
   bool neg;
   
  public: 
  
   explicit IntegerSIntBuilder(SInt val_)
    {
     val=UInt(val_);
     neg=(val_<0);
    }
   
   ulen getLen() const
    {
     return IntegerFillUInt<Unit,UInt>::Len;
    }
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *a=place;
     ulen n=getLen();
     
     if( neg )
       IntegerFillUInt<Unit,UInt>::FillNeg(a,val);
     else
       IntegerFillUInt<Unit,UInt>::FillPos(a,val);

     return Range(a,n);
    }
 };
 
/* class IntegerUIntBuilder<Algo,UInt> */

template <class Algo,class UInt>
class IntegerUIntBuilder
 {
   typedef typename Algo::Unit Unit;
 
   UInt val;
   
  public: 
  
   explicit IntegerUIntBuilder(UInt val_) : val(val_) {}
   
   ulen getLen() const
    {
     return IntegerFillUInt<Unit,UInt>::Len;
    }
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *a=place;
     ulen n=getLen();
     
     IntegerFillUInt<Unit,UInt>::FillPos(a,val);

     return Range(a,n);
    }
 };
 
/* class IntegerNegBuilder<Algo> */

template <class Algo>
class IntegerNegBuilder
 {
   typedef typename Algo::Unit Unit;
   
   PtrLen<const Unit> a;
   
  public: 
  
   explicit IntegerNegBuilder(PtrLen<const Unit> a_) : a(a_) {}
   
   ulen getLen() const { return AddLen(a.len,1); } 
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *b=place;
     ulen n=a.len;
     
     Range(b,n).copy(a.ptr);
     
     b[n]=Algo::Neg(b,n);
     
     return Range(b,n+1);
    }
 };
   
/* class IntegerAddBuilder<Algo> */

template <class Algo>
class IntegerAddBuilder
 {
   typedef typename Algo::Unit Unit;
  
   PtrLen<const Unit> a;
   PtrLen<const Unit> b;
   
  public:
  
   IntegerAddBuilder(PtrLen<const Unit> a_,PtrLen<const Unit> b_)
    {
     if( a_.len<=b_.len )
       {
        a=a_;
        b=b_;
       }
     else
       {
        a=b_;
        b=a_;
       } 
     
     // a.len <= b.len
    }
    
   ulen getLen() const { return AddLen(b.len,1); } 
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *c=place;
     ulen n=b.len;
     
     Range(c,n).copy(b.ptr);
     
     c[n]=Algo::Add(c,n,a.ptr,a.len);
     
     return Range(c,n+1);
    }
 };
 
/* IntegerSubBuilder<Algo> */

template <class Algo>
class IntegerSubBuilder
 {
   typedef typename Algo::Unit Unit;
  
   PtrLen<const Unit> a;
   PtrLen<const Unit> b;
   bool rev_flag;
   
  public:
  
   IntegerSubBuilder(PtrLen<const Unit> b_,PtrLen<const Unit> a_)
    {
     if( a_.len<=b_.len )
       {
        a=a_;
        b=b_;
        rev_flag=false;
       }
     else
       {
        a=b_;
        b=a_;
        rev_flag=true;
       }  
     
     // a.len <= b.len
    }
    
   ulen getLen() const { return AddLen(b.len,1); } 
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *c=place;
     ulen n=b.len;
     
     Range(c,n).copy(b.ptr);
     
     if( rev_flag )
       {
        c[n]=Algo::RevSub(c,n,a.ptr,a.len);
       } 
     else  
       {
        c[n]=Algo::Sub(c,n,a.ptr,a.len);
       } 
     
     return Range(c,n+1);
    }
 };
 
/* class IntegerMulBuilder<Algo> */

template <class Algo>
class IntegerMulBuilder
 {
   typedef typename Algo::Unit Unit;
  
   PtrLen<const Unit> a;
   PtrLen<const Unit> b;
   ulen n;
   
  public:
  
   IntegerMulBuilder(PtrLen<const Unit> a_,PtrLen<const Unit> b_) 
    : a(a_),b(b_) 
    {
     n=AddLen(a_.len,b_.len);
    }
    
   ulen getLen() const { return n; } 
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *c=place;
     
     Algo::Mul(c,a.ptr,a.len,b.ptr,b.len);
     
     return Range(c,n);
    }
 };

/* IntegerSqBuilder<Algo> */

template <class Algo>
class IntegerSqBuilder
 {
   typedef typename Algo::Unit Unit;
 
   PtrLen<const Unit> a;
   ulen n;
   
  public:
   
   explicit IntegerSqBuilder(PtrLen<const Unit> a_) 
    : a(a_) 
    {
     n=AddLen(a_.len,a_.len);
    }
   
   ulen getLen() const { return n; } 
  
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *c=place;
    
     Algo::Sq(c,a.ptr,a.len);
    
     return Range(c,n);
    }
 };
 
/* class IntegerLShiftBuilder<Algo> */

template <class Algo>
class IntegerLShiftBuilder
 {
   typedef typename Algo::Unit Unit;

   PtrLen<const Unit> a;
   unsigned shift,full;
   ulen n;
 
  public:
  
   IntegerLShiftBuilder(PtrLen<const Unit> a_,unsigned shift_)
    : a(a_)
    {
     full=unsigned(shift_/Algo::UnitBits);
     shift=unsigned(shift_%Algo::UnitBits);
     
     n=AddLen(full,a.len,(shift!=0));
    } 
   
   ulen getLen() const { return n; }
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *b=place;
     
     Algo::Null(b,full);
     
     if( shift )
       {
        b[full+a.len]=Algo::LShift(b+full,a.ptr,a.len,shift);
       }
     else
       {
        Range(b+full,a.len).copy(a.ptr);
       }
       
     return Range(b,n);
    }
 };
 
/* class IntegerRShiftBuilder<Algo> */

template <class Algo>
class IntegerRShiftBuilder
 {
   typedef typename Algo::Unit Unit;

   PtrLen<const Unit> a;
   unsigned shift,full;
   ulen n;
   
  public:
  
   IntegerRShiftBuilder(PtrLen<const Unit> a_,unsigned shift_)
    : a(a_)
    {
     full=unsigned(shift_/Algo::UnitBits);
     shift=unsigned(shift_%Algo::UnitBits);
     
     if( full<a.len )
       n=a.len-full;
     else
       n=1;  
    }
   
   ulen getLen() const { return n; }
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *b=place;
     
     if( full<a.len )
       {
        if( shift )
          Algo::RShift(b,a.ptr+full,n,shift);
        else
          Range(b,n).copy(a.ptr+full);
       }
     else
       {
        b[0]=Algo::SignExt(a.ptr,a.len);
       }
       
     return Range(b,n);
    }
 };
 
/* class IntegerDivider<Algo,ArrayAlgoType> */

template <class Algo, template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType > 
class IntegerDivider : NoCopy
 {
   typedef typename Algo::Unit Unit;
   
   struct Normalize;

   DynArray<Unit,ArrayAlgoType<Unit> > buf;
   Unit minus_one;
   PtrLen<const Unit> result;
   DynArray<Unit,ArrayAlgoType<Unit> > mod_buf;
   PtrLen<const Unit> mod;
   
  public:
  
   explicit IntegerDivider(PtrLen<const Unit> a,PtrLen<const Unit> b,bool do_mod=false);
   
   PtrLen<const Unit> getResult() const { return result; } // [a/b]
   
   PtrLen<const Unit> getMod() const { return mod; }
 };
 
template <class Algo, template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType > 
struct IntegerDivider<Algo,ArrayAlgoType>::Normalize
 {
  PtrLen<Unit> result_a;
  PtrLen<Unit> result_b;
  unsigned shift;
  bool neg;
  
  void doB(const Unit *b,ulen nb,Unit *c) // [nb+1]
   {
    Range(c,nb).copy(b);

    switch( Algo::Sign(c,nb) )
     {
      case CmpEqual : GuardIntegerZeroDivide();
    
      case CmpLess :
       {
        neg=true;
      
        Algo::UNeg(c,nb);
       }
      break; 
    
      default: // case CmpGreater :
       {
        neg=false;
       }
     }
     
    nb=Algo::UNormalize(c,nb);
      
    shift=Algo::CountZeroMSB(c[nb-1]);
      
    if( shift ) Algo::ULShift(c,nb,shift);
    
    c[nb]=0;
    
    result_b=Range(c,nb+1);
   }
  
  void doA(const Unit *a,ulen na,Unit *d) // [na+1]
   {
    if( shift )     
      {
       d[na]=Algo::LShift(d,a,na,shift);
      }
    else
      {
       Range(d,na).copy(a);
       
       d[na]=Algo::SignExt(d,na);
      }  
    
    if( neg ) Algo::UNeg(d,na+1); // 2 msb of d the same
    
    result_a=Range(d,na+1);
   }
  
  Normalize(PtrLen<const Unit> a,PtrLen<const Unit> b,Unit *temp) // [a.len+b.len+2]
   {
    doB(b.ptr,b.len,temp);
    doA(a.ptr,a.len,temp+b.len+1);
   };
 };

template <class Algo, template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType > 
IntegerDivider<Algo,ArrayAlgoType>::IntegerDivider(PtrLen<const Unit> a,PtrLen<const Unit> b,bool do_mod)
 {
  ulen len=AddLen(a.len,b.len,2);
  
  DynArray<Unit,ArrayAlgoType<Unit> > temp(DoRaw{len});
  
  Normalize norm(a,b,temp.getPtr());
  
  ulen nb=norm.result_b.len-1;
  ulen na=norm.result_a.len;
  
  if( na<=nb )
    {
     if( Algo::Sign(norm.result_a.ptr,na)<0 ) 
       {
        minus_one=Unit(-1);
        
        result.ptr=&minus_one;
        result.len=1;
        
        if( do_mod ) // mod = a+b
          {
           mod_buf.extend(IntegerAddBuilder<Algo>(a,b));
           
           ulen nlen=Algo::Normalize(mod_buf.getPtr(),mod_buf.getLen());
           
           mod=Range_const(mod_buf.getPtr(),nlen);
          }
       }
     else
       {
        // result == 0
        
        if( do_mod ) // mod = a
          {
           ulen nlen=Algo::Normalize(a.ptr,a.len);
           
           mod_buf.extend_copy(nlen,a.ptr);
           
           mod=Range_const(mod_buf);
          }
       }
    }
  else
    {
     IntegerInverse<Algo,ArrayAlgoType> c(norm.result_b.ptr,nb,na-nb); // c = [ (M^na)/norm_b ]
     
     DynArray<Unit,ArrayAlgoType<Unit> > ac(DoBuild,IntegerMulBuilder<Algo>(Range_const(norm.result_a),Range_const(c)));
     
     PtrLen<Unit> p(ac.getPtr()+na,ac.getLen()-na); // p = [ (norm_a*c)/(M^na) ]

     if( Algo::Sign(norm.result_a.ptr,na)>=0 )
       {
        Algo::UAddUnit(p.ptr,p.len,1);
       }

     DynArray<Unit,ArrayAlgoType<Unit> > bp(DoBuild,IntegerMulBuilder<Algo>(Range_const(norm.result_b),Range_const(p)));
        
     if( Algo::Cmp(bp.getPtr(),bp.getLen(),norm.result_a.ptr,na)>0 ) 
       {
        Algo::USubUnit(p.ptr,p.len,1);
        
        if( do_mod )
          {
           Algo::Sub(bp.getPtr(),bp.getLen(),norm.result_b.ptr,norm.result_b.len);
          }
       }
       
     ulen np=Algo::Normalize(p.ptr,p.len);
     
     result=Range_const(p.ptr,np);
     
     Swap(buf,ac);
     
     if( do_mod )
       {
        Algo::USub(norm.result_a.ptr,bp.getPtr(),norm.result_b.len);
        
        if( norm.shift ) Algo::URShift(norm.result_a.ptr,norm.result_b.len,norm.shift);
        
        if( norm.neg ) Algo::UNeg(norm.result_a.ptr,norm.result_b.len);
        
        ulen nlen=Algo::Normalize(norm.result_a.ptr,norm.result_b.len);

        mod=Range_const(norm.result_a.ptr,nlen);
        
        Swap(mod_buf,temp);
       }
    }
 }
 
/* class IntegerFromString<Integer> */

template <class Integer> 
class IntegerFromString 
 {
   static const ulen LoLen = (3*Meta::UIntBits<unsigned>::Ret)/10 ; // 10^LoLen-1 <= unsigned::MaxVal
                                                                    // 0.3 < log10(2) 
   
   static_assert( LoLen>=2 ,"CCore::Math::IntegerFromString<Integer> : bad LoLen");
  
  private:
   
   Integer pow10[Meta::UIntBits<ulen>::Ret]; // 10^(2^index) , [K+1]
   ulen K;
   
  private: 
 
   //
   // str.len <= 2^(k+1) , k<=K
   //

   Integer convert(StrLen str,ulen k) const;
   
  public:
  
   explicit IntegerFromString(ulen max_len);
   
   ~IntegerFromString() {}

   Integer operator () (StrLen str) const;
 };
 
template <class Integer> 
Integer IntegerFromString<Integer>::convert(StrLen str,ulen k) const
 {
  ulen n=str.len;
  
  if( n<=LoLen || k==0 )
    {
     if( !n ) GuardIntegerBadString();
     
     unsigned ret=0;
     
     for(; +str ;++str)
       {
        DecValue dig(*str);
        
        if( !dig ) GuardIntegerBadString();
       
        ret=10*ret+(*dig);
       }
    
     return ret;
    }
 
  ulen m=ulen(1)<<k;
  
  if( m<n )
    {
     StrLen str_hi=(str+=(n-m));
     
     Integer lo=convert(str,k-1);
     Integer hi=convert(str_hi,k-1);
  
     return lo+hi*pow10[k];
    }
  else
    {
     return convert(str,k-1);
    }
 }
 
template <class Integer> 
IntegerFromString<Integer>::IntegerFromString(ulen max_len)
 {
  if( !max_len ) GuardIntegerBadString();
 
  ulen k=0;
  
  pow10[0]=10;
  
  for(ulen m=1; m<max_len-m ;m<<=1,k++) pow10[k+1]=pow10[k].sq();
    
  K=k;  
 }
 
template <class Integer> 
Integer IntegerFromString<Integer>::operator () (StrLen str) const 
 {
  if( !str ) GuardIntegerBadString();
  
  switch( *str )
    {
     case '-' : ++str; return -convert(str,K);
     
     case '+' : ++str; // falldown;
     
     default: return convert(str,K);
    }
 }

/* struct IntegerPrintOpt */

struct IntegerPrintOpt
 {
  ulen width;
  IntShowSign show_sign;
  
  void setDefault()
   {
    width=0;
    show_sign=IntShowSignDefault;
   }
  
  IntegerPrintOpt() { setDefault(); }
  
  IntegerPrintOpt(const char *ptr,const char *lim);
  
  //
  // [+][width=0]
  //
 };

/* class PrintInteger<Integer> */

template <class Integer> 
class PrintInteger : NoCopy
 {
   typedef typename Integer::Unit Unit;
  
  private:
  
   Integer pow10[Integer::UnitBits+Meta::UIntBits<ulen>::Ret]; // 10^(2^index) , [K+1]
   ulen K;
   
  private:
   
   struct Get_combine
    {
     static bool Do(PtrLen<const Unit> body,unsigned &ret);
    };
   
   struct Get_never
    {
     static bool Do(PtrLen<const Unit>,unsigned &) { return false; }
    };
   
   typedef Meta::Select<( Integer::UnitBits<Meta::UIntBits<unsigned>::Ret ), Get_combine , Get_never > Get;
   
   static bool GetUnsigned(PtrLen<const Unit> body,unsigned &ret);
  
   template <class P>
   bool print_lo_short(P &out,PtrLen<const Unit> body,ulen k) const;
   
   template <class P>
   bool print_short(P &out,ulen width,PtrLen<const Unit> body) const;
   
   template <class P>
   void print_lo(P &out,ulen k) const;
    
   template <class P>
   void print_lo(P &out,Integer a,ulen k) const;
    
   //
   // a < 10^(2^(k+1)) , k <= K
   //
   
   template <class P>
   void print(P &out,ulen width,Integer a,ulen k) const;
   
  public:
  
   explicit PrintInteger(ulen max_body_len);
   
   ~PrintInteger() {}
   
   template <class P>
   void operator () (P &out,IntegerPrintOpt opt,Integer a) const;
 };
 
template <class Integer>
bool PrintInteger<Integer>::Get_combine::Do(PtrLen<const Unit> body,unsigned &ret)
 {
  if( body.len>Meta::UIntBits<unsigned>::Ret/Integer::UnitBits ) return false;
  
  unsigned temp=0;
  
  for(auto fin=body.getFin(); fin.next() ;)
    {
     temp<<=Integer::UnitBits;
     temp|=unsigned(*fin);
    }

  ret=temp;
  
  return true;
 }

template <class Integer> 
bool PrintInteger<Integer>::GetUnsigned(PtrLen<const Unit> body,unsigned &ret)
 {
  if( body.len && body.back(1)==0 ) body.len--;
  
  if( body.len==0 )
    {
     ret=0;
     
     return true;
    }
  
  if( body.len==1 )
    {
     Unit u=body[0];
     
     if( u<=unsigned(-1) )
       {
        ret=u;
     
        return true;
       }
     
     return false;
    }
  
  return Get::Do(body,ret);
 }

template <class Integer> 
template <class P>
bool PrintInteger<Integer>::print_lo_short(P &out,PtrLen<const Unit> body,ulen k) const
 {
  unsigned value;
  
  if( k+1<Meta::UIntBits<ulen>::Ret && GetUnsigned(body,value) )
    {
     IntPrintOpt opt;
     
     opt.width=ulen(1)<<(k+1);
     opt.align=IntAlignInternal;
     
     Putobj(out,BindOpt(opt,value));
     
     return true;
    }
  
  return false;
 }

template <class Integer> 
template <class P>
bool PrintInteger<Integer>::print_short(P &out,ulen width,PtrLen<const Unit> body) const
 {
  unsigned value;
  
  if( GetUnsigned(body,value) )
    {
     IntPrintOpt opt;
     
     opt.align=IntAlignInternal;
     opt.width=width;
     
     Putobj(out,BindOpt(opt,value));
     
     return true;
    }

  return false;
 }

template <class Integer> 
template <class P>
void PrintInteger<Integer>::print_lo(P &out,ulen k) const
 {
  if( k+1>=Meta::UIntBits<ulen>::Ret )
    { // huge output
     print_lo(out,k-1);
     print_lo(out,k-1);
    }
  else
    {
     Putobj(out,RepeatChar(ulen(1)<<(k+1),'0'));
    }  
 }
    
template <class Integer> 
template <class P>
void PrintInteger<Integer>::print_lo(P &out,Integer a,ulen k) const
 {
  if( print_lo_short(out,a.getBody(),k) ) return;
    
  if( !a )
    {
     print_lo(out,k);
    }
  else if( k>0 )
    {
     auto divmod=a.divmod(pow10[k]);
     
     print_lo(out,divmod.div,k-1);
     
     print_lo(out,divmod.mod,k-1);
    }
 }
    
template <class Integer> 
template <class P>
void PrintInteger<Integer>::print(P &out,ulen width,Integer a,ulen k) const
 {
  if( print_short(out,width,a.getBody()) ) return;
  
  if( k>0 )
    {
     if( a<pow10[k] )
       {
        print(out,width,a,k-1);
       } 
     else  
       {
        auto divmod=a.divmod(pow10[k]);
        
        if( k<Meta::UIntBits<ulen>::Ret && (width>>k) )
          width-=(ulen(1)<<k);
        else
          width=0;
          
        print(out,width,divmod.div,k-1);
        
        print_lo(out,divmod.mod,k-1);
       } 
    }
 }
  
template <class Integer> 
PrintInteger<Integer>::PrintInteger(ulen max_body_len)
 {
  pow10[0]=10;
     
  ulen k=0;
     
  for(;;) 
    {
     Integer p2=pow10[k].sq();
        
     if( p2.getBody().len>max_body_len ) break; // 10^(2^(k+1)) > 2^(max_body_len*UnitBits-1)
       
     pow10[++k]=p2;
    }
     
  K=k;
 }

template <class Integer> 
template <class P>
void PrintInteger<Integer>::operator () (P &out,IntegerPrintOpt opt,Integer a) const 
 {
  switch( a.sign() )
    {
     case CmpLess :
      {
       out.put('-');
       
       print(out,PosSub(opt.width,1),-a,K);
      }
     break;
     
     case CmpEqual :
      {
       if( opt.show_sign==IntShowPlus )
         {
          out.put('+');
          
          opt.width=PosSub(opt.width,1);
         }

       if( opt.width )
         out.put('0',opt.width);
       else
         out.put('0');
      }
     break;
     
     default: // case CmpGreater :
      {
       if( opt.show_sign==IntShowPlus )
         {
          out.put('+');
          
          opt.width=PosSub(opt.width,1);
         }
       
       print(out,opt.width,a,K);
      }
    }
 }

/* class Integer<Algo,ArrayType,ArrayAlgoType> */ 

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
class Integer
 {
  public:
   
   typedef Algo AlgoType;
   
   typedef typename Algo::Unit Unit;
   
   static const unsigned UnitBits = Algo::UnitBits ;
   
   using TempArrayType = DynArray<Unit,ArrayAlgoType<Unit> > ;
   
  private: 
   
   ArrayType<Unit,ArrayAlgoType<Unit> > body;
   
  private: 
   
   // builders

   typedef IntegerNegBuilder<Algo> NegBuilder;
   typedef IntegerAddBuilder<Algo> AddBuilder;
   typedef IntegerSubBuilder<Algo> SubBuilder;
   typedef IntegerMulBuilder<Algo> MulBuilder;
   typedef IntegerSqBuilder<Algo> SqBuilder;
   typedef IntegerLShiftBuilder<Algo> LShiftBuilder;
   typedef IntegerRShiftBuilder<Algo> RShiftBuilder;
   
   // normalization
   
   void normalize();
   
   // operators
   
   Integer & add(const Unit *b,ulen nb); // not overlapped
   
   Integer & sub(const Unit *b,ulen nb); // not overlapped
   
   Integer & revsub(const Unit *b,ulen nb); // not overlapped
   
   Integer & mul(const Unit *b,ulen nb);
   
   Integer & div(const Unit *b,ulen nb);
   
   Integer & mod(const Unit *b,ulen nb);
   
  private: 
   
   enum CopyFromType { CopyFrom };
   
   explicit Integer(CopyFromType,PtrLen<const Unit> data) : body(DoCopy(data.len),data.ptr) {}
   
  public:
   
   // generic constructor 

   template <class Builder>
   Integer(DoBuildType,Builder builder) : body(DoBuild,builder) { normalize(); }
   
   // constructors 
  
   Integer() {}
   
   Integer(StrLen str);
   
   template <class UInt>
   Integer(UInt val,Meta::EnableIf<Meta::IsUInt<UInt>::Ret> =0);
   
   template <class SInt>
   Integer(SInt val,Meta::EnableIf<Meta::IsSInt<SInt>::Ret> =0);
   
   ~Integer() {}
    
   // methods
   
   CmpResult sign() const;
   
   bool operator ! () const { return !sign(); }
   
   struct BitsOf
    {
     ulen units;
     unsigned msbits;
     
     BitsOf(ulen units_,unsigned msbits_) : units(units_),msbits(msbits_) {}
     
     template <class UInt>
     void total(UInt &ret) const
      {
       static_assert( UnitBits<=UInt(-1) ,"CCore::Math::Integer<Algo,ArrayType>::BitsOf::total<UInt> : too short UInt");
       
       if( units>(UInt(-1)-msbits)/UnitBits ) GuardBitsOfOverflow();
        
       ret=UInt( units*UInt(UnitBits)+msbits );
      }
     
     unsigned total() const
      {
       unsigned ret;
       
       total(ret);
       
       return ret;
      }
    };
   
   BitsOf bitsOf() const;
   
   Integer sq() const;
   
   Integer pow(unsigned deg) const;
   
   void modify() { body.modify(); }
   
   void cloneTo(Integer &ret) const { body.cloneTo(ret.body); }
   
   Integer & set_null() { body.erase(); return *this; }
   
   PtrLen<const Unit> getBody() const { return Range_const(body); }
   
   PtrLenReverse<const Unit> getBodyReverse() const { return RangeReverse_const(body); }
   
   bool isOdd() const { return body.getLen() && (body[0]&Unit(1)) ; }
   
   bool isEven() const { return !isOdd(); }
   
   // cast
   
   template <class UInt>
   Meta::EnableIf<Meta::IsUInt<UInt>::Ret,UInt> cast() const
    {
     UInt ret=0;
     unsigned shift=0;
     
     for(Unit a : body ) 
       {
        if( shift>=Meta::UIntBits<UInt>::Ret ) break;
       
        ret|=(UInt(a)<<shift);
        
        shift+=UnitBits;
       }
     
     return ret;
    }
   
   // cmp objects
   
   CmpResult objCmp(const Integer &b) const
    {
     return Algo::Cmp(body.getPtr(),body.getLen(),b.body.getPtr(),b.body.getLen());
    }
   
   // operators
   
   static Integer Neg(PtrLen<const Unit> a);
   
   static Integer Add(PtrLen<const Unit> a,PtrLen<const Unit> b);
   
   static Integer Sub(PtrLen<const Unit> a,PtrLen<const Unit> b);
   
   static Integer Mul(PtrLen<const Unit> a,PtrLen<const Unit> b);
   
   static Integer Sq(PtrLen<const Unit> a);
   
   static Integer Div(PtrLen<const Unit> a,PtrLen<const Unit> b);
   
   static Integer Mod(PtrLen<const Unit> a,PtrLen<const Unit> b);
   
   static Integer LShift(PtrLen<const Unit> a,unsigned shift);
   
   static Integer RShift(PtrLen<const Unit> a,unsigned shift);
   
   struct DivMod
    {
     Integer div;
     Integer mod;
     
     DivMod(PtrLen<const Unit> a,PtrLen<const Unit> b);
    };
   
   // operators
   
   Integer & neg();
   
   Integer & revsub(const Integer &b);
   
   Integer & operator += (const Integer &b);
   
   Integer & operator -= (const Integer &b);
   
   Integer & operator *= (const Integer &b);
   
   Integer & operator /= (const Integer &b);
   
   Integer & operator %= (const Integer &b);
   
   Integer & operator <<= (unsigned shift);
   
   Integer & operator >>= (unsigned shift);
   
   // operators
   
   Integer operator - () const 
    { 
     return Neg(getBody()); 
    }
   
   friend Integer operator + (const Integer &a,const Integer &b)
    {
     return Add(a.getBody(),b.getBody());
    }
    
   friend Integer operator - (const Integer &a,const Integer &b)
    {
     return Sub(a.getBody(),b.getBody());
    }
   
   friend Integer operator * (const Integer &a,const Integer &b)
    {
     return Mul(a.getBody(),b.getBody());
    }
   
   friend Integer operator / (const Integer &a,const Integer &b)
    {
     return Div(a.getBody(),b.getBody());
    }
   
   friend Integer operator % (const Integer &a,const Integer &b)
    {
     return Mod(a.getBody(),b.getBody());
    }
   
   Integer operator << (unsigned shift) const
    {
     if( shift )
       return LShift(getBody(),shift); 
     else
       return (*this);
    }
   
   Integer operator >> (unsigned shift) const
    {
     if( shift )
       return RShift(getBody(),shift); 
     else
       return (*this);
    }
   
   DivMod divmod(const Integer &b) const { return DivMod(getBody(),b.getBody()); }
   
   friend bool operator == (const Integer &a,const Integer &b) { return a.objCmp(b)==0; }
   
   friend bool operator != (const Integer &a,const Integer &b) { return a.objCmp(b)!=0; }
   
   friend bool operator < (const Integer &a,const Integer &b) { return a.objCmp(b)<0; }
   
   friend bool operator > (const Integer &a,const Integer &b) { return a.objCmp(b)>0; }
   
   friend bool operator <= (const Integer &a,const Integer &b) { return a.objCmp(b)<=0; }
   
   friend bool operator >= (const Integer &a,const Integer &b) { return a.objCmp(b)>=0; }
   
   // operators
   
   template <class SUInt,class RetType=Integer>
   using EnableIfSUInt = Meta::EnableIf< Meta::IsSUInt<SUInt>::Ret , RetType > ;
  
   template <class SUInt>
   EnableIfSUInt<SUInt> & revsub(SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);
     
     return revsub(cast.getPtr(),cast.getLen());
    }
   
   template <class SUInt>
   EnableIfSUInt<SUInt> & operator += (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);
     
     return add(cast.getPtr(),cast.getLen());
    }
   
   template <class SUInt>
   EnableIfSUInt<SUInt> & operator -= (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);
     
     return sub(cast.getPtr(),cast.getLen());
    }
   
   template <class SUInt>
   EnableIfSUInt<SUInt> & operator *= (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);
 
     return mul(cast.getPtr(),cast.getLen());
    }
   
   template <class SUInt>
   EnableIfSUInt<SUInt> & operator /= (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);
 
     return div(cast.getPtr(),cast.getLen());
    }
   
   template <class SUInt>
   EnableIfSUInt<SUInt> & operator %= (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);

     return mod(cast.getPtr(),cast.getLen());
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator + (const Integer &a,SUInt b)
    {
     CastInteger<Algo,SUInt> cast(b);

     return Add(a.getBody(),Range(cast));
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator + (SUInt a,const Integer &b)
    {
     CastInteger<Algo,SUInt> cast(a);

     return Add(Range(cast),b.getBody());
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator - (const Integer &a,SUInt b)
    {
     CastInteger<Algo,SUInt> cast(b);

     return Sub(a.getBody(),Range(cast));
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator - (SUInt a,const Integer &b)
    {
     CastInteger<Algo,SUInt> cast(a);

     return Sub(Range(cast),b.getBody());
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator * (const Integer &a,SUInt b)
    {
     CastInteger<Algo,SUInt> cast(b);

     return Mul(a.getBody(),Range(cast));
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator * (SUInt a,const Integer &b)
    {
     CastInteger<Algo,SUInt> cast(a);

     return Mul(Range(cast),b.getBody());
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator / (const Integer &a,SUInt b)
    {
     CastInteger<Algo,SUInt> cast(b);

     return Div(a.getBody(),Range(cast));
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator / (SUInt a,const Integer &b)
    {
     CastInteger<Algo,SUInt> cast(a);

     return Div(Range(cast),b.getBody());
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator % (const Integer &a,SUInt b)
    {
     CastInteger<Algo,SUInt> cast(b);

     return Mod(a.getBody(),Range(cast));
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt> operator % (SUInt a,const Integer &b)
    {
     CastInteger<Algo,SUInt> cast(a);

     return Mod(Range(cast),b.getBody());
    }
   
   template <class SUInt>
   EnableIfSUInt<SUInt,DivMod> divmod(SUInt b) const
    {
     CastInteger<Algo,SUInt> cast(b);
     
     return DivMod(getBody(),Range(cast)); 
    }
   
   template <class SUInt>
   EnableIfSUInt<SUInt,CmpResult> cmp(SUInt b) const
    {
     CastInteger<Algo,SUInt> cast(b);
     
     return Algo::Cmp(body.getPtr(),body.getLen(),cast.getPtr(),cast.getLen());
    }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator == (const Integer &a,SUInt b) { return a.cmp(b)==0; } 
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator == (SUInt a,const Integer &b) { return b.cmp(a)==0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator != (const Integer &a,SUInt b) { return a.cmp(b)!=0; } 
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator != (SUInt a,const Integer &b) { return b.cmp(a)!=0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator < (const Integer &a,SUInt b) { return a.cmp(b)<0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator < (SUInt a,const Integer &b) { return b.cmp(a)>0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator > (const Integer &a,SUInt b) { return a.cmp(b)>0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator > (SUInt a,const Integer &b) { return b.cmp(a)<0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator <= (const Integer &a,SUInt b) { return a.cmp(b)<=0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator <= (SUInt a,const Integer &b) { return b.cmp(a)>=0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator >= (const Integer &a,SUInt b) { return a.cmp(b)>=0; }
   
   template <class SUInt>
   friend EnableIfSUInt<SUInt,bool> operator >= (SUInt a,const Integer &b) { return b.cmp(a)<=0; }
   
   // print object

   typedef IntegerPrintOpt PrintOptType; 
   
   template <class P>   
   void print(P &out,PrintOptType opt) const;
   
   // swap/move objects
   
   void objSwap(Integer &obj) 
    {  
     Swap(body,obj.body);
    }
   
   explicit Integer(ToMoveCtor<Integer> obj) : body(ObjToMove(obj->body)) {}
   
   Integer * objMove(Place<void> place)
    {
     return CtorMove(this,place); 
    } 
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
 // normalization
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
void Integer<Algo,ArrayType,ArrayAlgoType>::normalize()
 {
  ulen len=body.getLen();
  ulen new_len=Algo::Normalize(body.getPtr(),len);

  if( len!=new_len ) body.shrink(len-new_len);
  
  body.shrink_extra();
 }
 
 // operators

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::add(const Unit *b,ulen nb)
 {
  ulen na=body.getLen();
  
  if( na>=nb )
    {
     Unit *a=body.append_raw();
     
     (*a)=Algo::Add(a-na,na,b,nb);
    }
  else
    {
     ArrayType<Unit,ArrayAlgoType<Unit> > result(DoBuild,AddBuilder(getBody(),Range(b,nb)));
     
     Swap(body,result);
    }  
  
  normalize();
  
  return *this;
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::sub(const Unit *b,ulen nb)
 {
  ulen na=body.getLen();
  
  if( na>=nb )
    {
     Unit *a=body.append_raw();
     
     (*a)=Algo::Sub(a-na,na,b,nb);
    }
  else
    {
     ArrayType<Unit,ArrayAlgoType<Unit> > result(DoBuild,SubBuilder(getBody(),Range(b,nb)));
     
     Swap(body,result);
    }  
  
  normalize();
  
  return *this;
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::revsub(const Unit *b,ulen nb)
 {
  ulen na=body.getLen();
  
  if( na>=nb )
    {
     Unit *a=body.append_raw();
     
     (*a)=Algo::RevSub(a-na,na,b,nb);
    }
  else
    {
     ArrayType<Unit,ArrayAlgoType<Unit> > result(DoBuild,SubBuilder(Range(b,nb),getBody()));
     
     Swap(body,result);
    }  
  
  normalize();
  
  return *this;
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::mul(const Unit *b,ulen nb)
 {
  ArrayType<Unit,ArrayAlgoType<Unit> > result(DoBuild,MulBuilder(getBody(),Range(b,nb)));
  
  Swap(body,result);
  
  normalize();
  
  return *this;
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::div(const Unit *b,ulen nb)
 {
  IntegerDivider<Algo,ArrayAlgoType> divider(getBody(),Range(b,nb));
  
  ArrayType<Unit,ArrayAlgoType<Unit> > result(DoCopy(divider.getResult().len),divider.getResult().ptr);
  
  Swap(body,result);
  
  return *this;
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::mod(const Unit *b,ulen nb)
 {
  IntegerDivider<Algo,ArrayAlgoType> divider(getBody(),Range(b,nb),true); 
  
  ArrayType<Unit,ArrayAlgoType<Unit> > result(DoCopy(divider.getMod().len),divider.getMod().ptr);
  
  Swap(body,result);
  
  return *this;
 }

 // constructors 
  
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType>::Integer(StrLen str)
 {
  IntegerFromString<Integer> conv(str.len);
  
  *this=conv(str);
 }
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
template <class UInt>
Integer<Algo,ArrayType,ArrayAlgoType>::Integer(UInt val,Meta::EnableIf<Meta::IsUInt<UInt>::Ret>)
 : body(DoBuild,IntegerUIntBuilder<Algo,UInt>(val))
 {
  normalize();
 }
   
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
template <class SInt>
Integer<Algo,ArrayType,ArrayAlgoType>::Integer(SInt val,Meta::EnableIf<Meta::IsSInt<SInt>::Ret>)
 : body(DoBuild,IntegerSIntBuilder<Algo,SInt>(val))
 {
  normalize();
 }
   
 // methods
   
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
CmpResult Integer<Algo,ArrayType,ArrayAlgoType>::sign() const
 {
  return Algo::Sign(body.getPtr(),body.getLen());
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
auto Integer<Algo,ArrayType,ArrayAlgoType>::bitsOf() const -> BitsOf
 {
  ulen len=body.getLen();
  
  if( len )
    {
     Unit msu=body[len-1];
     
     unsigned n;
     
     if( msu&Algo::MSBit )
       {
        n=Algo::CountZeroMSB(~msu);
       }
     else
       {
        n=Algo::CountZeroMSB(msu);
       }
     
     return BitsOf(len-1,UnitBits-n);
    }
  else
    {
     return BitsOf(0,0);
    }
 }
   
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::sq() const
 {
  return Sq(getBody());
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::pow(unsigned deg) const
 {
  if( deg==0 ) return 1;
  
  if( deg==1 ) return *this;
  
  Integer ret=*this;
  unsigned bits=CountBits(deg); // >=2
  
  for(unsigned mask=1u<<(bits-2); mask ;mask>>=1)
    {
     ret=ret.sq();
     
     if( deg&mask ) ret=ret*(*this);
    }
    
  return ret;  
 }
 
 // operators

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::Neg(PtrLen<const Unit> a)
 {
  return Integer(DoBuild,NegBuilder(a));
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::Add(PtrLen<const Unit> a,PtrLen<const Unit> b)
 {
  return Integer(DoBuild,AddBuilder(a,b));
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::Sub(PtrLen<const Unit> a,PtrLen<const Unit> b)
 {
  return Integer(DoBuild,SubBuilder(a,b));
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::Mul(PtrLen<const Unit> a,PtrLen<const Unit> b)
 {
  return Integer(DoBuild,MulBuilder(a,b));
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::Sq(PtrLen<const Unit> a)
 {
  return Integer(DoBuild,SqBuilder(a));
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::Div(PtrLen<const Unit> a,PtrLen<const Unit> b)
 {
  IntegerDivider<Algo,ArrayAlgoType> divider(a,b);
  
  return Integer(CopyFrom,divider.getResult());
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::Mod(PtrLen<const Unit> a,PtrLen<const Unit> b)
 {
  IntegerDivider<Algo,ArrayAlgoType> divider(a,b,true);
  
  return Integer(CopyFrom,divider.getMod());
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::LShift(PtrLen<const Unit> a,unsigned shift)
 {
  return Integer(DoBuild,LShiftBuilder(a,shift));
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::RShift(PtrLen<const Unit> a,unsigned shift)
 {
  return Integer(DoBuild,RShiftBuilder(a,shift));
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType>::DivMod::DivMod(PtrLen<const Unit> a,PtrLen<const Unit> b)
 {
  IntegerDivider<Algo,ArrayAlgoType> divider(a,b,true);
  
  Integer div_(CopyFrom,divider.getResult());
  Integer mod_(CopyFrom,divider.getMod());
  
  Swap(div,div_);
  Swap(mod,mod_);
 }

 // operators
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::neg()
 {
  ulen na=body.getLen();
  
  Unit *a=body.append_raw();
  
  *a=Algo::Neg(a-na,na);
  
  normalize();
  
  return *this;
 }

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::revsub(const Integer<Algo,ArrayType,ArrayAlgoType> &b_)
 {
  const Unit *b=b_.body.getPtr();
  
  if( body.getPtr()==b ) return set_null();
  
  ulen nb=b_.body.getLen();
 
  return revsub(b,nb);
 }
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator += (const Integer<Algo,ArrayType,ArrayAlgoType> &b_)
 {
  const Unit *b=b_.body.getPtr();
  
  if( body.getPtr()==b ) return (*this)<<=1;
  
  ulen nb=b_.body.getLen();
 
  return add(b,nb);
 }
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator -= (const Integer<Algo,ArrayType,ArrayAlgoType> &b_)
 {
  const Unit *b=b_.body.getPtr();
  
  if( body.getPtr()==b ) return set_null();
  
  ulen nb=b_.body.getLen();
  
  return sub(b,nb);
 }
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator *= (const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  return mul(b.body.getPtr(),b.body.getLen());
 }
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator /= (const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  return div(b.body.getPtr(),b.body.getLen());
 }
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator %= (const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  return mod(b.body.getPtr(),b.body.getLen());
 }
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator <<= (unsigned shift_)
 {
  if( !shift_ ) return *this;
  
  unsigned full=unsigned(shift_/Algo::UnitBits);
  unsigned shift=unsigned(shift_%Algo::UnitBits);
  
  if( shift )
    {
     ulen n=body.getLen();
     
     AddLen(full,n,1);
     
     Unit *a=body.extend_raw(full+1).ptr-n;
     
     a[n+full]=Algo::ShiftUp(a,n,full,shift);
     
     Algo::Null(a,full);
    }
  else
    {
     ulen n=body.getLen();
     
     AddLen(full,n);
     
     Unit *a=body.extend_raw(full).ptr-n;
     
     Algo::MoveUp(a,n,full);
     
     Algo::Null(a,full);
    }
  
  return *this;
 }
 
template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator >>= (unsigned shift_)
 {
  if( !shift_ || body.getLen()==0 ) return *this;
  
  unsigned full=unsigned(shift_/Algo::UnitBits);
  unsigned shift=unsigned(shift_%Algo::UnitBits);
  
  PtrLen<Unit> data=body.modify(); 
  
  if( data.len<=full )
    {
     Unit a=Algo::SignExt(data.ptr,data.len);
     
     if( a==0 )
       {
        body.erase();
       }
     else
       {
        data[0]=a;
        
        body.shrink(data.len-1);
       }
    }
  else
    {
     ulen na=data.len-full;
     
     if( shift )
       {
        Algo::ShiftDown(data.ptr,na,full,shift);
       }
     else
       {
        Algo::MoveDown(data.ptr,na,full);
       }
     
     body.shrink(full);
    }
  
  return *this;
 }
 
 // print object

template <class Algo,template <class T,class A> class ArrayType,template <class T,class F=NoThrowFlags<T> > class ArrayAlgoType>
template <class P>   
void Integer<Algo,ArrayType,ArrayAlgoType>::print(P &out,PrintOptType opt) const
 {
  PrintInteger<Integer> print(body.getLen());
  
  print(out,opt,*this);
 }
 
/* class RandomInteger<Integer> */ 
  
template <class Integer> 
class RandomInteger : public Integer
 {
   using Unit = typename Integer::Unit ; 
 
   template <class Random>
   class Builder
    {
      ulen n;
      Random &random;
    
     public:
     
      Builder(ulen n_,Random &random_) : n(n_),random(random_) {}
      
      ulen getLen() const { return n; }
      
      PtrLen<Unit> operator () (Place<void> place) const
       {
        PtrLen<Unit> ret(place,n);
        
        random.fill(ret);
        
        return ret;
       }
    };
     
  public:
  
   template <class Random>
   RandomInteger(ulen n,Random &random) : Integer(DoBuild,Builder<Random>(n,random)) {}
   
   ~RandomInteger() {}
 };

/* struct GCDAlgo<Algo,TempArrayType> */

template <class Algo,class TempArrayType>
struct GCDAlgo
 {
  typedef typename Algo::Unit Unit;
  
  // internal
  
  static CmpResult Cmp(PtrLen<Unit> a,PtrLen<Unit> b)
   {
    return Algo::UCmp(a.ptr,a.len,b.ptr,b.len);
   }
  
  static void Sub(PtrLen<Unit> b,PtrLen<Unit> a) // b>=a
   {
    if( a.len<b.len )
      {
       Unit c=Algo::USub(b.ptr,a.ptr,a.len);
       
       Algo::USubUnit(b.ptr+a.len,b.len-a.len,c);
      }
    else
      {
       Algo::USub(b.ptr,a.ptr,b.len);
      }
   }
  
  static PtrLen<Unit> Norm(PtrLen<Unit> a)
   {
    return Range(a.ptr,Algo::UNormalize(a.ptr,a.len));
   }
  
  static PtrLen<Unit> NormSub(PtrLen<Unit> b,PtrLen<Unit> a)
   {
    Sub(b,a);
    
    return Norm(b);
   }
  
  static PtrLen<Unit> Div2(PtrLen<Unit> a) // a!=0
   {
    while( *a==0 ) ++a;
    
    if( unsigned shift=Algo::CountZeroLSB(*a) ) Algo::URShift(a.ptr,a.len,shift);

    return Norm(a);
   }

  static PtrLen<Unit> Odd(PtrLen<Unit> a,PtrLen<Unit> b) // a and b are odd , no overlapp
   {
    for(;;)
      switch( Cmp(a,b) )
        {
         case CmpLess :
          {
           b=Div2(NormSub(b,a));
          }
         break;
          
         case CmpGreater :
          {
           a=Div2(NormSub(a,b));
          }
         break;
         
         default: // case CmpEqual :
          {
           return a;
          }
        }
   }

  struct Shift
   {
    ulen full;
    unsigned shift;
    
    bool operator < (Shift obj) const { return full<obj.full || ( full==obj.full && shift<obj.shift ) ; }
    
    Shift min(Shift obj) const { return Min(*this,obj); }
   };
  
  struct Result
   {
    PtrLen<Unit> result;
    Unit msu;
    
    explicit Result(PtrLen<Unit> a)
     {
      result=a;
      msu=0;
     }
    
    Result(Shift s,PtrLen<Unit> a)
     {
      if( s.shift )
        {
         msu=Algo::ULShift(a.ptr,a.len,s.shift);
        }
      else
        {
         msu=0;
        }
      
      for(ulen cnt=s.full; cnt ;cnt--)
        {
         --a;
         
         *a=0;
        }
      
      result=a;
     }
    
    ulen copyTo(Unit *buf) const // [result.len+2]
     {
      result.copyTo(buf);
      
      buf[result.len]=msu;
      buf[result.len+1]=0;
      
      return Algo::Normalize(buf,result.len+2);
     }
   };
  
  struct ShiftVal : Shift
   {
    using Shift::full;
    using Shift::shift;
    
    PtrLen<Unit> odd;
    
    explicit ShiftVal(PtrLen<Unit> a)
     {
      ulen len=a.len;
      
      for(; +a ;++a)
        if( Unit u=*a )
          {
           full=len-a.len;
           
           shift=Algo::CountZeroLSB(u);
           
           odd=a;
           
           return;
          }
      
      full=len;
      shift=0;
     }
    
    bool operator ! () const { return !odd.len; }
    
    void complete()
     {
      if( shift ) Algo::URShift(odd.ptr,odd.len,shift);
     }
   };
  
  // GCD
  
  static Result UnsignedGCD(PtrLen<Unit> a,PtrLen<Unit> b) // no overlap
   {
    ShiftVal sa(a);
    
    if( !sa ) return Result(b);
    
    ShiftVal sb(b);
    
    if( !sb ) return Result(a);
    
    sa.complete();
    sb.complete();
    
    PtrLen<Unit> c=Odd(sa.odd,sb.odd);
    
    return Result(sa.min(sb),c);
   }
  
  static Result SignedGCD(PtrLen<Unit> a,PtrLen<Unit> b) // no overlap
   {
    if( Algo::Sign(a.ptr,a.len)<0 ) Algo::UNeg(a.ptr,a.len);
    if( Algo::Sign(b.ptr,b.len)<0 ) Algo::UNeg(b.ptr,b.len);
    
    return UnsignedGCD(a,b);
   }
  
  // QSym
  
  static bool QSym2(Unit b) // Unit at least 3 bit
   {
    switch( b&7u )
      {
       case 3 : case 5 : return true;
       
       default: return false;
      }
   }
  
  static unsigned QSymEps(Unit a,Unit b)
   {
    if( (a&3u)==1 || (b&3u)==1 ) return 0;
    
    return 1;
   }
  
  static int UnsignedQSym(PtrLen<Unit> a,PtrLen<Unit> b) // no overlap
   {
    if( b.len==0 || (b[0]&1u)==0 ) GuardQSymEven();
    
    bool qsym2=QSym2(b[0]);
    
    for(unsigned ret=0;;)
      {
       ShiftVal sa(a);
       
       if( !sa )
         {
          if( Algo::UNormalize(b.ptr,b.len)!=1 || b[0]!=1 ) GuardQSymNotCoprime();
           
          return (ret&1)?-1:+1;
         }
       
       sa.complete();
       
       if( qsym2 ) 
         {
          if( Algo::UnitBits&1u )
            ret ^= sa.shift^unsigned(sa.full) ;
          else
            ret ^= sa.shift ;
         }
       
       if( Cmp(sa.odd,b)>=0 )
         {
          a=NormSub(sa.odd,b);
         }
       else
         {
          a=b;
          b=sa.odd;
          
          ret ^= QSymEps(a[0],b[0]) ;
          
          qsym2=QSym2(b[0]);
          
          a=NormSub(a,b);
         }
      }
   }

  static int SignedQSym(PtrLen<Unit> a,PtrLen<Unit> b) // no overlap
   {
    if( Algo::Sign(b.ptr,b.len)<0 ) Algo::UNeg(b.ptr,b.len);
    
    if( Algo::Sign(a.ptr,a.len)<0 )
      {
       Algo::UNeg(a.ptr,a.len);
       
       if( b.len>0 && (b[0]&3u)==3 )
         return -UnsignedQSym(a,b);
       else
         return UnsignedQSym(a,b);
      }
    else
      {
       return UnsignedQSym(a,b);
      }
   }
  
  static int QSym(PtrLen<const Unit> a,PtrLen<const Unit> b)
   {
    TempArrayType buf(DoRaw( AddLen(a.len,b.len) ));
    
    Unit *a1=buf.getPtr();
    Unit *b1=a1+a.len;
    
    a.copyTo(a1);
    b.copyTo(b1);

    return SignedQSym(Range(a1,a.len),Range(b1,b.len));
   }
 };

/* class GCDivBuilder<Algo,TempArrayType> */

template <class Algo,class TempArrayType>
class GCDivBuilder
 {
   typedef typename Algo::Unit Unit;
   
   PtrLen<const Unit> a;
   PtrLen<const Unit> b;
   
  public:
   
   GCDivBuilder(PtrLen<const Unit> a_,PtrLen<const Unit> b_) : a(a_),b(b_) {}
   
   ulen getLen() const { return AddLen(Max(a.len,b.len),2); }
   
   PtrLen<Unit> operator () (Place<void> place) const
    {
     TempArrayType buf(DoRaw( AddLen(a.len,b.len) ));
     
     Unit *a1=buf.getPtr();
     Unit *b1=a1+a.len;
     
     a.copyTo(a1);
     b.copyTo(b1);
     
     auto result=GCDAlgo<Algo,TempArrayType>::SignedGCD(Range(a1,a.len),Range(b1,b.len));
     
     Unit *c=place;
     ulen len=result.copyTo(c);
     
     return Range(c,len);
    }
 };

/* class GCDivType<Integer> */

template <class Integer>
class GCDivType : public Integer
 {
  public:
   
   GCDivType(const Integer &a,const Integer &b) 
    : Integer(DoBuild,GCDivBuilder<typename Integer::AlgoType,typename Integer::TempArrayType>(a.getBody(),b.getBody())) 
    {
    }
 };

/* GCDiv() */

template <class Integer>
Integer GCDiv(const Integer &a,const Integer &b) { return GCDivType<Integer>(a,b); }

/* QSym() */

template <class Integer>
int QSym(const Integer &a,const Integer &b)
 {
  return GCDAlgo<typename Integer::AlgoType,typename Integer::TempArrayType>::QSym(a.getBody(),b.getBody());
 }

} // namespace Math
} // namespace CCore
 
#endif
 

