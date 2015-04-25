/* DragWindow.cpp */ 
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
 
//#include <CCore/inc/video/DragWindow.h>
#include "DragWindow.h"

//#include <CCore/inc/video/DrawArt.h>
#include "DrawArt.h"

namespace CCore {
namespace Video {

/* class DragClient */

DragClient::DragClient()
 {
 }
   
DragClient::~DragClient()
 {
 }
   
void DragClient::layout(Point)
 {
 }
   
void DragClient::draw(FrameBuf<DesktopColor> buf,bool drag_active) const
 {
  buf.erase(drag_active?Gray:Black);
 }

/* class DragWindow::Shape */

void DragWindow::Shape::layout(Point size)
 {
  Coord dxy=cfg.frame_dxy;
  Coord tdy=cfg.title_dy;
  Coord bdx=cfg.btn_dx;
  Coord bdy=cfg.btn_dy;
  
  if( size>Point(2*dxy+5*bdx+bdx/2+Max(dxy,tdy),dxy+Max<Coord>(2*dxy,tdy)) )
    {
     dragUpLeft=Pane(0,0,dxy,dxy);
     dragLeft=Pane(0,dxy,dxy,size.y-2*dxy);
     dragDownLeft=Pane(0,size.y-dxy,dxy,dxy);
     
     dragDown=Pane(dxy,dragDownLeft.y,size.x-2*dxy,dxy);
     
     dragDownRight=Pane(size.x-dxy,dragDownLeft.y,dxy,dxy);
     dragRight=Pane(dragDownRight.x,dxy,dxy,dragLeft.dy);
     dragUpRight=Pane(dragDownRight.x,0,dxy,dxy);
     
     dragBar=Pane(dxy,0,dragDown.dx,tdy);
     
     client=Pane(dxy,tdy,dragDown.dx,size.y-dxy-tdy);
     
     Coord yb=(tdy-bdy)/2;
     
     Coord tx=dragBar.dx-5*bdx; 
     
     Coord xb0=dragBar.x+tx;
     Coord xb1=xb0+bdx+bdx/8;
     Coord xb2=xb1+bdx+bdx/8;
     Coord xb3=xb2+bdx+bdx/2;
     
     btnAlert=Pane(xb0,yb,bdx,bdy);
     btnMin=Pane(xb1,yb,bdx,bdy);
     btnMax=Pane(xb2,yb,bdx,bdy);
     btnClose=Pane(xb3,yb,bdx,bdy);
     
     titleBar=Pane(dragBar.x+bdx/4,2,tx-bdx/2,tdy-4);
    }
  else
    {
     dragUpLeft=Empty;
     dragLeft=Empty;
     dragDownLeft=Empty;
     
     dragDown=Empty;
     
     dragDownRight=Pane(Null,size);
     dragRight=Empty;
     dragUpRight=Empty;
     
     dragBar=Empty;
     
     client=Empty;
     
     btnAlert=Empty;
     btnMin=Empty;
     btnMax=Empty;
     btnClose=Empty;
     titleBar=Empty;
    }
 }

class DragWindow::Shape::DrawArt : public CommonDrawArt
 {
  public:
  
   explicit DrawArt(FrameBuf<DesktopColor> buf) : CommonDrawArt(buf) {}
   
   void box(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     const Point temp[]={
                         Point(pane.x,pane.y),
                         Point(pane.x,pane.y+pane.dy-1),
                         Point(pane.x+pane.dx-1,pane.y+pane.dy-1),
                         Point(pane.x+pane.dx-1,pane.y)
                        };
     
     block(pane,inner);
     loop(Range(temp),edge);
    }
   
   void boxX(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     block(pane,inner);
     path(edge,Point(pane.x,pane.y),Point(pane.x+pane.dx-1,pane.y));
     path(edge,Point(pane.x,pane.y+pane.dy-1),Point(pane.x+pane.dx-1,pane.y+pane.dy-1));
    }
   
   void boxY(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     block(pane,inner);
     path(edge,Point(pane.x,pane.y),Point(pane.x,pane.y+pane.dy-1));
     path(edge,Point(pane.x+pane.dx-1,pane.y),Point(pane.x+pane.dx-1,pane.y+pane.dy-1));
    }
   
