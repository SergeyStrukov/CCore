/* ShapeLib13.cpp */ 
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
 
#include <CCore/inc/video/ShapeLib.h>

#include <CCore/inc/video/SmoothDrawArt.h>
#include <CCore/inc/video/FigureLib.h>
 
namespace CCore {
namespace Video {

/* class ScrollShape */

unsigned ScrollShape::Accelerate(unsigned count,unsigned period)
 {
  if( count==0 ) return 1;
  
  if( count<period ) return 0;
  
  count-=period;
  
  count/=period;
  
  if( count<10 ) return count+1;
  
  return 10; 
 }

ulen ScrollShape::Delta(ulen m,uCoord p,uCoord q)
 {
  if( p>=q ) return m;
  
  UIntFunc<ulen>::Mul mul(m,p);
  
  return UIntFunc<ulen>::Div(mul.hi,mul.lo,q);
 }

ulen ScrollShape::delta(uCoord delta,uCoord len,uCoord dlen) const
 {
  if( total<=page ) return 0;
  
  uCoord ext=2*dlen;
  
  if( len<=ext ) return 0;
  
  len-=ext;
  
  if( len<=dlen ) return 0;
  
  if( Delta(total,dlen,len)<page ) return Delta(total,delta,len);
  
  return Delta(total-page,delta,len-dlen);
 }

void ScrollShape::dragPos(Coord from,Coord to,uCoord len,uCoord dlen)
 {
  if( from<to )
    {
     ulen d=delta(IntDist(from,to),len,dlen);
     ulen cap=getMaxPos();
     
     if( d<cap && drag_pos<cap-d )
       pos=drag_pos+d;
     else
       pos=cap;
    }
  else if( from>to )
    {
     ulen d=delta(IntDist(to,from),len,dlen);
    
     if( drag_pos>d )
       pos=drag_pos-d;
     else
       pos=0;
    }
 }

/* class XScrollShape */

Point XScrollShape::getMinSize() const
 {
  Coord w=RoundUpLen(+cfg.width);
  
  return 2*Point::Diag(w)+Point(40,8);
 }

ScrollType XScrollShape::getType(MPoint point) const
 {
  MPane p(pane);
  
  if( !p || page>=total || !enable ) return ScrollType_None;
  
  MPoint a=pane.getBase();
  MPoint s=p.getSize();
  
  MCoord y0=a.y;
  MCoord y1=y0+s.y;
  
  if( point.y<y0 || point.y>y1 ) return ScrollType_None;
   
  MCoord x0=a.x;
  MCoord x1=x0+s.y;
  MCoord x5=x0+s.x;
  MCoord x4=x5-s.y;
  
  if( point.x<x0 || point.x>x5 ) return ScrollType_None;
  
  if( point.x<x1 ) return ScrollType_Down;
  
  if( point.x>x4 ) return ScrollType_Up;
  
  ulen cap=total-page;
  ulen pos_=Min(pos,cap);
  
  MCoord len=Max(Position(page,total,0,x4-x1),s.y);
  
  MCoord x2=Position(pos_,cap,x1,x4-len);
  MCoord x3=x2+len;
  
  if( point.x<x2 ) return ScrollType_DownPage;
  
  if( point.x>x3 ) return ScrollType_UpPage;
  
  return ScrollType_Drag;
 }

void XScrollShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);
  
  if( !p ) return;
  
  Smooth::DrawArt art(buf);
  
  MPoint a=p.getBase();
  MPoint s=p.getSize();
  
  art.block(pane,+cfg.back);
  
  if( s.x<5*s.y ) return;
  
  MCoord y0=a.y;
  MCoord y1=y0+s.y;
  
  MCoord x0=a.x;
  MCoord x1=x0+s.y;
  MCoord x5=x0+s.x;
  MCoord x4=x5-s.y;
  
  bool enable_=enable;
  
  MCoord x2;
  MCoord x3;
  
  if( page>=total )
    {
     enable_=false;
     
     x2=x1;
     x3=x4;
    }
  else
    {
     ulen cap=total-page;
     ulen pos_=Min(pos,cap);
     
     MCoord len=Max(Position(page,total,0,x4-x1),s.y);
     
     x2=Position(pos_,cap,x1,x4-len);
     x3=x2+len;
    }
  
  MCoord width=+cfg.width;
  MCoord d=Max<MCoord>(s.y/6,width);
  
  // down
  
  if( down==ScrollType_Down )
    {
     FigureBox fig_box(x0,x1,y0,y1);
     
     fig_box.solid(art,+cfg.bottom);
      
     FigureLeftArrow fig(x0+d,x1-d,y0+d,y1-d);
     
     fig.transform(Smooth::DotShift(MPoint::Diag(width)));

     fig.curveSolid(art,enable_?+cfg.face:+cfg.bottom);
    }
  else
    {
     FigureTopBorder fig_top(x0,x1,y0,y1,width);
       
     fig_top.solid(art,focus?+cfg.focus:+cfg.top);
     
     FigureBottomBorder fig_bottom(x0,x1,y0,y1,width);
     
     fig_bottom.solid(art,+cfg.bottom);
     
     FigureLeftArrow fig(x0+d,x1-d,y0+d,y1-d);
     
     VColor cname;
     
     if( enable_ )
       {
        if( mover==ScrollType_Down )
          cname=+cfg.faceUp;
        else
          cname=+cfg.face;
       }
     else
       {
        cname=+cfg.bottom;
       }

     fig.curveSolid(art,cname);
    }

