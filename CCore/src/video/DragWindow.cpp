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
 
#include <CCore/inc/video/DragWindow.h>

#include <CCore/inc/video/DrawArt.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* DragPane() */

void DragPane(Pane &place,Point delta,DragType drag_type)
 {
  switch( drag_type )
    {
     case DragType_Top :
      {
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break; 
     
     case DragType_TopLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case DragType_Left :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
      }
     break;
     
     case DragType_BottomLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case DragType_Bottom :
      {
       place.dy+=delta.y;
      }
     break;
     
     case DragType_BottomRight :
      {
       place.dx+=delta.x;
       
       place.dy+=delta.y;
      }
     break;
     
     case DragType_Right :
      {
       place.dx+=delta.x;
      }
     break;
     
     case DragType_TopRight :
      {
       place.dx+=delta.x;
       
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;
     
     case DragType_Bar :
      {
       place.x+=delta.x;
       
       place.y+=delta.y;
      }
     break;
    }
 }

/* class DragWindow::Shape */

class DragWindow::Shape::DrawArt : public CommonDrawArt
 {
  public:
  
   explicit DrawArt(const DrawBuf &buf) : CommonDrawArt(buf) {}
   
   void box(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     PaneBorder border(pane);
     
     block(pane,inner);
     
     loop(border.get(),edge);
    }
   
   void boxX(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     PaneBorder border(pane);
     
     block(pane,inner);
     
     path(edge,border.topLeft(),border.topRight());
     path(edge,border.bottomLeft(),border.bottomRight());
    }
   
   void boxY(Pane pane,DesktopColor edge,DesktopColor inner)
    {
     PaneBorder border(pane);
     
     block(pane,inner);
     
     path(edge,border.topLeft(),border.bottomLeft());
     path(edge,border.topRight(),border.bottomRight());
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
     
     return Shrink(pane,px,px);
    }
   
   Pane title(Pane pane,ColorName up,ColorName down)
    {
     Coord px1=pane.dy/4;
     Coord px0=px1/3;
     
     Coord y0=pane.y;
     Coord y1=pane.y+pane.dy/4;
     Coord y2=pane.y+(pane.dy-1)/2;
     Coord y3=pane.y+pane.dy-1-pane.dy/4;
     Coord y4=pane.y+pane.dy-1;
     
     Coord x0=pane.x;
     Coord x1=pane.x+pane.dx-1;
     
     curvePath_smooth(up,Point(x0+px1,y4),
                         Point(x0+px0,y3),
                         Point(x0    ,y2),
                         Point(x0+px0,y1),
                         Point(x0+px1,y0));
     
     path(up,Point(x0+px1,y0),Point(x1-px1,y0));
     
     curvePath_smooth(down,Point(x1-px1,y4),
                           Point(x1-px0,y3),
                           Point(x1    ,y2),
                           Point(x1-px0,y1),
                           Point(x1-px1,y0));
     
     path(down,Point(x0+px1,y4),Point(x1-px1,y4));
     
     return Shrink(pane,2*px1,1);
    }
 };

void DragWindow::Shape::draw_TopLeft(DrawArt &art) const
 {
  if( +dragTopLeft )
    {
     Pane pane=dragTopLeft;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=accentColor(DragType_TopLeft);
     
     PaneBorder border(Shrink(pane,1,1));
   
     art.solid(SolidAll,cname,border.topLeft(),border.topRight(),border.bottomLeft());
    }
 }

void DragWindow::Shape::draw_Left(DrawArt &art) const
 {
  if( +dragLeft )
    {
     Pane pane=dragLeft;
    
     art.boxY(pane,cfg.edge,cfg.frame);
     
     ColorName cname=accentColor(DragType_Left);
     
     Coord delta=cfg.frame_dxy/2;
     
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+delta,pane.y+pane.dy-1-delta));
    }
 }

