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

#include <CCore/inc/Sort.h>

#include <CCore/inc/TaskMemStack.h>

namespace CCore {
namespace Video {
namespace Algo {

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

/* classes */

template <class UInt> class LineDriverBase;

class LineDriver;

class LineDriver2;

class CurveDriver;

template <class UInt> class LineAlphaFunc;

template <class UInt> class LineAlphaFunc2;

template <class UInt> class SmoothLineDriver;

struct LineEnd;

class LinePlotter;

class LinePlotter2;

class SolidSection;

/* class LineDriverBase<UInt> */

template <class UInt> 
class LineDriverBase
 {
   static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::Video::LineDriverBase<UInt> : UInt must be an unsigned integral type");
   
  protected: 
   
   UInt sx;
   UInt sy;
   
   UInt ty;
   UInt lim;
   
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
   
   bool back() { return !do_step(ty,sy); }
   
   UInt stepUp()
    {
     UInt ret;
     
     if( delta<=lim )
       {
        ret=(lim-delta)/sy;
       }
     else
       {
        ret=(sx-(delta-lim))/sy;
       }
     
     UInt s=ret*sy;
     
     if( s>=ty )
       s-=ty;
     else
       s+=sy;
     
     do_step(s);
     
     return ret;
    }
   
   UInt backDown()
    {
     UInt ret;
     
     if( delta>lim )
       {
        ret=(delta-lim-1)/sy;
       }
     else
       {
        ret=(sx-1-(lim-delta))/sy;
       }
     
     UInt s=ret*sy;
     
     if( s>=ty )
       s-=ty;
     else
       s+=sy;
     
     do_back(s);
     
     return ret;
    }
   
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

/* class LineDriver2 */

class LineDriver2 : public LineDriverBase<uLCoord>
 {
  public:
  
   LineDriver2(uLCoord sx,uLCoord sy) : LineDriverBase<uLCoord>(sx,sy) {} // sx >= sy > 0
   
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
   
   static uLCoord Count1(LCoord a,LCoord b)
    {
     LCoord A=LPoint::RShift_ext(a);
     LCoord B=LPoint::RShift_ext(b);
     
     return IntAbs(A,B);
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
      
      Num div_4() const { return value>>2; }
      
      friend bool operator < (Num a,Num b) { return a.value<b.value; }
      
      friend bool operator > (Num a,Num b) { return a.value>b.value; } 
      
      friend bool operator <= (Num a,Num b) { return a.value<=b.value; }
      
      friend bool operator >= (Num a,Num b) { return a.value>=b.value; }
      
      friend Num operator + (Num a,Num b) { return a.value+b.value; }
      
      friend Num operator - (Num a,Num b) { return a.value-b.value; }
      
      friend Num operator * (Num a,Num b) { return uint16( (uint32(a.value)*b.value)>>Precision ); }
      
      friend Num operator / (Num a,Num b) { return uint16( (uint32(a.value)<<Precision)/b.value ); }
      
      static Num Make(LCoord a) // [0,2) 
       { 
        if( LPoint::Precision==Precision ) return uint16( a );
        
        if( LPoint::Precision<Precision ) return uint16( a )<<(Precision-LPoint::Precision);
        
        return uint16( a>>(LPoint::Precision-Precision) );
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
     Num m=(One-p)*T;
     
     if( t<m.div_2() ) t=m-t;
    
     Num c=p*T;
    
     if( t<a )
       {
        Num s=a+c;
        
        if( s>b )
          {
           s=s-b;
         
           t=t-m.div_2();
             
           if( t>s.div_2() ) t=s.div_2();
            
           return Map( p*(One-(Sq(s)/c).div_4()-Sq(t)/c) );
          }
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
 
   unsigned alpha0(LCoord d) const // [-1/2,1/2]
    {
     if( d<0 ) d=-d;
     
     Num t=Num::Make(d);
     
     if( t<a ) return Map( M-T*Sq(t/T) );
     
     if( t<b ) return Map( One-T2*Sq(A+t/T) );
     
     return Map( S-t );
    }
   
   unsigned alpha1(LCoord d) const // [-1/2,1/2]
    {
     Num t=Num::Make(d+LPoint::LShift(1));
     
     if( t<b ) return Map( One-T2*Sq(A+t/T) );
     
     if( t+a<One ) return Map( S-t );
     
     if( t<One+b ) return Map( T2*Sq((One+b-t)/T) );
     
     return 0;
    }
   
   unsigned alpha2(LCoord d) const // [-1/2,1/2]
    {
     if( d>=0 ) return 0;
     
     Num t=Num::Make(d+LPoint::LShift(2));
     
     if( t<One+b ) return Map( T2*Sq((One+b-t)/T) );
     
     return 0;
    }
   
   unsigned alpha0before(LCoord d,LCoord part) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d);
        Num p=Num::Make(part);
      
        return alpha(t+T*(One-p),p);
       }
     else
       {
        Num t=Num::Make(d);
        Num p=Num::Make(part);
       
        return alpha(t,p);
       }
    }
   
