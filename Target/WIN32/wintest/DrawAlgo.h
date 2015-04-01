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

namespace CCore {
namespace Video {

/* PointDist() */

inline uint64 PointDist(LPoint a,LPoint b)
 {
  return Max(IntAbs(a.x,b.x),IntAbs(a.y,b.y))>>LPoint::Precision;
 }

/* PointNear() */

inline bool PointNear(int a,int b) { return (a<b)?( b-a==1 ):( a-b<=1 ); }

inline bool PointNear(Point a,Point b) { return PointNear(a.x,b.x) && PointNear(a.y,b.y) ; }

/* DistDir() */

template <class SInt,class UInt>
bool DistDir(int &e,UInt &s,SInt a,SInt b)
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

/* classes */

template <class UInt> class LineDriverBase;

class LineDriver;

class LineDriver32;

class CurveDriver;

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
     bool ret=false;
     
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

class LineDriver : public LineDriverBase<uint16>
 {
  public:
  
   LineDriver(unsigned sx,unsigned sy) : LineDriverBase<unsigned>(sx,sy) {} // sx >= sy > 0
   
   struct Result
    {
     unsigned off;
     unsigned lim;
     
     bool operator + () const { return off<lim; }
     
     bool operator ! () const { return off>=lim; }
    };
   
   static Result Inf(Result a,Result b) { return {Max(a.off,b.off),Min(a.lim,b.lim)}; }
   
   Result clip(int x,int y,int ex,int ey,int dx,int dy) const;

   unsigned clipToX(unsigned y) const;
   
   Result clipToX(Result clip_y) const;
   
   static Result Clip(int x,int e,int d);
 };

/* class LineDriver32 */

class LineDriver32 : public LineDriverBase<uint32>
 {
  public:
  
   LineDriver32(uint64 sx,uint64 sy) : LineDriverBase<uint64>(sx,sy) {} // sx >= sy > 0
   
   static uint64 First(sint64 a,int e)
    {
     int A=LPoint::RShift(a);
     
     if( e>0 )
       {
        return LPoint::LShift(A+1)-a;
       }
     else
       {
        return a-LPoint::LShift(A-1);
       }
    }
   
