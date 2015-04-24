/* Point.h */ 
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

#ifndef CCore_inc_video_Point_h
#define CCore_inc_video_Point_h
 
#include <CCore/inc/video/IntOp.h>

namespace CCore {
namespace Video {

/* types */

using Coord = sint16 ;

using uCoord = uint16 ;

using MCoord = sint32 ;

using uMCoord = uint32 ;

using LCoord = sint32 ;

using uLCoord = uint32 ;

using AreaType = unsigned ;

/* consts */

const Coord MaxCoord = 32767 ;

const Coord MinCoord = -32768 ;

/* functions */

inline constexpr AreaType Area(Coord dx,Coord dy) { return (AreaType)dx*(AreaType)dy; }

/* classes */ 

template <class T,class Int> struct BasePoint;

struct Point;

struct MilliPoint;

struct LPoint;

struct Pane;

/* struct BasePoint<T,Int> */

template <class T,class Int> 
struct BasePoint
 {
  Int x;
  Int y;
  
  // constructors
  
  BasePoint() : x(0),y(0) {}
  
  BasePoint(NothingType) : BasePoint() {}
  
  BasePoint(Int x_,Int y_) : x(x_),y(y_) {}
  
  // unsafe operations
  
  friend T operator - (T a) { return Null-a; }
  
  friend T operator + (T a,T b) { return T(IntAdd(a.x,b.x),IntAdd(a.y,b.y)); }
  
  friend T operator - (T a,T b) { return T(IntSub(a.x,b.x),IntSub(a.y,b.y)); }
  
  friend T operator * (Int a,T p) { return T(IntMul(a,p.x),IntMul(a,p.y)); }
  
  friend T operator * (T p,Int a) { return T(IntMul(p.x,a),IntMul(p.y,a)); }
  
  friend T operator / (T p,Int a) { return T(IntDiv(p.x,a),IntDiv(p.y,a)); }
  
  friend T operator << (T p,unsigned s) { return T(IntLShift(p.x,s),IntLShift(p.y,s)); }
  
  friend T operator >> (T p,unsigned s) { return T(IntRShift(p.x,s),IntRShift(p.y,s)); }
  
  // derived operations
  
  friend T operator += (T &a,T b) { return a=a+b; }
  
  friend T operator -= (T &a,T b) { return a=a-b; }
  
  friend T operator *= (T &p,Int a) { return p=p*a; }
  
  friend T operator /= (T &p,Int a) { return p=p/a; }
  
  friend T operator <<= (T &p,unsigned s) { return p=p<<s; }
  
  friend T operator >>= (T &p,unsigned s) { return p=p>>s; }
  
  // safe operations
  
  friend bool operator == (T a,T b) { return a.x==b.x && a.y==b.y ; }
  
  friend bool operator != (T a,T b) { return a.x!=b.x || a.y!=b.y ; }
  
  friend bool operator < (T a,T b) { return a.x<b.x && a.y<b.y ; }
  
  friend bool operator <= (T a,T b) { return a.x<=b.x && a.y<=b.y ; }
  
  friend bool operator > (T a,T b) { return a.x>b.x && a.y>b.y ; }
  
  friend bool operator >= (T a,T b) { return a.x>=b.x && a.y>=b.y ; }
  
  friend T Sup(T a,T b) { return T(Max(a.x,b.x),Max(a.y,b.y)); }
  
  friend T Inf(T a,T b) { return T(Min(a.x,b.x),Min(a.y,b.y)); }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;)",x,y);
   }
 
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* struct Point */

struct Point : BasePoint<Point,Coord>
 {
  using BasePoint<Point,Coord>::BasePoint;
  
  static Point Max() { return Point(MaxCoord,MaxCoord); }
  
  static Point Min() { return Point(MinCoord,MinCoord); }
 };

/* struct MilliPoint */

struct MilliPoint : BasePoint<MilliPoint,MCoord>
 {
  static const unsigned Precision = 10 ;
 
  static MCoord LShift(Coord a) { return IntLShift((MCoord)a,Precision); }
  
  // constructors
  
  using BasePoint<MilliPoint,MCoord>::BasePoint;
  
  MilliPoint() {}
  