   unsigned alpha1before(LCoord d,LCoord part) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d);
        Num p=Num::Make(part);
      
        return alpha(One-t,p);
       }
     else
       {
        Num t=Num::Make(d);
        Num p=Num::Make(part);
       
        return alpha(One+t,p);
       }
    }
   
   unsigned alpha2before(LCoord d,LCoord part) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d);
        Num p=Num::Make(part);

        t=One-t;
        
        if( t>=b ) return 0;
      
        return alpha(One+t,p);
       }
     else
       {
        return 0;
       }
    }
   
   unsigned alpha0after(LCoord d,LCoord part) const // [-1/2,1/2] , [0,1]
    {
     return alpha0before(-d,part);
    }
   
   unsigned alpha1after(LCoord d,LCoord part) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d);
        Num p=Num::Make(part);
      
        return alpha((One-t)+T*(One-p),p);
       }
     else
       {
        Num t=Num::Make(d);
        Num p=Num::Make(part);
        
        t=T*(One-p)+t;
        
        if( t>=b ) return 0;
       
        return alpha(One+t,p);
       }
    }
   
   unsigned alpha2after(LCoord d,LCoord part) const // [-1/2,1/2] , [0,1]
    {
     if( d<0 )
       {
        Num t=Num::Make(-d);
        Num p=Num::Make(part);

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

template <class Plot>
void Line(Point a,Point b,Plot plot) // [a,b)
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
        plot(a);
        
        a.y+=ey;
       }
     
     return;
    }
 
  if( !DistDir(ey,sy,a.y,b.y) )
    {
     for(auto count=sx; count>0 ;count--)
       {
        plot(a);
        
        a.x+=ex;
       }
    
     return;
    }

  if( sx>sy )
    {
     LineDriver driver(sx,sy);
    
     for(auto count=sx; count>0 ;count--)
       {
        plot(a);
        
        if( driver.step() ) a.y+=ey;
        
        a.x+=ex;
       }
    }
  else
    {
     LineDriver driver(sy,sx);
    
     for(auto count=sy; count>0 ;count--)
       {
        plot(a);
        
        if( driver.step() ) a.x+=ex;
        
        a.y+=ey;
       }
    }
 }

/* struct LineEnd */

struct LineEnd
 {
  Point last;
  Point ext;
  bool ok;
 };

/* class LinePlotter */