void DragWindow::Shape::draw_BottomLeft(DrawArt &art) const
 {
  if( +dragBottomLeft )
    {
     Pane pane=dragBottomLeft;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=accentColor(DragType_BottomLeft);
   
     PaneBorder border(Shrink(pane,1,1));
     
     art.solid(SolidAll,cname,border.topLeft(),border.bottomRight(),border.bottomLeft());
    }
 }

void DragWindow::Shape::draw_Bottom(DrawArt &art) const
 {
  if( +dragBottom )
    {
     Pane pane=dragBottom;
   
     art.boxX(pane,cfg.edge,cfg.frame);
    
     ColorName cname=accentColor(DragType_Bottom);
    
     Coord delta=cfg.frame_dxy/2;
    
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+pane.dx-1-delta,pane.y+delta));
    }
 }

void DragWindow::Shape::draw_BottomRight(DrawArt &art) const
 {
  if( +dragBottomRight )
    {
     Pane pane=dragBottomRight;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=accentColor(DragType_BottomRight);
     
     PaneBorder border(Shrink(pane,1,1));
   
     art.solid(SolidAll,cname,border.topRight(),border.bottomLeft(),border.bottomRight());
    }
 }

void DragWindow::Shape::draw_Right(DrawArt &art) const
 {
  if( +dragRight )
    {
     Pane pane=dragRight;
    
     art.boxY(pane,cfg.edge,cfg.frame);
     
     ColorName cname=accentColor(DragType_Right);
     
     Coord delta=cfg.frame_dxy/2;
     
     art.path(cname,Point(pane.x+delta,pane.y+delta),Point(pane.x+delta,pane.y+pane.dy-1-delta));
    }
 }

void DragWindow::Shape::draw_TopRight(DrawArt &art) const
 {
  if( +dragTopRight )
    {
     Pane pane=dragTopRight;
  
     art.box(pane,cfg.edge,cfg.frame);
   
     ColorName cname=accentColor(DragType_TopRight);
   
     PaneBorder border(Shrink(pane,1,1));
     
     art.solid(SolidAll,cname,border.topLeft(),border.bottomRight(),border.topRight());
    }
 }

void DragWindow::Shape::draw_Alert(DrawArt &art) const
 {
  if( +btnAlert )
    {
     ColorName cname=btnColor(DragType_Alert);
     
     Pane pane=art.btn(btnAlert,cname,cfg.btnEdge);
     
     if( !alert_blink )
       {
        ColorName cname=(alert_type==AlertType_No)?cfg.noAlert:( (alert_type==AlertType_Closed)?cfg.alert:cfg.closeAlert );
        
        cfg.title_font->text(art.getBuf(),pane,TextPlace(AlignX_Center,AlignY_Center),StrLen("!",1),cname);
       } 
    }
 }

void DragWindow::Shape::draw_Min(DrawArt &art) const
 {
  if( +btnMin )
    {
     ColorName cname=btnColor(DragType_Min);
     
     Pane pane=art.btn(btnMin,cname,cfg.btnEdge);
     
     if( pane.dx>0 && pane.dy>=cfg.min_dy )
       {
        Pane fig=SplitY(pane,cfg.min_dy);
       
        art.block(fig,cfg.btnPict);
       }
    }
 }

void DragWindow::Shape::draw_Max(DrawArt &art) const
 {
  if( +btnMax )
    {
     ColorName cname=btnColor(DragType_Max);
       
     Pane pane=art.btn(btnMax,cname,cfg.btnEdge);

     if( pane.dx>0 && pane.dy>=cfg.min_dy )
       {
        if( max_button )
          art.block(pane,cfg.btnPict);
        else
          art.block(Shrink(pane,pane.dx/4,pane.dy/4),cfg.btnPict);
       }
    }
 }

void DragWindow::Shape::draw_Close(DrawArt &art) const
 {
  if( +btnClose )
    {
     ColorName cname=btnColor(DragType_Close);
       
     Pane pane=art.btn(btnClose,cname,cfg.btnEdge);
     
     if( +pane )
       {
        PaneBorder border(pane);
       
        art.path_smooth(cfg.btnStop,border.topLeft(),border.bottomRight());
        art.path_smooth(cfg.btnStop,border.topRight(),border.bottomLeft());
       } 
    }
 }