   Pane btn(Pane pane,ColorName face,ColorName edge)
    {
     Coord px=pane.dx/4;
     Coord py=pane.dy/8;
     
     Coord x0=pane.x+py;
     Coord x1=pane.x+px;
     Coord x2=pane.x+pane.dx-1-px;
     Coord x3=pane.x+pane.dx-1-py;
     
     Coord y0=pane.y+py;
     Coord y1=pane.y+px;
     Coord y2=pane.y+pane.dy-1-px;
     Coord y3=pane.y+pane.dy-1-py;
     
     const Point dots[]={Point(x1,y0),
                         Point(x2,y0),
                         Point(x3,y1),
                         Point(x3,y2),
                         Point(x2,y3),
                         Point(x1,y3),
                         Point(x0,y2),
                         Point(x0,y1)};
     
     curveSolid(Range(dots),SolidAll,face);
     
     curveLoop_smooth(Range(dots),edge);
     
     Coord dx=pane.dx-2*px;
     Coord dy=pane.dy-2*px;
     
     if( dx>0 && dy>0 )
       return Pane(pane.x+px,pane.y+px,dx,dy);
     
     return Empty;
    }
   
   Pane title(Pane pane,ColorName up,ColorName down)
    {
     Coord px1=pane.dy/4;
     Coord px0=px1/3;
     
     curvePath_smooth(up,Point(pane.x+px1,pane.y+pane.dy-1),
                         Point(pane.x+px0,pane.y+pane.dy-1-pane.dy/4),
                         Point(pane.x    ,pane.y+(pane.dy-1)/2),
                         Point(pane.x+px0,pane.y+pane.dy/4),
                         Point(pane.x+px1,pane.y));
     
     path(up,Point(pane.x+px1,pane.y),Point(pane.x+pane.dx-1-px1,pane.y));
     
     curvePath_smooth(down,Point(pane.x+pane.dx-1-px1,pane.y+pane.dy-1),
                           Point(pane.x+pane.dx-1-px0,pane.y+pane.dy-1-pane.dy/4),
                           Point(pane.x+pane.dx-1    ,pane.y+(pane.dy-1)/2),
                           Point(pane.x+pane.dx-1-px0,pane.y+pane.dy/4),
                           Point(pane.x+pane.dx-1-px1,pane.y));
     
     path(down,Point(pane.x+px1,pane.y+pane.dy-1),Point(pane.x+pane.dx-1-px1,pane.y+pane.dy-1));
     
     Coord dx=pane.dx-2*px1;
     Coord dy=pane.dy-2;
     
     if( dx>0 && dy>0 )
       return Pane(pane.x+px1,pane.y+1,dx,dy);
     
     return Empty;
    }
 };

void DragWindow::Shape::draw(FrameBuf<DesktopColor> buf) const
 {
  DrawArt art(buf);
  
  if( +dragLeft )
    {
     Pane pane=dragLeft;
    
     art.boxY(pane,cfg.edge,cfg.frame);
     
     Coord delta=cfg.frame_dxy/2;
     
     ColorName cname=(drag_type==DragType::Left)?cfg.accentDrag:( (hilight==DragType::Left)?cfg.accentHilight:cfg.accent );
     
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+delta,pane.y+pane.dy-1-delta));
    }
  