class LinePlotter
 {
   static const uLCoord Step = uLCoord(1)<<LPoint::Precision ;
 
   LCoord ex;
   LCoord ey;
   uLCoord sx;
   uLCoord sy;
   
  private: 
   
   template <class Func,class Plot>
   LineEnd lineY(Func func,LPoint a,LPoint b,Plot plot)
    {
     auto count=LineDriver2::Count(a.y,b.y);
     
     if( !count ) return {Null,Null,false};
     
     Point E=a.toPoint();
     Point A=E;
     
     A.y+=ey;
     
     func(E,A,plot);
    
     plot(A);
    
     for(count--; count ;count--)
       {
        A.y+=ey;
        
        plot(A);
       }
     
     Point L=A;
     
     A.y+=ey;
      
     return {L,A,true};
    }
   
   template <class Func,class Plot>
   LineEnd lineX(Func func,LPoint a,LPoint b,Plot plot)
    {
     auto count=LineDriver2::Count(a.x,b.x);
     
     if( !count ) return {Null,Null,false};
    
     Point E=a.toPoint();
     Point A=E;
     
     A.x+=ex;
     
     func(E,A,plot);
    
     plot(A);
     
     for(count--; count ;count--)
       {
        A.x+=ex;
        
        plot(A);
       }
     
     Point L=A;

     A.x+=ex;
      
     return {L,A,true};
    }
   
   void stepX(LineDriver2 &driver,LPoint &a,Point &A)
    {
     uLCoord delta_y=driver.step_pow2(LPoint::Precision);
     
     a.y=IntMove(a.y,ey,delta_y);
     
     A.x+=ex;
     A.y=LPoint::RShift(a.y);
    }
   
   template <class Func,class Plot>
   LineEnd lineToX(Func func,LPoint a,LPoint b,Plot plot)
    {
     auto count=LineDriver2::Count(a.x,b.x);
    
     if( !count ) return {Null,Null,false};
     
     LineDriver2 driver(sx,sy);

     {
      uLCoord first=LineDriver2::First(a.x,ex);
      
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
      
      func(E,A,plot);
      
      plot(A);
     }
     
     for(count--; count ;count--)
       {
        stepX(driver,a,A);
        
        plot(A);
       }
     
     Point L=A;
     
     {
      stepX(driver,a,A);
      
      return {L,A,true};
     }
    }
   
   void stepY(LineDriver2 &driver,LPoint &a,Point &A)
    {
     uLCoord delta_x=driver.step_pow2(LPoint::Precision);
     
     a.x=IntMove(a.x,ex,delta_x);
     
     A.y+=ey;
     A.x=LPoint::RShift(a.x);
    }
   
   template <class Func,class Plot>
   LineEnd lineToY(Func func,LPoint a,LPoint b,Plot plot)
    {
     auto count=LineDriver2::Count(a.y,b.y);
    
     if( !count ) return {Null,Null,false};
     
     LineDriver2 driver(sy,sx);

     {
      uLCoord first=LineDriver2::First(a.y,ey);
      
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
      
      func(E,A,plot);
      
      plot(A);
     }
     
     for(count--; count ;count--)
       {
        stepY(driver,a,A);
        
        plot(A);
       }
     
     Point L=A;
     
     {
      stepY(driver,a,A);
      
      return {L,A,true};
     }
    }
   
  public:
  
   template <class Func,class Plot>
   LineEnd run(Func func,LPoint a,LPoint b,Plot plot)
    {
     if( !DistDir(ex,sx,a.x,b.x) )
       {
        if( !DistDir(ey,sy,a.y,b.y) ) 
          {
           return {Null,Null,false};
          }
        
        return lineY(func,a,b,plot);
       }
     
     if( !DistDir(ey,sy,a.y,b.y) )
       {
        return lineX(func,a,b,plot);
       }
     
     if( sx>sy )
       {
        return lineToX(func,a,b,plot);
       }
     else
       {
        return lineToY(func,a,b,plot);
       }
    }
 };

/* Line(...,LPoint a,LPoint b,...) */

template <class Func,class Plot>
LineEnd Line(Func func,LPoint a,LPoint b,Plot plot) // func(ext,first,plot) (a,b)
 {
  LinePlotter plotter;
  
  return plotter.run(func,a,b,plot);
 }

/* LineFirst/LineNext(...,LPoint a,LPoint b,...) */

template <class Plot>
LineEnd LineFirst(LPoint a,LPoint b,Plot plot) // [a,b)
 {
  return Line( [] (Point E,Point,Plot plot) { plot(E); } ,a,b,plot);
 }