void DragWindow::Shape::layout(Point size)
 {
  Coord dxy=cfg.frame_dxy;
  Coord tdy=cfg.title_dy;
  Coord bdx=cfg.btn_dx;
  Coord bdy=cfg.btn_dy;
  
  if( size>Point(2*dxy+5*bdx+bdx/2+Max(dxy,tdy),dxy+Max<Coord>(2*dxy,tdy)) )
    {
     Pane pane(0,0,size.x,size.y);
     
     Pane left=SplitX(dxy,pane);
     Pane right=SplitX(pane,dxy);
    
     dragTopLeft=SplitY(dxy,left);
     dragBottomLeft=SplitY(left,dxy);
     dragLeft=left;
     
     dragTopRight=SplitY(dxy,right);
     dragBottomRight=SplitY(right,dxy);
     dragRight=right;
     
     dragBar=SplitY(tdy,pane);
     dragBottom=SplitY(pane,dxy);
     client=pane;
     
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
     dragTopLeft=Empty;
     dragBottomLeft=Empty;
     dragLeft=Empty;
     
     dragTopRight=Empty;
     dragBottomRight=Pane(Null,size);
     dragRight=Empty;
     
     dragBar=Empty;
     dragBottom=Empty;
     client=Empty;
     
     btnAlert=Empty;
     btnMin=Empty;
     btnMax=Empty;
     btnClose=Empty;
     
     titleBar=Empty;
    }
 }

void DragWindow::Shape::draw(DrawBuf buf) const
 {
  try
    {
     DrawArt art(buf);
     
     draw_TopLeft(art);
     draw_Left(art);
     draw_BottomLeft(art);
     draw_Bottom(art);
     draw_BottomRight(art);
     draw_Right(art);
     draw_TopRight(art);
     
     if( +dragBar )
       {
        Pane pane=dragBar;
    
        art.boxX(pane,cfg.edge, has_focus?cfg.active:cfg.inactive );
       }
     
     if( +titleBar )
       {
        Pane pane=art.title(titleBar, has_focus?cfg.titleActiveUp:cfg.titleUp , has_focus?cfg.titleActiveDown:cfg.titleDown );
        
        cfg.title_font->text(buf,pane,TextPlace(AlignX_Left,AlignY_Center),Range(title),cfg.title);
       }
     
     draw_Alert(art);
     draw_Min(art);
     draw_Max(art);
     draw_Close(art);
    }
  catch(CatchType)
    {
    }
 }

void DragWindow::Shape::draw(DrawBuf buf,DragType drag_type) const
 {
  try
    {
     DrawArt art(buf);
     
     switch( drag_type )
       {
        case DragType_TopLeft     : draw_TopLeft(art); break; 
        case DragType_Left        : draw_Left(art); break;
        case DragType_BottomLeft  : draw_BottomLeft(art); break;
        case DragType_Bottom      : draw_Bottom(art); break;
        case DragType_BottomRight : draw_BottomRight(art); break; 
        case DragType_Right       : draw_Right(art); break;
        case DragType_TopRight    : draw_TopRight(art); break;
        case DragType_Alert       : draw_Alert(art); break;
        case DragType_Min         : draw_Min(art); break;
        case DragType_Max         : draw_Max(art); break;
        case DragType_Close       : draw_Close(art); break;
       }
    }
  catch(CatchType)
    {
    }
 }

Pane DragWindow::Shape::getPane(DragType drag_type) const
 {
  switch( drag_type )
    {
     case DragType_TopLeft     : return dragTopLeft; 
     case DragType_Left        : return dragLeft;
     case DragType_BottomLeft  : return dragBottomLeft;
     case DragType_Bottom      : return dragBottom;
     case DragType_BottomRight : return dragBottomRight; 
     case DragType_Right       : return dragRight;
     case DragType_TopRight    : return dragTopRight;
     
     case DragType_Alert       : return btnAlert;
     case DragType_Min         : return btnMin;
     case DragType_Max         : return btnMax;
     case DragType_Close       : return btnClose;
     
     default: return Empty;
    }
 }

