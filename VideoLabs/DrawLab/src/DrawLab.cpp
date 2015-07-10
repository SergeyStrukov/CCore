/* DrawLab.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: DrawLab 1.00
//
//  Tag: private
//
//  License: proprietary software, don't distribute!
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/DrawLab.h>

#include <CCore/inc/algon/SimpleRotate.h>

namespace App {

/* functions */

template <class A>
void DelElement(A &a,ulen index)
 {
  Algon::RangeRotateLeft(Range(a).part(index));
  
  a.shrink_one();
 }

/* class DrawLab */

Ratio DrawLab::Zoom(Coord delta)
 {
  if( delta>0 )
    {
     return Ratio(17,4).pow(delta); 
    }
  else
    {
     return Ratio(15,4).pow(-delta);
    }
 }

MCoord DrawLab::toMilli(Coord x) const
 {
  return MCoord( IntLShift<MCoord>(x,MPoint::Precision-cfg.zoom_deg)-MPoint::Half );
 }

Coord DrawLab::fromMilli(MCoord x) const
 {
  return From32To16( IntRShift<MCoord>(x+MPoint::Half,MPoint::Precision-cfg.zoom_deg) );
 }

MPoint DrawLab::toMilli(Point point) const
 {
  return MPoint(toMilli(point.x),toMilli(point.y));
 }

Point DrawLab::fromMilli(MPoint point) const
 {
  return Point(fromMilli(point.x),fromMilli(point.y));
 }

MPoint DrawLab::map(Point point) const
 {
  return point-normal.getBase();
 }

MPoint DrawLab::mapZoom(Point point) const
 {
  return toMilli(point-zoom.getBase())+part.getBase();
 }

 // react 

void DrawLab::ins(MPoint point)
 {
  if( dots.getLen() ) 
    {
     dots.append_fill(point,dot_type);
    
     pick_ind++;
    
     Algon::RangeRotateRight(Range(dots).part(pick_ind));
    } 
  else 
    { 
     dots.reserve(100);

     dots.append_fill(point,dot_type);
    }
  
  noNear();
  
  redraw();
 }

void DrawLab::move(MPoint point)
 {
  if( pick_ind<dots.getLen() )
    {
     dots[pick_ind].point=point;
     
     redraw();
    }
 }

void DrawLab::zoom_based(MPoint base,Coord delta)
 {
  if( !delta ) return;
 
  Pane clip=Pane(Null,normal.getSize());
  
  ulen len=dots.getLen();
  
  Ratio zoom=Zoom(delta);

  DynArray<Smooth::Dot> new_dots(len);
   
  for(ulen i=0; i<len ;i++) 
    {
     Smooth::Dot dot=dots[i];
     
     dot.point=Zoom(dot.point,base,zoom);
     
     if( !clip.contains(dot.point.toPoint()) ) return;
    
     new_dots[i]=dot;
    }
     
  Swap(dots,new_dots);
   
  redraw();
 }

void DrawLab::setType(Smooth::DotType dot_type)
 {
  if( pick_ind<dots.getLen() )
    {
     dots[pick_ind].type=dot_type;
     
     redraw();
    }
 }

void DrawLab::insDot(Point point)
 {
  ins(map(point));
 }

void DrawLab::insZoomDot(Point point)
 {
  ins(mapZoom(point));
 }

void DrawLab::delDot()
 {
  if( dots.getLen() )
    {
     DelElement(dots,pick_ind);
     
     if( pick_ind>=dots.getLen() )
       {
        if( pick_ind ) pick_ind--;
       }
     
     noNear();
     
     redraw();
    }
 }

void DrawLab::moveDot(Point point)
 {
  move(map(point));
 }

void DrawLab::moveZoomDot(Point point)
 {
  move(mapZoom(point));
 }

void DrawLab::zoomDots(Point point,Coord delta)
 {
  zoom_based(map(point),delta);
 }

void DrawLab::zoomZoomDots(Point point,Coord delta)
 {
  zoom_based(mapZoom(point),delta);
 }