template <class Plot>
LineEnd LineNext(LineEnd end,LPoint a,LPoint b,Plot plot) // [a,b)
 {
  Point A=a.toPoint();
  
  auto func = [end,A] (Point E,Point F,Plot plot) 
                      {
                       if( end.ext==E )
                         {
                          plot(E);
                         }
                       else if( PointNear(end.ext,E) )
                         {
                          if( end.ext==A )
                            {
                             if( PointNear(end.last,E) )
                               {
                                plot(E);
                               }
                             else if( PointNear(end.ext,F) )
                               {
                                plot(end.ext);
                               }
                             else
                               {
                                plot(end.ext);
                                plot(E);
                               }
                            }
                          else
                            {
                             if( PointNear(end.ext,F) )
                               {
                                plot(end.ext);
                               }
                             else if( PointNear(end.last,E) )
                               {
                                plot(E);
                               }
                             else
                               {
                                plot(end.ext);
                                plot(E);
                               }
                            }
                         }
                       else
                         {
                          if( !PointNear(A,end.last) ) plot(end.ext);
                          
                          plot(A);
                          
                          if( !PointNear(A,F) ) plot(E);
                         } 
                      } ;
  
  return Line(func,a,b,plot);
 }

/* LineSmooth(Point a,Point b,...) */

template <class Plot>
void LineSmooth(Point a,Point b,Plot plot) // [a,b)
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
        plot(a);
        
        a.y+=ey;
       }
     
     return;
    }
 
  if( !DistDir(ey,sy,a.y,b.y) )
    {
     for(auto count=sx; count>0 ;count--)
       {
        plot(a);
        
        a.x+=ex;
       }
    
     return;
    }

  if( sx>sy )
    {
     SmoothLineDriver<uCoord> driver(sx,sy);
     
     auto endalpha=driver.alpha2();
    
     plot(a);
     plot(a+Point(0,ey),endalpha);
     
     for(auto count=sx-1; count>0 ;count--)
       {
        if( driver.step() ) a.y+=ey;
        
        a.x+=ex;
        
        plot(a-Point(0,ey)  ,driver.alpha0());
        plot(a              ,driver.alpha1());
        plot(a+Point(0,ey)  ,driver.alpha2());
        plot(a+Point(0,2*ey),driver.alpha3());
       }
     
     plot(b-Point(0,ey),endalpha);
    }
  else
    {
     SmoothLineDriver<uCoord> driver(sy,sx);
     
     auto endalpha=driver.alpha2();
    
     plot(a);
     plot(a+Point(ex,0),endalpha);
     
     for(auto count=sy-1; count>0 ;count--)
       {
        if( driver.step() ) a.x+=ex;
        
        a.y+=ey;
        
        plot(a-Point(ex,0)  ,driver.alpha0());
        plot(a              ,driver.alpha1());
        plot(a+Point(ex,0)  ,driver.alpha2());
        plot(a+Point(2*ex,0),driver.alpha3());
       }
     
     plot(b-Point(ex,0),endalpha);
    }
 }

/* class LinePlotter2 */