DragType DragWindow::Shape::dragTest(Point point) const
 {
  if( dragTopLeft.contains(point) ) return DragType_TopLeft;

  if( dragLeft.contains(point) ) return DragType_Left;
  
  if( dragBottomLeft.contains(point) ) return DragType_BottomLeft;
  
  if( dragBottom.contains(point) ) return DragType_Bottom;
  
  if( dragBottomRight.contains(point) ) return DragType_BottomRight;
  
  if( dragRight.contains(point) ) return DragType_Right;
  
  if( dragTopRight.contains(point) ) return DragType_TopRight;
  
  if( dragBar.contains(point) ) 
    {
     if( btnAlert.contains(point) ) return DragType_Alert;
      
     if( btnMin.contains(point) ) return DragType_Min;
    
     if( btnMax.contains(point) ) return DragType_Max;
    
     if( btnClose.contains(point) ) return DragType_Close;
     
     return DragType_Bar;
    }
  
  return DragType_None;
 }

/* class DragWindow */

void DragWindow::guardClient()
 {
  if( !client )
    {
     Printf(Exception,"CCore::Video::DragWindow::guardClient() : no client");
    }
 }

void DragWindow::guardDead()
 {
  if( isAlive() )
    {
     Printf(Exception,"CCore::Video::DragWindow::guardDead() : window is alive");
    }
 }

void DragWindow::replace(Pane place,Point delta,DragType drag_type)
 {
  DragPane(place,delta,drag_type);
  
  Point new_size(place.dx,place.dy);
  
  if( new_size>Null && new_size<=host->getMaxSize() ) 
    {
     Pane screen=Extent(Null,desktop->getScreenSize());
    
     if( +Inf(place,screen) ) 
       {
        if( !shape.max_button )
          {
           shape.max_button=true;
        
           redrawFrame(DragType_Max);
          } 
        
        host->move(place);
        
        host->invalidate(1);
       }
    }
 }

void DragWindow::replace(Point delta,DragType drag_type)
 {
  Pane place=host->getPlace();

  replace(place,delta,drag_type);
 }

void DragWindow::startDrag(Point point,DragType drag_type)
 {
  shape.drag_type=drag_type;
  
  if( !client_capture ) host->captureMouse();
 
  Pane place=host->getPlace();
  
  drag_from=point+place.getBase();
  
  redrawAll();
 }

void DragWindow::dragTo(Point point)
 {
  Pane place=host->getPlace();
  Point delta=Diff(drag_from,point+place.getBase());
  
  replace(place,delta,shape.drag_type);
 }

void DragWindow::endDrag()
 {
  shape.drag_type=DragType_None;
  
  redrawAll();
 }

void DragWindow::endDrag(Point point)
 {
  dragTo(point);
  
  shape.drag_type=DragType_None;
  
  if( !client_capture ) host->releaseMouse();
  
  redrawAll();
 }

bool DragWindow::forwardKey(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  if( kmod&KeyMod_Alt )
    {
     switch( vkey )
       {
        case VKey_Left  : replace(Point(-(Coord)repeat,0),(kmod&KeyMod_Shift)?DragType_Right:DragType_Bar); return true;
        
        case VKey_Right : replace(Point((Coord)repeat,0),(kmod&KeyMod_Shift)?DragType_Right:DragType_Bar); return true;
        
        case VKey_Up    : replace(Point(0,-(Coord)repeat),(kmod&KeyMod_Shift)?DragType_Bottom:DragType_Bar); return true;
        
        case VKey_Down  : replace(Point(0,(Coord)repeat),(kmod&KeyMod_Shift)?DragType_Bottom:DragType_Bar); return true;
        
        case VKey_F2    : minimize(); return true;
        
        case VKey_F3    : maximize(); return true;
        
        case VKey_F4    : destroy(); return true;
        
        case VKey_F12   : switchClients(); return true;
        
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
        case VKey_F4    : 
        case VKey_F12   : return true;
        
        default: return false;
       }
    }
  else
    {
     return false;
    }
 }