void DrawLab::setNear_based(Point point)
 {
  ulen best_ind=dots.getLen();
  uCoord best=UIntMax();
  
  for(ulen ind=0,len=dots.getLen(); ind<len ;ind++)
    {
     uCoord d=Distance(dots[ind].point.toPoint(),point);
     
     if( d<best )
       {
        best_ind=ind;
        best=d;
       }
    }
  
  if( best_ind!=near_ind )
    {
     near_ind=best_ind;
     
     redraw();
    }
 }

void DrawLab::setNear(Point point)
 {
  setNear_based( point-normal.getBase() );
 }

void DrawLab::setZoomNear(Point point)
 {
  setNear_based( (point-zoom.getBase())/cfg.zoom_mul+part.getBase() );
 }

void DrawLab::setPickInd(ulen ind)
 {
  if( pick_ind!=ind && ind<dots.getLen() )
    {
     pick_ind=ind;
     
     redraw();
    }
 }

bool DrawLab::noNear()
 {
  ulen ind=dots.getLen();
  
  if( near_ind!=ind )
    {
     near_ind=ind;
     
     return true;
    }
  
  return false;
 }

void DrawLab::setWidth(MCoord width)
 {
  line_width=Cap<MCoord>(1024/16,width,16*1024);
 
  redraw();
 }

void DrawLab::incWidth()
 {
  setWidth(line_width+1024/16);
 }

void DrawLab::decWidth()
 {
  setWidth(line_width-1024/16);
 }

 // layout

void DrawLab::setEmpty()
 {
  control=Empty;
  zoom=Empty;
  normal=Empty;
  part=Empty;
  
  select_Path=Empty;
  select_Loop=Empty;
  select_Curve=Empty;
  select_CurveLoop=Empty;
  
  select_SolidOdd=Empty;
  select_SolidAll=Empty;
  select_CurveSolidOdd=Empty;
  select_CurveSolidAll=Empty;
  
  select_LinePath=Empty;
  select_LineLoop=Empty;
  select_LineCurve=Empty;
  select_LineCurveLoop=Empty;
 }

 // draw

void DrawLab::drawMark(Smooth::DrawArt &art,Point point,Smooth::DotType dot_type) const
 {
  switch( dot_type )
    {
     case Smooth::DotSimple :
      {
       art.ball(point,Fraction(cfg.simple_len),cfg.mark);
      }
     break;
     
     case Smooth::DotBreak :
      {
       art.knob(point,Fraction(cfg.break_len),cfg.mark);
      }
     break;
    }
 }

void DrawLab::drawPickMark(Smooth::DrawArt &art,Point point) const
 {
  art.ballField(point,Fraction(cfg.pick_len),ConstantAlphaField(cfg.pick,MedClr));
 }

void DrawLab::drawNearMark(Smooth::DrawArt &art,Point point) const
 {
  art.circle(point,Fraction(cfg.near_len),cfg.width,cfg.near);
 }

template <class Map>
void DrawLab::drawPath(Smooth::DrawArt art,Map map,bool do_loop) const
 {
  if( pick_ind<dots.getLen() )
    {
     drawPickMark(art,map(dots[pick_ind]));
    }
  
  auto r=Range(dots);
  
  if( +r )
    {
     Point a=map(*r);
     Point o=a;
     
     for(++r; +r ;++r)
       {
        Point b=map(*r);
        
        art.pathOf(cfg.width,cfg.path,a,b);
        
        a=b;
       }
     
     if( do_loop )
       {
        art.pathOf(cfg.width,cfg.path,a,o);
       }
    }
  
  for(Smooth::Dot dot : dots )
    {
     drawMark(art,map(dot),dot.type);
    }
  
  if( near_ind<dots.getLen() )
    {
     drawNearMark(art,map(dots[near_ind]));
    }
 }

void DrawLab::drawMarks(DrawBuf buf) const
 {
  if( show_marks )
    {
     Smooth::DrawArt art(buf);
     
     for(Smooth::Dot dot : dots )
       {
        drawMark(art,dot.point.toPoint(),dot.type);
       }
    }
 }