class LinePlotter2
 {
   static const uLCoord Step = uLCoord(1)<<LPoint::Precision ;
   
   static const LCoord Half = LCoord(1)<<(LPoint::Precision-1) ;
   
   LCoord ex;
   LCoord ey;
   uLCoord sx;
   uLCoord sy;
   
  private: 
  
   static LCoord Delta(LCoord e,LCoord x)
    {
     return Direct(e,x-LPoint::LShift_ext(LPoint::RShift_ext(x)));
    }
   
   static LCoord PartBefore(LCoord e,LCoord x)
    {
     return Half+Delta(e,x);
    }
   
   static LCoord PartAfter(LCoord e,LCoord x)
    {
     return Half-Delta(e,x);
    }
   
   static unsigned AlphaDelta(LCoord delta)
    {
     const LCoord M = LCoord(1)<<LPoint::Precision ;
     
     return unsigned( (M-delta)>>(LPoint::Precision-ClrBits) );
    }

   static unsigned AlphaPart(unsigned alpha,LCoord part)
    {
     return unsigned( (alpha*uLCoord(part))>>LPoint::Precision );
    }
   
   template <class Plot>
   bool lineY(LPoint a,LPoint b,Plot plot)
    {
     auto count=LineDriver2::Count1(a.y,b.y);
   
     if( !count ) return false;
     
     count--;
    
     Point A=a.toPoint();
     LCoord delta=Delta(1,a.x);
     
     unsigned alpha0;
     unsigned alpha1;
     unsigned alpha2;
     
     if( delta>=0 )
       {
        alpha0=0;
        
        alpha1=AlphaDelta(delta);
        alpha2=(1u<<ClrBits)-alpha1;
       }
     else
       {
        alpha2=0;
       
        alpha1=AlphaDelta(-delta);
        alpha0=(1u<<ClrBits)-alpha1;
       }
     
     {
      uLCoord first=LineDriver2::First(a.y,ey);
      LCoord part=(LCoord)first-Half;

      plot(A-Point(1,0),AlphaPart(alpha0,part));
      plot(A           ,AlphaPart(alpha1,part));
      plot(A+Point(1,0),AlphaPart(alpha2,part));
     }
    
     for(; count ;count--)
       {
        A.y+=ey;
        
        plot(A-Point(1,0),alpha0);
        plot(A           ,alpha1);
        plot(A+Point(1,0),alpha2);
       }
     
     {
      A.y+=ey;
      
      LCoord part=PartBefore(ey,b.y);
      
      plot(A-Point(1,0),AlphaPart(alpha0,part));
      plot(A           ,AlphaPart(alpha1,part));
      plot(A+Point(1,0),AlphaPart(alpha2,part));
     }
     
     return true;
    }
   
   template <class Plot>
   bool lineX(LPoint a,LPoint b,Plot plot)
    {
     auto count=LineDriver2::Count1(a.x,b.x);
   
     if( !count ) return false;
     
     count--;
    
     Point A=a.toPoint();
     LCoord delta=Delta(1,a.y);
     
     unsigned alpha0;
     unsigned alpha1;
     unsigned alpha2;
     
     if( delta>=0 )
       {
        alpha0=0;
        
        alpha1=AlphaDelta(delta);
        alpha2=(1u<<ClrBits)-alpha1;
       }
     else
       {
        alpha2=0;
       
        alpha1=AlphaDelta(-delta);
        alpha0=(1u<<ClrBits)-alpha1;
       }
     
     {
      uLCoord first=LineDriver2::First(a.x,ex);
      LCoord part=(LCoord)first-Half;

      plot(A-Point(0,1),AlphaPart(alpha0,part));
      plot(A           ,AlphaPart(alpha1,part));
      plot(A+Point(0,1),AlphaPart(alpha2,part));
     }
    
     for(; count ;count--)
       {
        A.x+=ex;
        
        plot(A-Point(0,1),alpha0);
        plot(A           ,alpha1);
        plot(A+Point(0,1),alpha2);
       }
     
     {
      A.x+=ex;
      
      LCoord part=PartBefore(ex,b.x);
      
      plot(A-Point(0,1),AlphaPart(alpha0,part));
      plot(A           ,AlphaPart(alpha1,part));
      plot(A+Point(0,1),AlphaPart(alpha2,part));
     }
    
     return true;
    }
   
   void stepX(LineDriver2 &driver,LPoint &a,Point &A)
    {
     uLCoord delta_y=driver.step_pow2(LPoint::Precision);
     
     a.y=IntMove(a.y,ey,delta_y);
     
     A.x+=ex;
     A.y=LPoint::RShift(a.y);
    }

   template <class Plot>
   void plotX(LineAlphaFunc2<uLCoord> &func,LPoint a,Point A,Plot plot)
    {
     LCoord delta=Delta(ey,a.y);
     
     plot(A-Point(0,2*ey),func.alpha2(delta));
     plot(A-Point(0,ey)  ,func.alpha1(delta));
     plot(A              ,func.alpha0(delta));
     plot(A+Point(0,ey)  ,func.alpha1(-delta));
     plot(A+Point(0,2*ey),func.alpha2(-delta));
    }
   
   template <class Plot>
   bool lineToX(LPoint a,LPoint b,Plot plot)
    {
     auto count=LineDriver2::Count1(a.x,b.x);
   
     if( !count ) return false;
     
     count--;
    
     LineDriver2 driver(sx,sy);
     LineAlphaFunc2<uLCoord> func(sx,sy); 

     Point A;
     
     {
      uLCoord first=LineDriver2::First(a.x,ex);
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
      
      A=a.toPoint();
      
      LCoord delta=Delta(ey,a.y);
      
      plot(A-Point(0,2*ey),func.alpha2after(delta,part));
      plot(A-Point(0,ey)  ,func.alpha1after(delta,part));
      plot(A              ,func.alpha0after(delta,part));
      plot(A+Point(0,ey)  ,func.alpha1before(-delta,part));
      plot(A+Point(0,2*ey),func.alpha2before(-delta,part));
     }
    
     for(; count ;count--)
       {
        stepX(driver,a,A);
        plotX(func,a,A,plot);
       }
     
     {
      stepX(driver,a,A);
      
      LCoord delta=Delta(ey,a.y);
      LCoord part=PartBefore(ex,b.x);
      
      plot(A-Point(0,2*ey),func.alpha2before(delta,part));
      plot(A-Point(0,ey)  ,func.alpha1before(delta,part));
      plot(A              ,func.alpha0before(delta,part));
      plot(A+Point(0,ey)  ,func.alpha1after(-delta,part));
      plot(A+Point(0,2*ey),func.alpha2after(-delta,part));
     }
     
     return true;
    }
   
   void stepY(LineDriver2 &driver,LPoint &a,Point &A)
    {
     uLCoord delta_x=driver.step_pow2(LPoint::Precision);
     
     a.x=IntMove(a.x,ex,delta_x);
     
     A.y+=ey;
     A.x=LPoint::RShift(a.x);
    }
   
   template <class Plot>
   void plotY(LineAlphaFunc2<uLCoord> &func,LPoint a,Point A,Plot plot)
    {
     LCoord delta=Delta(ex,a.x);
     
     plot(A-Point(2*ex,0),func.alpha2(delta));
     plot(A-Point(ex,0)  ,func.alpha1(delta));
     plot(A              ,func.alpha0(delta));
     plot(A+Point(ex,0)  ,func.alpha1(-delta));
     plot(A+Point(2*ex,0),func.alpha2(-delta));
    }
   
   template <class Plot>
   bool lineToY(LPoint a,LPoint b,Plot plot)
    {
     auto count=LineDriver2::Count1(a.y,b.y);
   
     if( !count ) return false;
     
     count--;
    
     LineDriver2 driver(sy,sx);
     LineAlphaFunc2<uLCoord> func(sy,sx);
     
     Point A;
 
     {
      uLCoord first=LineDriver2::First(a.y,ey);
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
      
      A=a.toPoint();
      
      LCoord delta=Delta(ex,a.x);
      
      plot(A-Point(2*ex,0),func.alpha2after(delta,part));
      plot(A-Point(ex,0)  ,func.alpha1after(delta,part));
      plot(A              ,func.alpha0after(delta,part));
      plot(A+Point(ex,0)  ,func.alpha1before(-delta,part));
      plot(A+Point(2*ex,0),func.alpha2before(-delta,part));
     }
    
     for(; count ;count--)
       {
        stepY(driver,a,A);
        plotY(func,a,A,plot);
       }
     
     {
      stepY(driver,a,A);
      
      LCoord delta=Delta(ex,a.x);
      LCoord part=PartBefore(ey,b.y);
      
      plot(A-Point(2*ex,0),func.alpha2before(delta,part));
      plot(A-Point(ex,0)  ,func.alpha1before(delta,part));
      plot(A              ,func.alpha0before(delta,part));
      plot(A+Point(ex,0)  ,func.alpha1after(-delta,part));
      plot(A+Point(2*ex,0),func.alpha2after(-delta,part));
     }
    
     return true;
    }
   
  public:
  
   template <class Plot>
   bool run(LPoint a,LPoint b,Plot plot)
    {
     if( !DistDir(ex,sx,a.x,b.x) )
       {
        if( !DistDir(ey,sy,a.y,b.y) ) 
          {
           return false;
          }
       
        return lineY(a,b,plot); 
       }
     
     if( !DistDir(ey,sy,a.y,b.y) )
       {
        return lineX(a,b,plot);
       }
     
     if( sx>sy )
       {
        return lineToX(a,b,plot);
       }
     else
       {
        return lineToY(a,b,plot);
       }
    }
 };