ClientWindow & DragWindow::getClient()
 {
  if( alert_client && shape.alert_type==AlertType_Opened ) return *alert_client;
  
  guardClient();
  
  return *client;
 }

void DragWindow::redrawFrame()
 {
  if( host->isDead() ) return;
  
  if( host->getToken() ) 
    {
     delay_draw=true;
     
     return;
    }
  
  FrameBuf<DesktopColor> buf(host->getDrawPlane());
  
  if( size<=buf.getSize() ) 
    {
     shape.draw(buf);
    
     host->invalidate(1);
    }
  else
    {
     buf.erase(Black);
     
     host->invalidate(1);
    }
 }

void DragWindow::redrawFrame(DragType drag_type)
 {
  Pane pane=shape.getPane(drag_type);
  
  if( !pane ) return;
  
  if( host->isDead() ) return;
  
  if( host->getToken() ) 
    {
     delay_draw=true;
     
     return;
    }
  
  FrameBuf<DesktopColor> buf(host->getDrawPlane());
  
  if( size<=buf.getSize() ) 
    {
     shape.draw(buf,drag_type);
    
     host->invalidate(pane,1);
    }
  else
    {
     buf.erase(Black);
     
     host->invalidate(1);
    }
 }

void DragWindow::pushAlertBlink()
 {
  if( !tick_count )
    {
     tick_count=shape.cfg.blink_time;
     
     defer_tick.start();
    }
  else
    {
     tick_count=shape.cfg.blink_time;
    }
 }

void DragWindow::tick()
 {
  if( tick_count )
    {
     if( !(tick_count%shape.cfg.blink_period) )
       {
        shape.alert_blink=!shape.alert_blink;
        
        redrawFrame(DragType_Alert);
       }
     
     tick_count--;
    }
  else
    {
     defer_tick.stop();
     
     shape.alert_blink=false;
     
     redrawFrame(DragType_Alert);
    }
 }

void DragWindow::switchClients()
 {
  if( shape.alert_type && alert_client )
    {
     getClientSub().close();
    
     shape.alert_type=(shape.alert_type==AlertType_Closed)?AlertType_Opened:AlertType_Closed;
     
     getClientSub().open();
    
     redrawAll();
    }
 }

DragWindow::DragWindow(Desktop *desktop,Shape::Config &cfg)
 : FrameWindow(desktop),
   shape(cfg),
   input(this),
   connector_updateConfig(this,&DragWindow::updateConfig,cfg.update)
 {
  defer_tick=input.create(&DragWindow::tick);
 }

DragWindow::~DragWindow()
 {
 }

 // methods

void DragWindow::createMain(CmdDisplay cmd_display,Point max_size,String title)
 {
  guardClient();
  
  shape.reset(title, cmd_display!=CmdDisplay_Maximized );
  
  host->createMain(max_size);
  
  host->display(cmd_display);
  host->update();
 }

void DragWindow::create(Pane pane,Point max_size,String title)
 {
  guardClient();
  
  shape.reset(title,true);
  
  host->create(pane,max_size);
  host->show();
 }

void DragWindow::create(WindowHost *parent,Pane pane,Point max_size,String title)
 {
  guardClient();
  
  shape.reset(title,true);
  
  host->create(parent,pane,max_size);
  host->show();
 }

void DragWindow::destroy()
 { 
  if( client && client->askDestroy() ) host->destroy(); 
 }

void DragWindow::minimize()
 {
  host->display(CmdDisplay_Minimized);
 }