  MilliPoint(Point p) : BasePoint<MilliPoint,MCoord>(LShift(p.x),LShift(p.y)) {}
 };

/* struct LPoint */

struct LPoint : BasePoint<LPoint,LCoord>
 {
  static const unsigned Precision = 14 ;
 
  static LCoord LShift(Coord a) { return IntLShift((LCoord)a,Precision); }
  
  static LCoord LShift_ext(LCoord a) { return IntLShift(a,Precision); }
  
  static const LCoord RShiftBias = LCoord(1)<<(Precision-1) ;
 
  static Coord RShift(LCoord a) { return (Coord)IntRShift(IntAdd(a,RShiftBias),Precision); }
  
  static LCoord RShift_ext(LCoord a) { return IntRShift(IntAdd(a,RShiftBias),Precision); }
  
  static LCoord LShift_m(MCoord a) { return IntLShift((LCoord)a,Precision-MilliPoint::Precision); }
  
  // constructors
  
  using BasePoint<LPoint,LCoord>::BasePoint;
  
  LPoint() {}
  
  LPoint(Point p) : BasePoint<LPoint,LCoord>(LShift(p.x),LShift(p.y)) {}
  
  LPoint(MilliPoint p) : BasePoint<LPoint,LCoord>(LShift_m(p.x),LShift_m(p.y)) {}
  
  // methods
  
  Point toPoint() const { return Point(RShift(x),RShift(y)); }
 };

/* struct Pane */ 

struct Pane
 {
  Coord x;
  Coord y;
  Coord dx; // >=0 
  Coord dy; // >=0
  
  Pane() : x(0),y(0),dx(0),dy(0) {}
  
  Pane(NothingType) : Pane() {}
  
  Pane(Coord x_,Coord y_,Coord dx_,Coord dy_)
   : x(x_),y(y_),dx(dx_),dy(dy_) 
   {
    getLim();
    
    IntGuard( dx>=0 && dy>=0 );
   }

  Pane(Point base,Point lim) // base<=lim
   {
    x=base.x;
    y=base.y;
    dx=IntSub(lim.x,base.x);
    dy=IntSub(lim.y,base.y);
    
    IntGuard( dx>=0 && dy>=0 );
   }
  
  bool operator + () const { return dx>0 && dy>0 ; }  
  
  bool operator ! () const { return dx<=0 || dy<=0 ; }
  
  Point getBase() const { return Point(x,y); }
  
  Point getSize() const { return Point(dx,dy); }
  
  Point getLim() const { return Point(IntAdd(x,dx),IntAdd(y,dy)); }
  
  AreaType getArea() const { return Area(dx,dy); }
  
  bool contains(Point point) const
   { 
    return point>=getBase() && point<getLim() ; 
   }
  
  bool contains_nonempty(Pane pane) const // +pane
   { 
    return pane.getBase()>=getBase() && pane.getLim()<=getLim() ; 
   }
  
  bool contains(Pane pane) const
   {
    if( !pane ) return true;
    
    return contains_nonempty(pane);
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#; +#;,#; +#;)",x,dx,y,dy);
   }
 };

inline Pane Sup_nonempty(Pane a,Pane b) // +a && +b
 {
  Point base=Inf(a.getBase(),b.getBase());
  Point lim=Sup(a.getLim(),b.getLim());
  
  return Pane(base,lim); 
 }

inline Pane Sup(Pane a,Pane b)
 {
  if( !a ) return b;
  
  if( !b ) return a;
  
  return Sup_nonempty(a,b);
 }

inline Pane Inf_nonempty(Pane a,Pane b) // +a && +b
 {
  Point base=Sup(a.getBase(),b.getBase());
  Point lim=Inf(a.getLim(),b.getLim());
  
  if( base<lim ) return Pane(base,lim);
  
  return Empty;
 }

inline Pane Inf(Pane a,Pane b)
 {
  if( !a ) return a;
  
  if( !b ) return b;
  
  return Inf_nonempty(a,b);
 }

inline Pane Extent(Point base,Coord dx,Coord dy) { return Pane(base.x,base.y,dx,dy); }

inline Pane Extent(Point base,Point size) { return Pane(base.x,base.y,size.x,size.y); }

} // namespace Video
} // namespace CCore
 
#endif
 