/* LineSmooth(LPoint a,LPoint b,...) */

template <class Plot>
bool LineSmooth(LPoint a,LPoint b,Plot plot) // [a,b]
 {
  LinePlotter2 plotter;
  
  return plotter.run(a,b,plot);
 }

/* Circle() */

template <class UInt>
UInt SqRoot(UInt S,UInt x)
 {
  for(;;)
    {
     x=(x+S/x)/2;
     
     UInt q=x*x;
     
     if( q<=S ) 
       {
        if( q+x<=S ) return x+1;
       
        return x;
       }
    }
 }

template <class Plot>
void Circle(Point a,Coord radius,Plot plot)
 {
  if( radius<0 ) return;
  
  if( radius==0 )
    {
     plot(a);
     
     return;
    }
  
  {
   Coord x=radius;
   
   plot(a+Point(x,0));
   plot(a+Point(0,x));
   plot(a+Point(-x,0));
   plot(a+Point(0,-x));
  }
  
  uLCoord S=Sq<uLCoord>(radius)-1;
  
  Coord last_x=radius;
  
  for(Coord y=1;;S-=2*y+1,y++)
    {
     Coord x=(Coord)SqRoot<uLCoord>(S,radius);
     
     if( y>=x )
       {
        x=last_x-1;
        
        for(; y<=x ;y++,x--)
          {
           plot(a+Point(x,y));
           plot(a+Point(y,x));
           plot(a+Point(-x,y));
           plot(a+Point(-y,x));
           plot(a+Point(x,-y));
           plot(a+Point(y,-x));
           plot(a+Point(-x,-y));
           plot(a+Point(-y,-x));
          }
       
        break;
       }
     
     plot(a+Point(x,y));
     plot(a+Point(y,x));
     plot(a+Point(-x,y));
     plot(a+Point(-y,x));
     plot(a+Point(x,-y));
     plot(a+Point(y,-x));
     plot(a+Point(-x,-y));
     plot(a+Point(-y,-x));
     
     last_x=x;
    }
 }