void DragWindow::maximize()
 {
  if( shape.max_button )
    {
     shape.max_button=false;
     
     redrawFrame(DragType_Max);
     
     host->display(CmdDisplay_Maximized);
    } 
  else
    {
     shape.max_button=true;
     
     redrawFrame(DragType_Max);
     
     host->display(CmdDisplay_Restore);
    } 
 }

void DragWindow::redrawAll(bool do_layout)
 {
  if( do_layout )
    {
     shape.layout(size);
    
     if( client ) client->getSubWindow().setPlace(shape.getClient());
     
     if( alert_client ) alert_client->getSubWindow().setPlace(shape.getClient());  
    }
  
  if( host->isDead() ) return;
  
  if( host->getToken() ) 
    {
     delay_draw=true;
     
     return;
    }
  
  FrameBuf<DesktopColor> buf(host->getDrawPlane());
  
  if( size<=buf.getSize() ) 
    {
     shape.draw(buf);
    
     getClientSub().forward_draw(buf,shape.drag_type);
    
     host->invalidate(1);
    }
  else
    {
     buf.erase(Black);
     
     host->invalidate(1);
    }
 }

void DragWindow::redrawClient()
 {
  if( host->isDead() ) return;
  
  if( host->getToken() ) 
    {
     delay_draw=true;
     
     return;
    }
  
  FrameBuf<DesktopColor> buf(host->getDrawPlane());
  
  if( size<=buf.getSize() ) 
    {
     getClientSub().forward_draw(buf,shape.drag_type);
    
     host->invalidate(shape.getClient(),1);
    }
  else
    {
     buf.erase(Black);
     
     host->invalidate(1);
    }
 }

void DragWindow::redrawClient(Pane pane)
 {
  if( host->isDead() ) return;
  
  if( host->getToken() ) 
    {
     delay_draw=true;
     
     return;
    }
  
  FrameBuf<DesktopColor> buf(host->getDrawPlane());
  
  if( size<=buf.getSize() ) 
    {
     getClientSub().forward_draw(buf,pane,shape.drag_type);
    
     host->invalidate(pane,1);
    }
  else
    {
     buf.erase(Black);
     
     host->invalidate(1);
    }
 }

void DragWindow::alert()
 {
  switch( shape.alert_type )
    {
     case AlertType_No :
      {
       shape.alert_type=AlertType_Closed;
       
       redrawFrame(DragType_Alert);
       
       pushAlertBlink();
      }
     break;
     
     case AlertType_Closed :
      {
       pushAlertBlink();
      }
     break;
     
     case AlertType_Opened :
      {
       redrawClient();
      }
     break;
    }
 }

 // SubWinControl

FrameWindow * DragWindow::getFrame()
 {
  return this;
 }

Point DragWindow::getScreenOrigin()
 {
  Pane pane=host->getPlace();
  
  return pane.getBase();
 }

void DragWindow::redraw(Pane pane)
 {
  input.redrawClient(pane);
 }

void DragWindow::setFocus(SubWindow *)
 {
  if( shape.has_focus )
    {
     getClientSub().gainFocus();
    }
 }

void DragWindow::captureMouse(SubWindow *)
 {
  if( !client_capture )
    {
     client_capture=true;
    
     if( !shape.drag_type ) host->captureMouse();
    }
 }

void DragWindow::releaseMouse(SubWindow *)
 {
  if( client_capture )
    {
     client_capture=false;
    
     if( !shape.drag_type ) host->releaseMouse();
    }
 }

 // base

void DragWindow::alive()
 {
  reset();
  
  host->trackMouseHover();
  host->trackMouseLeave();
  
  if( client ) client->alive();
  
  if( alert_client ) alert_client->alive();
  
  getClientSub().open();
 }

void DragWindow::dead()
 {
  getClientSub().close();
  
  if( client ) client->dead();
  
  if( alert_client ) alert_client->dead();
 }

void DragWindow::setSize(Point size_,bool buf_dirty)
 {
  if( size!=size_ || buf_dirty )
    {
     size=size_;
    
     redrawAll(true);
    }
 }

