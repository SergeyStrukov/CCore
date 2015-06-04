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

using DCoord = sint64 ;

using AreaType = uint32 ;

/* consts */

const Coord MaxCoord = 32767 ;

const Coord MinCoord = -32768 ;

/* functions */

inline constexpr AreaType Area(Coord dx,Coord dy) { return AreaType(dx)*AreaType(dy); }

/* classes */ 

struct Coordinate;

template <class T,class Int> struct BasePoint;

struct Point;

struct MPoint;

struct Ratio;

struct Pane;

class PointMap;

/* struct Coordinate */

struct Coordinate
 {
  Coord x;
  
  // constructors
  
  Coordinate() : x(0) {}
  
  Coordinate(NothingType) : Coordinate() {}
  
  Coordinate(Coord x_) : x(x_) {}
  
  // methods
  
  Coord operator + () const { return x; }
  
  static Coordinate Max() { return Coordinate(MaxCoord); }
  
  static Coordinate Min() { return Coordinate(MinCoord); }
  
  // unsafe operations
  
  friend Coordinate operator - (Coordinate a) { return Coordinate()-a; }
  
  friend Coordinate operator + (Coordinate a,Coordinate b) { return Coordinate(IntAdd(a.x,b.x)); }
  
  friend Coordinate operator - (Coordinate a,Coordinate b) { return Coordinate(IntSub(a.x,b.x)); }
  
  friend Coordinate operator * (Coordinate a,Coordinate b) { return Coordinate(IntMul(a.x,b.x)); }
  
  friend Coordinate operator / (Coordinate a,Coordinate b) { return Coordinate(IntDiv(a.x,b.x)); }
  
  friend Coordinate operator << (Coordinate a,unsigned s) { return Coordinate(IntLShift(a.x,s)); }
  
  friend Coordinate operator >> (Coordinate a,unsigned s) { return Coordinate(IntRShift(a.x,s)); }
  
  // derived operations
  
  friend Coordinate operator += (Coordinate &a,Coordinate b) { return a=a+b; }
  
  friend Coordinate operator -= (Coordinate &a,Coordinate b) { return a=a-b; }
  
  friend Coordinate operator *= (Coordinate &a,Coordinate b) { return a=a*b; }
  
  friend Coordinate operator /= (Coordinate &a,Coordinate b) { return a=a/b; }
  
  friend Coordinate operator <<= (Coordinate &a,unsigned s) { return a=a<<s; }
  
  friend Coordinate operator >>= (Coordinate &a,unsigned s) { return a=a>>s; }
  
  // safe operations
  
  friend bool operator == (Coordinate a,Coordinate b) { return a.x==b.x ; }
  
  friend bool operator != (Coordinate a,Coordinate b) { return a.x!=b.x ; }
  
  friend bool operator < (Coordinate a,Coordinate b) { return a.x<b.x ; }
  
  friend bool operator <= (Coordinate a,Coordinate b) { return a.x<=b.x ; }
  
  friend bool operator > (Coordinate a,Coordinate b) { return a.x>b.x ; }
  
  friend bool operator >= (Coordinate a,Coordinate b) { return a.x>=b.x ; }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Putobj(out,x);
   }
 
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

inline Coordinate Sup(Coordinate a,Coordinate b) { return Coordinate(Max(a.x,b.x)); }

inline Coordinate Inf(Coordinate a,Coordinate b) { return Coordinate(Min(a.x,b.x)); }

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
  
  friend T operator - (T a) { return T()-a; }
  
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

/* struct MPoint */

struct MPoint : BasePoint<MPoint,MCoord>
 {
  static const unsigned Precision = 10 ;
 
  static MCoord LShift(Coord a) { return IntLShift((MCoord)a,Precision); }
  
  static MCoord LShift_ext(MCoord a) { return IntLShift(a,Precision); }
  
  static const MCoord RShiftBias = MCoord(1)<<(Precision-1) ;
 
  static Coord RShift(MCoord a) { return From32To16( IntRShift(IntAdd(a,RShiftBias),Precision) ); }
  
  static MCoord RShift_ext(MCoord a) { return IntRShift(IntAdd(a,RShiftBias),Precision); }
  
  // constructors
  
  using BasePoint<MPoint,MCoord>::BasePoint;
  
  MPoint() {}
  
  MPoint(Point p) : BasePoint<MPoint,MCoord>(LShift(p.x),LShift(p.y)) {}
  
  // methods
  
  Point toPoint() const { return Point(RShift(x),RShift(y)); }
 };

/* struct Ratio */

