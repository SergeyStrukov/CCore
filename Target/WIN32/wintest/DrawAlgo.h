/* DrawAlgo.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_DrawAlgo_h
#define CCore_inc_video_DrawAlgo_h
 
#include <CCore/inc/video/Point.h>
#include <CCore/inc/video/Color.h>

namespace CCore {
namespace Video {

/* PointDist() */

inline uLCoord PointDist(LPoint a,LPoint b)
 {
  return Max(IntAbs(a.x,b.x),IntAbs(a.y,b.y))>>LPoint::Precision;
 }

/* PointNear() */

inline bool PointNear(Coord a,Coord b) { return (a<b)?( b-a==1 ):( a-b<=1 ); }

inline bool PointNear(Point a,Point b) { return PointNear(a.x,b.x) && PointNear(a.y,b.y) ; }

/* DistDir() */

template <class SInt,class UInt>
bool DistDir(SInt &e,UInt &s,SInt a,SInt b)
 {
  if( a<b )
    {
     e=1;
     s=IntDist(a,b);
     
     return true;
    }
  
  if( a>b )
    {
     e=-1;
     s=IntDist(b,a);
     
     return true;
    }
  
  return false;
 }

/* Direct() */

template <class SInt>
SInt Direct(SInt e,SInt a) { return (e>0)?a:(-a); }

/* AlphaDelta() */

template <class SInt,unsigned AlphaBits=8>
unsigned AlphaDelta(SInt delta,unsigned precision)
 {
  const SInt M = SInt(1)<<precision ;
  
  return unsigned( (M-delta)>>(precision-AlphaBits) );
 }

/* AlphaPart() */

template <class SInt>
unsigned AlphaPart(unsigned alpha,SInt part,unsigned precision)
 {
  return unsigned( (alpha*part)>>precision );
 }

/* classes */

template <class UInt> class LineDriverBase;

class LineDriver;

class LineDriverL;

class CurveDriver;

template <class UInt> class LineAlphaFunc;

template <class UInt> class LineAlphaFunc2;

template <class UInt> class SmoothLineDriver; 

/* class LineDriverBase<UInt> */

template <class UInt> 
class LineDriverBase
 {
   static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::Video::LineDriverBase<UInt> : UInt must be an unsigned integral type");
   
  protected: 
   
   const UInt sx;
   const UInt sy;
   
   const UInt ty;
   const UInt lim;
   
  private:
   
   UInt delta = 0 ;
   bool flag = false ;
  
  private:
   
   bool do_step(UInt s,UInt t) // t == sx-s
    {
     bool ret;
     
     if( delta<t ) 
       {
        bool next_flag=( (delta+=s)>lim );
        
        ret=( flag!=next_flag );
        
        flag=next_flag;
       } 
     else
       {
        bool next_flag=( (delta-=t)>lim );
        
        ret=( flag==next_flag );
        
        flag=next_flag;
       }
     
     return ret;
    }

   bool do_step(UInt s) { return do_step(s,sx-s); }
   
   bool do_back(UInt s) { return !do_step(sx-s,s); }
   
  public:
  
   LineDriverBase(UInt sx_,UInt sy_) : sx(sx_),sy(sy_),ty(sx_-sy_),lim(sx_/2) {} // sx >= sy > 0
   
   bool step() { return do_step(sy,ty); }
   
   UInt step(UInt delta_x)
    {
     if( sy==sx ) return delta_x;
     
     typename UIntFunc<UInt>::Mul mul(delta_x,sy);
     typename UIntFunc<UInt>::DivMod divmod(mul.hi,mul.lo,sx);
 
     return divmod.div+do_step(divmod.mod);
    }
   
   UInt step_pow2(unsigned s) // 0 < s < Meta::UIntBits<UInt>::Ret
    {
     if( sy==sx ) return UInt(1)<<s;
     
     UInt hi=sy>>(Meta::UIntBits<UInt>::Ret-s);
     UInt lo=sy<<s;
     
     typename UIntFunc<UInt>::DivMod divmod(hi,lo,sx);
 
     return divmod.div+do_step(divmod.mod);
    }
   
   UInt back(UInt delta_x)
    {
     if( sy==sx ) return delta_x;
     
     typename UIntFunc<UInt>::Mul mul(delta_x,sy);
     typename UIntFunc<UInt>::DivMod divmod(mul.hi,mul.lo,sx);
 
     return divmod.div+do_back(divmod.mod);
    }
 };

/* class LineDriver */

class LineDriver : public LineDriverBase<uCoord>
 {
  public:
  
   LineDriver(uCoord sx,uCoord sy) : LineDriverBase<uCoord>(sx,sy) {} // sx >= sy > 0
   
   struct Result
    {
     uCoord off;
     uCoord lim;
     
     bool operator + () const { return off<lim; }
     
     bool operator ! () const { return off>=lim; }
    };
   
   static Result Inf(Result a,Result b) { return {Max(a.off,b.off),Min(a.lim,b.lim)}; }
   
   Result clip(Coord x,Coord y,Coord ex,Coord ey,Coord dx,Coord dy) const;

   uCoord clipToX(uCoord y) const;
   
   Result clipToX(Result clip_y) const;
   
   static Result Clip(Coord x,Coord e,Coord d);
 };