  if( +dragRight )
    {
     Pane pane=dragRight;
    
     art.boxY(pane,cfg.edge,cfg.frame);
     
     Coord delta=cfg.frame_dxy/2;
     
     ColorName cname=(drag_type==DragType::Right)?cfg.accentDrag:( (hilight==DragType::Right)?cfg.accentHilight:cfg.accent );
     
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+delta,pane.y+pane.dy-1-delta));
    }

  if( +dragDown )
    {
     Pane pane=dragDown;
   
     art.boxX(pane,cfg.edge,cfg.frame);
    
     Coord delta=cfg.frame_dxy/2;
    
     ColorName cname=(drag_type==DragType::Down)?cfg.accentDrag:( (hilight==DragType::Down)?cfg.accentHilight:cfg.accent );
    
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+pane.dx-1-delta,pane.y+delta));
    }
  
  if( +dragUpLeft )
    {
     Pane pane=dragUpLeft;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=(drag_type==DragType::UpLeft)?cfg.accentDrag:( (hilight==DragType::UpLeft)?cfg.accentHilight:cfg.accent );
   
     art.solid(SolidAll,cname,Point(pane.x+1,pane.y+1),Point(pane.x+pane.dx-2,pane.y+1),Point(pane.x+1,pane.y+pane.dy-2));
    }
  
  if( +dragDownLeft )
    {
     Pane pane=dragDownLeft;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=(drag_type==DragType::DownLeft)?cfg.accentDrag:( (hilight==DragType::DownLeft)?cfg.accentHilight:cfg.accent );
   
     art.solid(SolidAll,cname,Point(pane.x+1,pane.y+1),Point(pane.x+pane.dx-2,pane.y+pane.dy-2),Point(pane.x+1,pane.y+pane.dy-2));
    }
  
  if( +dragDownRight )
    {
     Pane pane=dragDownRight;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=(drag_type==DragType::DownRight)?cfg.accentDrag:( (hilight==DragType::DownRight)?cfg.accentHilight:cfg.accent );
   
     art.solid(SolidAll,cname,Point(pane.x+pane.dx-2,pane.y+1),Point(pane.x+1,pane.y+pane.dy-2),Point(pane.x+pane.dx-2,pane.y+pane.dy-2));
    }
  
  if( +dragUpRight )
    {
     Pane pane=dragUpRight;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=(drag_type==DragType::UpRight)?cfg.accentDrag:( (hilight==DragType::UpRight)?cfg.accentHilight:cfg.accent );
   
     art.solid(SolidAll,cname,Point(pane.x+1,pane.y+1),Point(pane.x+pane.dx-2,pane.y+pane.dy-2),Point(pane.x+pane.dx-2,pane.y+1));
    }
  
  if( +dragBar )
    {
     Pane pane=dragBar;
 
     art.boxX(pane,cfg.edge,has_focus?cfg.active:cfg.inactive);
    }
  
  if( +titleBar )
    {
     Pane pane=art.title(titleBar, has_focus?cfg.titleActiveUp:cfg.titleUp , has_focus?cfg.titleActiveDown:cfg.titleDown );
     
     cfg.title_font->text(buf.cut(pane),TextPlace(AlignX::Left,AlignY::Center),Range(title),cfg.title);
    }
  
  if( +btnAlert )
    {
     Pane pane=art.btn(btnAlert, (hilight==DragType::Alert)?cfg.btnFaceHilight:cfg.btnFace ,cfg.btnEdge);
     
     ColorName cname=(alert_type==AlertType::No)?cfg.noAlert:( (alert_type==AlertType::Closed)?cfg.alert:cfg.closeAlert );
        
     cfg.title_font->text(buf.cut(pane),TextPlace(AlignX::Center,AlignY::Center),StrLen("!"),cname);
    }

  if( +btnMin )
    {
     ColorName cname=(btn_type==DragType::Min)?cfg.btnFaceDown:( (hilight==DragType::Min)?cfg.btnFaceHilight:cfg.btnFace );
     
     Pane pane=art.btn(btnMin,cname,cfg.btnEdge);
     
     if( pane.dx>0 && pane.dy>=cfg.min_dy )
       {
        art.block(Pane(pane.x,pane.y+pane.dy-cfg.min_dy,pane.dx,cfg.min_dy),cfg.btnPict);
       }
    }
  
  if( +btnMax )
    {
     ColorName cname=(btn_type==DragType::Max)?cfg.btnFaceDown:( (hilight==DragType::Max)?cfg.btnFaceHilight:cfg.btnFace );
       
     Pane pane=art.btn(btnMax,cname,cfg.btnEdge);

     if( pane.dx>0 && pane.dy>=cfg.min_dy )
       {
        if( max_button )
          art.block(pane,cfg.btnPict);
        else
          art.block(Pane(pane.x+pane.dx/4,pane.y+pane.dy/4,pane.dx/2,pane.dy/2),cfg.btnPict);
       }
    }
  
  if( +btnClose )
    {
     ColorName cname=(btn_type==DragType::Close)?cfg.btnFaceDown:( (hilight==DragType::Close)?cfg.btnFaceClose:cfg.btnFace );
       
     Pane pane=art.btn(btnClose,cname,cfg.btnEdge);
     
     if( +pane )
       {
        art.path_smooth(cfg.btnStop,Point(pane.x,pane.y),Point(pane.x+pane.dx-1,pane.y+pane.dy-1));
        art.path_smooth(cfg.btnStop,Point(pane.x,pane.y+pane.dy-1),Point(pane.x+pane.dx-1,pane.y));
       } 
    }
 }