   static unsigned Count(sint64 a,sint64 b)
    {
     int A=LPoint::RShift(a);
     int B=LPoint::RShift(b);
     
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
   
   static const ulen Len = (1u<<MaxLevel) ;
   
   static uint64 Fineness(PtrStepLen<const LPoint> dots);
   
   static sint64 Spline(sint64 a,sint64 b,sint64 c,sint64 d);
 
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

/* Line(Point a,Point b,...) */

template <class Color,class Plot>
void Line(Point a,Point b,Color color,Plot plot) // [a,b)
 {
  int ex;
  int ey;
  unsigned sx;
  unsigned sy;
  
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
  const unsigned Step = 1u<<LPoint::Precision ;
  
  int ex;
  int ey;
  uint64 sx;
  uint64 sy;
  
  if( !DistDir(ex,sx,a.x,b.x) )
    {
     if( !DistDir(ey,sy,a.y,b.y) ) 
       {
        return {Null,Null,false};
       }
    
     unsigned count=LineDriver64::Count(a.y,b.y);
     
     if( !count ) return {Null,Null,false};
     
     Point E;
 
     {
      uint64 first=LineDriver64::First(a.y,ey);
      
      if( first>=Step )
        {
         uint64 delta_y=first-Step;
         
         a.y=IntMove(a.y,ey,delta_y);
         
         E=a.toPoint();
        }
      else
        {
         uint64 delta_y=Step-first;
         
         a.y=IntMove(a.y,-ey,delta_y);
         
         E=a.toPoint();
        }
     }

     Point A=E;
     
     if( ey>0 )
       {
        A.y++;
        
        func(E,A,color,plot);
       
        plot(A,color);
       
        for(count--; count ;count--)
          {
           A.y++;
           
           plot(A,color);
          }
       }
     else
       {
        A.y--;
       
        func(E,A,color,plot);
        
        plot(A,color);
        
        for(count--; count ;count--)
          {
           A.y--;
           
           plot(A,color);
          }
       }
     
     Point L=A;
     
     if( ey>0 ) A.y++; else A.y--;
      
     return {L,A,true};
    }
 
  if( !DistDir(ey,sy,a.y,b.y) )
    {
     unsigned count=LineDriver64::Count(a.x,b.x);
     
     if( !count ) return {Null,Null,false};
    
     Point E;
 
     {
      uint64 first=LineDriver64::First(a.x,ex);
      
      if( first>=Step )
        {
         uint64 delta_x=first-Step;
         
         a.x=IntMove(a.x,ex,delta_x);
         
         E=a.toPoint();
        }
      else
        {
         uint64 delta_x=Step-first;
         
         a.x=IntMove(a.x,-ex,delta_x);
         
         E=a.toPoint();
        }
     }
 
     Point A=E;
     
     if( ex>0 )
       {
        A.x++;
        
        func(E,A,color,plot);
       
        plot(A,color);
        
        for(count--; count ;count--)
          {
           A.x++;
           
           plot(A,color);
          }
       }
     else
       {
        A.x--;
       
        func(E,A,color,plot);
        
        plot(A,color);
        
        for(count--; count ;count--)
          {
           A.x--;
           
           plot(A,color);
          }
       }
     
     Point L=A;
     
     if( ex>0 ) A.x++; else A.x--;
      
     return {L,A,true};
    }
  
  if( sx>sy )
    {
     unsigned count=LineDriver64::Count(a.x,b.x);
    
     if( !count ) return {Null,Null,false};
     
     LineDriver driver(sx,sy);
     Point E;

     {
      uint64 first=LineDriver64::First(a.x,ex);
      
      if( first>=Step )
        {
         uint64 delta_x=first-Step;
         uint64 delta_y=driver.step(delta_x);
         
         a.x=IntMove(a.x,ex,delta_x);
         a.y=IntMove(a.y,ey,delta_y);
         
         E=a.toPoint();
        }
      else
        {
         uint64 delta_x=Step-first;
         uint64 delta_y=driver.back(delta_x);
         
         a.x=IntMove(a.x,-ex,delta_x);
         a.y=IntMove(a.y,-ey,delta_y);
         
         E=a.toPoint();
        }
     }
     
     Point A;
     
     {
      uint64 delta_x=Step;
      uint64 delta_y=driver.step_pow2(LPoint::Precision);
      
      a.x=IntMove(a.x,ex,delta_x);
      a.y=IntMove(a.y,ey,delta_y);
      
      A=a.toPoint();
      
      func(E,A,color,plot);
      
      plot(A,color);
     }
     
     for(count--; count ;count--)
       {
        uint64 delta_x=Step;
        uint64 delta_y=driver.step_pow2(LPoint::Precision);
        
        a.x=IntMove(a.x,ex,delta_x);
        a.y=IntMove(a.y,ey,delta_y);
        
        A=a.toPoint();
        
        plot(A,color);
       }
     
     Point L=A;
     
     {
      uint64 delta_x=Step;
      uint64 delta_y=driver.step_pow2(LPoint::Precision);
      
      a.x=IntMove(a.x,ex,delta_x);
      a.y=IntMove(a.y,ey,delta_y);
      
      A=a.toPoint();
      
      return {L,A,true};
     }
    }
  else
    {
     unsigned count=LineDriver64::Count(a.y,b.y);
     
     if( !count ) return {Null,Null,false};
     
     LineDriver driver(sy,sx);
     Point E;
 
     {
      uint64 first=LineDriver64::First(a.y,ey);
      
      if( first>=Step )
        {
         uint64 delta_y=first-Step;
         uint64 delta_x=driver.step(delta_y);
         
         a.y=IntMove(a.y,ey,delta_y);
         a.x=IntMove(a.x,ex,delta_x);
         
         E=a.toPoint();
        }
      else
        {
         uint64 delta_y=Step-first;
         uint64 delta_x=driver.back(delta_y);
         
         a.y=IntMove(a.y,-ey,delta_y);
         a.x=IntMove(a.x,-ex,delta_x);
         
         E=a.toPoint();
        }
     }
     
     Point A;
     
     {
      uint64 delta_y=Step;
      uint64 delta_x=driver.step_pow2(LPoint::Precision);
      
      a.y=IntMove(a.y,ey,delta_y);
      a.x=IntMove(a.x,ex,delta_x);
      
      A=a.toPoint();
      
      func(E,A,color,plot);
      
      plot(A,color);
     }
     
     for(count--; count ;count--)
       {
        uint64 delta_y=Step;
        uint64 delta_x=driver.step_pow2(LPoint::Precision);
        
        a.y=IntMove(a.y,ey,delta_y);
        a.x=IntMove(a.x,ex,delta_x);
        
        A=a.toPoint();
        
        plot(A,color);
       }
     
     Point L=A;
     
     {
      uint64 delta_y=Step;
      uint64 delta_x=driver.step_pow2(LPoint::Precision);
      
      a.y=IntMove(a.y,ey,delta_y);
      a.x=IntMove(a.x,ex,delta_x);
      
      A=a.toPoint();
      
      return {L,A,true};
     }
    }
 }

/* Line(Point A,LPoint a,LPoint b,...) */

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

} // namespace Video
} // namespace CCore
 
#endif
 