/* class LineDriverL */

class LineDriverL : public LineDriverBase<uLCoord>
 {
  public:
  
   LineDriverL(uLCoord sx,uLCoord sy) : LineDriverBase<uLCoord>(sx,sy) {} // sx >= sy > 0
   
   static uLCoord First(LCoord a,LCoord e)
    {
     LCoord A=LPoint::RShift_ext(a);
     
     if( e>0 )
       {
        return LPoint::LShift_ext(A+1)-a;
       }
     else
       {
        return a-LPoint::LShift_ext(A-1);
       }
    }
   
   static uLCoord Count(LCoord a,LCoord b)
    {
     LCoord A=LPoint::RShift_ext(a);
     LCoord B=LPoint::RShift_ext(b);
     
     if( A<B )
       {
        return IntDist(A,B)-1;
       }
     else if( A>B )
       {
        return IntDist(B,A)-1;
       }
     else
       {
        return 0;
       }
    }
 };

/* class CurveDriver */

class CurveDriver : NoCopy
 {
   static const unsigned MaxLevel = 10 ;
   
   static const unsigned MaxFineness = 5 ;
   
   static const unsigned Len = (1u<<MaxLevel) ;
   
   static uLCoord Fineness(PtrStepLen<const LPoint> dots);
   
   static LCoord Spline(LCoord a,LCoord b,LCoord c,LCoord d);
 
   static LPoint Spline(LPoint a,LPoint b,LPoint c,LPoint d);
   
  private:
   
   LPoint buf[3*Len+1];
   unsigned level = 0 ;
   
   LPoint e;
  
  private:
   
   void spline();
   
   void spline(LPoint a,LPoint b,LPoint c,LPoint d,LPoint p,LPoint q,LPoint r);
   
  public:
   
   CurveDriver() {}
  
   void spline(Point a,Point b,Point c,Point d);
   
   void spline(Point a,Point b,Point c,Point d,Point e,Point f);
   
   void shift(Point f);
   
   void shift();
   
   PtrStepLen<const LPoint> getCurve() const { return {buf+Len,1u<<(MaxLevel-level),(1u<<level)+1}; }
 };

/* class LineAlphaFunc<UInt> */

template <class UInt> 
class LineAlphaFunc
 {
  protected:
  
   enum OneType
    {
     One = 1
    };
  
   class Num // [0,2)
    {
      static const unsigned Precision = 15 ;
      
      static const uint16 OneValue = uint16(1)<<Precision ;
     
      uint16 value;
      
     private: 
     
      Num(uint16 value_) : value(value_) {}
      
      template <class T>
      static Meta::EnableIf<( T(-1)>Quick::ScanUInt(-1) ),unsigned> Bits(T c)
       {
        const unsigned s=Meta::UIntBits<Quick::ScanUInt>::Ret;
        
        unsigned ret=1;

        for(;;)
          {
           Quick::ScanUInt u=(Quick::ScanUInt)c;
          
           if( u==c ) return Quick::ScanMSBit(u)+ret;
           
           c>>=s;
           ret+=s;
          }
       }
      
      template <class T>
      static Meta::EnableIf<( T(-1)<=Quick::ScanUInt(-1) ),unsigned> Bits(T c)
       {
        return Quick::ScanMSBit(c)+1;
       }
      
      template <class T>
      static Meta::EnableIf<( Meta::UIntBits<T>::Ret>16 ),void> Prepare(T &a,T &b)
       {
        if( UInt c=a>>16 )
          {
           unsigned s=Bits(c);
             
           a>>=s;
           b>>=s;
          }
       }
      
      template <class T>
      static Meta::EnableIf<( Meta::UIntBits<T>::Ret<=16 ),void> Prepare(T &,T &)
       {
       }
      
     public:
      
      Num() : value(0) {}
      
      Num(OneType) : value(OneValue) {}
      
      Num(UInt a,UInt b) // a<=b , a/b
       {
        Prepare(a,b);
        
        value=uint16( (uint32(a)<<Precision)/b );
       }
      
      unsigned map() const { return value>>(Precision-ClrBits); }
      
      Num div_2() const { return value>>1; }
      
      friend bool operator < (Num a,Num b) { return a.value<b.value; }
      
      friend bool operator > (Num a,Num b) { return a.value>b.value; } 
      
      friend bool operator <= (Num a,Num b) { return a.value<=b.value; }
      
      friend bool operator >= (Num a,Num b) { return a.value>=b.value; }
      
      friend Num operator + (Num a,Num b) { return a.value+b.value; }
      
      friend Num operator - (Num a,Num b) { return a.value-b.value; }
      
      friend Num operator * (Num a,Num b) { return uint16( (uint32(a.value)*b.value)>>Precision ); }
      
      friend Num operator / (Num a,Num b) { return uint16( (uint32(a.value)<<Precision)/b.value ); }
      
      template <class SInt>
      static Num Make(SInt a,unsigned precision) // [0,2) 
       { 
        if( precision==Precision ) return uint16( a );
        
        if( precision<Precision ) return uint16( a )<<(Precision-precision);
        
        return uint16( a>>(precision-Precision) );
       } 
    };
  
   static unsigned Map(Num a) { return a.map(); }
   
  protected: 
   
   Num T,A,B;
   
   Num T2,M,S;
  
  public:
  
   LineAlphaFunc(UInt sx,UInt sy) // sx >= sy > 0
    {
     T=Num(sy,sx);
     
     T2=T.div_2();

     Num C=T2;
     
     unsigned count=0;
     
     for(; count<10u ;count++)
       {
        Num next=T2*((One+C*C)/(One+T*C));
        
        if( next>=C ) break;
        
        C=next;
       }
     
     A=(One-C).div_2();
     
     B=(One+C).div_2();
     
     M=One-Sq(A)*T;
     
     S=One+T2*C;
    }
   
   unsigned alpha0(UInt d,UInt sx,UInt sy) const // d in [0,sx]
    {
     if( d<sy )
       {
        Num t(d,sy);
        
        if( t<=A ) return Map( M-T*Sq(t) );
        
        if( t<=B ) return Map( One-T2*Sq(A+t) );
       }
     
     UInt e=sx-d;
     
     if( e<sy )
       {
        Num t(e,sy);
        
        if( t<=A ) return Map( T2*Sq(B+t) );
       }
     
     Num t(d,sx);
     
     return Map( S-t );
    }
 
   unsigned alpha1(UInt d,UInt /* sx */,UInt sy) const // d in [0,sx]
    {
     if( d>=sy ) return 0;
     
     Num t(d,sy);
     
     if( t>=B ) return 0;
     
     return Map( T2*Sq(B-t) );
    }
 };

