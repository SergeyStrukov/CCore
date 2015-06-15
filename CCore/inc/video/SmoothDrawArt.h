/* SmoothDrawArt.h */ 
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

#ifndef CCore_inc_video_SmoothDrawArt_h
#define CCore_inc_video_SmoothDrawArt_h

#include <CCore/inc/video/DrawBuf.h>
#include <CCore/inc/video/ColorField.h>

#include <CCore/inc/video/CurveDriver.h>
#include <CCore/inc/video/SmoothAlgo.h>

namespace CCore {
namespace Video {
namespace Smooth {

/* PrefixWith() */

template <class R>
R PrefixWith(R r,R suffix)
 {
  auto len=Algon::BaseRangeAlgo<R>::GetLen(r)-Algon::BaseRangeAlgo<R>::GetLen(suffix)+1;
  
  return Algon::BaseRangeAlgo<R>::GetPrefix(r,len);
 }

/* classes */

//enum DotType;

struct Dot;

class DotShift;

template <class R> class DotBreaker;

class FieldPlotBase;

template <class Field> class FieldPlot;

template <class R,class Map> class NextLine;

class PathDots;

class LoopDots;

class HalfPathDots;

class HalfLoopDots;

class DrawArt;

/* enum DotType */

enum DotType
 {
  DotBreak,
  
  DotSimple
 };

const char * GetTextDesc(DotType type);

/* struct Dot */

struct Dot
 {
  MPoint point;
  DotType type = DotSimple ;
  
  Dot() {}
  
  Dot(const MPoint &point_) : point(point_) {}
  
  Dot(const MPoint &point_,DotType type_) : point(point_),type(type_) {}
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };

/* class DotShift */

class DotShift
 {
   MPoint shift;
   
  public:
   
   explicit DotShift(MPoint shift_) : shift(shift_) {}
   
   MPoint operator () (Dot dot) const { return dot.point+shift; }
   
   MPoint operator () (MPoint point) const { return point+shift; }
 };

/* class DotBreaker<R> */

template <class R>
class DotBreaker
 {
   R dots;
   
  public: 
   
   explicit DotBreaker(R dots_) : dots(dots_) {}
   
