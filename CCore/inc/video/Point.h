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

/* classes */ 

template <class T,class Int> struct BasePoint;

struct Point;

struct MilliPoint;

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
  
  friend T operator + (T a,T b) { return T(IntAdd(a.x,b.x),IntAdd(a.y,b.y)); }
  
  friend T operator - (T a,T b) { return T(IntSub(a.x,b.x),IntSub(a.y,b.y)); }
  
  friend T operator * (Int a,T p) { return T(IntMul(a,p.x),IntMul(a,p.y)); }
  
  friend T operator * (T p,Int a) { return T(IntMul(p.x,a),IntMul(p.y,a)); }
  
  friend T operator << (T p,unsigned s) { return T(IntLShift(p.x,s),IntLShift(p.y,s)); }
  
  friend T operator >> (T p,unsigned s) { return T(IntRShift(p.x,s),IntRShift(p.y,s)); }
  
  // derived operations
  
  friend T operator += (T &a,T b) { return a=a+b; }
  
  friend T operator -= (T &a,T b) { return a=a-b; }
  
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

struct Point : BasePoint<Point,int>
 {
  using BasePoint<Point,int>::BasePoint;
 };

/* struct MilliPoint */

struct MilliPoint : BasePoint<MilliPoint,int>
 {
  using BasePoint<MilliPoint,int>::BasePoint;
  
  MilliPoint(Point p) : BasePoint<MilliPoint,int>(p.x*1024,p.y*1024) {}
 };

/* struct Pane */ 

struct Pane
 {
  int x;
  int y;
  int dx; // >=0 
  int dy; // >=0
  
  Pane() : x(0),y(0),dx(0),dy(0) {}
  
  Pane(NothingType) : Pane() {}
  
  Pane(int x_,int y_,int dx_,int dy_)
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

inline Pane Extent(Point base,int dx,int dy) { return Pane(base.x,base.y,dx,dy); }

inline Pane Extent(Point base,Point size) { return Pane(base.x,base.y,size.x,size.y); }

} // namespace Video
} // namespace CCore
 
#endif
 

