/* SimpleSpan.h */
//----------------------------------------------------------------------------------------
//
//  Project: EllipticPi 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef EllipticPi_SimpleSpan_h
#define EllipticPi_SimpleSpan_h

#include <CCore/inc/String.h>

namespace App {

/* using */ 

using namespace CCore;

/* functions */

void GuardSpanZeroDivisor();

void GuardSpanBrokenLimits();

void GuardSpanExactDivision();

/* classes */

class StrPunct;

template <class Int> class SimpleSpan;

/* class StrPunct */

class StrPunct : NoCopy
 {
   unsigned ind;
   unsigned period;
   
  public: 
   
   explicit StrPunct(unsigned period_) : ind(period_),period(period_) {}
   
   template <class P>
   void operator () (P &out,bool more)
     {
      if( more )
        {
         if( --ind )
           {
            out.put(' ');
           }
         else
           {
            out.put('\n');
            
            ind=period;
           }
        }
      else
        {
         out.put('\n');
        }
     }
 };

/* PrintDigits() */

template <class P>
void PrintDigits(P &out,PtrLen<const char> str)
 {
  StrPunct punct(5);
  
  while( +str )
    {
     auto frame=str.takeup(10);
     
     out.put(frame.ptr,frame.len);
     
     punct(out,+str);
    }
 }

/* class SimpleSpan<Int> */

template <class Int>
class SimpleSpan
 {
   static const unsigned D0 = 10 ;
   static const unsigned D1 = 10 ;
  
  private:
  
   Int lo;
   Int hi;
   unsigned exp;
   
   //
   // [lo,hi]/2^exp
   //
   
  private: 
  
   SimpleSpan(Int lo,Int hi,unsigned exp);
   
   SimpleSpan<Int> redexp() const;
   
   static unsigned Exp2Of(Int a) { return a.bitsOf().total(); }

   static SimpleSpan<Int> ExtraExp(Int lo,Int hi,unsigned exp1,unsigned exp2);
   
   // a.exp >= b.exp
   
   static bool Less(SimpleSpan<Int> a,SimpleSpan<Int> b);
   
   static SimpleSpan<Int> Add(SimpleSpan<Int> a,SimpleSpan<Int> b);
   
   static SimpleSpan<Int> Unite(SimpleSpan<Int> a,SimpleSpan<Int> b);
   
   // b > 0
   
   static SimpleSpan<Int> Div(SimpleSpan<Int> a,SimpleSpan<Int> b);
   
  public: 
   
   // constructors
   
   SimpleSpan() : lo(),hi(),exp(0) {}
   
   SimpleSpan(Int a) : lo(a),hi(a),exp(0) {}
   
   SimpleSpan(Int a,unsigned exp_) : lo(a<<exp_),hi(lo+1),exp(exp_) {}
   
   ~SimpleSpan() {}
   
   // methods
   
   unsigned precision() const;
   
   SimpleSpan<Int> operator - () const;
   
   SimpleSpan<Int> min() const;
   
   SimpleSpan<Int> max() const;
   
   SimpleSpan<Int> mul2pow(unsigned n) const;
   
   SimpleSpan<Int> div2pow(unsigned n) const;
   
   SimpleSpan<Int> sq() const;
   
   // operators

   friend bool operator < (SimpleSpan<Int> a,SimpleSpan<Int> b)
    {
     if( a.exp>=b.exp )
       return SimpleSpan<Int>::Less(a,b);
     else 
       return SimpleSpan<Int>::Less(-b,-a);
    }
   
   friend bool operator == (SimpleSpan<Int> a,SimpleSpan<Int> b) { return !( a<b || b<a ); }
   
   friend SimpleSpan<Int> operator + (SimpleSpan<Int> a,SimpleSpan<Int> b)
    {
     if( a.exp>=b.exp )
       return SimpleSpan<Int>::Add(a,b);
     else 
       return SimpleSpan<Int>::Add(b,a);
    }
   