/* class LineAlphaFunc2<UInt> */

template <class UInt> 
class LineAlphaFunc2 : LineAlphaFunc<UInt>
 {
   using Num = typename LineAlphaFunc<UInt>::Num ;
   
   using LineAlphaFunc<UInt>::One;
   
   using LineAlphaFunc<UInt>::T;
   using LineAlphaFunc<UInt>::A;
   using LineAlphaFunc<UInt>::B;
   using LineAlphaFunc<UInt>::T2;
   using LineAlphaFunc<UInt>::M;
   using LineAlphaFunc<UInt>::S;
   
   using LineAlphaFunc<UInt>::Map;
   
   Num a,b;
 
  private: 
   
   unsigned alpha(Num t,Num p) const
    {
     Num c=p*T;
    
     if( t<a )
       {
        Num x;
        
        {
         Num s=a-t;
         
         if( s<c ) 
           x=(Sq(s)/c).div_2();
         else
           x=One+c.div_2()-s;
        }
       
        Num s=b-t;
       
        if( s<c ) return Map( p*(One-(Sq(s)/c).div_2()-x) );
      
        return Map( p*(One-x) );
       }
     
     if( t<b )
       {
        Num s=b-t;
        
        if( s<c ) return Map( p*(One-(Sq(s)/c).div_2()) );
       
        return Map( p );
       }
     
     if( t<One+b )
       {
        Num s=One+b-t;
        
        if( s<c ) return Map( p*(Sq(s)/c).div_2() );
        
        return Map( p*(s-c.div_2()) );
       }
     
     return 0;
    }
   
  public:
 
   LineAlphaFunc2(UInt sx,UInt sy) // sx >= sy > 0
    : LineAlphaFunc<UInt>(sx,sy) 
    {
     a=T*A;
     b=T*B;
    }
 
   template <class SInt>
   unsigned alpha0(SInt d,unsigned precision) const // [-1/2,1/2]
    {
     if( d<0 ) d=-d;
     
     Num t=Num::Make(d,precision);
     
     if( t<a ) return Map( M-T*Sq(t/T) );
     
     if( t<b ) return Map( One-T2*Sq(A+t/T) );
     
     return Map( S-t );
    }
   
   template <class SInt>
   unsigned alpha1(SInt d,unsigned precision) const // [-1/2,1/2]
    {
     Num t=Num::Make(d+(SInt(1)<<precision),precision);
     
     if( t<b ) return Map( One-T2*Sq(A+t/T) );
     
     if( t+a<One ) return Map( S-t );
     
     if( t<One+b ) return Map( T2*Sq((One+b-t)/T) );
     
     return 0;
    }
   
   template <class SInt>
   unsigned alpha2(SInt d,unsigned precision) const // [-1/2,1/2]
    {
     if( d>=0 ) return 0;
     
     Num t=Num::Make(d+(SInt(2)<<precision),precision);
     
     if( t<One+b ) return Map( T2*Sq((One+b-t)/T) );
     
     return 0;
    }
   
   template <class SInt>
   unsigned alpha0before(SInt d,SInt part,unsigned precision) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d,precision);
        Num p=Num::Make(part,precision);
      
        return alpha(t+T*(One-p),p);
       }
     else
       {
        Num t=Num::Make(d,precision);
        Num p=Num::Make(part,precision);
       
        return alpha(t,p);
       }
    }
   
   template <class SInt>
   unsigned alpha1before(SInt d,SInt part,unsigned precision) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d,precision);
        Num p=Num::Make(part,precision);
      
        return alpha(One-t,p);
       }
     else
       {
        Num t=Num::Make(d,precision);
        Num p=Num::Make(part,precision);
       
        return alpha(One+t,p);
       }
    }
   
   template <class SInt>
   unsigned alpha2before(SInt d,SInt part,unsigned precision) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d,precision);
        Num p=Num::Make(part,precision);

        t=One-t;
        
        if( t>=b ) return 0;
      
        return alpha(One+t,p);
       }
     else
       {
        return 0;
       }
    }
   
   template <class SInt>
   unsigned alpha0after(SInt d,SInt part,unsigned precision) const // [-1/2,1/2] , [0,1]
    {
     return alpha0before(-d,part,precision);
    }
   
   template <class SInt>
   unsigned alpha1after(SInt d,SInt part,unsigned precision) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d,precision);
        Num p=Num::Make(part,precision);
      
        return alpha((One-t)+T*(One-p),p);
       }
     else
       {
        Num t=Num::Make(d,precision);
        Num p=Num::Make(part,precision);
        
        t=T*(One-p)+t;
        
        if( t>=b ) return 0;
       
        return alpha(One+t,p);
       }
    }
   
   template <class SInt>
   unsigned alpha2after(SInt d,SInt part,unsigned precision) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d,precision);
        Num p=Num::Make(part,precision);

        t=One-t;
        
        if( t>=b ) return 0;
        
        t=t+T*(One-p);
        
        if( t>=b ) return 0;
        
        return alpha(One+t,p);
       }
     else
       {
        return 0;
       }
    }
 };