   R next()
    {
     R r=dots;
     
     if( !r ) return r;
     
     for(++r; +r ;++r)
       if( r->type==DotBreak )
         {
          R ret=PrefixWith(dots,r);
         
          dots=r;
          
          return ret;
         }
     
     return Replace_null(dots);
    }
 };

/* CurvePath() */

template <class R,class Map,class FuncInit>
void CurvePath(R dots,Map map,FuncInit func_init) // map(...) -> MPoint , func(MPoint)
 {
  switch( Algon::BaseRangeAlgo<R>::GetLen(dots) )
    {
     case 0 :
      {
       // do nothing
      }
     break;
     
     case 1 :
      {
       FunctorTypeOf<FuncInit> func(func_init);
       
       func(map(dots[0]));
      }
     break;
     
     case 2 :
      {
       FunctorTypeOf<FuncInit> func(func_init);
       
       func(map(dots[0]));
       func(map(dots[1]));
      }
     break;
     
     case 3 :
      {
       FunctorTypeOf<FuncInit> func(func_init);
       StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
       
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       
       func(a);
       
       driver->spline(a,b,c,c);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift();
       
       PutWithoutFirst(driver->getCurve(),func);
      }
     break;
     
     default:
      {
       FunctorTypeOf<FuncInit> func(func_init);
       StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
       
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       auto d=map(dots[3]);
       
       func(a);
       
       driver->spline(a,b,c,d);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       for(dots+=4; +dots ;++dots)
         {
          driver->shift( map(dots[0]) );
          
          PutWithoutFirst(driver->getCurve(),func);
         }
       
       driver->shift();
       
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift();
       
       PutWithoutFirst(driver->getCurve(),func);
      }
    }
 }

/* CurveLoop() */

template <class R,class Map,class FuncInit>
void CurveLoop(R dots,Map map,FuncInit func_init) // map(...) -> MPoint , func(MPoint)
 {
  switch( Algon::BaseRangeAlgo<R>::GetLen(dots) )
    {
     case 0 :
      {
       // do nothing
      }
     break; 
   
     case 1 :
      {
       FunctorTypeOf<FuncInit> func(func_init);
       
       func( map(dots[0]) );
      }
     break;
     
     case 2 :
      {
       FunctorTypeOf<FuncInit> func(func_init);
       StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
       
       auto a=map(dots[0]);
       auto b=map(dots[1]);
      
       driver->spline(a,b,a,b,a,b);
       
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(a);
      
       PutWithoutFirst(driver->getCurve(),func);
      }
     break;
     
     case 3 :
      {
       FunctorTypeOf<FuncInit> func(func_init);
       StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
       
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
      
       driver->spline(a,b,c,a,b,c);
       
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(a);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(b);
      
       PutWithoutFirst(driver->getCurve(),func);
      }
     break;
     
     case 4 :
      {
       FunctorTypeOf<FuncInit> func(func_init);
       StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
       
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       auto d=map(dots[3]);
      
       driver->spline(a,b,c,d,a,b);
       
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(c);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(d);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(a);
      
       PutWithoutFirst(driver->getCurve(),func);
      }
     break;
     
     case 5 :
      {
       FunctorTypeOf<FuncInit> func(func_init);
       StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
       
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       auto d=map(dots[3]);
       auto e=map(dots[4]);
      
       driver->spline(a,b,c,d,e,a);
       
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(b);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(c);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(d);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(e);
      
       PutWithoutFirst(driver->getCurve(),func);
      }
     break;
     
     default: // >=6
      {
       FunctorTypeOf<FuncInit> func(func_init);
       StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
      
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       auto d=map(dots[3]);
       auto e=map(dots[4]);
       auto f=map(dots[5]);
       
       driver->spline(a,b,c,d,e,f);
       
       PutWithoutFirst(driver->getCurve(),func);
       
       for(dots+=6; +dots ;++dots)
         {
          driver->shift( map(dots[0]) );
         
          PutWithoutFirst(driver->getCurve(),func);
         }

       driver->shift(a);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(b);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(c);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(d);
      
       PutWithoutFirst(driver->getCurve(),func);
       
       driver->shift(e);
      
       PutWithoutFirst(driver->getCurve(),func);
      }
    }
 }

/* CurveExtPath() */

template <class R,class Map,class Func>
void CurveExtPath(R dots,Map map,DrawAlgo::CurveDriver &driver,Func &func)
 {
  switch( Algon::BaseRangeAlgo<R>::GetLen(dots) )
    {
     case 0 :
     case 1 : 
      {
       // do nothing
      }
     break; 
 
     case 2 :
      {
       func( map(dots[1]) );
      }
     break;
     
     case 3 :
      {
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       
       driver.spline(a,b,c,c);
       
       PutWithoutFirst(driver.getCurve(),func); 
       
       driver.shift();
       
       PutWithoutFirst(driver.getCurve(),func); 
      }
     break;
     
     default: // >=4
      {
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       auto d=map(dots[3]);
       
       driver.spline(a,b,c,d);
       
       PutWithoutFirst(driver.getCurve(),func);
       
       for(dots+=4; +dots ;++dots)
         {
          driver.shift( map(dots[0]) );
          
          PutWithoutFirst(driver.getCurve(),func); 
         }
       
       driver.shift();
       
       PutWithoutFirst(driver.getCurve(),func); 
       
       driver.shift();
       
       PutWithoutFirst(driver.getCurve(),func); 
      }
    }
 }

template <class R,class Map,class Func>
void CurveExtPath(R dots,R ext,Map map,DrawAlgo::CurveDriver &driver,Func &func)
 {
  switch( Algon::BaseRangeAlgo<R>::GetLen(dots) )
    {
     case 0 :
      {
       CurveExtPath(ext,map,driver,func);
      }
     break;
     
     case 1 :
      {
       auto a=map(dots[0]);
       
       switch( Algon::BaseRangeAlgo<R>::GetLen(ext) )
         {
          case 0 :
           {
            // do nothing
           }
          break;
          
          case 1 :
           {
            auto b=map(ext[0]);
            
            func(b);
           }
          break;
          
          case 2 :
           {
            auto b=map(ext[0]);
            auto c=map(ext[1]);
            
            driver.spline(a,b,c,c);
            
            PutWithoutFirst(driver.getCurve(),func); 
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
           }
          break;
          
          default: // >=3
           {
            auto b=map(ext[0]);
            auto c=map(ext[1]);
            auto d=map(ext[2]);
            
            driver.spline(a,b,c,d);
            
            PutWithoutFirst(driver.getCurve(),func);
            
            for(ext+=3; +ext ;++ext)
              {
               driver.shift( map(ext[0]) );
               
               PutWithoutFirst(driver.getCurve(),func); 
              }
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
           }
         }
      }
     break;
     
     case 2 :
      {
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       
       switch( Algon::BaseRangeAlgo<R>::GetLen(ext) )
         {
          case 0 :
           {
            func(b);
           }
          break;
          
          case 1 :
           {
            auto c=map(ext[0]);
            
            driver.spline(a,b,c,c);
            
            PutWithoutFirst(driver.getCurve(),func); 
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
           }
          break;
          
          default: // >=2
           {
            auto c=map(ext[0]);
            auto d=map(ext[1]);
            
            driver.spline(a,b,c,d);
            
            PutWithoutFirst(driver.getCurve(),func);
            
            for(ext+=2; +ext ;++ext)
              {
               driver.shift( map(ext[0]) );
               
               PutWithoutFirst(driver.getCurve(),func); 
              }
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
           }
         }
      }
     break;
     
     case 3 :
      {
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       
       switch( Algon::BaseRangeAlgo<R>::GetLen(ext) )
         {
          case 0 :
           {
            driver.spline(a,b,c,c);
            
            PutWithoutFirst(driver.getCurve(),func); 
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
           }
          break;
          
          default: // >=1
           {
            auto d=map(ext[0]);
            
            driver.spline(a,b,c,d);
            
            PutWithoutFirst(driver.getCurve(),func);
            
            for(ext+=1; +ext ;++ext)
              {
               driver.shift( map(ext[0]) );
               
               PutWithoutFirst(driver.getCurve(),func); 
              }
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
            
            driver.shift();
            
            PutWithoutFirst(driver.getCurve(),func); 
           }
         }
      }
     break;
     
     default: // >=4
      {
       auto a=map(dots[0]);
       auto b=map(dots[1]);
       auto c=map(dots[2]);
       auto d=map(dots[3]);
       
       driver.spline(a,b,c,d);
       
       PutWithoutFirst(driver.getCurve(),func);
       
       for(dots+=4; +dots ;++dots)
         {
          driver.shift( map(dots[0]) );
          
          PutWithoutFirst(driver.getCurve(),func); 
         }
       
       for(; +ext ;++ext)
         {
          driver.shift( map(ext[0]) );
          
          PutWithoutFirst(driver.getCurve(),func); 
         }
       
       driver.shift();
       
       PutWithoutFirst(driver.getCurve(),func); 
       
       driver.shift();
       
       PutWithoutFirst(driver.getCurve(),func); 
      }
    }
 }

/* CurvePath() */

template <class R,class Map,class FuncInit>
void CurveBreakPath(R dots,Map map,FuncInit func_init) // Dot , map(...) -> MPoint , func(MPoint)
 {
  if( !dots ) return;
  
  FunctorTypeOf<FuncInit> func(func_init);
  
  func( map(dots[0]) );
  
  StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
  
  for(DotBreaker<R> breaker(dots);;)
    {
     R r=breaker.next();
     
     if( !r ) return;
     
     CurveExtPath(r,map,*driver,func);
    }
 }

/* CurvePath() */

template <class R,class Map,class FuncInit>
void CurvePath(R dots,R ext,Map map,FuncInit func_init) // ext no break , func(MPoint) , put without first point
 {
  FunctorTypeOf<FuncInit> func(func_init);
  StackObject<DrawAlgo::CurveDriver> driver(MaxFineness);
  
  DotBreaker<R> breaker(dots);
  
  R cur=breaker.next();
  
  for(;;)
    {
     R next=breaker.next();
     
     if( !next )
       {
        CurveExtPath(cur,ext,map,*driver,func);
        
        return;
       }
     
     CurveExtPath(cur,map,*driver,func);
     
     cur=next;
    }
 }

/* CurveBreakLoop() */

template <class R,class Map,class FuncInit>
void CurveBreakLoop(R dots,Map map,FuncInit func_init) // Dot , map(...) -> MPoint , func(MPoint)
 {
  if( !dots ) return;
  
  for(R r=dots; +r ;++r)
    {
     if( r->type==DotBreak )
       {
        CurvePath(r,PrefixWith(dots,r),map,func_init);
       
        return;
       }
    }
  
  CurveLoop(dots,map,func_init);
 }

/* class FieldPlotBase */

class FieldPlotBase : DrawBuf
 {
  public:
 