void DragWindow::paintDone(unsigned)
 {
  if( delay_draw )
    {
     delay_draw=false;
     
     redrawAll();
    }
 }

 // keyboard

void DragWindow::gainFocus()
 {
  shape.has_focus=true;
  
  redrawFrame();
  
  getClientSub().gainFocus();
 }

void DragWindow::looseFocus()
 {
  shape.has_focus=false;
  
  redrawFrame();
  
  getClientSub().looseFocus();
 }

void DragWindow::key(VKey vkey,KeyMod kmod)
 {
  if( !forwardKey(vkey,kmod) ) getClientSub().key(vkey,kmod);
 }

void DragWindow::key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  if( !forwardKey(vkey,kmod,repeat) ) getClientSub().key(vkey,kmod,repeat);
 }

void DragWindow::keyUp(VKey vkey,KeyMod kmod)
 {
  if( !forwardKeyUp(vkey,kmod) ) getClientSub().keyUp(vkey,kmod);
 }

void DragWindow::keyUp(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  if( !forwardKeyUp(vkey,kmod,repeat) ) getClientSub().keyUp(vkey,kmod,repeat);
 }

 // character

void DragWindow::putch(char ch)
 {
  getClientSub().putch(ch);
 }

void DragWindow::putch(char ch,unsigned repeat)
 {
  getClientSub().putch(ch,repeat);
 }

void DragWindow::putchAlt(char ch)
 {
  getClientSub().putchAlt(ch);
 }

void DragWindow::putchAlt(char ch,unsigned repeat)
 {
  getClientSub().putchAlt(ch,repeat);
 }

 // mouse

void DragWindow::looseCapture()
 {
  if( shape.drag_type ) endDrag();
  
  if( client_capture )
    {
     client_capture=false;
     
     getClientSub().looseCapture();
    }
 }

void DragWindow::clickLeft(Point point,MouseKey mkey)
 {
  switch( auto drag_type=shape.dragTest(point) )
    {
     case DragType_None :
      {
       if( client_capture || shape.getClient().contains(point) )
         {
          getClientSub().forward_clickLeft(point,mkey);
         }
      }
     break;
   
     case DragType_Alert : 
     case DragType_Min   : 
     case DragType_Max   : 
     case DragType_Close : shape.btn_type=drag_type; redrawFrame(drag_type); break;
     
     default: if( !shape.drag_type ) startDrag(point,drag_type);
    }
 }

void DragWindow::upLeft(Point point,MouseKey mkey)
 {
  if( shape.drag_type )
    {
     endDrag(point);
     
     return;
    }
  
  if( shape.btn_type )
    {
     auto type=Replace(shape.btn_type,DragType_None);
     
     redrawFrame(type);
    
     if( shape.dragTest(point)==type )
       {
        switch( type )
          {
           case DragType_Alert : switchClients(); return;
           
           case DragType_Min   : minimize(); return;
           
           case DragType_Max   : maximize(); return;
           
           case DragType_Close : destroy(); return;
          }
       }
    }
  
  if( client_capture || shape.getClient().contains(point) )
    {
     getClientSub().forward_upLeft(point,mkey);
    }
 }

void DragWindow::dclickLeft(Point point,MouseKey mkey)
 {
  if( shape.drag_type ) return;
  
  if( client_capture || shape.getClient().contains(point) )
    {
     getClientSub().forward_dclickLeft(point,mkey);
    }
 }

void DragWindow::clickRight(Point point,MouseKey mkey)
 {
  if( shape.drag_type ) return;
  
  if( client_capture || shape.getClient().contains(point) )
    {
     getClientSub().forward_clickRight(point,mkey);
    }
 }

void DragWindow::upRight(Point point,MouseKey mkey)
 {
  if( shape.drag_type ) return;
  
  if( client_capture || shape.getClient().contains(point) )
    {
     getClientSub().forward_upRight(point,mkey);
    }
 }