  // up
  
  if( down==ScrollType_Up )
    {
     FigureBox fig_box(x4,x5,y0,y1);
   
     fig_box.solid(art,+cfg.bottom);
     
     FigureRightArrow fig(x4+d,x5-d,y0+d,y1-d);
    
     fig.transform(Smooth::DotShift(MPoint::Diag(width)));

     fig.curveSolid(art,enable_?+cfg.face:+cfg.bottom);
    }
  else
    {
     FigureTopBorder fig_top(x4,x5,y0,y1,width);
      
     fig_top.solid(art,focus?+cfg.focus:+cfg.top);
    
     FigureBottomBorder fig_bottom(x4,x5,y0,y1,width);
      
     fig_bottom.solid(art,+cfg.bottom);
    
     FigureRightArrow fig(x4+d,x5-d,y0+d,y1-d);
     
     VColor cname;
     
     if( enable_ )
       {
        if( mover==ScrollType_Up )
          cname=+cfg.faceUp;
        else
          cname=+cfg.face;
       }
     else
       {
        cname=+cfg.bottom;
       }
     
     fig.curveSolid(art,cname);
    }
  
  // down page
  
  {
   FigureBox fig_top(x1,x2,y0,y0+width);
   
   fig_top.solid(art,focus?+cfg.focus:+cfg.top);
   
   FigureBox fig_bottom(x1,x2,y1-width,y1);
   
   fig_bottom.solid(art,+cfg.bottom);
  }
  
  if( down==ScrollType_DownPage )
    {
     MCoord e=(5*s.y)/12;
    
     FigureBox fig(x1,x2,y0+e,y1-e);
     
     fig.solid(art,+cfg.face);
    }
  else
    {
     MCoord e=(3*s.y)/8;
     
     FigureBox fig(x1,x2,y0+e,y1-e);
     
     VColor cname;
     
     if( enable_ )
       {
        if( mover==ScrollType_DownPage )
          cname=+cfg.faceUp;
        else
          cname=+cfg.face;
       }
     else
       {
        cname=+cfg.bottom;
       }

     fig.solid(art,cname);
    }
  
  // up page
  
  {
   FigureBox fig_top(x3,x4,y0,y0+width);
   
   fig_top.solid(art,focus?+cfg.focus:+cfg.top);
   
   FigureBox fig_bottom(x3,x4,y1-width,y1);
   
   fig_bottom.solid(art,+cfg.bottom);
  }
  
  if( down==ScrollType_UpPage )
    {
     MCoord e=(5*s.y)/12;
   
     FigureBox fig(x3,x4,y0+e,y1-e);
     
     fig.solid(art,+cfg.face);
    }
  else
    {
     MCoord e=(3*s.y)/8;
     
     FigureBox fig(x3,x4,y0+e,y1-e);
     
     VColor cname;
     
     if( enable_ )
       {
        if( mover==ScrollType_UpPage )
          cname=+cfg.faceUp;
        else
          cname=+cfg.face;
       }
     else
       {
        cname=+cfg.bottom;
       }

     fig.solid(art,cname);
    }
  
  // drag
  
  {
   FigureBox fig(x2,x3,y0,y1);
   
   fig.solid(art,TwoField({x0,y0},+cfg.top,{x0,y1},+cfg.bottom));
  }
  
  {
   MCoord f=(x3-x2)/4;
   
   MCoord a0=x2+f;
   MCoord a1=x2+(x3-x2)/2;
   MCoord a2=x3-f;
   
   MCoord e=s.y/3;
   
   MCoord b0=y0+e;
   MCoord b1=y0+s.y/2;
   MCoord b2=y1-e;
   
   VColor cname;
   
   if( enable_ )
     {
      if( mover==ScrollType_Drag )
        cname=+cfg.faceUp;
      else
        cname=+cfg.face;
     }
   else
     {
      cname=+cfg.bottom;
     }
   
   if( a2-a0>2*(b2-b0) )
     {
      MCoord c=(a2-a0)/2-(b2-b0);
      
      FigurePoints<6> fig;
      
      fig[0]={a0,b1};
      fig[1]={a1-c,b0};
      fig[2]={a1+c,b0};
      fig[3]={a2,b1};
      fig[4]={a1+c,b2};
      fig[5]={a1-c,b2};
      
      fig.solid(art,cname);
     }
   else
     {
      FigurePoints<4> fig;
      
      fig[0]={a0,b1};
      fig[1]={a1,b0};
      fig[2]={a2,b1};
      fig[3]={a1,b2};

      fig.solid(art,cname);
     }
  }
 }

} // namespace Video
} // namespace CCore
 