   explicit FieldPlotBase(const DrawBuf &buf) : DrawBuf(buf) {}
   
   using DrawBuf::map;
   using DrawBuf::getSize;
   
   void plot(Point p,ColorName cname)
    {
     pixel(p,cname);
    }
   
   void plot(Point p,ColorName cname,unsigned alpha)
    {
     DesktopColor::BlendTo(Blender(Clr(alpha),cname),place(p));
    }
   
   void plot_safe(Point p,ColorName cname,unsigned alpha)
    {
     if( alpha>=AlphaLim )
       plot(p,cname);
     else if( alpha )
       plot(p,cname,alpha);
    }
   
   void plot(Point p,AlphaColorName aname)
    {
     plot_safe(p,aname.cname,aname.alpha);
    }
   
   void plot(Point p,AlphaColorName aname,unsigned alpha)
    {
     plot_safe(p,aname.cname,(Min(aname.alpha,AlphaLim)*alpha)>>ClrBits);
    }
 };

/* class FieldPlot<Field> */

template <class Field>
class FieldPlot : FieldPlotBase
 {
   Field field;
   
  public: 
   
   FieldPlot(const DrawBuf &buf,const Field &field_) : FieldPlotBase(buf),field(field_) {}
   
   void operator () (MPoint point)
    {
     MPoint p=map(point);
     MPoint biased=p+MPoint(MPoint::Half,MPoint::Half);
     
     if( biased>=Null && biased<getSize() )
       {
        plot(p.toPoint(),field(point));
       }
    }
   
   void operator () (MPoint point,unsigned alpha)
    {
     if( !alpha ) return;
     
     if( alpha>=AlphaLim )
       {
        (*this)(point);
        
        return;
       }
     
     MPoint p=map(point);
     MPoint biased=p+MPoint(MPoint::Half,MPoint::Half);
     
     if( biased>=Null && biased<getSize() )
       {
        plot(p.toPoint(),field(point),alpha);
       }
    }
 };

/* class NextLine<R,Map> */

template <class R,class Map>
class NextLine
 {
   R dots;
   Map map;
   
  public:
   
   MPoint a;
   MPoint b;
   MPoint c;
   
   NextLine(R dots_,Map map_) : dots(dots_),map(map_) {}
   
   bool first()
    {
     if( !dots ) return false;
     
     b=map(*dots);
     
     ++dots;
     
     while( +dots )
       {
        auto d=map(*dots);
        
        ++dots;
        
        if( d!=b )
          {
           c=d;
           
           return true;
          }
       }
     
     return false;
    }
   
   bool next()
    {
     while( +dots )
       {
        auto d=map(*dots); 
        
        ++dots;
        
        if( d!=c )
          {
           a=b;
           b=c;
           c=d;
          
           return true;
          }
       }
     
     return false;
    }
   