/* class SmoothLineDriver<UInt> */

template <class UInt> 
class SmoothLineDriver 
 {
  private:
  
   const UInt sx;
   const UInt sy;
  
   const UInt ty;
   
   UInt delta = 0 ;
   
   const LineAlphaFunc<UInt> func; 
   
  public:
  
   SmoothLineDriver(UInt sx_,UInt sy_) : sx(sx_),sy(sy_),ty(sx_-sy_),func(sx_,sy_) {} // sx_ >= sy_ > 0
   
   bool step()
    {
     if( delta<ty ) 
       {
        delta+=sy;
        
        return false;
       } 
     else
       {
        delta-=ty;
        
        return true;
       }
    }
   
   unsigned alpha0() const { return func.alpha1(delta,sx,sy); }
   
   unsigned alpha1() const { return func.alpha0(delta,sx,sy); }
   
   unsigned alpha2() const { return func.alpha0(sx-delta,sx,sy); }
   
   unsigned alpha3() const { return func.alpha1(sx-delta,sx,sy); } 
 };

/* Line(Point a,Point b,...) */

template <class Color,class Plot>
void Line(Point a,Point b,Color color,Plot plot) // [a,b)
 {
  Coord ex;
  Coord ey;
  uCoord sx;
  uCoord sy;
  
  if( !DistDir(ex,sx,a.x,b.x) )
    {
     if( !DistDir(ey,sy,a.y,b.y) ) return;
    
     for(auto count=sy; count>0 ;count--)
       {
        plot(a,color);
        
        a.y+=ey;
       }
     
     return;
    }
 
  if( !DistDir(ey,sy,a.y,b.y) )
    {
     for(auto count=sx; count>0 ;count--)
       {
        plot(a,color);
        
        a.x+=ex;
       }
    
     return;
    }

  if( sx>sy )
    {
     LineDriver driver(sx,sy);
    
     for(auto count=sx; count>0 ;count--)
       {
        plot(a,color);
        
        if( driver.step() ) a.y+=ey;
        
        a.x+=ex;
       }
    }
  else
    {
     LineDriver driver(sy,sx);
    
     for(auto count=sy; count>0 ;count--)
       {
        plot(a,color);
        
        if( driver.step() ) a.x+=ex;
        
        a.y+=ey;
       }
    }
 }

/* Line(...,LPoint a,LPoint b,...) */

struct LineEnd
 {
  Point last;
  Point ext;
  bool ok;
 };