DragType DragWindow::Shape::dragTest(Point point) const
 {
  if( dragUpLeft.contains(point) ) return DragType::UpLeft;

  if( dragLeft.contains(point) ) return DragType::Left;
  
  if( dragDownLeft.contains(point) ) return DragType::DownLeft;
  
  if( dragDown.contains(point) ) return DragType::Down;
  
  if( dragDownRight.contains(point) ) return DragType::DownRight;
  
  if( dragRight.contains(point) ) return DragType::Right;
  
  if( dragUpRight.contains(point) ) return DragType::UpRight;
  
  if( dragBar.contains(point) ) 
    {
     if( btnAlert.contains(point) ) return DragType::Alert;
      
     if( btnMin.contains(point) ) return DragType::Min;
    
     if( btnMax.contains(point) ) return DragType::Max;
    
     if( btnClose.contains(point) ) return DragType::Close;
     
     return DragType::Bar;
    }
  
  return DragType::None;
 }

/* class DragWindow */

void DragWindow::replace(Pane place,Point delta,DragType drag_type)
 {
  DragPane(place,delta,drag_type);
  
  Point new_size(place.dx,place.dy);
  
  if( new_size>Null && new_size<=win->getMaxSize() ) 
    {
     Pane screen=Extent(Null,desktop->getScreenSize());
    
     if( +Inf(place,screen) ) win->move(place);
    }
 }

void DragWindow::replace(Point delta,DragType drag_type)
 {
  Pane place=win->getPlacement();

  replace(place,delta,drag_type);
 }

void DragWindow::startDrag(Point point,DragType drag_type)
 {
  win->captureMouse();
 
  Pane place=win->getPlacement();
  
  shape.drag_type=drag_type;
  
  drag_from=point+place.getBase();
  
  redraw();
 }

void DragWindow::dragTo_(Point point)
 {
  Pane place=win->getPlacement();
  Point delta=Diff(drag_from,point+place.getBase());
  
  replace(place,delta,shape.drag_type);
 }

void DragWindow::dragTo(Point point)
 {
  if( win->getToken() ) return;
  
  dragTo_(point);
 }

void DragWindow::endDrag(Point point)
 {
  dragTo_(point);
  
  if( !client_capture ) win->releaseMouse();
  
  shape.drag_type=DragType::None;
  
  redraw();
 }

bool DragWindow::forwardKey(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  if( kmod&KeyMod_Alt )
    {
     switch( vkey )
       {
        case VKey_Left  : replace(Point(-(Coord)repeat,0),(kmod&KeyMod_Shift)?DragType::Right:DragType::Bar); return true;
        
        case VKey_Right : replace(Point((Coord)repeat,0),(kmod&KeyMod_Shift)?DragType::Right:DragType::Bar); return true;
        
        case VKey_Up    : replace(Point(0,-(Coord)repeat),(kmod&KeyMod_Shift)?DragType::Down:DragType::Bar); return true;
        
        case VKey_Down  : replace(Point(0,(Coord)repeat),(kmod&KeyMod_Shift)?DragType::Down:DragType::Bar); return true;
        
        case VKey_F2    : minimize(); return true;
        
        case VKey_F3    : maximize(); return true;
        
        case VKey_F4    : destroy(); return true;
        
        default: return false;
       }
    }
  else
    {
     return false;
    }
 }

bool DragWindow::forwardKeyUp(VKey vkey,KeyMod kmod,unsigned)
 {
  if( kmod&KeyMod_Alt )
    {
     switch( vkey )
       {
        case VKey_Left  : 
        case VKey_Right : 
        case VKey_Up    : 
        case VKey_Down  : 
        case VKey_F2    : 
        case VKey_F3    : 
        case VKey_F4    : return true;
        
        default: return false;
       }
    }
  else
    {
     return false;
    }
 }

DragWindow::DragWindow(Desktop *desktop,Shape::Config &cfg,DragClient &client_)
 : FrameWindow(desktop),
   shape(cfg),
   client(client_),
   input(this),
   connector_updateConfig(this,&DragWindow::updateConfig,shape.cfg.update)
 {
  client_.win=this;
 }