   bool next(MPoint d)
    {
     if( d!=c )
       {
        a=b;
        b=c;
        c=d;
       
        return true;
       }
     
     return false;
    }
 };

/* class PathDots */

class PathDots : NoCopy
 {
   Collector<MPoint> buf;
   
  private:
   
   struct AddBuf
    {
     Collector<MPoint> &buf;
     
     explicit AddBuf(Collector<MPoint> &buf_) : buf(buf_) {}
     
     void operator () (MPoint point) { buf.append_copy(point); }
    };
   
   void addRound(MPoint a,MCoord width)
    {
     AddLineRound(a,width,AddBuf(buf));
    }
   
   void addCap(MPoint a,MPoint b,MCoord width)
    {
     AddLineCap(a,b,width,AddBuf(buf));
    }
   
   void addArc(MPoint a,MPoint b,MPoint c,MCoord width)
    {
     AddLineArc(a,b,c,width,AddBuf(buf));
    }
   
   template <class R,class Map>
   bool addDirect(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);
     
     if( line.first() )
       {
        addCap(line.b,line.c,width);
        
        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }
        
        return true;
       }
     else
       {
        addRound(line.b,width);
        
        return false;
       }
    }
   
   template <class R,class Map>
   void addBack(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);
     
     if( line.first() )
       {
        addCap(line.b,line.c,width);
        
        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }
       }
    }
   
  public:
  
   template <class R,class Map>
   PathDots(R dots,Map map,MCoord width) // map(...) -> MPoint
    {
     if( !dots ) return;
     
     width/=2;
     
     if( addDirect(dots,map,width) )
       {
        addBack(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width);
       }
    }
   
   template <class R>
   PathDots(R dots,MCoord width) : PathDots(dots, [] (MPoint point) { return point; } ,width) {} // MPoint
   
   ~PathDots()
    {
    }
   
   PtrLen<const MPoint> complete() { return Range_const(buf.flat()); }
 };

/* class LoopDots */

class LoopDots : NoCopy
 {
   Collector<MPoint> buf;
   
  private:
   
   struct AddBuf
    {
     Collector<MPoint> &buf;
     
     explicit AddBuf(Collector<MPoint> &buf_) : buf(buf_) {}
     
     void operator () (MPoint point) { buf.append_copy(point); }
    };
   
   void addRound(MPoint a,MCoord width)
    {
     AddLineRound(a,width,AddBuf(buf));
    }
   
   void addCap(MPoint a,MPoint b,MCoord width)
    {
     AddLineCap(a,b,width,AddBuf(buf));
    }
   
   void addArc(MPoint a,MPoint b,MPoint c,MCoord width)
    {
     AddLineArc(a,b,c,width,AddBuf(buf));
    }
   
   template <class R,class Map>
   bool addDirect(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);
     
     if( line.first() )
       {
        MPoint o=line.b;
       
        addCap(line.b,line.c,width);
        
        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }
        
        if( line.next(o) )
          {
           addArc(line.a,line.b,line.c,width);
           
           addCap(line.c,line.b,width);
           
           addArc(line.c,line.b,line.a,width);
          }
        else
          {
           addCap(line.c,line.b,width);
          }
        
        return true;
       }
     else
       {
        addRound(line.b,width);
        
        return false;
       }
    }
   
   template <class R,class Map>
   void addBack(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);
     
     if( line.first() )
       {
        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }
       }
    }
   
  public:
  
   template <class R,class Map>
   LoopDots(R dots,Map map,MCoord width) // map(...) -> MPoint
    {
     if( !dots ) return;
     
     width/=2;
     
     if( addDirect(dots,map,width) )
       {
        addBack(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width);
       }
    }
   
   template <class R>
   LoopDots(R dots,MCoord width) : LoopDots(dots, [] (MPoint point) { return point; } ,width) {} // MPoint
   
   ~LoopDots()
    {
    }
   
   PtrLen<const MPoint> complete() { return Range_const(buf.flat()); }
 };

/* class HalfPathDots */

class HalfPathDots
 {
   Collector<MPoint> buf;
   
  private:
   
   struct AddBuf
    {
     Collector<MPoint> &buf;
     
     explicit AddBuf(Collector<MPoint> &buf_) : buf(buf_) {}
     
     void operator () (MPoint point) { buf.append_copy(point); }
    };
   
   void addInCap(MPoint a,MPoint b,MCoord width)
    {
     AddLineInCap(a,b,width,AddBuf(buf));
    }
   
   void addOutCap(MPoint a,MPoint b,MCoord width)
    {
     AddLineOutCap(a,b,width,AddBuf(buf));
    }
   
   void addArc(MPoint a,MPoint b,MPoint c,MCoord width)
    {
     AddLineArc(a,b,c,width,AddBuf(buf));
    }
   
   template <class R,class Map>
   bool addDirect(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);
     
     if( line.first() )
       {
        addInCap(line.b,line.c,width);
        
        while( line.next() ) buf.append_copy(line.b);
        
        return true;
       }
     else
       {
        return false;
       }
    }
   
   template <class R,class Map>
   void addBack(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);
     
     if( line.first() )
       {
        addOutCap(line.b,line.c,width);
        
        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }
       }
    }
   
  public:
  
   template <class R,class Map>
   HalfPathDots(R dots,Map map,HalfFlag half_flag,MCoord width) // map(...) -> MPoint
    {
     if( !dots ) return;
     
     if( half_flag==HalfNeg )
       {
        if( addDirect(dots,map,width) )
          {
           addBack(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width);
          }
       }
     else
       {
        if( addDirect(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width) )
          {
           addBack(dots,map,width);
          }
       }
    }
   
   template <class R>
   HalfPathDots(R dots,HalfFlag half_flag,MCoord width) : HalfPathDots(dots, [] (MPoint point) { return point; } ,half_flag,width) {} // MPoint
   
   ~HalfPathDots()
    {
    }
   
   PtrLen<const MPoint> complete() { return Range_const(buf.flat()); }
 };