template <class HPlot>
void Ball(Point a,Coord radius,HPlot plot)
 {
  if( radius<0 ) return;
  
  if( radius==0 )
    {
     plot(a);
     
     return;
    }
  
  {
   Coord x=radius;
   
   plot(a.y,a.x-x,a.x+x);
   
   plot(a+Point(0,x));
   plot(a+Point(0,-x));
  }
  
  uLCoord S=Sq<uLCoord>(radius)-1;
  
  Coord last_x=radius;
  
  for(Coord y=1;;S-=2*y+1,y++)
    {
     Coord x=(Coord)SqRoot<uLCoord>(S,radius);
     
     if( y>=x )
       {
        x=last_x-1;
        
        for(; y<=last_x ;y++,x--)
          {
           plot(a.y+y,a.x-x,a.x+x);
           plot(a.y-y,a.x-x,a.x+x);
          }
       
        break;
       }
     
     plot(a.y+y,a.x-x,a.x+x);
     plot(a.y-y,a.x-x,a.x+x);
     
     if( x<last_x )
       {
        Coord last_y=y-1;
        
        plot(a.y+last_x,a.x-last_y,a.x+last_y);
        plot(a.y-last_x,a.x-last_y,a.x+last_y);
       }
     
     last_x=x;
    }
 }

/* class SolidSection */

