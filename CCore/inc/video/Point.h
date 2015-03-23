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

template <int Den> struct DenPoint;

struct Pane;

/* struct DenPoint<int Den> */ 

template <int Den>
struct DenPoint
 {
  int x;
  int y;
  
  DenPoint() : x(0),y(0) {}
  
  DenPoint(NothingType) : DenPoint() {}
  
  template <class Unused=int>
  DenPoint(DenPoint<1> p,Meta::EnableIf< (Den>1) ,Unused> unused=0) : x(IntMul(p.x,Den)),y(IntMul(p.y,Den)) {}
  
  DenPoint(int x_,int y_) : x(x_),y(y_) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;)",x,y);
   }
 };
 
template <int Den>
DenPoint<Den> operator + (DenPoint<Den> a,DenPoint<Den> b) { return DenPoint<Den>(IntAdd(a.x,b.x),IntAdd(a.y,b.y)); }
 
template <int Den>
DenPoint<Den> operator - (DenPoint<Den> a,DenPoint<Den> b) { return DenPoint<Den>(IntSub(a.x,b.x),IntSub(a.y,b.y)); }

template <int Den>
DenPoint<Den> operator += (DenPoint<Den> &a,DenPoint<Den> b) { return a=a+b; }
 
template <int Den>
DenPoint<Den> operator -= (DenPoint<Den> &a,DenPoint<Den> b) { return a=a-b; }

template <int Den>
bool operator == (DenPoint<Den> a,DenPoint<Den> b) { return a.x==b.x && a.y==b.y ; }
 
template <int Den>
bool operator != (DenPoint<Den> a,DenPoint<Den> b) { return a.x!=b.x || a.y!=b.y ; }

template <int Den>
bool operator < (DenPoint<Den> a,DenPoint<Den> b) { return a.x<b.x && a.y<b.y ; }

template <int Den>
bool operator > (DenPoint<Den> a,DenPoint<Den> b) { return a.x>b.x && a.y>b.y ; }

template <int Den>
bool operator <= (DenPoint<Den> a,DenPoint<Den> b) { return a.x<=b.x && a.y<=b.y ; }

template <int Den>
bool operator >= (DenPoint<Den> a,DenPoint<Den> b) { return a.x>=b.x && a.y>=b.y ; }

template <int Den>
DenPoint<Den> Sup(DenPoint<Den> a,DenPoint<Den> b) { return DenPoint<Den>(Max(a.x,b.x),Max(a.y,b.y)); }
 
template <int Den>
DenPoint<Den> Inf(DenPoint<Den> a,DenPoint<Den> b) { return DenPoint<Den>(Min(a.x,b.x),Min(a.y,b.y)); }

/* type Point */

using Point = DenPoint<1> ; 

/* type MilliPoint */

using MilliPoint = DenPoint<1024> ; 

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
 