template <class Func,class Color,class Plot>
LineEnd Line(Func func,LPoint a,LPoint b,Color color,Plot plot) // func(ext,first,color,plot) (a,b)
 {
  const uLCoord Step = uLCoord(1)<<LPoint::Precision ;
 
  class Driver
   {
     LCoord ex;
     LCoord ey;
     uLCoord sx;
     uLCoord sy;
     
    private: 
     
     LineEnd lineY(Func func,LPoint a,LPoint b,Color color,Plot plot)
      {
       auto count=LineDriverL::Count(a.y,b.y);
       
       if( !count ) return {Null,Null,false};
       
       Point E=a.toPoint();
       Point A=E;
       
       A.y+=ey;
       
       func(E,A,color,plot);
      
       plot(A,color);
      
       for(count--; count ;count--)
         {
          A.y+=ey;
          
          plot(A,color);
         }
       
       Point L=A;
       
       A.y+=ey;
        
       return {L,A,true};
      }
     
     LineEnd lineX(Func func,LPoint a,LPoint b,Color color,Plot plot)
      {
       auto count=LineDriverL::Count(a.x,b.x);
       
       if( !count ) return {Null,Null,false};
      
       Point E=a.toPoint();
       Point A=E;
       
       A.x+=ex;
       
       func(E,A,color,plot);
      
       plot(A,color);
       
       for(count--; count ;count--)
         {
          A.x+=ex;
          
          plot(A,color);
         }
       
       Point L=A;

       A.x+=ex;
        
       return {L,A,true};
      }
     
     void stepX(LineDriverL &driver,LPoint &a,Point &A)
      {
       uLCoord delta_y=driver.step_pow2(LPoint::Precision);
       
       a.y=IntMove(a.y,ey,delta_y);
       
       A.x+=ex;
       A.y=LPoint::RShift(a.y);
      }
     
     LineEnd lineToX(Func func,LPoint a,LPoint b,Color color,Plot plot)
      {
       auto count=LineDriverL::Count(a.x,b.x);
      
       if( !count ) return {Null,Null,false};
       
       LineDriverL driver(sx,sy);

       {
        uLCoord first=LineDriverL::First(a.x,ex);
        
        if( first>=Step )
          {
           uLCoord delta_x=first-Step;
           uLCoord delta_y=driver.step(delta_x);
           
           a.x=IntMove(a.x,ex,delta_x);
           a.y=IntMove(a.y,ey,delta_y);
          }
        else
          {
           uLCoord delta_x=Step-first;
           uLCoord delta_y=driver.back(delta_x);
           
           a.x=IntMove(a.x,-ex,delta_x);
           a.y=IntMove(a.y,-ey,delta_y);
          }
       }
       
       Point E=a.toPoint();
       Point A=E;
       
       {
        stepX(driver,a,A);
        
        func(E,A,color,plot);
        
        plot(A,color);
       }
       
       for(count--; count ;count--)
         {
          stepX(driver,a,A);
          
          plot(A,color);
         }
       
       Point L=A;
       
       {
        stepX(driver,a,A);
        
        return {L,A,true};
       }
      }
     
     void stepY(LineDriverL &driver,LPoint &a,Point &A)
      {
       uLCoord delta_x=driver.step_pow2(LPoint::Precision);
       
       a.x=IntMove(a.x,ex,delta_x);
       
       A.y+=ey;
       A.x=LPoint::RShift(a.x);
      }
     
     LineEnd lineToY(Func func,LPoint a,LPoint b,Color color,Plot plot)
      {
       auto count=LineDriverL::Count(a.y,b.y);
      
       if( !count ) return {Null,Null,false};
       
       LineDriverL driver(sy,sx);

       {
        uLCoord first=LineDriverL::First(a.y,ey);
        
        if( first>=Step )
          {
           uLCoord delta_y=first-Step;
           uLCoord delta_x=driver.step(delta_y);
           
           a.y=IntMove(a.y,ey,delta_y);
           a.x=IntMove(a.x,ex,delta_x);
          }
        else
          {
           uLCoord delta_y=Step-first;
           uLCoord delta_x=driver.back(delta_y);
           
           a.y=IntMove(a.y,-ey,delta_y);
           a.x=IntMove(a.x,-ex,delta_x);
          }
       }
       
       Point E=a.toPoint();
       Point A=E;
       
       {
        stepY(driver,a,A);
        
        func(E,A,color,plot);
        
        plot(A,color);
       }
       
       for(count--; count ;count--)
         {
          stepY(driver,a,A);
          
          plot(A,color);
         }
       
       Point L=A;
       
       {
        stepY(driver,a,A);
        
        return {L,A,true};
       }
      }
     
    public:
    
     LineEnd run(Func func,LPoint a,LPoint b,Color color,Plot plot)
      {
       if( !DistDir(ex,sx,a.x,b.x) )
         {
          if( !DistDir(ey,sy,a.y,b.y) ) 
            {
             return {Null,Null,false};
            }
          
          return lineY(func,a,b,color,plot);
         }
       
       if( !DistDir(ey,sy,a.y,b.y) )
         {
          return lineX(func,a,b,color,plot);
         }
       
       if( sx>sy )
         {
          return lineToX(func,a,b,color,plot);
         }
       else
         {
          return lineToY(func,a,b,color,plot);
         }
      }
   };
  
  Driver driver;
  
  return driver.run(func,a,b,color,plot);
 }