/* class HalfLoopDots */

class HalfLoopDots
 {
  Collector<MPoint> buf;
  
  MPoint last_a;
  MPoint last_b;
  MPoint last_c;
  
 private:
  
  struct AddBuf
   {
    Collector<MPoint> &buf;
    
    explicit AddBuf(Collector<MPoint> &buf_) : buf(buf_) {}
    
    void operator () (MPoint point) { buf.append_copy(point); }
   };
  
  void addArc(MPoint a,MPoint b,MPoint c,MCoord width)
   {
    AddLineArc(a,b,c,width,AddBuf(buf));
   }
  
  template <class R,class Map>
  bool addDirect(R dots,Map map,MCoord width)
   {
    NextLine<R,Map> line(dots,map);
    
    if( line.first() )
      {
       MPoint o=line.b;
       MPoint s=line.c;
      
       buf.append_copy(o);
       
       while( line.next() ) buf.append_copy(line.b);
       
       if( line.next(o) )
         {
          buf.append_copy(line.b);
          
          buf.append_copy(line.c);
          
          addArc(s,line.c,line.b,width);
          
          last_a=s;
          last_b=line.c;
          last_c=line.b;
          
          addArc(line.c,line.b,line.a,width);
         }
       else
         {
          buf.append_copy(line.c);
         
          addArc(s,line.c,line.b,width);
         
          last_a=s;
          last_b=line.c;
          last_c=line.b;
         }
       
       return true;
      }
    else
      {
       return false;
      }
   }
  
  template <class R,class Map>
  void addBack(R dots,Map map,MCoord width)
   {
    NextLine<R,Map> line(dots,map);
    
    if( line.first() )
      {
       while( line.next() )
         {
          addArc(line.a,line.b,line.c,width);
         }
       
       addArc(last_a,last_b,last_c,width);
      }
   }
  
 public:
 
  template <class R,class Map>
  HalfLoopDots(R dots,Map map,HalfFlag half_flag,MCoord width) // map(...) -> MPoint
   {
    if( !dots ) return;
    
    if( half_flag==HalfNeg )
      {
       if( addDirect(dots,map,width) )
         {
          addBack(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width);
         }
      }
    else
      {
       if( addDirect(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width) )
         {
          addBack(dots,map,width);
         }
      }
   }
  
  template <class R>
  HalfLoopDots(R dots,HalfFlag half_flag,MCoord width) : HalfLoopDots(dots, [] (MPoint point) { return point; } ,half_flag,width) {} // MPoint
  
  ~HalfLoopDots()
   {
   }
  
  PtrLen<const MPoint> complete() { return Range_const(buf.flat()); }
 };

/* class DrawArt */