class SolidSection : NoCopy
 {
   struct Dot : NoThrowFlagsBase
    {
     Point dot;
     ulen sect = 0 ;
     
     Dot() {}
    };
   
   struct Sect : NoThrowFlagsBase
    {
     Coord y = 0 ;
     ulen dot = 0 ;
     
     Sect() {}
     
     void set(Coord y_,ulen dot_) { y=y_; dot=dot_; }
     
     bool operator < (Sect obj) const { return y<obj.y; }
     
     bool operator != (Sect obj) const { return y!=obj.y; }
    };
   
   using IndexType = int ;
   
   struct Line : NoThrowFlagsBase
    {
     Point a;
     Point b;
     IndexType delta_index = 0 ;
     ulen bottom = 0 ;
     ulen top = 0 ;
     
     Line() {}
     
     Line(Dot a,Dot b);
     
     Coord ex = 0 ;
     Coord ey = 0 ;
     uCoord sx = 0 ;
     uCoord sy = 0 ;
     
     union Driver
      {
       LineDriver obj;
       
       Driver() {}
      };
     
     Driver driver;
     
     Coord x0 = 0 ;
     Coord x1 = 0 ;
     
     void step();
    };
   
   StackArray<Dot> path;
   StackArray<Sect> sect;
   StackArray<Line> line_buf;
   StackArray<Line *> lines;
   
   ulen sect_count = 0 ;
   
  private: 
   
   static void Sort(PtrLen<Line *> set);
   
   static void Step(PtrLen<Line *> set);
   
   template <class HPlot>
   void fill(Coord bottom,Coord top,PtrLen<Line *> set,bool all_flag,HPlot plot)
    {
     for(; bottom<top ;bottom++)
       {
        Sort(set);
        
        if( all_flag )
          {
           Coord x=0;
           IndexType index=0;
         
           for(Line *line : set ) 
             {
              if( index==0 ) x=line->x0;
             
              index+=line->delta_index;
              
              if( index==0 ) plot(bottom,x,line->x1); 
             }
          }
        else
          {
           Coord x=0;
           bool flag=false;
         
           for(Line *line : set ) 
             {
              if( !flag ) x=line->x0;
             
              flag=!flag;
              
              if( !flag ) plot(bottom,x,line->x1); 
             }
          }
        
        Step(set);
       }
    }
   
  public:
 
   explicit SolidSection(PtrLen<const Point> dots);
   
   ~SolidSection();
   
   template <class HPlot>
   void fill(bool all_flag,HPlot plot)
    {
     ulen off=0;
     ulen lim=0;
     
     Coord bottom=sect[0].y;
     
     for(ulen s=1; s<sect_count ;s++)
       {
        Coord top=sect[s].y;
        
        for(; lim<lines.getLen() && lines[lim]->bottom<s ;lim++);
        
        ulen ind=lim;
        
        while( ind>off )
          {
           if( lines[--ind]->top<s )
             {
              ulen i=ind;
              
              while( i>off )
                {
                 if( lines[--i]->top>=s )
                   {
                    lines[ind--]=lines[i];
                   }
                }
              
              ind++;
             
              break;
             }
          }
        
        off=ind;
        
        fill(bottom,top,Range(lines).part(off,lim-off),all_flag,plot);
        
        bottom=top;
       }

     {
      Coord top=sect[sect_count-1].y;
      
      for(Line &line : line_buf )
        {
         Point a=line.a;
         Point b=line.b;
         
         if( a.y==b.y ) plot(a.y,a.x,b.x);
         
         if( b.y==top ) plot(b);
        }
     }
    }
 };

/* Solid() */

template <class HPlot>
void Solid(PtrLen<const Point> dots,bool all_flag,HPlot plot)
 {
  if( dots.len==0 ) return;
  
  if( dots.len==1 )
    {
     plot(dots[0]);
     
     return;
    }
  
  SolidSection data(dots);
  
  data.fill(all_flag,plot);
 }

} // namespace Algo
} // namespace Video
} // namespace CCore
 
#endif
 