DragWindow::~DragWindow()
 {
 }

 // methods

void DragWindow::createMain(CmdDisplay cmd_display,Point max_size,String title)
 {
  shape.max_button=( cmd_display!=CmdDisplay_Maximized );
  shape.title=title;
  
  win->createMain(max_size);
  
  win->display(cmd_display);
  win->update();
 }

void DragWindow::create(Pane pane,Point max_size,String title)
 {
  shape.title=title;
  
  win->create(pane,max_size);
  win->show();
 }

void DragWindow::create(WinControl *parent,Pane pane,Point max_size,String title)
 {
  shape.title=title;
  
  win->create(parent,pane,max_size);
  win->show();
 }

void DragWindow::minimize()
 {
  win->display(CmdDisplay_Minimized);
 }

void DragWindow::maximize()
 {
  if( shape.max_button )
    {
     shape.max_button=false;
     
     win->display(CmdDisplay_Maximized);
    } 
  else
    {
     shape.max_button=true;
     
     win->display(CmdDisplay_Restore);
    } 
  
  redraw();
 }

void DragWindow::redraw(bool do_layout)
 {
  if( do_layout )
    {
     shape.layout(size);
    
     client.layout(shape.client.getSize());
    }
  
  FrameBuf<DesktopColor> buf(win->getDrawPlane());
  
  if( size<=buf.getSize() ) 
    {
     shape.draw(buf);
    
     client.draw(buf.cut(shape.client),(bool)shape.drag_type);
    
     win->invalidate(1);
    }
  else
    {
     CommonDrawArt(buf).erase(Black);
    }
 }

void DragWindow::captureMouse()
 {
  client_capture=true;
  
  if( !(bool)shape.drag_type ) win->captureMouse();
 }

void DragWindow::releaseMouse()
 {
  client_capture=false;
  
  if( !(bool)shape.drag_type ) win->releaseMouse();
 }

 // base

void DragWindow::alive()
 {
  win->trackMouseHover();
  win->trackMouseLeave();
  
  client.alive();
 }

void DragWindow::dead()
 {
  client.dead();
 }

void DragWindow::setSize(Point size_,bool)
 {
  if( size==size_ ) return;
  
  size=size_;
  
  shape.layout(size_);
  
  client.layout(shape.client.getSize());
  
  redraw();
 }

 // keyboard

void DragWindow::gainFocus()
 {
  shape.has_focus=true;
  
  redraw();
 }

void DragWindow::looseFocus()
 {
  shape.has_focus=false;
  
  redraw();
 }

void DragWindow::key(VKey vkey,KeyMod kmod)
 {
  if( !forwardKey(vkey,kmod) ) client.key(vkey,kmod);
 }

void DragWindow::key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  if( !forwardKey(vkey,kmod,repeat) ) client.key(vkey,kmod,repeat);
 }

void DragWindow::keyUp(VKey vkey,KeyMod kmod)
 {
  if( !forwardKeyUp(vkey,kmod) ) client.keyUp(vkey,kmod);
 }

void DragWindow::keyUp(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  if( !forwardKeyUp(vkey,kmod,repeat) ) client.keyUp(vkey,kmod,repeat);
 }

 // character

void DragWindow::putch(char ch)
 {
  client.putch(ch);
 }

void DragWindow::putch(char ch,unsigned repeat)
 {
  client.putch(ch,repeat);
 }

void DragWindow::putchAlt(char ch)
 {
  client.putchAlt(ch);
 }

void DragWindow::putchAlt(char ch,unsigned repeat)
 {
  client.putchAlt(ch,repeat);
 }

 // mouse

void DragWindow::clickLeft(Point point,MouseKey mkey)
 {
  switch( auto drag_type=shape.dragTest(point) )
    {
     case DragType::None :
      {
       if( client_capture || shape.client.contains(point) )
         {
          client.clickLeft(point-shape.client.getBase(),mkey);
         }
      }
     break;
   
     case DragType::Min   : minimize(); break;
     
     case DragType::Max   : maximize(); break;
     
     case DragType::Close : destroy(); break;
     
     default: if( !(bool)shape.drag_type ) startDrag(point,drag_type);
    }
 }