void DrawLab::drawNormal(DrawBuf buf) const
 {
  switch( draw_type )
    {
     case DrawPath :
      {
       drawPath(buf, [] (Smooth::Dot dot) { return dot.point.toPoint(); } ,false);
      }
     break;
     
     case DrawLoop :
      {
       drawPath(buf, [] (Smooth::Dot dot) { return dot.point.toPoint(); } ,true);
      }
     break;
     
     case DrawCurve :
      {
       Smooth::DrawArt art(buf);
       
       art.curveBreak(Range(dots),cfg.width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawCurveLoop :
      {
       Smooth::DrawArt art(buf);
       
       art.curveBreakLoop(Range(dots),cfg.width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawSolidOdd :
      {
       Smooth::DrawArt art(buf);
       
       art.solid(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,SolidOdd,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawSolidAll :
      {
       Smooth::DrawArt art(buf);
       
       art.solid(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,SolidAll,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawCurveSolidOdd :
      {
       Smooth::DrawArt art(buf);
       
       art.curveBreakSolid(Range_const(dots),SolidOdd,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawCurveSolidAll :
      {
       Smooth::DrawArt art(buf);
       
       art.curveBreakSolid(Range_const(dots),SolidAll,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawLinePath :
      {
       Smooth::DrawArt art(buf);
       
       art.path(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,line_width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawLineLoop :
      {
       Smooth::DrawArt art(buf);
       
       art.loop(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,line_width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawLineCurve :
      {
       Smooth::DrawArt art(buf);
       
       art.curveBreak(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,line_width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawLineCurveLoop :
      {
       Smooth::DrawArt art(buf);
       
       art.curveBreakLoop(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,line_width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawHalfLinePath :
      {
       Smooth::DrawArt art(buf);
       
       art.path(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,half_flag,line_width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawHalfLineLoop :
      {
       Smooth::DrawArt art(buf);
       
       art.loop(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,half_flag,line_width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawHalfLineCurve :
      {
       Smooth::DrawArt art(buf);
       
       art.curveBreak(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,half_flag,line_width,cfg.path);
       
       drawMarks(buf);
      }
     break;
     
     case DrawHalfLineCurveLoop :
      {
       Smooth::DrawArt art(buf);
       
       art.curveBreakLoop(Range_const(dots), [] (Smooth::Dot dot) { return dot.point; } ,half_flag,line_width,cfg.path);
       
       drawMarks(buf);
      }
     break; 
    }
 }

class DrawLab::ZoomMap
 {
   unsigned deg;
   
  private: 
   
   Coord map(MCoord x) const
    {
     return Coord( (x+MPoint::Half)>>(MPoint::Precision-deg) );
    }
   
  public:
   
   explicit ZoomMap(unsigned deg_) : deg(deg_) {}
   
   Point operator () (MPoint point) const
    {
     return Point(map(point.x),map(point.y));
    }
 };

class DrawLab::ZoomPath
 {
   Smooth::DrawArt art;
   ZoomMap map;
   MCoord width;
   VColor cname;
  
   Point prev;
   bool first = true ;
  
  public:
  
   ZoomPath(const DrawBuf &buf,unsigned deg,MCoord width_,VColor cname_) : art(buf),map(deg),width(width_),cname(cname_) {}
   
   void operator () (MPoint point)
    {
     Point p=map(point);
     
     if( first )
       {
        first=false;
       }
     else
       {
        art.pathOf(width,cname,prev,p);
       }
     
     prev=p;
    }
 };

class DrawLab::ZoomLoop
 {
   const DrawBuf &buf;
   ZoomMap map;
   MCoord width;
   VColor cname;
   
  public:
  
   ZoomLoop(const DrawBuf &buf_,unsigned deg,MCoord width_,VColor cname_) : buf(buf_),map(deg),width(width_),cname(cname_) {}
   
   class FunctorType : NoCopy
    {
      Smooth::DrawArt art;
      ZoomMap map;
      MCoord width;
      VColor cname;

      Point start;
      Point prev;
      bool first = true ;
     
     public: 
      
      explicit FunctorType(ZoomLoop init) : art(init.buf),map(init.map),width(init.width),cname(init.cname) {}
      
      ~FunctorType()
       {
        if( !first )
          {
           art.pathOf(width,cname,prev,start);
          }
       }
      
      void operator () (MPoint point)
       {
        Point p=map(point);
        
        if( first )
          {
           start=p;
           first=false;
          }
        else
          {
           art.pathOf(width,cname,prev,p);
          }
        
        prev=p;
       }
    };
 };

class DrawLab::ZoomDot
 {
   Smooth::DrawArt art;
   ZoomMap map;
   Coord len;
   VColor cname;
   
  public:
   
   ZoomDot(const DrawBuf &buf,unsigned deg,Coord len_,VColor cname_) : art(buf),map(deg),len(len_),cname(cname_) {}
   
   void operator () (MPoint point)
    {
     Point p=map(point);
     
     art.knob(p,Fraction(len),cname);
    } 
 };

template <class R,class Map,class FuncInit>
void DrawLab::Apply(R r,Map map,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);
  
  for(; +r ;++r) func(map(*r));
 }

void DrawLab::drawZoom(DrawBuf buf) const
 {
  Smooth::DrawArt art(buf);
  
  // grid
  {
   for(Coord x=0,i=0; x<zoom.dx ;x+=cfg.zoom_mul,i++) art.pathOf(cfg.grid_width,(i%16)?cfg.grid:cfg.grid2,Point(x,0),Point(x,zoom.dy-1));
   
   for(Coord y=0,i=0; y<zoom.dy ;y+=cfg.zoom_mul,i++) art.pathOf(cfg.grid_width,(i%16)?cfg.grid:cfg.grid2,Point(0,y),Point(zoom.dx-1,y));
  }
  
  switch( draw_type )
    {
     case DrawPath :
      {
       drawPath(art, [this] (Smooth::Dot dot) { return fromMilli(dot.point-part.getBase()); } ,false);
      }
     break;
     
     case DrawLoop :
     case DrawSolidOdd :
     case DrawSolidAll :
      {
       drawPath(art, [this] (Smooth::Dot dot) { return fromMilli(dot.point-part.getBase()); } ,true);
      }
     break;
     
     case DrawCurve :
      {
       Point base=part.getBase();
       
       Smooth::CurveBreakPath(Range(dots), [base] (Smooth::Dot dot) { return dot.point-base; } ,ZoomPath(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Smooth::CurveBreakPath(Range(dots), [base] (Smooth::Dot dot) { return dot.point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break;
     
     case DrawCurveLoop :
     case DrawCurveSolidOdd :
     case DrawCurveSolidAll :
      {
       Point base=part.getBase();
       
       Smooth::CurveBreakLoop(Range(dots), [base] (Smooth::Dot dot) { return dot.point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Smooth::CurveBreakLoop(Range(dots), [base] (Smooth::Dot dot) { return dot.point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break;
     
     case DrawLinePath : 
      {
       Smooth::PathDots path(Range(dots), [] (Smooth::Dot dot) { return dot.point; } ,line_width);
       
       auto r=path.complete();

       Point base=part.getBase();
       
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break;
     
     case DrawLineLoop :
      {
       Smooth::LoopDots loop(Range(dots), [] (Smooth::Dot dot) { return dot.point; } ,line_width);
       
       auto r=loop.complete();

       Point base=part.getBase();
       
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break;
     
     case DrawLineCurve :
      {
       Collector<MPoint> temp;
       
       Smooth::CurveBreakPath(Range(dots), [] (Smooth::Dot dot) { return dot.point; }, [&temp] (MPoint point) { temp.append_copy(point); } );
       
       Smooth::PathDots path(Range_const(temp.flat()), [] (MPoint point) { return point; } ,line_width);
       
       auto r=path.complete();

       Point base=part.getBase();
       
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break;
     
     case DrawLineCurveLoop :
      {
       Collector<MPoint> temp;
       
       Smooth::CurveBreakLoop(Range(dots), [] (Smooth::Dot dot) { return dot.point; }, [&temp] (MPoint point) { temp.append_copy(point); } );
       
       Smooth::LoopDots loop(Range_const(temp.flat()), [] (MPoint point) { return point; } ,line_width);
       
       auto r=loop.complete();

       Point base=part.getBase();
       
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break; 
     
     case DrawHalfLinePath :
      {
       Smooth::HalfPathDots path(Range(dots), [] (Smooth::Dot dot) { return dot.point; } ,half_flag,line_width);
       
       auto r=path.complete();

       Point base=part.getBase();
       
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break;
     
     case DrawHalfLineLoop :
      {
       Smooth::HalfLoopDots loop(Range(dots), [] (Smooth::Dot dot) { return dot.point; } ,half_flag,line_width);
       
       auto r=loop.complete();

       Point base=part.getBase();
       
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break;
     
     case DrawHalfLineCurve :
      {
       Collector<MPoint> temp;
       
       Smooth::CurveBreakPath(Range(dots), [] (Smooth::Dot dot) { return dot.point; }, [&temp] (MPoint point) { temp.append_copy(point); } );
       
       Smooth::HalfPathDots path(Range_const(temp.flat()), [] (MPoint point) { return point; } ,half_flag,line_width);
       
       auto r=path.complete();

       Point base=part.getBase();
       
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break;
     
     case DrawHalfLineCurveLoop :
      {
       Collector<MPoint> temp;
       
       Smooth::CurveBreakLoop(Range(dots), [] (Smooth::Dot dot) { return dot.point; }, [&temp] (MPoint point) { temp.append_copy(point); } );
       
       Smooth::HalfLoopDots loop(Range_const(temp.flat()), [] (MPoint point) { return point; } ,half_flag,line_width);
       
       auto r=loop.complete();

       Point base=part.getBase();
       
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomLoop(buf,cfg.zoom_deg,cfg.width,cfg.path));
       Apply(r, [base] (MPoint point) { return point-base; } ,ZoomDot(buf,cfg.zoom_deg,cfg.dot_len,cfg.mark));
      }
     break; 
    }
 }

DrawLab::DrawLab(SubWindowHost &host)
 : SubWindow(host) 
 {
 }
  
DrawLab::~DrawLab()
 {
 }
   
 // drawing
   
void DrawLab::layout()
 {
  Pane total=Pane(Null,getSize());
  
  FontSize font_size=cfg.font->getSize();
  
  // areas
  
  Coord info_dy=2*cfg.textspace_dxy+font_size.dy;
  
  Coord delta=2*cfg.space_dxy+info_dy;
  
  if( delta>total.dy ) 
    {
     info=Empty;
     
     return setEmpty();
    }
  
  info=SplitY(delta,total).shrink(cfg.space_dxy);
  
  if( total.dy<cfg.space_dxy ) return setEmpty();
  
  total.dy-=cfg.space_dxy;
  
  if( total.dx<4*cfg.space_dxy+cfg.control_dx ) return setEmpty();
  
  SplitX(cfg.space_dxy,total);
  
  control=SplitX(cfg.control_dx,total);
  
  SplitX(cfg.space_dxy,total);
  
  Coord zoom_dx=total.dx/2-cfg.space_dxy;
  
  zoom=SplitX(zoom_dx,total);
  
  SplitX(cfg.space_dxy,total);
  
  normal=SplitX(zoom_dx,total);
  
  part.dx=zoom.dx/cfg.zoom_mul;
  part.dy=zoom.dy/cfg.zoom_mul;
  
  Replace_min<Coord>(part.x,normal.dx-part.dx);
  Replace_min<Coord>(part.y,normal.dy-part.dy);
  
  // select
  
  Pane temp=control;
  
  select_Path=TrySplitY(info_dy,temp);
  select_Loop=TrySplitY(info_dy,temp);
  select_Curve=TrySplitY(info_dy,temp);
  select_CurveLoop=TrySplitY(info_dy,temp);
  
  TrySplitY(info_dy/2,temp);
  
  select_SolidOdd=TrySplitY(info_dy,temp);
  select_SolidAll=TrySplitY(info_dy,temp);
  select_CurveSolidOdd=TrySplitY(info_dy,temp);
  select_CurveSolidAll=TrySplitY(info_dy,temp);
  
  TrySplitY(info_dy/2,temp);
  
  select_LinePath=TrySplitY(info_dy,temp);
  select_LineLoop=TrySplitY(info_dy,temp);
  select_LineCurve=TrySplitY(info_dy,temp);
  select_LineCurveLoop=TrySplitY(info_dy,temp);
  
  TrySplitY(info_dy/2,temp);
  
  select_HalfLinePath=TrySplitY(info_dy,temp);
  select_HalfLineLoop=TrySplitY(info_dy,temp);
  select_HalfLineCurve=TrySplitY(info_dy,temp);
  select_HalfLineCurveLoop=TrySplitY(info_dy,temp);
  
  TrySplitY(info_dy/2,temp);
  
  width=TrySplitY(info_dy,temp);
  
  width_value=width;
  
  width_plus=TrySplitX(info_dy,width_value);
  width_minus=TrySplitX(width_value,info_dy);
  
  width_plus=width_plus.shrink(cfg.textspace_dxy/2);
  width_value=width_value.shrink(cfg.textspace_dxy/2);
  width_minus=width_minus.shrink(cfg.textspace_dxy/2);
 }
   
void DrawLab::draw(DrawBuf buf,bool) const
 {
  Smooth::DrawArt art(buf);
  
  // areas
  {
   art.erase(cfg.back);
   
   art.block(info,cfg.work);
   art.block(control,cfg.work);
   art.block(zoom,cfg.work);
   art.block(normal,cfg.work);
   
   art.block(Inner(normal,part),cfg.part);
  }
  
  // control
  {
   Pane pane;
   
   switch( draw_type )
     {
      case DrawPath          : pane=select_Path; break;
      case DrawLoop          : pane=select_Loop; break;
      case DrawCurve         : pane=select_Curve; break;
      case DrawCurveLoop     : pane=select_CurveLoop; break;
      
      case DrawSolidOdd      : pane=select_SolidOdd; break;
      case DrawSolidAll      : pane=select_SolidAll; break;
      case DrawCurveSolidOdd : pane=select_CurveSolidOdd; break;
      case DrawCurveSolidAll : pane=select_CurveSolidAll; break;
      
      case DrawLinePath      : pane=select_LinePath; break;
      case DrawLineLoop      : pane=select_LineLoop; break;
      case DrawLineCurve     : pane=select_LineCurve; break;
      case DrawLineCurveLoop : pane=select_LineCurveLoop; break;
      
      case DrawHalfLinePath      : pane=select_HalfLinePath; break;
      case DrawHalfLineLoop      : pane=select_HalfLineLoop; break;
      case DrawHalfLineCurve     : pane=select_HalfLineCurve; break;
      case DrawHalfLineCurveLoop : pane=select_HalfLineCurveLoop; break;
     }
   
   art.block(pane,cfg.select);
   
   cfg.font->text(buf,select_Path.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Path",cfg.menu);
   cfg.font->text(buf,select_Loop.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Loop",cfg.menu);
   cfg.font->text(buf,select_Curve.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Curve",cfg.menu);
   cfg.font->text(buf,select_CurveLoop.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"CurveLoop",cfg.menu);
   
   cfg.font->text(buf,select_SolidOdd.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Solid Odd",cfg.menu);
   cfg.font->text(buf,select_SolidAll.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Solid All",cfg.menu);
   cfg.font->text(buf,select_CurveSolidOdd.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"CurveSolid Odd",cfg.menu);
   cfg.font->text(buf,select_CurveSolidAll.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"CurveSolid All",cfg.menu);
   
   cfg.font->text(buf,select_LinePath.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Line Path",cfg.menu);
   cfg.font->text(buf,select_LineLoop.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Line Loop",cfg.menu);
   cfg.font->text(buf,select_LineCurve.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Line Curve",cfg.menu);
   cfg.font->text(buf,select_LineCurveLoop.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Line CurveLoop",cfg.menu);
   
   cfg.font->text(buf,select_HalfLinePath.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Half Line Path",cfg.menu);
   cfg.font->text(buf,select_HalfLineLoop.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Half Line Loop",cfg.menu);
   cfg.font->text(buf,select_HalfLineCurve.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Half Line Curve",cfg.menu);
   cfg.font->text(buf,select_HalfLineCurveLoop.shrink(cfg.textspace_dxy,cfg.textspace_dxy),TextPlace(AlignX_Left,AlignY_Center),"Half Line CurveLoop",cfg.menu);
   
   art.block(width,cfg.width1);
   
   art.block(width_plus,cfg.width2);
   art.block(width_value,cfg.width2);
   art.block(width_minus,cfg.width2);
   
   cfg.font->text(buf,width_plus,TextPlace(AlignX_Center,AlignY_Center),"+",cfg.menu);
   cfg.font->text(buf,width_minus,TextPlace(AlignX_Center,AlignY_Center),"-",cfg.menu);

   char temp[TextBufLen];
   PrintBuf out(Range(temp));
   
   Printf(out,"#; #;/16",line_width/1024,(line_width%1024)>>6);
   
   cfg.font->text(buf,width_value,TextPlace(AlignX_Center,AlignY_Center),out.close(),cfg.menu);
  }
  
  // info
  {
   Pane pane=info.shrink(cfg.textspace_dxy,cfg.textspace_dxy);
   
   char temp[TextBufLen];
   PrintBuf out(Range(temp));
   
   Printf(out,"#;",part);
   
   if( do_ins ) Printf(out," Insert #;",dot_type);
   
   cfg.font->text(buf,pane,TextPlace(AlignX_Left,AlignY_Center),out.close(),cfg.text);
  }  

  drawNormal(buf.cutRebase(normal));
  
  drawZoom(buf.cutRebase(zoom));
 }
   
 // base
   
void DrawLab::open()
 {
  move_normal=false;
  move_zoom=false;
 }
   
 // mouse
 
void DrawLab::looseCapture()
 {
  move_normal=false;
  move_zoom=false;
 }
 
MouseShape DrawLab::getMouseShape(Point point)
 {
  if( zoom.contains(point) && normal.contains(point) ) return Mouse_Cross;
  
  return Mouse_Arrow;
 }

 // user input

void DrawLab::react(UserAction action)
 {
  action.dispatch(*this);
 }

void DrawLab::react_Key(VKey vkey,KeyMod kmod)
 {
  switch( vkey )
    {
     case VKey_Insert :
      {
       do_ins=!do_ins;
       
       redraw();
      } 
     break;
     
     case VKey_Delete :
      {
       delDot();
      }
     break;
     
     case VKey_1 :
      {
       if( do_ins )
         {
          dot_type=Smooth::DotSimple;
         
          redraw();
         }
       else
         {
          setType(Smooth::DotSimple);
         }
      } 
     break; 
     
     case VKey_2 :
      {
       if( do_ins )
         {
          dot_type=Smooth::DotBreak;
         
          redraw();
         }
       else
         {
          setType(Smooth::DotBreak);
         }
      } 
     break; 
     
     case VKey_Home :
      {
       setPickInd(0);
      }
     break; 
     
     case VKey_End :
      {
       setPickInd(dots.getLen()-1);
      }
     break; 
     
     case VKey_Tab :
      {
       ulen len=dots.getLen();
       
       if( len>1 )
         {
          if( kmod&KeyMod_Shift )
            {
             if( pick_ind )
               {
                pick_ind--;
               }
             else
               {
                pick_ind=len-1;
               }
            }
          else
            {
             pick_ind++;
             
             if( pick_ind>=len ) pick_ind=0;
            }
         
          redraw();
         }
      }
     break;
     
     case VKey_Space :
      {
       setPickInd(near_ind);
      }
     break; 
     
     case VKey_Equal :
     case VKey_NumPlus :
      {
       incWidth();
      }
     break; 
     
     case VKey_Minus :
     case VKey_NumMinus :
      {
       decWidth();
      }
     break; 

     case VKey_F8 :
      {
       show_marks=!show_marks;
       
       redraw();
      }
     break; 
     
     case VKey_F9 :
      {
       half_flag=(half_flag==HalfPos)?HalfNeg:HalfPos;
       
       redraw();
      }
     break;
     
     case VKey_F10 :
      {
       ulen len=dots.getLen();
       
       if( len )
         {
          dots.append_copy(dots[0]);
          
          noNear();
          
          redraw();
         }
      }
     break;
    }
 }
   
void DrawLab::react_LeftClick(Point point,MouseKey)
 {
  if( control.contains(point) )
    {
     if( select_Path.contains(point) )
       {
        draw_type=DrawPath;
        
        redraw();
        
        return;
       }
     
     if( select_Loop.contains(point) )
       {
        draw_type=DrawLoop;
        
        redraw();
        
        return;
       }
     
     if( select_Curve.contains(point) )
       {
        draw_type=DrawCurve;
        
        redraw();
        
        return;
       }
     
     if( select_CurveLoop.contains(point) )
       {
        draw_type=DrawCurveLoop;
        
        redraw();
        
        return;
       }
     
     if( select_SolidOdd.contains(point) )
       {
        draw_type=DrawSolidOdd;
        
        redraw();
        
        return;
       }
     
     if( select_SolidAll.contains(point) )
       {
        draw_type=DrawSolidAll;
        
        redraw();
        
        return;
       }
     
     if( select_CurveSolidOdd.contains(point) )
       {
        draw_type=DrawCurveSolidOdd;
        
        redraw();
        
        return;
       }
     
     if( select_CurveSolidAll.contains(point) )
       {
        draw_type=DrawCurveSolidAll;
        
        redraw();
        
        return;
       }
     
     if( select_LinePath.contains(point) )
       {
        draw_type=DrawLinePath;
        
        redraw();
        
        return;
       }
     
     if( select_LineLoop.contains(point) )
       {
        draw_type=DrawLineLoop;
        
        redraw();
        
        return;
       }
     
     if( select_LineCurve.contains(point) )
       {
        draw_type=DrawLineCurve;
        
        redraw();
        
        return;
       }
     
     if( select_LineCurveLoop.contains(point) )
       {
        draw_type=DrawLineCurveLoop;
        
        redraw();
        
        return;
       }
     
     if( select_HalfLinePath.contains(point) )
       {
        draw_type=DrawHalfLinePath;
        
        redraw();
        
        return;
       }
     
     if( select_HalfLineLoop.contains(point) )
       {
        draw_type=DrawHalfLineLoop;
        
        redraw();
        
        return;
       }
     
     if( select_HalfLineCurve.contains(point) )
       {
        draw_type=DrawHalfLineCurve;
        
        redraw();
        
        return;
       }
     
     if( select_HalfLineCurveLoop.contains(point) )
       {
        draw_type=DrawHalfLineCurveLoop;
        
        redraw();
        
        return;
       }
     
     if( width_plus.contains(point) )
       {
        incWidth();
       
        return;
       }
     
     if( width_minus.contains(point) )
       {
        decWidth();
        
        return;
       }
    }
  
  if( normal.contains(point) )
    {
     move_normal=true;
     
     if( do_ins )
       insDot(point);
     else
       moveDot(point);
     
     captureMouse();
    
     return;
    }
  
  if( zoom.contains(point) )
    {
     move_zoom=true;
     
     if( do_ins )
       insZoomDot(point);
     else
       moveZoomDot(point);
    
     captureMouse();
     
     return;
    }
 }
   
void DrawLab::react_LeftUp(Point,MouseKey)
 {
  if( move_normal || move_zoom )
    {
     move_normal=false;
     move_zoom=false;
     
     releaseMouse();
    }
 }
   
void DrawLab::react_RightClick(Point point,MouseKey)
 {
  if( normal.contains(point) )
    {
     part.x=Cap<Coord>(0, point.x-normal.x-part.dx/2 ,normal.dx-part.dx);
     part.y=Cap<Coord>(0, point.y-normal.y-part.dy/2 ,normal.dy-part.dy);
     
     redraw();
    }
 }

void DrawLab::react_Move(Point point,MouseKey mkey)
 {
  if( mkey&MouseKey_Right )
    {
     react_RightClick(point,mkey);
    }
  
  if( mkey&MouseKey_Left )
    {
     if( move_normal )
       {
        moveDot(point);
       
        return;
       }
     
     if( move_zoom )
       {
        moveZoomDot(point);
       
        return;
       }
    }
  
  if( normal.contains(point) )
    {
     setNear(point);
    }
  else if( zoom.contains(point) )
    {
     setZoomNear(point);
    }
  else
    {
     if( noNear() ) redraw();
    }
 }
   
void DrawLab::react_Leave()
 {
  if( noNear() ) redraw();
 }
   
void DrawLab::react_Wheel(Point point,MouseKey,Coord delta)
 {
  if( normal.contains(point) )
    {
     zoomDots(point,delta);
    }
  else if( zoom.contains(point) )
    {
     zoomZoomDots(point,delta);
    }
 }

} // namespace App