class DrawArt
 {
   class WorkBuf : public DrawBuf
    {
     public:
     
      explicit WorkBuf(const DrawBuf &buf) : DrawBuf(buf) {}
      
      void pixel_safe(Point p,DesktopColor color) { if( p>=Null && p<getSize() ) pixel(p,color); }
      
      void block_safe(Pane pane,DesktopColor color) { block(Inf(pane,getPane()),color); }
      
      void block_safe(Pane pane,ColorName cname,Clr alpha) { block(Inf(pane,getPane()),cname,alpha); }
    };
 
   WorkBuf buf;
   
  public:
   
   DrawArt(const DrawBuf &buf_) : buf(buf_) {}
   
   const DrawBuf & getBuf() const { return buf; }
   
   // simple
   
   void pixel(Point p,DesktopColor color);
   
   void erase(DesktopColor color);
  
   void block(Pane pane,DesktopColor color);
   
   void block(Pane pane,ColorName cname,Clr alpha);
   
   // solid
   
   template <class R>
   void solid(R dots,SolidFlag solid_flag,ColorName cname) // MPoint
    {
     solid(dots,solid_flag,ConstantField(cname));
    }
   
   template <class R>
   void curveSolid(R dots,SolidFlag solid_flag,ColorName cname) // MPoint
    {
     curveSolid(dots,solid_flag,ConstantField(cname));
    }
   
   template <class R>
   void curveBreakSolid(R dots,SolidFlag solid_flag,ColorName cname) // Dot
    {
     curveBreakSolid(dots,solid_flag,ConstantField(cname));
    }
   
   template <class R,class Field>
   void solid(R dots,SolidFlag solid_flag,const Field &field) // MPoint
    {
     SolidDriver driver(dots);
     
     driver(solid_flag,FieldPlot<Field>(buf,field));
    }
   
   template <class R,class Field>
   void curveSolid(R dots,SolidFlag solid_flag,const Field &field) // MPoint
    {
     Collector<MPoint> temp;
     
     CurveLoop(dots, [] (MPoint point) { return point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     solid(Range_const(temp.flat()),solid_flag,field);
    }
   
   template <class R,class Field>
   void curveBreakSolid(R dots,SolidFlag solid_flag,const Field &field) // Dot
    {
     Collector<MPoint> temp;
     
     CurveBreakLoop(dots, [] (Dot dot) { return dot.point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     solid(Range_const(temp.flat()),solid_flag,field);
    }

   
   template <class R,class Map>
   void solid(R dots,Map map,SolidFlag solid_flag,ColorName cname) // map(...) -> MPoint
    {
     solid(dots,map,solid_flag,ConstantField(cname));
    }
   
   template <class R,class Map>
   void curveSolid(R dots,Map map,SolidFlag solid_flag,ColorName cname) // map(...) -> MPoint
    {
     curveSolid(dots,map,solid_flag,ConstantField(cname));
    }
   
   template <class R,class Map>
   void curveBreakSolid(R dots,Map map,SolidFlag solid_flag,ColorName cname) // Dot dots, map(...) -> MPoint
    {
     curveBreakSolid(dots,map,solid_flag,ConstantField(cname));
    }
   
   template <class R,class Map,class Field>
   void solid(R dots,Map map,SolidFlag solid_flag,const Field &field) // map(...) -> MPoint
    {
     SolidDriver driver(dots,map);
     
     driver(solid_flag,FieldPlot<Field>(buf,field));
    }
   
   template <class R,class Map,class Field>
   void curveSolid(R dots,Map map,SolidFlag solid_flag,const Field &field) // map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurveLoop(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     solid(Range_const(temp.flat()),solid_flag,field);
    }
   
   template <class R,class Map,class Field>
   void curveBreakSolid(R dots,Map map,SolidFlag solid_flag,const Field &field) // Dot dots, map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurveBreakLoop(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     solid(Range_const(temp.flat()),solid_flag,field);
    }
   
   // line
   
   template <class R>
   void path(R dots,MCoord width,ColorName cname) // MPoint
    {
     path(dots,width,ConstantField(cname));
    }
   
   template <class R>
   void loop(R dots,MCoord width,ColorName cname) // MPoint
    {
     loop(dots,width,ConstantField(cname));
    }
   
   template <class R,class Field>
   void path(R dots,MCoord width,const Field &field) // MPoint
    {
     PathDots path(dots,width);
     
     solid(path.complete(),SolidAll,field);
    }
   
   template <class R,class Field>
   void loop(R dots,MCoord width,const Field &field) // MPoint
    {
     LoopDots loop(dots,width);
     
     solid(loop.complete(),SolidAll,field);
    }
   
   
   template <class R,class Map>
   void path(R dots,Map map,MCoord width,ColorName cname) // map(...) -> MPoint
    {
     path(dots,map,width,ConstantField(cname));
    }
   
   template <class R,class Map>
   void loop(R dots,Map map,MCoord width,ColorName cname) // map(...) -> MPoint
    {
     loop(dots,map,width,ConstantField(cname));
    }
   
   template <class R,class Map,class Field>
   void path(R dots,Map map,MCoord width,const Field &field) // map(...) -> MPoint
    {
     PathDots path(dots,map,width);
     
     solid(path.complete(),SolidAll,field);
    }
   
   template <class R,class Map,class Field>
   void loop(R dots,Map map,MCoord width,const Field &field) // map(...) -> MPoint
    {
     LoopDots loop(dots,map,width);
     
     solid(loop.complete(),SolidAll,field);
    }
   
   // curve

   template <class R>
   void curve(R dots,MCoord width,ColorName cname) // MPoint
    {
     curve(dots,width,ConstantField(cname));
    }
   
   template <class R>
   void curveBreak(R dots,MCoord width,ColorName cname) // Dot
    {
     curveBreak(dots,width,ConstantField(cname));
    }
   
   template <class R>
   void curveLoop(R dots,MCoord width,ColorName cname) // MPoint
    {
     curveLoop(dots,width,ConstantField(cname));
    }
   
   template <class R>
   void curveBreakLoop(R dots,MCoord width,ColorName cname) // Dot
    {
     curveBreakLoop(dots,width,ConstantField(cname));
    }
   
   template <class R,class Field>
   void curve(R dots,MCoord width,const Field &field) // MPoint
    {
     Collector<MPoint> temp;
     
     CurvePath(dots, [] (MPoint point) { return point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     path(Range_const(temp.flat()),width,field);
    }
   
   template <class R,class Field>
   void curveBreak(R dots,MCoord width,const Field &field) // Dot
    {
     Collector<MPoint> temp;
     
     CurveBreakPath(dots, [] (Dot dot) { return dot.point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     path(Range_const(temp.flat()),width,field);
    }
   
   template <class R,class Field>
   void curveLoop(R dots,MCoord width,const Field &field) // MPoint
    {
     Collector<MPoint> temp;
     
     CurveLoop(dots, [] (MPoint point) { return point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     loop(Range_const(temp.flat()),width,field);
    }
   
   template <class R,class Field>
   void curveBreakLoop(R dots,MCoord width,const Field &field) // Dot
    {
     Collector<MPoint> temp;
     
     CurveBreakLoop(dots, [] (Dot dot) { return dot.point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     loop(Range_const(temp.flat()),width,field);
    }
   

   template <class R,class Map>
   void curve(R dots,Map map,MCoord width,ColorName cname) // map(...) -> MPoint
    {
     curve(dots,map,width,ConstantField(cname));
    }
   
   template <class R,class Map>
   void curveBreak(R dots,Map map,MCoord width,ColorName cname) // Dot , map(...) -> MPoint
    {
     curveBreak(dots,map,width,ConstantField(cname));
    }
   
   template <class R,class Map>
   void curveLoop(R dots,Map map,MCoord width,ColorName cname) // map(...) -> MPoint
    {
     curveLoop(dots,map,width,ConstantField(cname));
    }
   
   template <class R,class Map>
   void curveBreakLoop(R dots,Map map,MCoord width,ColorName cname) // Dot , map(...) -> MPoint
    {
     curveBreakLoop(dots,map,width,ConstantField(cname));
    }
   
   template <class R,class Map,class Field>
   void curve(R dots,Map map,MCoord width,const Field &field) // map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurvePath(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     path(Range_const(temp.flat()),width,field);
    }
   
   template <class R,class Map,class Field>
   void curveBreak(R dots,Map map,MCoord width,const Field &field) // Dot , map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurveBreakPath(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     path(Range_const(temp.flat()),width,field);
    }
   
   template <class R,class Map,class Field>
   void curveLoop(R dots,Map map,MCoord width,const Field &field) // map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurveLoop(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     loop(Range_const(temp.flat()),width,field);
    }
   
   template <class R,class Map,class Field>
   void curveBreakLoop(R dots,Map map,MCoord width,const Field &field) // Dot , map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurveBreakLoop(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     loop(Range_const(temp.flat()),width,field);
    }

   // half line
   
   template <class R>
   void path(R dots,HalfFlag half_flag,MCoord width,ColorName cname) // MPoint
    {
     path(dots,half_flag,width,ConstantField(cname));
    }
   
   template <class R>
   void loop(R dots,HalfFlag half_flag,MCoord width,ColorName cname) // MPoint
    {
     loop(dots,half_flag,width,ConstantField(cname));
    }
   
   template <class R,class Field>
   void path(R dots,HalfFlag half_flag,MCoord width,const Field &field) // MPoint
    {
     HalfPathDots path(dots,half_flag,width);
     
     solid(path.complete(),SolidAll,field);
    }
   
   template <class R,class Field>
   void loop(R dots,HalfFlag half_flag,MCoord width,const Field &field) // MPoint
    {
     HalfLoopDots loop(dots,half_flag,width);
     
     solid(loop.complete(),SolidAll,field);
    }
   
   
   template <class R,class Map>
   void path(R dots,Map map,HalfFlag half_flag,MCoord width,ColorName cname) // map(...) -> MPoint
    {
     path(dots,map,half_flag,width,ConstantField(cname));
    }
   
   template <class R,class Map>
   void loop(R dots,Map map,HalfFlag half_flag,MCoord width,ColorName cname) // map(...) -> MPoint
    {
     loop(dots,map,half_flag,width,ConstantField(cname));
    }
   
   template <class R,class Map,class Field>
   void path(R dots,Map map,HalfFlag half_flag,MCoord width,const Field &field) // map(...) -> MPoint
    {
     HalfPathDots path(dots,map,half_flag,width);
     
     solid(path.complete(),SolidAll,field);
    }
   
   template <class R,class Map,class Field>
   void loop(R dots,Map map,HalfFlag half_flag,MCoord width,const Field &field) // map(...) -> MPoint
    {
     HalfLoopDots loop(dots,map,half_flag,width);
     
     solid(loop.complete(),SolidAll,field);
    }
   
   // half curve

   template <class R>
   void curve(R dots,HalfFlag half_flag,MCoord width,ColorName cname) // MPoint
    {
     curve(dots,half_flag,width,ConstantField(cname));
    }
   
   template <class R>
   void curveBreak(R dots,HalfFlag half_flag,MCoord width,ColorName cname) // Dot
    {
     curveBreak(dots,half_flag,width,ConstantField(cname));
    }
   
   template <class R>
   void curveLoop(R dots,HalfFlag half_flag,MCoord width,ColorName cname) // MPoint
    {
     curveLoop(dots,half_flag,width,ConstantField(cname));
    }
   
   template <class R>
   void curveBreakLoop(R dots,HalfFlag half_flag,MCoord width,ColorName cname) // Dot
    {
     curveBreakLoop(dots,half_flag,width,ConstantField(cname));
    }
   
   template <class R,class Field>
   void curve(R dots,HalfFlag half_flag,MCoord width,const Field &field) // MPoint
    {
     Collector<MPoint> temp;
     
     CurvePath(dots, [] (MPoint point) { return point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     path(Range_const(temp.flat()),half_flag,width,field);
    }
   
   template <class R,class Field>
   void curveBreak(R dots,HalfFlag half_flag,MCoord width,const Field &field) // Dot
    {
     Collector<MPoint> temp;
     
     CurveBreakPath(dots, [] (Dot dot) { return dot.point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     path(Range_const(temp.flat()),half_flag,width,field);
    }
   
   template <class R,class Field>
   void curveLoop(R dots,HalfFlag half_flag,MCoord width,const Field &field) // MPoint
    {
     Collector<MPoint> temp;
     
     CurveLoop(dots, [] (MPoint point) { return point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     loop(Range_const(temp.flat()),half_flag,width,field);
    }
   
   template <class R,class Field>
   void curveBreakLoop(R dots,HalfFlag half_flag,MCoord width,const Field &field) // Dot
    {
     Collector<MPoint> temp;
     
     CurveBreakLoop(dots, [] (Dot dot) { return dot.point; } , [&temp] (MPoint point) { temp.append_copy(point); } );
     
     loop(Range_const(temp.flat()),half_flag,width,field);
    }
   

   template <class R,class Map>
   void curve(R dots,Map map,HalfFlag half_flag,MCoord width,ColorName cname) // map(...) -> MPoint
    {
     curve(dots,map,half_flag,width,ConstantField(cname));
    }
   
   template <class R,class Map>
   void curveBreak(R dots,Map map,HalfFlag half_flag,MCoord width,ColorName cname) // Dot , map(...) -> MPoint
    {
     curveBreak(dots,map,half_flag,width,ConstantField(cname));
    }
   
   template <class R,class Map>
   void curveLoop(R dots,Map map,HalfFlag half_flag,MCoord width,ColorName cname) // map(...) -> MPoint
    {
     curveLoop(dots,map,half_flag,width,ConstantField(cname));
    }
   
   template <class R,class Map>
   void curveBreakLoop(R dots,Map map,HalfFlag half_flag,MCoord width,ColorName cname) // Dot , map(...) -> MPoint
    {
     curveBreakLoop(dots,map,half_flag,width,ConstantField(cname));
    }
   
   template <class R,class Map,class Field>
   void curve(R dots,Map map,HalfFlag half_flag,MCoord width,const Field &field) // map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurvePath(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     path(Range_const(temp.flat()),half_flag,width,field);
    }
   
   template <class R,class Map,class Field>
   void curveBreak(R dots,Map map,HalfFlag half_flag,MCoord width,const Field &field) // Dot , map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurveBreakPath(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     path(Range_const(temp.flat()),half_flag,width,field);
    }
   
   template <class R,class Map,class Field>
   void curveLoop(R dots,Map map,HalfFlag half_flag,MCoord width,const Field &field) // map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurveLoop(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     loop(Range_const(temp.flat()),half_flag,width,field);
    }
   
   template <class R,class Map,class Field>
   void curveBreakLoop(R dots,Map map,HalfFlag half_flag,MCoord width,const Field &field) // Dot , map(...) -> MPoint
    {
     Collector<MPoint> temp;
     
     CurveBreakLoop(dots,map, [&temp] (MPoint point) { temp.append_copy(point); } );
     
     loop(Range_const(temp.flat()),half_flag,width,field);
    }

   // special
   
   void knob(MPoint p,MCoord len,ColorName cname);
   
   void ball(MPoint center,MCoord radius,ColorName cname);
   
   void circle(MPoint center,MCoord radius,MCoord width,ColorName cname);

   template <class Field>
   void knob(MPoint p,MCoord len,const Field &field)
    {
     MPoint temp[]=
      {
       p+MPoint(-len,-len),
       p+MPoint(len,-len),
       p+MPoint(len,len),
       p+MPoint(-len,len)
      };
     
     solid(Range_const(temp),SolidAll,field);
    }
   
   template <class Field>
   void ball(MPoint center,MCoord radius,const Field &field)
    {
     LineRound obj(center,radius);
     
     curveSolid(obj.get(),SolidAll,field);
    }
   
   template <class Field>
   void circle(MPoint center,MCoord radius,MCoord width,const Field &field)
    {
     LineRound obj(center,radius);
     
     curveLoop(obj.get(),width,field);
    }
 
   void pathOf(PtrLen<const MPoint> dots,MCoord width,ColorName cname);
   
   void loopOf(PtrLen<const MPoint> dots,MCoord width,ColorName cname);
   
   template <class ... TT>
   void pathOf(MCoord width,ColorName cname,TT ... tt)
    {
     MPoint temp[sizeof ... (TT)]={ tt... };
     
     pathOf(Range_const(temp),width,cname);
    }
   
   template <class ... TT>
   void loopOf(MCoord width,ColorName cname,TT ... tt)
    {
     MPoint temp[sizeof ... (TT)]={ tt... };
     
     loopOf(Range_const(temp),width,cname);
    }
   
   void pathOf(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,ColorName cname);
   
   void loopOf(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,ColorName cname);
   
   template <class ... TT>
   void pathOf(HalfFlag half_flag,MCoord width,ColorName cname,TT ... tt)
    {
     MPoint temp[sizeof ... (TT)]={ tt... };
     
     pathOf(Range_const(temp),half_flag,width,cname);
    }
   
   template <class ... TT>
   void loopOf(HalfFlag half_flag,MCoord width,ColorName cname,TT ... tt)
    {
     MPoint temp[sizeof ... (TT)]={ tt... };
     
     loopOf(Range_const(temp),half_flag,width,cname);
    }
 };
  
} // namespace Smooth
} // namespace Video
} // namespace CCore
 
#endif
 