void DragWindow::upLeft(Point point,MouseKey mkey)
 {
  if( (bool)shape.drag_type )
    {
     endDrag(point);
     
     return;
    }
  
  if( client_capture || shape.client.contains(point) )
    {
     client.upLeft(point-shape.client.getBase(),mkey);
    }
 }

void DragWindow::dclickLeft(Point point,MouseKey mkey)
 {
  if( (bool)shape.drag_type ) return;
  
  if( client_capture || shape.client.contains(point) )
    {
     client.dclickLeft(point-shape.client.getBase(),mkey);
    }
 }

void DragWindow::clickRight(Point point,MouseKey mkey)
 {
  if( (bool)shape.drag_type ) return;
  
  if( client_capture || shape.client.contains(point) )
    {
     client.clickRight(point-shape.client.getBase(),mkey);
    }
 }

void DragWindow::upRight(Point point,MouseKey mkey)
 {
  if( (bool)shape.drag_type ) return;
  
  if( client_capture || shape.client.contains(point) )
    {
     client.upRight(point-shape.client.getBase(),mkey);
    }
 }

void DragWindow::dclickRight(Point point,MouseKey mkey)
 {
  if( (bool)shape.drag_type ) return;
  
  if( client_capture || shape.client.contains(point) )
    {
     client.dclickRight(point-shape.client.getBase(),mkey);
    }
 }

void DragWindow::move(Point point,MouseKey mkey)
 {
  if( (bool)shape.drag_type )
    {
     if( mkey&MouseKey_Left )
       dragTo(point);
     else
       endDrag(point);
     
     return;
    }
  
  auto drag_type=shape.dragTest(point);
  
  if( drag_type==DragType::Bar ) drag_type=DragType::None;
  
  if( drag_type!=shape.hilight )
    {
     shape.hilight=drag_type;
     
     redraw();
    }
  
  if( shape.client.contains(point) )
    {
     client_enter=true;
     
     client.move(point-shape.client.getBase(),mkey);
    }
  else
    {
     if( client_capture ) client.move(point-shape.client.getBase(),mkey);
      
     if( client_enter )
       {
        client_enter=false;
        
        client.leave();
       }
    }
 }

void DragWindow::hover(Point point,MouseKey mkey)
 {
  if( (bool)shape.drag_type ) return;
  
  if( client_capture || shape.client.contains(point) )
    {
     client.hover(point-shape.client.getBase(),mkey);
    }
 }

void DragWindow::leave()
 {
  if( (bool)shape.hilight )
    {
     shape.hilight=DragType::None;
     
     redraw();
    }
  
  if( (bool)shape.drag_type ) return;
  
  if( client_enter )
    {
     client_enter=false;
     
     client.leave();
    }
 }

void DragWindow::wheel(Point point,MouseKey mkey,Coord delta)
 {
  if( (bool)shape.drag_type ) return;
  
  if( client_capture || shape.client.contains(point) )
    {
     client.wheel(point-shape.client.getBase(),mkey,delta);
    }
 }

void DragWindow::setMouseShape(Point point)
 {
  switch( shape.dragTest(point) )
    {
     case DragType::Up        : win->setMouseShape(Mouse_SizeUpDown); break;
      
     case DragType::UpLeft    : win->setMouseShape(Mouse_SizeUpLeft); break;

     case DragType::Left      : win->setMouseShape(Mouse_SizeLeftRight); break;
     
     case DragType::DownLeft  : win->setMouseShape(Mouse_SizeUpRight); break;
     
     case DragType::Down      : win->setMouseShape(Mouse_SizeUpDown); break;
     
     case DragType::DownRight : win->setMouseShape(Mouse_SizeUpLeft); break;
     
     case DragType::Right     : win->setMouseShape(Mouse_SizeLeftRight); break;
     
     case DragType::UpRight   : win->setMouseShape(Mouse_SizeUpRight); break;
     
     case DragType::Alert     :
     case DragType::Min       : 
     case DragType::Max       : win->setMouseShape(Mouse_Hand); break;
     
     case DragType::Close     : win->setMouseShape(Mouse_Stop); break;
      
     case DragType::Bar       : win->setMouseShape(Mouse_SizeAll); break;
     
     default: win->setMouseShape(client.getMouseShape(point-shape.client.getBase()));
    }
 }

} // namespace Video
} // namespace CCore
 