/* LineFirst/LineNext(...,LPoint a,LPoint b,...) */

template <class Color,class Plot>
LineEnd LineFirst(LPoint a,LPoint b,Color color,Plot plot) // [a,b)
 {
  return Line( [] (Point E,Point,Color color,Plot plot) { plot(E,color); } ,a,b,color,plot);
 }

template <class Color,class Plot>
LineEnd LineNext(LineEnd end,LPoint a,LPoint b,Color color,Plot plot) // [a,b)
 {
  Point A=a.toPoint();
  
  auto func = [end,A] (Point E,Point F,Color color,Plot plot) 
                      {
                       if( end.ext==E )
                         {
                          plot(E,color);
                         }
                       else if( PointNear(end.ext,E) )
                         {
                          if( end.ext==A )
                            {
                             if( PointNear(end.last,E) )
                               {
                                plot(E,color);
                               }
                             else if( PointNear(end.ext,F) )
                               {
                                plot(end.ext,color);
                               }
                             else
                               {
                                plot(end.ext,color);
                                plot(E,color);
                               }
                            }
                          else
                            {
                             if( PointNear(end.ext,F) )
                               {
                                plot(end.ext,color);
                               }
                             else if( PointNear(end.last,E) )
                               {
                                plot(E,color);
                               }
                             else
                               {
                                plot(end.ext,color);
                                plot(E,color);
                               }
                            }
                         }
                       else
                         {
                          if( !PointNear(A,end.last) ) plot(end.ext,color);
                          
                          plot(A,color);
                          
                          if( !PointNear(A,F) ) plot(E,color);
                         } 
                      } ;
  
  return Line(func,a,b,color,plot);
 }

/* LineSmooth(Point a,Point b,...) */

template <class Color,class Plot>
void LineSmooth(Point a,Point b,Color color,Plot plot) // [a,b)
 {
  Coord ex;
  Coord ey;
  uCoord sx;
  uCoord sy;
  
  if( !DistDir(ex,sx,a.x,b.x) )
    {
     if( !DistDir(ey,sy,a.y,b.y) ) return;
    
     for(auto count=sy; count>0 ;count--)
       {
        plot(a,color);
        
        a.y+=ey;
       }
     
     return;
    }
 
  if( !DistDir(ey,sy,a.y,b.y) )
    {
     for(auto count=sx; count>0 ;count--)
       {
        plot(a,color);
        
        a.x+=ex;
       }
    
     return;
    }

  if( sx>sy )
    {
     SmoothLineDriver<uCoord> driver(sx,sy);
     
     auto endalpha=driver.alpha2();
    
     plot(a,color);
     plot(a+Point(0,ey),color,endalpha);
     
     for(auto count=sx-1; count>0 ;count--)
       {
        if( driver.step() ) a.y+=ey;
        
        a.x+=ex;
        
        plot(a-Point(0,ey)  ,color,driver.alpha0());
        plot(a              ,color,driver.alpha1());
        plot(a+Point(0,ey)  ,color,driver.alpha2());
        plot(a+Point(0,2*ey),color,driver.alpha3());
       }
     
     plot(b-Point(0,ey),color,endalpha);
    }
  else
    {
     SmoothLineDriver<uCoord> driver(sy,sx);
     
     auto endalpha=driver.alpha2();
    
     plot(a,color);
     plot(a+Point(ex,0),color,endalpha);
     
     for(auto count=sy-1; count>0 ;count--)
       {
        if( driver.step() ) a.x+=ex;
        
        a.y+=ey;
        
        plot(a-Point(ex,0)  ,color,driver.alpha0());
        plot(a              ,color,driver.alpha1());
        plot(a+Point(ex,0)  ,color,driver.alpha2());
        plot(a+Point(2*ex,0),color,driver.alpha3());
       }
     
     plot(b-Point(ex,0),color,endalpha);
    }
 }

/* LineSmooth(LPoint a,LPoint b,...) */