struct Ratio
 {
  static const unsigned Precision = 16 ;
  
  MCoord value;
  
  // constructors
  
  Ratio() : value(0) {}
  
  explicit Ratio(MCoord value_) : value(value_) {}
  
  Ratio(MCoord value_,unsigned prec) : value( IntLShift(value_,Precision-prec) ) {} // prec <= Precision
  
  // methods
  
  Ratio pow(unsigned deg) const;
  
  // operators
  
  friend Ratio operator - (Ratio a)
   {
    return Ratio(-a.value);
   }
  
  friend Ratio operator + (Ratio a,Ratio b)
   {
    return Ratio(a.value+b.value);
   }
  
  friend Ratio operator - (Ratio a,Ratio b)
   {
    return Ratio(a.value-b.value);
   }
  
  friend Ratio operator * (Ratio a,Ratio b)
   {
    return Ratio( MCoord( IntRShift(DCoord(a.value)*b.value,Precision) ) );
   }
  
  friend Ratio operator / (Ratio a,Ratio b)
   {
    return Ratio( MCoord( IntLShift(DCoord(a.value),Precision)/b.value ) );
   }
  
  friend MCoord operator * (Ratio a,MCoord b)
   {
    return MCoord( IntRShift(DCoord(a.value)*b,Precision) );
   }
  
  friend MPoint operator * (Ratio a,MPoint point)
   {
    return MPoint(a*point.x,a*point.y);
   }
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
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#; +#;,#; +#;)",x,dx,y,dy);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* functions */

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


inline Pane Extent(Coord x,Coord y,Coord dx,Coord dy) { if( dx>0 && dy>0 ) return Pane(x,y,dx,dy); return Empty; }

inline Pane Extent(Coord x,Coord y,Point size) { return Extent(x,y,size.x,size.y); }

inline Pane Extent(Point base,Coord dx,Coord dy) { return Extent(base.x,base.y,dx,dy); }

inline Pane Extent(Point base,Point size) { return Extent(base.x,base.y,size.x,size.y); }


inline Pane Envelope(Point a,Point b) { return Pane(Inf(a,b),Sup(a,b)+Point(1,1)); }


inline Pane operator + (Pane pane,Point point) { return Pane(IntAdd(pane.x,point.x),IntAdd(pane.y,point.y),pane.dx,pane.dy); }

inline Pane operator += (Pane &pane,Point point) { return pane=pane+point; }

inline Pane operator - (Pane pane,Point point) { return Pane(IntSub(pane.x,point.x),IntSub(pane.y,point.y),pane.dx,pane.dy); }

inline Pane operator -= (Pane &pane,Point point) { return pane=pane-point; }


inline Pane Inner(Pane pane,Pane subpane) { return Inf(subpane+pane.getBase(),pane); }


inline Pane Shrink(Pane pane,Point delta) { return Extent(pane.getBase()+delta,pane.getSize()-2*delta); }

inline Pane Shrink(Pane pane,Coord delta_x,Coord delta_y) { return Shrink(pane,Point(delta_x,delta_y)); }

inline Pane Shrink(Pane pane,Coord delta) { return Shrink(pane,Point(delta,delta)); }

inline Pane Expand(Pane pane,Point delta) { return Shrink(pane,-delta); }

inline Pane Expand(Pane pane,Coord delta_x,Coord delta_y) { return Shrink(pane,-Point(delta_x,delta_y)); }

inline Pane Expand(Pane pane,Coord delta) { return Shrink(pane,-Point(delta,delta)); }


inline Pane SplitX(Coord delta,Pane &pane)
 {
  Pane ret=Pane(pane.x,pane.y,delta,pane.dy);
  
  pane=Pane(IntAdd(pane.x,delta),pane.y,IntSub(pane.dx,delta),pane.dy);
  
  return ret;
 }

inline Pane SplitX(Pane &pane,Coord delta)
 {
  Coord dx=IntSub(pane.dx,delta);
  
  Pane ret=Pane(IntAdd(pane.x,dx),pane.y,delta,pane.dy);
  
  pane=Pane(pane.x,pane.y,dx,pane.dy);
  
  return ret;
 }

inline Pane SplitY(Coord delta,Pane &pane)
 {
  Pane ret=Pane(pane.x,pane.y,pane.dx,delta);
  
  pane=Pane(pane.x,IntAdd(pane.y,delta),pane.dx,IntSub(pane.dy,delta));
  
  return ret;
 }

inline Pane SplitY(Pane &pane,Coord delta)
 {
  Coord dy=IntSub(pane.dy,delta);
  
  Pane ret=Pane(pane.x,IntAdd(pane.y,dy),pane.dx,delta);
  
  pane=Pane(pane.x,pane.y,pane.dx,dy);
  
  return ret;
 }


inline Pane TrySplitX(Coord delta,Pane &pane)
 {
  if( delta<=pane.dx ) return SplitX(delta,pane);
  
  return Empty;
 }

inline Pane TrySplitX(Pane &pane,Coord delta)
 {
  if( delta<=pane.dx ) return SplitX(pane,delta);
  
  return Empty;
 }

inline Pane TrySplitY(Coord delta,Pane &pane)
 {
  if( delta<=pane.dy ) return SplitY(delta,pane);
  
  return Empty;
 }

inline Pane TrySplitY(Pane &pane,Coord delta)
 {
  if( delta<=pane.dy ) return SplitY(pane,delta);
  
  return Empty;
 }

/* class PointMap */

class PointMap
 {
   Point origin;
   
  public:
   
   explicit PointMap(Point origin_) : origin(origin_) {}
  
   template <class T>
   T operator () (T obj) const { return obj+origin; }
 };

} // namespace Video
} // namespace CCore
 
#endif
 