   friend SimpleSpan<Int> operator - (SimpleSpan<Int> a,SimpleSpan<Int> b) { return a+(-b); }
   
   friend SimpleSpan<Int> operator * (SimpleSpan<Int> a,SimpleSpan<Int> b)
    {
     if( a.lo.sign()>=0 )
       {
        if( b.lo.sign()>=0 )
          {
           return SimpleSpan<Int>::ExtraExp(a.lo*b.lo,a.hi*b.hi,a.exp,b.exp).redexp();
          }
        else if( b.hi.sign()<=0 )
          {
           return SimpleSpan<Int>::ExtraExp(a.hi*b.lo,a.lo*b.hi,a.exp,b.exp).redexp();
          }
        else
          {
           return SimpleSpan<Int>::ExtraExp(a.hi*b.lo,a.hi*b.hi,a.exp,b.exp).redexp();
          }
       }
     else if( a.hi.sign()<=0 )
       {
        if( b.lo.sign()>=0 )
          {
           return SimpleSpan<Int>::ExtraExp(a.lo*b.hi,a.hi*b.lo,a.exp,b.exp).redexp();
          }
        else if( b.hi.sign()<=0 )
          {
           return SimpleSpan<Int>::ExtraExp(a.hi*b.hi,a.lo*b.lo,a.exp,b.exp).redexp();
          }
        else
          {
           return SimpleSpan<Int>::ExtraExp(a.lo*b.hi,a.lo*b.lo,a.exp,b.exp).redexp();
          }
       }
     else
       {
        if( b.lo.sign()>=0 )
          {
           return SimpleSpan<Int>::ExtraExp(a.lo*b.hi,a.hi*b.hi,a.exp,b.exp).redexp();
          }
        else if( b.hi.sign()<=0 )
          {
           return SimpleSpan<Int>::ExtraExp(a.hi*b.lo,a.lo*b.lo,a.exp,b.exp).redexp();
          }
        else
          {
           return SimpleSpan<Int>::ExtraExp(Min(a.lo*b.hi,a.hi*b.lo),Max(a.lo*b.lo,a.hi*b.hi),a.exp,b.exp).redexp();
          }
       }
    }
   
   friend SimpleSpan<Int> operator / (SimpleSpan<Int> a,SimpleSpan<Int> b)
    {
     if( b.lo.sign()<=0 )
       {
        if( b.hi.sign()>=0 ) GuardSpanZeroDivisor();
        
        return SimpleSpan<Int>::Div(-a,-b);
       }
     else
       {
        return SimpleSpan<Int>::Div(a,b);
       }
    }
   
   friend SimpleSpan<Int> operator | (SimpleSpan<Int> a,SimpleSpan<Int> b)
    {
     if( a.exp>=b.exp )
       return SimpleSpan<Int>::Unite(a,b);
     else 
       return SimpleSpan<Int>::Unite(b,a);
    }
   
   // print object
   
   template <class P>
   void print(P &out,unsigned dexp) const;
   