template <class Color,class Plot>
bool LineSmooth(LPoint a,LPoint b,Color color,Plot plot) // [a,b]
 {
  const uLCoord Step = uLCoord(1)<<LPoint::Precision ;
  const LCoord Half = LCoord(1)<<(LPoint::Precision-1) ;
  
  LCoord ex;
  LCoord ey;
  uLCoord sx;
  uLCoord sy;
  
  if( !DistDir(ex,sx,a.x,b.x) )
    {
     if( !DistDir(ey,sy,a.y,b.y) ) 
       {
        return false;
       }
    
     auto count=LineDriverL::Count(a.y,b.y);
   
     if( !count ) return false;
    
     Point A=a.toPoint();
     LCoord delta=a.x-LPoint::LShift(A.x);
     
     unsigned alpha0;
     unsigned alpha1;
     unsigned alpha2;
     
     if( delta>=0 )
       {
        alpha0=0;
        
        alpha1=AlphaDelta(delta,LPoint::Precision);
        alpha2=256-alpha1;
       }
     else
       {
        alpha2=0;
       
        alpha1=AlphaDelta(-delta,LPoint::Precision);
        alpha0=256-alpha1;
       }
     
     {
      uLCoord first=LineDriverL::First(a.y,ey);
      LCoord part=(LCoord)first-Half;

      A.y+=ey;
      
      plot(A-Point(1,0),color,AlphaPart(alpha0,part,LPoint::Precision));
      plot(A,color,AlphaPart(alpha1,part,LPoint::Precision));
      plot(A+Point(1,0),color,AlphaPart(alpha2,part,LPoint::Precision));
     }
    
     for(; count ;count--)
       {
        A.y+=ey;
        
        plot(A-Point(1,0),color,alpha0);
        plot(A,color,alpha1);
        plot(A+Point(1,0),color,alpha2);
       }
     
     {
      A.y+=ey;
      
      LCoord part=Direct(ey,b.y-LPoint::LShift(A.y))+Half;
      
      plot(A-Point(1,0),color,AlphaPart(alpha0,part,LPoint::Precision));
      plot(A,color,AlphaPart(alpha1,part,LPoint::Precision));
      plot(A+Point(1,0),color,AlphaPart(alpha2,part,LPoint::Precision));
     }
      
     return true;
    }
 
  if( !DistDir(ey,sy,a.y,b.y) )
    {
     auto count=LineDriverL::Count(a.x,b.x);
   
     if( !count ) return false;
    
     Point A=a.toPoint();
     LCoord delta=a.y-LPoint::LShift(A.y);
     
     unsigned alpha0;
     unsigned alpha1;
     unsigned alpha2;
     
     if( delta>=0 )
       {
        alpha0=0;
        
        alpha1=AlphaDelta(delta,LPoint::Precision);
        alpha2=256-alpha1;
       }
     else
       {
        alpha2=0;
       
        alpha1=AlphaDelta(-delta,LPoint::Precision);
        alpha0=256-alpha1;
       }
     
     {
      uLCoord first=LineDriverL::First(a.x,ex);
      LCoord part=(LCoord)first-Half;

      A.x+=ex;
      
      plot(A-Point(0,1),color,AlphaPart(alpha0,part,LPoint::Precision));
      plot(A,color,AlphaPart(alpha1,part,LPoint::Precision));
      plot(A+Point(0,1),color,AlphaPart(alpha2,part,LPoint::Precision));
     }
    
     for(; count ;count--)
       {
        A.x+=ex;
        
        plot(A-Point(0,1),color,alpha0);
        plot(A,color,alpha1);
        plot(A+Point(0,1),color,alpha2);
       }
     
     {
      A.x+=ex;
      
      LCoord part=Direct(ex,b.x-LPoint::LShift(A.x))+Half;
      
      plot(A-Point(0,1),color,AlphaPart(alpha0,part,LPoint::Precision));
      plot(A,color,AlphaPart(alpha1,part,LPoint::Precision));
      plot(A+Point(0,1),color,AlphaPart(alpha2,part,LPoint::Precision));
     }
    
     return true;
    }
  
  if( sx>sy )
    {
     auto count=LineDriverL::Count(a.x,b.x);
   
     if( !count ) return false;
    
     LineDriverL driver(sx,sy);
     LineAlphaFunc2<uLCoord> func(sx,sy); 

     {
      uLCoord first=LineDriverL::First(a.x,ex);
      LCoord part=(LCoord)first-Half;
      
      if( first>=Step )
        {
         uLCoord delta_x=first-Step;
         uLCoord delta_y=driver.step(delta_x);
         
         a.x=IntMove(a.x,ex,delta_x);
         a.y=IntMove(a.y,ey,delta_y);
        }
      else
        {
         uLCoord delta_x=Step-first;
         uLCoord delta_y=driver.back(delta_x);
        
         a.x=IntMove(a.x,-ex,delta_x);
         a.y=IntMove(a.y,-ey,delta_y);
        }
      
      Point A=a.toPoint();
      
      LCoord delta=Direct(ey,a.y-LPoint::LShift(A.y));
      
      plot(A-Point(0,2*ey),color,func.alpha2after(delta,part,LPoint::Precision));
      plot(A-Point(0,ey),color,func.alpha1after(delta,part,LPoint::Precision));
      plot(A,color,func.alpha0after(delta,part,LPoint::Precision));
      plot(A+Point(0,ey),color,func.alpha1before(-delta,part,LPoint::Precision));
      plot(A+Point(0,2*ey),color,func.alpha2before(-delta,part,LPoint::Precision));
     }
    
     for(; count ;count--)
       {
        uLCoord delta_x=Step;
        uLCoord delta_y=driver.step_pow2(LPoint::Precision);
        
        a.x=IntMove(a.x,ex,delta_x);
        a.y=IntMove(a.y,ey,delta_y);
        
        Point A=a.toPoint();
        
        LCoord delta=Direct(ey,a.y-LPoint::LShift(A.y));
        
        plot(A-Point(0,2*ey),color,func.alpha2(delta,LPoint::Precision));
        plot(A-Point(0,ey),color,func.alpha1(delta,LPoint::Precision));
        plot(A,color,func.alpha0(delta,LPoint::Precision));
        plot(A+Point(0,ey),color,func.alpha1(-delta,LPoint::Precision));
        plot(A+Point(0,2*ey),color,func.alpha2(-delta,LPoint::Precision));
       }
     
     {
      uLCoord delta_x=Step;
      uLCoord delta_y=driver.step_pow2(LPoint::Precision);
      
      a.x=IntMove(a.x,ex,delta_x);
      a.y=IntMove(a.y,ey,delta_y);
      
      Point A=a.toPoint();
      
      LCoord delta=Direct(ey,a.y-LPoint::LShift(A.y));
      LCoord part=Direct(ex,b.x-a.x)+Half;
      
      plot(A-Point(0,2*ey),color,func.alpha2before(delta,part,LPoint::Precision));
      plot(A-Point(0,ey),color,func.alpha1before(delta,part,LPoint::Precision));
      plot(A,color,func.alpha0before(delta,part,LPoint::Precision));
      plot(A+Point(0,ey),color,func.alpha1after(-delta,part,LPoint::Precision));
      plot(A+Point(0,2*ey),color,func.alpha2after(-delta,part,LPoint::Precision));
     }
     
     return true;
    }
  else
    {
     auto count=LineDriverL::Count(a.y,b.y);
   
     if( !count ) return false;
    
     LineDriverL driver(sy,sx);
     LineAlphaFunc2<uLCoord> func(sy,sx); 
 
     {
      uLCoord first=LineDriverL::First(a.y,ey);
      LCoord part=(LCoord)first-Half;
      
      if( first>=Step )
        {
         uLCoord delta_y=first-Step;
         uLCoord delta_x=driver.step(delta_y);
         
         a.y=IntMove(a.y,ey,delta_y);
         a.x=IntMove(a.x,ex,delta_x);
        }
      else
        {
         uLCoord delta_y=Step-first;
         uLCoord delta_x=driver.back(delta_y);
        
         a.y=IntMove(a.y,-ey,delta_y);
         a.x=IntMove(a.x,-ex,delta_x);
        }
      
      Point A=a.toPoint();
      
      LCoord delta=Direct(ex,a.x-LPoint::LShift(A.x));
      
      plot(A-Point(2*ex,0),color,func.alpha2after(delta,part,LPoint::Precision));
      plot(A-Point(ex,0),color,func.alpha1after(delta,part,LPoint::Precision));
      plot(A,color,func.alpha0after(delta,part,LPoint::Precision));
      plot(A+Point(ex,0),color,func.alpha1before(-delta,part,LPoint::Precision));
      plot(A+Point(2*ex,0),color,func.alpha2before(-delta,part,LPoint::Precision));
     }
    
     for(; count ;count--)
       {
        uLCoord delta_y=Step;
        uLCoord delta_x=driver.step_pow2(LPoint::Precision);
        
        a.y=IntMove(a.y,ey,delta_y);
        a.x=IntMove(a.x,ex,delta_x);
        
        Point A=a.toPoint();
        
        LCoord delta=Direct(ex,a.x-LPoint::LShift(A.x));
        
        plot(A-Point(2*ex,0),color,func.alpha2(delta,LPoint::Precision));
        plot(A-Point(ex,0),color,func.alpha1(delta,LPoint::Precision));
        plot(A,color,func.alpha0(delta,LPoint::Precision));
        plot(A+Point(ex,0),color,func.alpha1(-delta,LPoint::Precision));
        plot(A+Point(2*ex,0),color,func.alpha2(-delta,LPoint::Precision));
       }
     
     {
      uLCoord delta_y=Step;
      uLCoord delta_x=driver.step_pow2(LPoint::Precision);
      
      a.y=IntMove(a.y,ey,delta_y);
      a.x=IntMove(a.x,ex,delta_x);
      
      Point A=a.toPoint();
      
      LCoord delta=Direct(ex,a.x-LPoint::LShift(A.x));
      LCoord part=Direct(ey,b.y-a.y)+Half;
      
      plot(A-Point(2*ex,0),color,func.alpha2before(delta,part,LPoint::Precision));
      plot(A-Point(ex,0),color,func.alpha1before(delta,part,LPoint::Precision));
      plot(A,color,func.alpha0before(delta,part,LPoint::Precision));
      plot(A+Point(ex,0),color,func.alpha1after(-delta,part,LPoint::Precision));
      plot(A+Point(2*ex,0),color,func.alpha2after(-delta,part,LPoint::Precision));
     }
    
     return true;
    }
 }

} // namespace Video
} // namespace CCore
 
#endif
 