void DragWindow::dclickRight(Point point,MouseKey mkey)
 {
  if( shape.drag_type ) return;
  
  if( client_capture || shape.getClient().contains(point) )
    {
     getClientSub().forward_dclickRight(point,mkey);
    }
 }

void DragWindow::move(Point point,MouseKey mkey)
 {
  if( shape.drag_type )
    {
     if( mkey&MouseKey_Left )
       dragTo(point);
     else
       endDrag(point);
     
     return;
    }
  
  if( shape.btn_type )
    {
     if( mkey&MouseKey_Left )
       {
        if( shape.dragTest(point)!=shape.btn_type )
          {
           auto type=Replace(shape.btn_type,DragType_None);
          
           redrawFrame(type);
          }
       }
     else
       {
        auto type=Replace(shape.btn_type,DragType_None);
        
        redrawFrame(type);
       }
     
     return;
    }
  
  auto drag_type=shape.dragTest(point);
  
  if( drag_type==DragType_Bar ) drag_type=DragType_None;
  
  if( drag_type!=shape.hilight )
    {
     auto type=Replace(shape.hilight,drag_type);
     
     redrawFrame(type);
     redrawFrame(drag_type);
    }
  
  if( shape.getClient().contains(point) )
    {
     client_enter=true;
     
     getClientSub().forward_move(point,mkey);
    }
  else
    {
     if( client_capture ) getClientSub().forward_move(point,mkey);
      
     if( client_enter )
       {
        client_enter=false;
        
        getClientSub().leave();
       }
    }
 }

void DragWindow::hover(Point point,MouseKey mkey)
 {
  if( shape.drag_type ) return;
  
  if( client_capture || shape.getClient().contains(point) )
    {
     getClientSub().forward_hover(point,mkey);
    }
 }

void DragWindow::leave()
 {
  if( shape.hilight  )
    {
     redrawFrame(Replace(shape.hilight,DragType_None));
    }
  
  if( shape.btn_type )
    {
     redrawFrame(Replace(shape.btn_type,DragType_None));
    }
  
  if( shape.drag_type ) return;
  
  if( client_enter )
    {
     client_enter=false;
     
     getClientSub().leave();
    }
 }

void DragWindow::wheel(Point point,MouseKey mkey,Coord delta)
 {
  if( shape.drag_type ) return;
  
  if( client_capture || shape.getClient().contains(point) )
    {
     getClientSub().forward_wheel(point,mkey,delta);
    }
 }

void DragWindow::setMouseShape(Point point)
 {
  switch( shape.dragTest(point) )
    {
     case DragType_Top         : host->setMouseShape(Mouse_SizeUpDown); break;
      
     case DragType_TopLeft     : host->setMouseShape(Mouse_SizeUpLeft); break;

     case DragType_Left        : host->setMouseShape(Mouse_SizeLeftRight); break;
     
     case DragType_BottomLeft  : host->setMouseShape(Mouse_SizeUpRight); break;
     
     case DragType_Bottom      : host->setMouseShape(Mouse_SizeUpDown); break;
     
     case DragType_BottomRight : host->setMouseShape(Mouse_SizeUpLeft); break;
     
     case DragType_Right       : host->setMouseShape(Mouse_SizeLeftRight); break;
     
     case DragType_TopRight    : host->setMouseShape(Mouse_SizeUpRight); break;
     
     case DragType_Alert       :
     case DragType_Min         : 
     case DragType_Max         : host->setMouseShape(Mouse_Hand); break;
     
     case DragType_Close       : host->setMouseShape(Mouse_Stop); break;
      
     case DragType_Bar         : host->setMouseShape(Mouse_SizeAll); break;
     
     default: host->setMouseShape(getClientSub().forward_getMouseShape(point));
    }
 }

 // signals

void DragWindow::updateConfig()
 { 
  input.redrawAll(true); 
 }

} // namespace Video
} // namespace CCore
 