   template <class P>
   void print(P &out) const;
 };

template <class Int>
SimpleSpan<Int>::SimpleSpan(Int lo_,Int hi_,unsigned exp_) 
 : lo(lo_),
   hi(hi_),
   exp(exp_) 
 {
  if( hi<lo ) GuardSpanBrokenLimits();
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::redexp() const 
 {
  unsigned n=Exp2Of(hi-lo);
  
  if( n<D1 ) return *this;
  
  unsigned d=Min(exp,n-D1);
  
  if( d )
    return SimpleSpan<Int>(lo>>d,-((-hi)>>d),exp-d);
  else
    return *this;
 } 

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::ExtraExp(Int lo,Int hi,unsigned exp1,unsigned exp2)
 {
  unsigned exp=exp1+exp2;
  
  if( exp1<=exp )
    {
     return SimpleSpan<Int>(lo,hi,exp);
    }
  else
    {
     exp++;
     
     return SimpleSpan<Int>(lo>>exp,-((-hi)>>exp),unsigned(-1));
    }
 }

template <class Int>
bool SimpleSpan<Int>::Less(SimpleSpan<Int> a,SimpleSpan<Int> b)
 {
  unsigned n=a.exp-b.exp;

  return (a.hi>>n) < b.lo ;
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::Add(SimpleSpan<Int> a,SimpleSpan<Int> b)
 {
  unsigned n=a.exp-b.exp;
  
  return SimpleSpan<Int>(a.lo+(b.lo<<n),a.hi+(b.hi<<n),a.exp).redexp(); 
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::Unite(SimpleSpan<Int> a,SimpleSpan<Int> b)
 {
  unsigned n=a.exp-b.exp;

  return SimpleSpan<Int>(Min(a.lo,b.lo<<n),Max(a.hi,b.hi<<n),a.exp).redexp();  
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::Div(SimpleSpan<Int> a,SimpleSpan<Int> b)
 {
  Int c=a.hi*b.hi-a.lo*b.lo;
  
  if( c==0 ) GuardSpanExactDivision();
  
  unsigned d=D0+Exp2Of(b.lo)+Exp2Of(b.hi)-Exp2Of(c);
  
  if( a.exp>=b.exp )
    return SimpleSpan<Int>((a.lo<<d)/b.hi,((a.hi<<d)+b.lo-1)/b.lo,d).redexp().div2pow(a.exp-b.exp);
  else
    return SimpleSpan<Int>((a.lo<<d)/b.hi,((a.hi<<d)+b.lo-1)/b.lo,d).redexp().mul2pow(b.exp-a.exp);
 }

 // methods

template <class Int>
unsigned SimpleSpan<Int>::precision() const
 {
  return PosSub(exp,Exp2Of(hi-lo));
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::operator - () const
 {
  return SimpleSpan<Int>(-hi,-lo,exp);
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::min() const
 {
  return SimpleSpan<Int>(lo,lo,exp);
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::max() const
 {
  return SimpleSpan<Int>(hi,hi,exp);
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::mul2pow(unsigned n) const
 {
  if( n<=exp )
    {
     return SimpleSpan<Int>(lo,hi,exp-n);
    }
  else
    {
     n-=exp;
     
     return SimpleSpan<Int>(lo<<n,hi<<n,0);
    }
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::div2pow(unsigned n) const
 {
  return ExtraExp(lo,hi,exp,n);
 }

template <class Int>
SimpleSpan<Int> SimpleSpan<Int>::sq() const
 {
  if( lo.sign()>=0 )
    {
     return ExtraExp(lo.sq(),hi.sq(),exp,exp).redexp();
    }
  else if( hi.sign()<=0 )
    {
     return ExtraExp(hi.sq(),lo.sq(),exp,exp).redexp();
    }
  else
    {
     return ExtraExp(Int(0),Max(-lo,hi).sq(),exp,exp).redexp();
    }
 }

 // print object

template <class Int>
template <class P>
void SimpleSpan<Int>::print(P &out,unsigned dexp) const
 {
  Int mul=Int(10).pow(dexp);
  
  Int a=(lo*mul)>>exp;
  Int b=-((-(hi*mul))>>exp);
  
  Int c=(a+b)>>1;
  Int d=(b-a+1)>>1;
  
  if( c<0 )
    {
     out.put('-');
     
     c=-c;
    }
  
  auto x=c.divmod(mul);
  
  Printf(out,"#;.\n",x.div);
  
  if( !!x.mod )
    {
     typename Int::PrintOptType opt;
     
     opt.width=dexp;
     
     String str=StringCat(BindOpt(opt,x.mod));
     
     PrintDigits(out,Range(str));
    }
  
  Printf(out,"+- #; E-#;\n",d,dexp);
 }

template <class Int>
template <class P>
void SimpleSpan<Int>::print(P &out) const
 {
  unsigned n=precision();
  
  unsigned dexp=n/5+n/10+n/1000+n/50000+n/100000;
  
  print(out,dexp);
 }

} // namespace App

#endif
